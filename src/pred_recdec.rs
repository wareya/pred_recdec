// Predicated Recursive Descent

use std::rc::Rc;

use rustc_hash::FxBuildHasher;
type HashMap<K, V> = std::collections::HashMap::<K, V, FxBuildHasher>;

use crate::bnf::*;

#[derive(Clone, Debug, Default)]
pub struct ASTNode {
    pub children : Option<Vec<ASTNode>>,
    pub token_count : u32, // IF POISONED: xor with !0u32 (all one-bits)
    pub text : u32, // index into grammar.string_cache_inv
}

impl ASTNode {
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

pub enum GuardResult {
    Accept,
    Reject,
    #[allow(unused)] HardError(String)
}


#[derive(Default)]
pub struct AnyMap { map: HashMap<std::any::TypeId, Box<dyn std::any::Any>> }

impl AnyMap {
    pub fn insert<T: 'static>(&mut self, value: T) { self.map.insert(std::any::TypeId::of::<T>(), Box::new(value)); }
    pub fn get<T: 'static>(&self) -> Option<&T> { self.map.get(&std::any::TypeId::of::<T>())?.downcast_ref::<T>() }
    pub fn get_mut<T: 'static>(&mut self) -> Option<&mut T> { self.map.get_mut(&std::any::TypeId::of::<T>())?.downcast_mut::<T>() }
}


pub struct PrdGlobal<'a> {
    pub guards : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize) -> GuardResult>>,
    pub hooks : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize, &mut Vec<ASTNode>) -> Result<usize, String>>>,
    
    #[allow(unused)] pub udata : AnyMap,
    pub udata_r : HashMap<usize, RegexCacher>,
    
    #[allow(unused)] pub g : &'a Grammar,
}

pub fn pred_recdec_parse_impl_recursive(
    global : &mut PrdGlobal,
    gp_id : usize, tokens : &[Token], token_start : usize,
    depth : usize
) -> Result<ASTNode, String>
{
    const DEPTH_LIMIT : usize = 1000;
    if depth > DEPTH_LIMIT { return Err(format!("Exceeded recursion depth limit of {DEPTH_LIMIT}.")); }
    let mut g_item = &global.g.points[gp_id];
    let mut chosen_name_id = g_item.name_id;
    
    let mut children = vec!();
    let mut i = token_start;
    
    let mut poisoned = false;
    let mut pruned = false;
    
    #[cfg(feature = "parse_trace")] { println!("entered {} at {i}, depth {depth}", global.g.string_cache_inv[chosen_name_id as usize]); }
    
    // Structured this way for the sake of $become
    // 1) We can't use an iterator because then we can't go back to alternation 0.
    // 2) We can't have a "find alt" loop followed by a non-loop process block because then we can't go back to the "find alt" loop during $BECOME.
    let mut alt_id = 0;
    'top: while alt_id < g_item.forms.len()
    {
        let alt = &g_item.forms[alt_id];
        alt_id += 1;
        
        if alt.matching_terms.len() == 0
        {
            return Ok(ASTNode {
                text : chosen_name_id,
                children : Some(children),
                token_count : (i - token_start) as u32,
            });
        }
        
        let mut term_idx = 0;
        
        let mut accepted = true;
        let first_term = alt.matching_terms.get(0);
        let first_term = first_term.as_ref().unwrap();
        match first_term
        {
            MatchingTerm::Guard(guard) =>
            {
                accepted = false;
                if let Some(f) = global.guards.get(&**guard)
                {
                    let f = Rc::clone(&f);
                    match f(global, tokens, i)
                    {
                        GuardResult::Accept => accepted = true,
                        GuardResult::HardError(e) => { return Err(e); }
                        _ => {}
                    }
                }
                else
                {
                    return Err(format!("Unknown guard {guard}"));
                }
                term_idx += 1;
            }
            MatchingTerm::Peek(loc, tester) =>
            {
                accepted = false;
                let loc = (i as isize + loc) as usize;
                if loc < tokens.len() && tokens[loc].text == *tester
                {
                    accepted = true;
                }
                term_idx += 1;
            }
            MatchingTerm::PeekR(loc, tester) =>
            {
                accepted = false;
                let loc = (i as isize + loc) as usize;
                //if loc < tokens.len() && tester.is_match(&global.g.string_cache_inv[tokens[loc].text as usize])
                if loc < tokens.len() && tester.is_match_2(tokens[loc].text, &global.g.string_cache_inv)
                {
                    accepted = true;
                }
                term_idx += 1;
            }
            MatchingTerm::PeekRes(loc, tester) =>
            {
                accepted = false;
                let loc = (i as isize + loc) as usize;
                //if loc < tokens.len() && tester.is_match(&global.g.string_cache_inv[tokens[loc].text as usize])
                if loc < tokens.len() && tester.is_match_2(tokens[loc].text, &global.g.string_cache_inv)
                {
                    accepted = true;
                    if let Some(r) = &global.g.reserved
                    {
                        if r.is_match(&global.g.string_cache_inv[tokens[loc].text as usize]) { accepted = false; }
                    }
                }
                term_idx += 1;
            }
            MatchingTerm::Eof =>
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
            match term
            {
                MatchingTerm::Rule(id) =>
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
                                child = Ok(ASTNode {
                                    text : global.g.points[*id].name_id,
                                    children : Some(vec!()),
                                    token_count : (j - i) as u32 ^ !0u32,
                                });
                            }
                        }
                    }
                    let child = child.map_err(|e| format!("In {}: {e}", g_item.name))?;
                    if child.is_poisoned()
                    {
                        poisoned = true;
                    }
                    i += child.get_real_token_count() as usize;
                    children.push(child);
                    matched = true;
                }
                MatchingTerm::TermLit(lit) =>
                {
                    if i < tokens.len() && tokens[i].text == *lit
                    {
                        if !pruned
                        {
                            children.push(ASTNode {
                                text : tokens[i].text.clone(), children : None,
                                token_count : 1,
                            });
                        }
                        //println!("munched {lit} at {i}");
                        i += 1;
                        matched = true;
                    }
                }
                MatchingTerm::TermRegex(regex) => if i < tokens.len() && regex.is_match_2(tokens[i].text, &global.g.string_cache_inv)
                {
                    if !pruned
                    {
                        children.push(ASTNode {
                            text : tokens[i].text.clone(), children : None,
                            token_count : 1,
                        });
                    }
                    //println!("munched {} at {i}", tokens[i].text);
                    i += 1;
                    matched = true;
                }
                MatchingTerm::Directive(d) =>
                {
                    match d
                    {
                        MatchDirective::Become | MatchDirective::BecomeAs =>
                        {
                            if let Some(MatchingTerm::Rule(id)) = alt.matching_terms.get(term_idx + 1)
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
                            children.push(ASTNode {
                                text : tokens[i].text.clone(), children : None,
                                token_count : 1,
                            });
                            matched = true;
                            i += 1;
                        }
                        MatchDirective::Pruned => { pruned = true; matched = true; }
                        MatchDirective::HoistUnitary =>
                        {
                            matched = true;
                            if children.len() == 1 || children[0].children.is_some()
                            {
                                chosen_name_id = children[0].text;
                                children = children[0].children.take().unwrap();
                            }
                        }
                        _ => panic!("TODO: {:?}", d), // also TODO: combine into parent match once all implemented
                    }
                }
                MatchingTerm::Hook(name) =>
                {
                    if let Some(f) = global.hooks.get(&**name)
                    {
                        let f = Rc::clone(&f);
                        match f(global, tokens, i, &mut children)
                        {
                            Ok(consumed) => { i += consumed; }
                            Err(e) => Err(e)?
                        }
                    }
                    else
                    {
                        Err(format!("Unknown custom hook {:?} inside of {}", name, global.g.string_cache_inv[chosen_name_id as usize]))?
                    }
                    matched = true;
                }
                _ => Err(format!("Term type {:?} not supported in this position in a rule (context: {})", term, global.g.string_cache_inv[chosen_name_id as usize]))?
            }
            if !matched
            {
                Err(format!("Failed to match token at {i} in rule {} alt {alt_id}. Token is `{:?}`.\n{:?}",
                    global.g.string_cache_inv[chosen_name_id as usize],
                    tokens.get(i).map(|x| global.g.string_cache_inv[x.text as usize].clone()),
                    tokens[token_start..tokens.len().min(token_start+15)].iter().map(|x| global.g.string_cache_inv[x.text as usize].clone()).collect::<Vec<_>>()))?
            }
            term_idx += 1;
        }
        
        #[cfg(feature = "parse_trace")] { println!("accepted {} from {token_start} to {i}, depth {depth}", global.g.string_cache_inv[chosen_name_id as usize]); }
        let mut token_count = (i - token_start) as u32;
        if poisoned
        {
            token_count = token_count ^ !0u32;
        }
        return Ok(ASTNode {
            text : chosen_name_id,
            children : Some(children),
            token_count,
        });
    }
    
    Err(format!("Failed to match rule {} at token position {token_start}\n{:?}", global.g.string_cache_inv[chosen_name_id as usize],
        tokens[token_start..tokens.len().min(token_start+15)].iter().map(|x| global.g.string_cache_inv[x.text as usize].clone()).collect::<Vec<_>>()))
}

/// Takes a fn that returns whether it's OK to also visit the children of this node.
pub fn visit_mut(n : &mut ASTNode, f : &mut dyn FnMut(&mut ASTNode) -> bool)
{
    let flag = f(n);
    if flag && let Some(c) = &mut n.children
    {
        for c in c.iter_mut()
        {
            visit_mut(c, f);
        }
    }
}
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

#[allow(unused)]
pub fn pred_recdec_parse(
    g : &Grammar, root_rule_name : &str, tokens : &[Token],
    guards : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize) -> GuardResult>>,
    hooks : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize, &mut Vec<ASTNode>) -> Result<usize, String>>>,
) -> Result<ASTNode, String>
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
