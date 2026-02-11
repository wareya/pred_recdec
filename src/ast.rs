// Predicated Recursive Descent

use std::rc::Rc;

type HashMap<K, V> = std::collections::HashMap::<K, V, crate::HashBuilder>;

use crate::bnf::*;

#[derive(Clone, Debug, Default)]
/// AST node. Grammar rules have children, tokens do not.
///
/// The total structure of the AST is defined by the grammar that it was parsed with.
///
/// Why isn't this an enum? `Option<Vec<ASTNode>>` and other two-variant enums containing a Vec undergo niche optimization. If this were `enum ASTNode { Rule{...}, Token(u32) }` then it would look like you can just add a third variant (e.g. poisoned) without issue. However, doing that would actually increase the size of the ASTNode from 32 bytes to 40 bytes.
/// 
/// If the size is ever forced above 32 bytes (e.g. increasing token count from u32 to u64) then I'll probably change it to an enum.
#[non_exhaustive]
pub struct ASTNode {
    /// If `Some`, this node is a parent/nonterminal. If `None`, this node is a token/leaf/terminal.
    pub children : Option<Vec<ASTNode>>,
    /// Due to error recovery, AST nodes can be marked as "poisoned".
    ///
    /// When a node is poisoned, its token count is XOR'd with !0u32 (all one-bits).
    pub token_count : u32,
    /// Index into grammar.string_cache_inv, giving an `Rc<String>`.
    ///
    /// For parents, it's the name of the associated grammar rule.
    ///
    /// For tokens, it's the token content (the *actual* token contents, but what it was matched with, i.e. it's not a regex).
    pub text : u32,
}

impl ASTNode {
    /// Create an AST node.
    pub fn new(children : Option<Vec<ASTNode>>, token_count : u32, text : u32) -> Self { Self { children, token_count, text } }
    /// Is this AST node "poisoned", i.e. does it contain something that experienced error recovery?
    pub fn is_poisoned(&self) -> bool { self.token_count >= 0x80000000 }
    /// The `token_count` field of `ASTNode` is sometimes encoded non-literally.
    pub fn get_real_token_count(&self) -> u32 { if self.token_count >= 0x80000000 { self.token_count ^ !0u32 } else { self.token_count } }
}

// ASTs can be deeply recursive, so we need to avoid destroying them recursively.
// This is slightly slower than normal dropping (around 1.8x the cost) but much safer.
impl Drop for ASTNode {
    fn drop(&mut self)
    {
        if let Some(c) = self.children.take()
        {
            let mut q = vec!();
            q.push(c);
            while let Some(v) = q.pop()
            {
                for mut p in v.into_iter().rev()
                {
                    if let Some(c) = p.children.take()
                    {
                        q.push(c);
                    }
                    // p is dropped and destructed here.
                    // it only contains a None, a u32, and a u32, so we can safely "forget" it without leaking memory.
                    std::mem::forget(p);
                }
            }
        }
    }
}

/// Result of a [`Guard`] checking if a given alternation should be taken or not.
pub enum GuardResult {
    /// The alternation is chosen.
    #[allow(unused)] Accept,
    /// The alternation is rejected.
    #[allow(unused)] Reject,
    /// The guard has preemptively decided the the parse is invalid at this state and position.
    #[allow(unused)] HardError(String)
}

/// Arguments:
/// - `&mut PrdGlobal` - context
/// - `&[Token]` - tokenstream
/// - `usize` - position in tokenstream.
pub type Guard = Rc<dyn Fn(&mut PrdGlobal, &[Token], usize) -> GuardResult>;
/// Arguments:
/// - `&mut PrdGlobal` - context
/// - `&[Token]` - tokenstream
/// - `usize` - position in tokenstream.
/// - `&mut Vec<ASTNode>` - current partially-produced AST item.
///
/// Return: `Ok(tokens_consumed)` or `Err(human_readable_string)`.
pub type Hook = Rc<dyn Fn(&mut PrdGlobal, &[Token], usize, &mut Vec<ASTNode>) -> Result<usize, String>>;

/// Standard "AnyMap" for putting whatever you want in it.
#[derive(Default)]
pub struct AnyMap { map: HashMap<std::any::TypeId, Box<dyn std::any::Any>> }

impl AnyMap {
    /// Insert an item of type `T` into the `AnyMap`. Overwrites any such existing item.
    #[allow(unused)] pub fn insert<T: 'static>(&mut self, value: T) { self.map.insert(std::any::TypeId::of::<T>(), Box::new(value)); }
    /// Get an item of type `T` if it exists.
    #[allow(unused)] pub fn get<T: 'static>(&self) -> Option<&T> { self.map.get(&std::any::TypeId::of::<T>())?.downcast_ref::<T>() }
    /// Get an item of type `T` if it exists (mutable version).
    #[allow(unused)] pub fn get_mut<T: 'static>(&mut self) -> Option<&mut T> { self.map.get_mut(&std::any::TypeId::of::<T>())?.downcast_mut::<T>() }
}

/// Exposable parts of current parser state.
pub struct PrdGlobal<'a> {
    /// The guards you passed into the parse function.
    pub (crate) guards : Rc<HashMap<String, Guard>>,
    /// The hooks you passed into the parse function.
    pub (crate) hooks : Rc<HashMap<String, Hook>>,
    
    /// Put your impure data here.
    #[allow(unused)] pub udata : AnyMap,
    /// Put your impure data here (simple path for cached regexes).
    #[allow(unused)] pub udata_r : HashMap<usize, RegexCacher>,
    /// Reference to the grammar you passed into the parse function.
    #[allow(unused)] pub g : &'a Grammar,
}

/// Parser error state.
#[derive(Clone, Debug)]
pub struct PrdError {
    /// Human-readable error message. Format is not guaranteed and may change arbitrarily.
    #[allow(unused)] pub err_message : String,
    /// How far into the token stream did we successfully parse? Note: this is NOT
    #[allow(unused)] pub token_index : usize,
    /// Which rule's alternations were we inside of? (Index into [`bnf::Grammar::points`](`super::bnf::Grammar::points`))
    #[allow(unused)] pub rule : u32,
    /// Which alternation was it?
    ///
    /// If `u16::MAX`, we errored out before entering an alternation.
    ///
    /// If past the end of the grammar point's list of alternations, then every alternation was checked and failed.
    #[allow(unused)] pub in_alt : u16,
    /// Where were we inside of that alternation?
    ///
    /// If "None", we errored on a guard/lookahead test.
    #[allow(unused)] pub alt_progress : Option<u16>,
    /// On behalf of what rule were we parsing for? (e.g. the parent of a `$become`)
    #[allow(unused)] pub on_behalf_of_rule : u32,
}

struct WorkState<'a> { 
    pub (crate) g_item : &'a GrammarPoint,
    pub (crate) chosen_name_id : u32,
    pub (crate) children : Vec<ASTNode>,
    pub (crate) i : usize,
    pub (crate) token_start : usize,
    pub (crate) poisoned : bool,
    pub (crate) alt_id : usize,
    pub (crate) term_idx : u16,
}

impl<'a> std::fmt::Debug for WorkState<'a> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.debug_struct("WorkState")
        .field("g_item.name_id", &self.g_item.name_id)
        .field("chosen_name_id", &self.chosen_name_id)
        .field("children.len()", &self.children.len())
        .field("i", &self.i)
        .field("token_start", &self.i)
        .field("poisoned", &self.poisoned)
        .field("alt_id", &self.alt_id)
        .field("term_idx", &self.term_idx)
        .finish()
    }
}

fn error_builder(msg : String, i : usize, id : u32, behalf : u32, in_alt : u16, prog : Option<u16>) -> Box<PrdError>
{
    Box::new(PrdError {
        err_message : msg, token_index : i, rule : id, on_behalf_of_rule : behalf,
        in_alt : in_alt, alt_progress : prog
    })
}
macro_rules! build_err { ($prog:expr, $ws:expr, $($tts:tt)*) => { {
    #[inline(never)]
    fn ___build_err_temp(a : std::fmt::Arguments) -> String {
        format!("{a}")
    }
    Err(error_builder(___build_err_temp(format_args!($($tts)*)), $ws.i, $ws.g_item.name_id, $ws.chosen_name_id, $ws.alt_id.wrapping_sub(1) as u16, $prog))
} } }
#[inline(never)]
fn token_name(cache : &Vec<Rc<String>>, t : Option<&Token>) -> String
{
    if let Some(t) = t { (*cache[t.text as usize]).clone() }
    else { "<no token>".to_string() }
}

#[inline(always)]
fn handle_matchterm(
    global : &mut PrdGlobal, tokens : &[Token],
    ws : &mut WorkState, term: &MatchingTermE, matched : &mut bool)
    -> Result<(), Box<PrdError>>
{
    let alt = &ws.g_item.forms[ws.alt_id as usize];
    match &term
    {
        MatchingTermE::Rule(_) => {} // already handled
        MatchingTermE::TermLit(lit) =>
        {
            if ws.i < tokens.len() && tokens[ws.i].text == *lit
            {
                if !alt.pruned
                {
                    ws.children.push(ASTNode::new(None, 1, tokens[ws.i].text));
                }
                ws.i += 1;
                *matched = true;
            }
        }
        MatchingTermE::TermRegex(regex) => if ws.i < tokens.len() && regex.is_match_interned(tokens[ws.i].text, &global.g.string_cache_inv)
        {
            if !alt.pruned
            {
                ws.children.push(ASTNode::new(None, 1, tokens[ws.i].text));
            }
            ws.i += 1;
            *matched = true;
        }
        MatchingTermE::Directive(d) =>
        {
            match d
            {
                MatchDirective::Become | MatchDirective::BecomeAs => {} // handled externally
                MatchDirective::Rename =>
                {
                    if let Some(qx) = alt.matching_terms.get(ws.term_idx as usize + 1) && let MatchingTermE::Rule(id) = &qx.t
                    {
                        ws.chosen_name_id = *id as u32;
                        ws.term_idx += 1;
                        *matched = true;
                    }
                }
                MatchDirective::Drop => if ws.children.len() > 0
                {
                    ws.children.pop();
                    *matched = true;
                }
                MatchDirective::DropIfEmpty => if ws.children.len() > 0
                {
                    if ws.children.last().unwrap().children.is_some()
                    {
                        ws.children.pop();
                    }
                    *matched = true;
                }
                MatchDirective::Hoist => if ws.children.len() > 0
                {
                    let mut x = ws.children.pop().unwrap();
                    if let Some(mut c) = x.children.take()
                    {
                        ws.children.append(&mut c);
                    }
                    *matched = true;
                }
                MatchDirective::HoistIfUnit => if ws.children.len() > 0
                {
                    let mut x = ws.children.pop().unwrap();
                    if let Some(mut c) = x.children.take() && c.len() == 1
                    {
                        ws.children.append(&mut c);
                    }
                    *matched = true;
                }
                MatchDirective::Any => if ws.i < tokens.len()
                {
                    ws.children.push(ASTNode::new(None, 1, tokens[ws.i].text));
                    *matched = true;
                    ws.i += 1;
                }
            }
        }
        MatchingTermE::Hook(name) =>
        {
            if let Some(f) = global.hooks.get(&**name)
            {
                let f = Rc::clone(&f);
                match f(global, tokens, ws.i, &mut ws.children)
                {
                    Ok(consumed) => { ws.i += consumed; }
                    Err(e) => build_err!(Some(ws.term_idx as u16), ws, "{}", e)?
                }
            }
            else
            {
                build_err!(
                    Some(ws.term_idx as u16), ws,
                    "Unknown custom hook {:?} inside of {}",
                    name, 
                    global.g.string_cache_inv[ws.chosen_name_id as usize],
                )?
            }
            *matched = true;
        }
        _ => build_err!(
                Some(ws.term_idx as u16), ws,
                "Term type {:?} not supported in this position in a rule (context: {})",
                term, global.g.string_cache_inv[ws.chosen_name_id as usize]
            )?
    }
    Ok(())
}

#[inline(always)]
fn handle_acceptance(
    global : &mut PrdGlobal, tokens : &[Token],
    alt : &Alternation,
    ws : &WorkState, accepted : &mut bool)
    -> Result<usize, Box<PrdError>>
{
    match &alt.matching_terms.get(0).as_ref().unwrap().t
    {
        MatchingTermE::Guard(guard) =>
        {
            *accepted = false;
            if let Some(f) = global.guards.get(&**guard)
            {
                let f = Rc::clone(&f);
                match f(global, tokens, ws.i)
                {
                    GuardResult::Accept => *accepted = true,
                    GuardResult::HardError(e) => build_err!(None, ws, "{}", e)?,
                    _ => {}
                }
            }
            else
            {
                return build_err!(None, ws, "Unknown guard {guard}");
            }
            return Ok(1);
        }
        MatchingTermE::Peek(loc, tester) =>
        {
            *accepted = false;
            let loc = (ws.i as isize + loc) as usize;
            if loc < tokens.len() && tokens[loc].text == *tester
            {
                *accepted = true;
            }
            return Ok(1);
        }
        MatchingTermE::PeekR(loc, tester) =>
        {
            *accepted = false;
            let loc = (ws.i as isize + loc) as usize;
            if loc < tokens.len() && tester.is_match_interned(tokens[loc].text, &global.g.string_cache_inv)
            {
                *accepted = true;
            }
            return Ok(1);
        }
        MatchingTermE::PeekRes(loc, tester) =>
        {
            *accepted = false;
            let loc = (ws.i as isize + loc) as usize;
            if loc < tokens.len() && tester.is_match_interned(tokens[loc].text, &global.g.string_cache_inv)
            {
                *accepted = true;
                if let Some(r) = &global.g.reserved
                {
                    if regex_is_match(r, &global.g.string_cache_inv[tokens[loc].text as usize]) { *accepted = false; }
                }
            }
            return Ok(1);
        }
        MatchingTermE::Eof =>
        {
            *accepted = ws.i == tokens.len();
            return Ok(1);
        }
        _ => {}
    }
    Ok(0)
}

#[inline(always)]
fn check_recovery(
    global : &mut PrdGlobal, tokens : &[Token],
    ws : &mut WorkState, child : &mut Result<ASTNode, Box<PrdError>>, id : usize)
    -> Result<(), Box<PrdError>>
{
    if child.is_err() && global.g.points[id].recover.is_some()
    {
        if let Some((r, after)) = &global.g.points[id].recover
        {
            let mut j = ws.i + 1;
            while j < tokens.len() && !r.is_match(&global.g.string_cache_inv[tokens[j].text as usize])
            {
                j += 1;
            }
            if j < tokens.len()
            {
                if *after { j += 1; }
                *child = Ok(ASTNode::new(Some(vec!()), (j - ws.i) as u32 ^ !0u32, global.g.points[id].name_id));
            }
        }
    }
    Ok(())
}

fn make_workstate<'a>(
    g_item : &'a GrammarPoint, token_start : usize,
) -> WorkState<'a>
{
    let ws = WorkState {
        g_item, chosen_name_id : g_item.name_id, children : vec!(),
        i : token_start, token_start : token_start, poisoned : false, alt_id : 0, term_idx : 0
    };
    ws
}

#[inline(never)]
pub (crate) fn pred_recdec_parse_impl_recursive(
    global : &mut PrdGlobal,
    gp_id : usize, tokens : &[Token], _token_start : usize,
    depth : usize
) -> Result<ASTNode, Box<PrdError>>
{
    // BE WARNED: There are a bunch of very strange patterns in this function that look like they have no purpose,
    //   but exist to trick LLVM into spilling less data onto the stack.
    // In the future, I'll write a non-recursive implementation, but it'll likely be a bit slower.
    const DEPTH_LIMIT : usize = if cfg!(debug_assertions) { 300 } else { 1500 };
    
    let mut ws = make_workstate(&global.g.points[gp_id], _token_start);
    
    if depth > DEPTH_LIMIT { return build_err!(None, ws, "Exceeded recursion depth limit of {DEPTH_LIMIT}."); }
    
    #[cfg(feature = "parse_trace")] { println!("entered {} at {}, depth {depth}", global.g.string_cache_inv[ws.chosen_name_id as usize], ws.i); }
    
    // Structured this way for the sake of $become
    // 1) We can't use an iterator because then we can't go back to alternation 0.
    // 2) We can't have a "find alt" loop followed by a non-loop process block because then we can't go back to the "find alt" loop during $BECOME.
    'top: while (ws.alt_id as usize) < ws.g_item.forms.len()
    {
        let alt = &ws.g_item.forms[ws.alt_id as usize];
        ws.term_idx = 0;
        
        if alt.matching_terms.len() == 0
        {
            return Ok(ASTNode::new(Some(ws.children), (ws.i - ws.token_start) as u32, ws.chosen_name_id));
        }
        else
        {
            let mut accepted = true;
            let a = handle_acceptance(
                global, tokens,
                &ws.g_item.forms[ws.alt_id as usize],
                &mut ws, &mut accepted
            )?;
            if !accepted { ws.alt_id += 1; ws.term_idx = 0; continue; }
            ws.term_idx += a as u16;
        }
        
        #[cfg(feature = "parse_trace")] { println!("chose variant {}", ws.alt_id); }
        
        if ws.children.capacity() == 0
        {
            ws.children.reserve_exact(alt.matching_terms.len());
        }
        
        while (ws.term_idx as usize) < alt.matching_terms.len()
        {
            let term = &alt.matching_terms[ws.term_idx as usize].t;
            let mut matched = false;
            match &term
            {
                MatchingTermE::Rule(id) =>
                {
                    let mut child = pred_recdec_parse_impl_recursive(global, *id, tokens, ws.i, depth + 1);
                    check_recovery(global, tokens, &mut ws, &mut child, *id)?;
                    #[cfg(feature = "deep_errors")]
                    {
                        if let Err(e) = child
                        {
                            let mut e2 = e.clone();
                            e2.err_message = format!("In {}: {}", ws.g_item.name, e2.err_message);
                            child = Err(e2);
                        }
                    }
                    let child = child?;
                    if child.is_poisoned()
                    {
                        ws.poisoned = true;
                    }
                    ws.i += child.get_real_token_count() as usize;
                    #[cfg(feature = "parse_trace")]
                    { println!("added {} to i via child", child.get_real_token_count()); }
                    ws.children.push(child);
                    matched = true;
                }
                MatchingTermE::Directive(MatchDirective::Become | MatchDirective::BecomeAs) =>
                {
                    if let Some(qx) = alt.matching_terms.get(ws.term_idx as usize + 1) && let MatchingTermE::Rule(id) = &qx.t
                    {
                        ws.g_item = &global.g.points[*id];
                        ws.alt_id = 0;
                        ws.term_idx = 0;
                        #[cfg(feature = "parse_trace")] { println!("became {} at {}, depth {depth}", ws.g_item.name, ws.i); }
                        if matches!(term, MatchingTermE::Directive(MatchDirective::BecomeAs))
                        {
                            ws.chosen_name_id = ws.g_item.name_id;
                        }
                        continue 'top;
                    }
                }
                _ => {}
            }
            handle_matchterm(global, tokens, &mut ws, term, &mut matched)?;
            
            if !matched
            {
                let token_text = token_name(&global.g.string_cache_inv, tokens.get(ws.i));
                build_err!(
                    Some(ws.term_idx as u16), &ws,
                    "Failed to match token at {} in rule {} alt {}. Token is `{}`.",
                    ws.i, global.g.string_cache_inv[ws.g_item.name_id as usize], ws.alt_id, token_text,
                )?
            }
            ws.term_idx += 1;
        }
        
        //println!("Validating {:?}", ws);
        
        #[cfg(feature = "parse_trace")] { println!("accepted {} from {} to {}, depth {depth}", global.g.string_cache_inv[ws.g_item.name_id as usize], ws.token_start, ws.i); }
        let mut token_count = (ws.i - ws.token_start) as u32;
        if ws.poisoned
        {
            token_count = token_count ^ !0u32;
        }
        return Ok(ASTNode::new(Some(ws.children), token_count, ws.chosen_name_id));
    }
    
    build_err!(
        Some(ws.g_item.forms.len() as u16),
        &ws,
        "Failed to match rule {} at token position {}",
        global.g.string_cache_inv[ws.g_item.name_id as usize],
        ws.token_start
    )
}

#[inline(never)]
pub (crate) fn pred_recdec_parse_impl_lifo(
    global : &mut PrdGlobal,
    gp_id : usize, tokens : &[Token], _token_start : usize,
) -> Result<ASTNode, Box<PrdError>>
{
    let mut stack : Vec<WorkState> = vec!();
    stack.reserve(128);
    let mut ready_child : Option<(Result<_, _>, u32)> = None;
    let mut ws = make_workstate(&global.g.points[gp_id], _token_start);
    
    #[cfg(feature = "parse_trace")]
    { println!("entered {} at {}", global.g.string_cache_inv[ws.g_item.name_id as usize], ws.i); }
    
    'top: while (ws.alt_id as usize) < ws.g_item.forms.len()
    {
        macro_rules! set_ready_child { ($ex:expr) => { {
            ready_child = Some($ex);
            ws = stack.pop().unwrap();
        } } }
        macro_rules! engage_ready_child { ($ex:expr) => { {
            ready_child = Some($ex);
            ws = stack.pop().unwrap();
            
            while let Some((child, _)) = &ready_child && child.is_ok()
            {
                let child = ready_child.take().unwrap().0.unwrap();
                if child.is_poisoned()
                {
                    ws.poisoned = true;
                }
                ws.i += child.get_real_token_count() as usize;
                #[cfg(feature = "parse_trace")]
                { println!("added {} to i via child", child.get_real_token_count()); }
                ws.children.push(child);
                ws.term_idx += 1;
                
                let alt = &ws.g_item.forms[ws.alt_id as usize];
                
                if ws.term_idx as usize >= alt.matching_terms.len()
                {
                    if stack.len() == 0
                    {
                        return Ok(ASTNode::new(Some(ws.children), (ws.i - ws.token_start) as u32, ws.chosen_name_id));
                    }
                    else
                    {
                        set_ready_child!((Ok(ASTNode::new(Some(ws.children), (ws.i - ws.token_start) as u32, ws.chosen_name_id)), ws.g_item.name_id));
                    }
                }
            }
            
            continue 'top;
        } } }
        
        macro_rules! errify { ($x:expr) => { {
            let _e = $x;
            if stack.len() > 0 {
                if let Err(e) = _e {
                    engage_ready_child!((Err(e), 0));
                } else { _e.unwrap() }
            } else { _e? }
        }}}
        
        #[cfg(feature = "parse_trace")]
        let depth = stack.len() + 1;
        
        let mut alt = &ws.g_item.forms[ws.alt_id as usize];
        
        if let Some((mut child, id)) = ready_child.take()
        {
            errify!(check_recovery(global, tokens, &mut ws, &mut child, id as usize));
            
            let child = errify!(child);
            if child.is_poisoned()
            {
                ws.poisoned = true;
            }
            ws.i += child.get_real_token_count() as usize;
            #[cfg(feature = "parse_trace")]
            { println!("added {} to i via child", child.get_real_token_count()); }
            ws.children.push(child);
            ws.term_idx += 1;
            
            if ws.term_idx as usize >= alt.matching_terms.len()
            {
                if stack.len() == 0
                {
                    return Ok(ASTNode::new(Some(ws.children), (ws.i - ws.token_start) as u32, ws.chosen_name_id));
                }
                else
                {
                    engage_ready_child!((Ok(ASTNode::new(Some(ws.children), (ws.i - ws.token_start) as u32, ws.chosen_name_id)), ws.g_item.name_id));
                }
            }
            continue 'top;
        }
        if ws.term_idx == 0
        {
            for id in 0..ws.g_item.forms.len()
            {
                ws.alt_id = id;
                ws.term_idx = 0;
                alt = &ws.g_item.forms[ws.alt_id as usize];
                if alt.matching_terms.len() == 0
                {
                    if stack.len() == 0
                    {
                        return Ok(ASTNode::new(Some(ws.children), (ws.i - ws.token_start) as u32, ws.chosen_name_id));
                    }
                    else
                    {
                        engage_ready_child!((Ok(ASTNode::new(Some(ws.children), (ws.i - ws.token_start) as u32, ws.chosen_name_id)), ws.g_item.name_id));
                    }
                }
                else
                {
                    let mut accepted = true;
                    let a = errify!(handle_acceptance(global, tokens, alt, &mut ws, &mut accepted));
                    if !accepted
                    {
                        if ws.alt_id as usize + 1 >= ws.g_item.forms.len()
                        {
                            ws.alt_id += 1;
                            break 'top;
                        }
                        continue;
                    }
                    ws.term_idx += a as u16;
                    break;
                }
            }
            #[cfg(feature = "parse_trace")] { println!("chose variant {}", ws.alt_id); }
            
            if ws.children.capacity() == 0
            {
                ws.children.reserve_exact(alt.matching_terms.len());
            }
        }
        
        while (ws.term_idx as usize) < alt.matching_terms.len()
        {
            let term = &alt.matching_terms[ws.term_idx as usize].t;
            match &term
            {
                MatchingTermE::Rule(id) =>
                {
                    let next_ws = make_workstate(&global.g.points[*id], ws.i);
                    stack.push(ws);
                    ws = next_ws;
                    
                    #[cfg(feature = "parse_trace")]
                    { println!("entered {} at {}, depth {depth}", global.g.string_cache_inv[ws.g_item.name_id as usize], ws.i); }
                    
                    continue 'top;
                }
                MatchingTermE::Directive(MatchDirective::Become | MatchDirective::BecomeAs) =>
                {
                    if let Some(qx) = alt.matching_terms.get(ws.term_idx as usize + 1) && let MatchingTermE::Rule(id) = &qx.t
                    {
                        ws.g_item = &global.g.points[*id];
                        ws.alt_id = 0;
                        ws.term_idx = 0;
                        #[cfg(feature = "parse_trace")] { println!("became {} at {}, depth {depth}", ws.g_item.name, ws.i); }
                        if matches!(term, MatchingTermE::Directive(MatchDirective::BecomeAs))
                        {
                            ws.chosen_name_id = ws.g_item.name_id;
                        }
                        continue 'top;
                    }
                }
                _ => {}
            }
            let mut matched = false;
            errify!(handle_matchterm(global, tokens, &mut ws, term, &mut matched));
            
            if !matched
            {
                let token_text = token_name(&global.g.string_cache_inv, tokens.get(ws.i));
                errify!(build_err!(
                    Some(ws.term_idx as u16), &ws,
                    "Failed to match token at {} in rule {} alt {}. Token is `{}`.",
                    ws.i, global.g.string_cache_inv[ws.g_item.name_id as usize], ws.alt_id, token_text,
                ))
            }
            ws.term_idx += 1;
        }
        
        #[cfg(feature = "parse_trace")] { println!("accepted {} from {} to {}, depth {depth}", global.g.string_cache_inv[ws.g_item.name_id as usize], ws.token_start, ws.i); }
        let mut token_count = (ws.i - ws.token_start) as u32;
        if ws.poisoned
        {
            token_count = token_count ^ !0u32;
        }
        
        if stack.len() == 0
        {
            return Ok(ASTNode::new(Some(ws.children), token_count, ws.chosen_name_id));
        }
        else
        {
            engage_ready_child!((Ok(ASTNode::new(Some(ws.children), token_count, ws.chosen_name_id)), ws.g_item.name_id));
        }
    }
    
    build_err!(
        Some(ws.g_item.forms.len() as u16),
        &ws,
        "Failed to match rule {} at token position {}",
        global.g.string_cache_inv[ws.g_item.name_id as usize],
        ws.token_start,
    )
}

/// Visit the AST with a possibly-impure callback. The AST itself cannot be modified this way.
/// 
/// The AST is visited according to depth-first pre-order. In other words, for `A{B{C D}E}`, it visits A, then B, then C, then D, then E.
/// 
/// Takes a function that returns whether it's OK to also visit the children of this node.
#[allow(unused)]
pub fn visit_ast(n : &ASTNode, f : &mut dyn FnMut(&ASTNode) -> bool)
{
    visit_ast_recursive(n, f, 0);
}
pub (crate) fn visit_ast_iterative(n : &ASTNode, f : &mut dyn FnMut(&ASTNode) -> bool)
{
    let mut v = vec!(n);
    while let Some(n) = v.pop()
    {
        let flag = f(n);
        if flag && let Some(c) = &n.children
        {
            for c in c.iter().rev() // yes
            {
                v.push(c); // pushed and popped in FILO order, not FIFO. thus the .rev().
            }
        }
    }
}
pub (crate) fn visit_ast_recursive(n : &ASTNode, f : &mut dyn FnMut(&ASTNode) -> bool, depth : usize)
{
    if depth > 100
    {
        return visit_ast_iterative(n, f);
    }
    let flag = f(n);
    if flag && let Some(c) = &n.children
    {
        for c in c.iter()
        {
            visit_ast_recursive(c, f, depth + 1);
        }
    }
}

#[allow(unused)]
/// *Recursive implementation:* Parse the given token stream (produced by [`bnf::tokenize`](`super::bnf::tokenize`)) into an AST, using the given [`bnf::Grammar`](`super::bnf::Grammar`), and taking the given root rule name as the starting point.
/// 
/// Guards and hooks are for advanced usage (e.g. parsing C).
/// 
/// This implementation is vulnerable to deep recursion issues. Depending on compiler settings, the recursion depth limit may vary from 300 to 3000, with very little control. For this reason, there's a hard depth limit of about 1500 in release mode and 300 in debug mode.
///
/// However, this version is about 4% faster than [`parse`].
/// 
/// See also: [`ASTNode`], [`parse`]
pub fn parse_recursive(
    g : &Grammar, root_rule_name : &str, tokens : &[Token],
    guards : Rc<HashMap<String, Guard>>,
    hooks : Rc<HashMap<String, Hook>>,
) -> Result<ASTNode, Box<PrdError>>
{
    let gp_id = g.by_name.get(root_rule_name).unwrap();
    let mut global = PrdGlobal { guards, hooks, udata : <_>::default(), udata_r : <_>::default(), g };
    
    if let Some(f) = global.hooks.get("init")
    {
        let f = Rc::clone(&f);
        let _ = f(&mut global, tokens, 0, &mut vec!());
    }
    
    pred_recdec_parse_impl_recursive(&mut global, *gp_id, tokens, 0, 0)
}

#[allow(unused)]
/// *Worklist implementation:* Parse the given token stream (produced by [`bnf::tokenize`](`super::bnf::tokenize`)) into an AST, using the given [`bnf::Grammar`](`super::bnf::Grammar`), and taking the given root rule name as the starting point.
/// 
/// Guards and hooks are for advanced usage (e.g. parsing C).
/// 
/// This implementation is not vulnerable to deep recursion issues. Each level of nesting depth consumes only 64 more bytes of memory.
/// 
/// However, this version is about 4% slower than [`parse`]. I'm going to keep working on optimizing it.
/// 
/// This implementation does not yet support the "deep_errors" feature. When it does, adding support for it will not be considered a breaking change.
/// 
/// The exact algorithm may change in any update, as long as it produces the same result and is safe in the same circumstances.
/// 
/// See also: [`ASTNode`], [`parse_recursive`]
pub fn parse(
    g : &Grammar, root_rule_name : &str, tokens : &[Token],
    guards : Rc<HashMap<String, Guard>>,
    hooks : Rc<HashMap<String, Hook>>,
) -> Result<ASTNode, Box<PrdError>>
{
    let gp_id = g.by_name.get(root_rule_name).unwrap();
    let mut global = PrdGlobal { guards, hooks, udata : <_>::default(), udata_r : <_>::default(), g };
    
    if let Some(f) = global.hooks.get("init")
    {
        let f = Rc::clone(&f);
        let _ = f(&mut global, tokens, 0, &mut vec!());
    }
    
    pred_recdec_parse_impl_lifo(&mut global, *gp_id, tokens, 0)
}


#[allow(unused)]
/// For debugging only: print out the given AST.
pub fn print_ast_pred_recdec(ast : &ASTNode, string_cache_inv : &Vec<Rc<String>>, indent : usize)
{
    print!("{}", " ".repeat(indent));
    if let Some(c) = &ast.children
    {
        if ast.is_poisoned() { println!("{} (POISONED) {{", ast.text); } else
        { println!("{} {{", string_cache_inv[ast.text as usize]); }
        for c in c.iter()
        {
            print_ast_pred_recdec(c, string_cache_inv, indent+1);
        }
        print!("{}", " ".repeat(indent));
        println!("}};");
    }
    else
    {
        println!("{}", string_cache_inv[ast.text as usize]);
    }
}

#[allow(unused)]
/// For testing only: convert the AST's shape to a string. Example output: `++.-..+--`
///
/// Parents turn into `+<contents>-`. If poisoned (i.e. containing any error recovery), they're prefixed with `p`.
///
/// Leaves turn into `.`
pub fn ast_to_shape_string(ast : &ASTNode) -> String
{
    let mut s = "".to_string();
    if let Some(c) = &ast.children
    {
        if ast.is_poisoned() { s += "p"; }
        s += "+";
        for c in c.iter()
        {
            s += &ast_to_shape_string(c);
        }
        s += "-";
    }
    else
    {
        s += ".";
    }
    s
}
