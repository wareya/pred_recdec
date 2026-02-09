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
    pub token_count : u32, // IF POISONED: xor with !0u32 (all one-bits)
    /// Index into grammar.string_cache_inv, giving an `Rc<String>`.
    ///
    /// For parents, it's the name of the associated grammar rule.
    ///
    /// For tokens, it's the token content (the *actual* token contents, but what it was matched with, i.e. it's not a regex).
    pub text : u32,
}

impl ASTNode {
    pub fn new(children : Option<Vec<ASTNode>>, token_count : u32, text : u32) -> Self { Self { children, token_count, text } }
    pub fn is_poisoned(&self) -> bool { self.token_count >= 0x80000000 }
    pub fn get_real_token_count(&self) -> u32 { if self.token_count >= 0x80000000 { self.token_count ^ !0u32 } else { self.token_count } }
}

// ASTs can be deeply recursive, so we need to avoid destroying them recursively.
// Collect all transitive children into self.
// This is slower than normal dropping (around 2x the runtime) but much safer.
/*
impl Drop for ASTNode {
    fn drop(&mut self)
    {
        if let Some(collected) = self.children.as_mut()
        {
            let mut i = 0;
            while i < collected.len()
            {
                if let Some(mut c) = collected[i].children.take()
                {
                    collected.append(&mut c);
                }
                i += 1;
            }
        }
    }
}
*/

/// Result of a [`Guard`] checking if a given alternation should be taken or not.
pub enum GuardResult {
    /// The alternation is chosen.
    #[allow(unused)] Accept,
    /// The alternation is rejected.
    #[allow(unused)] Reject,
    /// The guard has preemptively decided the the parse is invalid at this state and position.
    #[allow(unused)] HardError(String)
}

/// Standard "AnyMap" for putting whatever you want in it.
#[derive(Default)]
pub struct AnyMap { map: HashMap<std::any::TypeId, Box<dyn std::any::Any>> }

impl AnyMap {
    #[allow(unused)] pub fn insert<T: 'static>(&mut self, value: T) { self.map.insert(std::any::TypeId::of::<T>(), Box::new(value)); }
    #[allow(unused)] pub fn get<T: 'static>(&self) -> Option<&T> { self.map.get(&std::any::TypeId::of::<T>())?.downcast_ref::<T>() }
    #[allow(unused)] pub fn get_mut<T: 'static>(&mut self) -> Option<&mut T> { self.map.get_mut(&std::any::TypeId::of::<T>())?.downcast_mut::<T>() }
}

/// Exposable parts of current parser state.
pub struct PrdGlobal<'a> {
    pub (crate) guards : Rc<HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize) -> GuardResult>>>,
    pub (crate) hooks : Rc<HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize, &mut Vec<ASTNode>) -> Result<usize, String>>>>,
    
    /// Put your impure data here.
    #[allow(unused)] pub udata : AnyMap,
    /// Put your impure data here (simple path for cached regexes).
    #[allow(unused)] pub udata_r : HashMap<usize, RegexCacher>,
    
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

pub (crate) fn pred_recdec_parse_impl_recursive(
    global : &mut PrdGlobal,
    gp_id : usize, tokens : &[Token], token_start : usize,
    depth : usize
) -> Result<ASTNode, PrdError>
{
    const DEPTH_LIMIT : usize = if cfg!(debug_assertions) { 300 } else { 1000 };
    let mut g_item = &global.g.points[gp_id];
    let mut chosen_name_id = g_item.name_id;
    
    let mut children = vec!();
    let mut i = token_start;
    
    let mut poisoned = false;
    let mut alt_id : usize = 0;
    
    macro_rules! build_err { ($x:expr, $prog:expr) => {
        Err(PrdError {
            err_message : $x, token_index : i, rule : g_item.name_id, on_behalf_of_rule : chosen_name_id,
            in_alt : alt_id.wrapping_sub(1) as u16, alt_progress : $prog
        })
    } }
    
    if depth > DEPTH_LIMIT { return build_err!(format!("Exceeded recursion depth limit of {DEPTH_LIMIT}."), None); }
    
    #[cfg(feature = "parse_trace")] { println!("entered {} at {i}, depth {depth}", global.g.string_cache_inv[chosen_name_id as usize]); }
    
    // Structured this way for the sake of $become
    // 1) We can't use an iterator because then we can't go back to alternation 0.
    // 2) We can't have a "find alt" loop followed by a non-loop process block because then we can't go back to the "find alt" loop during $BECOME.
    'top: while alt_id < g_item.forms.len()
    {
        let alt = &g_item.forms[alt_id];
        alt_id += 1;
        
        if alt.matching_terms.len() == 0
        {
            return Ok(ASTNode::new(Some(children), (i - token_start) as u32, chosen_name_id));
        }
        
        let mut term_idx = 0;
        
        let mut accepted = true;
        let first_term = alt.matching_terms.get(0);
        let first_term = first_term.as_ref().unwrap();
        match &first_term.t
        {
            MatchingTermE::Guard(guard) =>
            {
                accepted = false;
                if let Some(f) = global.guards.get(&**guard)
                {
                    let f = Rc::clone(&f);
                    match f(global, tokens, i)
                    {
                        GuardResult::Accept => accepted = true,
                        GuardResult::HardError(e) => build_err!(e, None)?,
                        _ => {}
                    }
                }
                else
                {
                    return build_err!(format!("Unknown guard {guard}"), None);
                }
                term_idx += 1;
            }
            MatchingTermE::Peek(loc, tester) =>
            {
                accepted = false;
                let loc = (i as isize + loc) as usize;
                if loc < tokens.len() && tokens[loc].text == *tester
                {
                    accepted = true;
                }
                term_idx += 1;
            }
            MatchingTermE::PeekR(loc, tester) =>
            {
                accepted = false;
                let loc = (i as isize + loc) as usize;
                //if loc < tokens.len() && tester.is_match(&global.g.string_cache_inv[tokens[loc].text as usize])
                if loc < tokens.len() && tester.is_match_interned(tokens[loc].text, &global.g.string_cache_inv)
                {
                    accepted = true;
                }
                term_idx += 1;
            }
            MatchingTermE::PeekRes(loc, tester) =>
            {
                accepted = false;
                let loc = (i as isize + loc) as usize;
                //if loc < tokens.len() && tester.is_match(&global.g.string_cache_inv[tokens[loc].text as usize])
                if loc < tokens.len() && tester.is_match_interned(tokens[loc].text, &global.g.string_cache_inv)
                {
                    accepted = true;
                    if let Some(r) = &global.g.reserved
                    {
                        if regex_is_match(r, &global.g.string_cache_inv[tokens[loc].text as usize]) { accepted = false; }
                    }
                }
                term_idx += 1;
            }
            MatchingTermE::Eof =>
            {
                accepted = i == tokens.len();
                term_idx += 1;
            }
            _ => {}
        }
        
        if !accepted { continue; }
        
        #[cfg(feature = "parse_trace")] { println!("chose variant {}", alt_id-1); }
        
        if children.capacity() == 0
        {
            children.reserve_exact(alt.matching_terms.len());
        }
        
        while term_idx < alt.matching_terms.len()
        {
            let term = &alt.matching_terms[term_idx];
            let mut matched = false;
            match &term.t
            {
                MatchingTermE::Rule(id) =>
                {
                    let mut child = pred_recdec_parse_impl_recursive(global, *id, tokens, i, depth + 1);
                    child = std::hint::black_box(child);
                    if child.is_err() && global.g.points[*id].recover.is_some()
                    {
                        if let Some((r, after)) = &global.g.points[*id].recover
                        {
                            let mut j = i + 1;
                            while j < tokens.len() && !r.is_match(&global.g.string_cache_inv[tokens[j].text as usize])
                            {
                                j += 1;
                            }
                            if j < tokens.len()
                            {
                                if *after { j += 1; }
                                child = Ok(ASTNode::new(Some(vec!()), (j - i) as u32 ^ !0u32, global.g.points[*id].name_id));
                            }
                        }
                    }
                    const FAT_ERRS : bool = true;
                    if FAT_ERRS
                    {
                        child = child.map_err(|e| {
                            let mut e2 = e.clone(); e2.err_message = format!("In {}: {}", g_item.name, e2.err_message); e2
                        });
                    }
                    let child = child?;
                    if child.is_poisoned()
                    {
                        poisoned = true;
                    }
                    i += child.get_real_token_count() as usize;
                    children.push(child);
                    matched = true;
                }
                MatchingTermE::TermLit(lit) =>
                {
                    if i < tokens.len() && tokens[i].text == *lit
                    {
                        if !alt.pruned
                        {
                            children.push(ASTNode::new(None, 1, tokens[i].text));
                        }
                        //println!("munched {lit} at {i}");
                        i += 1;
                        matched = true;
                    }
                }
                MatchingTermE::TermRegex(regex) => if i < tokens.len() && regex.is_match_interned(tokens[i].text, &global.g.string_cache_inv)
                {
                    if !alt.pruned
                    {
                        children.push(ASTNode::new(None, 1, tokens[i].text));
                    }
                    //println!("munched {} at {i}", tokens[i].text);
                    i += 1;
                    matched = true;
                }
                MatchingTermE::Directive(d) =>
                {
                    match d
                    {
                        MatchDirective::Become | MatchDirective::BecomeAs =>
                        {
                            if let Some(MatchingTermE::Rule(id)) = alt.matching_terms.get(term_idx + 1).map(|x| &x.t)
                            {
                                g_item = &global.g.points[*id];
                                #[cfg(feature = "parse_trace")] { println!("became {} at {i}, depth {depth}", g_item.name); }
                                alt_id = 0;
                                if matches!(d, MatchDirective::BecomeAs)
                                {
                                    chosen_name_id = g_item.name_id;
                                }
                                continue 'top;
                            }
                        }
                        MatchDirective::Any => if i < tokens.len()
                        {
                            children.push(ASTNode::new(None, 1, tokens[i].text));
                            matched = true;
                            i += 1;
                        }
                        _ => panic!("TODO: {:?}", d), // also TODO: combine into parent match once all implemented
                    }
                }
                MatchingTermE::Hook(name) =>
                {
                    if let Some(f) = global.hooks.get(&**name)
                    {
                        let f = Rc::clone(&f);
                        match f(global, tokens, i, &mut children)
                        {
                            Ok(consumed) => { i += consumed; }
                            Err(e) => build_err!(e, Some(term_idx as u16))?
                        }
                    }
                    else
                    {
                        build_err!(
                            format!("Unknown custom hook {:?} inside of {}",
                                name, global.g.string_cache_inv[chosen_name_id as usize]
                            ),
                            Some(term_idx as u16)
                        )?
                    }
                    matched = true;
                }
                _ => build_err!(
                        format!("Term type {:?} not supported in this position in a rule (context: {})",
                            term, global.g.string_cache_inv[chosen_name_id as usize]
                        ),
                        Some(term_idx as u16)
                    )?
            }
            if !matched
            {
                build_err!(
                    format!("Failed to match token at {i} in rule {} alt {alt_id}. Token is `{:?}`.\n{:?}",
                        global.g.string_cache_inv[chosen_name_id as usize],
                        tokens.get(i).map(|x| global.g.string_cache_inv[x.text as usize].clone()),
                        tokens[token_start..tokens.len().min(token_start+15)].iter()
                            .map(|x| global.g.string_cache_inv[x.text as usize].clone()).collect::<Vec<_>>()
                    ),
                    Some(term_idx as u16)
                )?
            }
            term_idx += 1;
        }
        
        #[cfg(feature = "parse_trace")] { println!("accepted {} from {token_start} to {i}, depth {depth}", global.g.string_cache_inv[chosen_name_id as usize]); }
        let mut token_count = (i - token_start) as u32;
        if poisoned
        {
            token_count = token_count ^ !0u32;
        }
        return Ok(ASTNode::new(Some(children), token_count, chosen_name_id));
    }
    
    build_err!(
        format!("Failed to match rule {} at token position {token_start}\n{:?}", global.g.string_cache_inv[chosen_name_id as usize],
            tokens[token_start..tokens.len().min(token_start+15)].iter().map(|x| global.g.string_cache_inv[x.text as usize].clone()).collect::<Vec<_>>()
        ),
        Some(g_item.forms.len() as u16)
    )
}

/// Visit the AST with a possibly-impure callback. The AST itself cannot be modified this way.
///
/// Takes a function that returns whether it's OK to also visit the children of this node.
#[allow(unused)]
pub fn visit_ast(n : &ASTNode, f : &mut dyn FnMut(&ASTNode) -> bool)
{
    let flag = f(n);
    if flag && let Some(c) = &n.children
    {
        for c in c.iter()
        {
            visit_ast(c, f);
        }
    }
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
pub type Hook = Rc<dyn Fn(&mut PrdGlobal, &[Token], usize, &mut Vec<ASTNode>) -> Result<usize, String>>;

#[allow(unused)]
/// Parse the given token stream (produced by [`bnf::tokenize`](`super::bnf::tokenize`)) into an AST, using the given [`bnf::Grammar`](`super::bnf::Grammar`), and taking the given root rule name as the starting point.
///
/// Guards and hooks are for advanced usage (e.g. parsing C).
/// 
/// See also: [`ASTNode`]
pub fn parse(
    g : &Grammar, root_rule_name : &str, tokens : &[Token],
    guards : Rc<HashMap<String, Guard>>,
    hooks : Rc<HashMap<String, Hook>>,
) -> Result<ASTNode, PrdError>
{
    let gp_id = g.by_name.get(root_rule_name).unwrap();
    let mut global = PrdGlobal {
        guards,
        hooks,
        udata : <_>::default(),
        udata_r : <_>::default(),
        g,
    };
    
    if let Some(f) = global.hooks.get("init")
    {
        let f = Rc::clone(&f);
        let _ = f(&mut global, tokens, 0, &mut vec!());
    }
    
    pred_recdec_parse_impl_recursive(&mut global, *gp_id, tokens, 0, 0)
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
