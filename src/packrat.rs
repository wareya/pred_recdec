use std::collections::{HashMap, HashSet};
use std::rc::Rc;
use std::cell::RefCell;

use crate::bnf::*;

#[derive(Clone, Debug, Default, Eq, PartialEq)]
pub struct PackratASTNode {
    pub text : Rc<String>,
    pub children : Option<Vec<Rc<RefCell<PackratASTNode>>>>,
    pub token_start : usize,
    pub token_count : usize,
}

// ASTs can be deeply recursive, so we need to avoid destroying them recursively.
// Collect all transitive children into self.
impl Drop for PackratASTNode {
    fn drop(&mut self)
    {
        if let Some(collected) = self.children.as_mut()
        {
            let mut i = 0;
            while i < collected.len()
            {
                let c = collected[i].borrow_mut().children.as_mut().map(|c| std::mem::take(c));
                if let Some(mut c) = c
                {
                    collected.append(&mut c);
                }
                i += 1;
            }
        }
    }
}

#[allow(unused)]
// Provided as documentation of algorithmic intent. Do not use.
// Does not have all the features that the non-recursive implementation has.
pub fn packrat_parse_recursive_impl(cache : &mut HashMap<(usize, usize), Option<Rc<RefCell<PackratASTNode>>>>, g : &Grammar, gp_id : usize, tokens : &[Token], token_start : usize) -> Option<Rc<RefCell<PackratASTNode>>>
{
    // Deliberately written in a way that minimizes the changes needed for the non-recursive version.
    let mut token_i = token_start;
    let forms = &g.points[gp_id].forms;
    let mut i = 0;
    let mut terms = &forms[i].matching_terms;
    let mut j = 0;
    let mut children = Vec::new();
    while i < forms.len() && j < terms.len() && token_i <= tokens.len()
    {
        let term = &terms[j];
        let old_childcount = children.len();
        let mut token_match = false;
        match term
        {
            MatchingTerm::Rule(id) =>
                if let Some(cached) = cache.get(&(*id, token_i))
                {
                    // cannot be combined into above if statement
                    if let Some(child) = cached
                    {
                        let child = child.clone();
                        token_i += child.borrow().token_count;
                        children.push(child);
                    }
                }
                else if let Some(child) = packrat_parse_recursive_impl(cache, g, *id, tokens, token_i)
                {
                    token_i += child.borrow().token_count;
                    children.push(child);
                }
            MatchingTerm::TermLit(lit) =>
                token_match = token_i < tokens.len() && tokens[token_i].text == *lit,
            MatchingTerm::TermRegex(regex) =>
                token_match = token_i < tokens.len() && regex.is_match(&tokens[token_i].text),
        }
        if token_match
        {
            children.push(Rc::new(RefCell::new(PackratASTNode {
                text : Rc::clone(&tokens[token_i].text),
                children : None, token_start : token_i, token_count : 1,
            })));
            token_i += 1;
        }
        
        j += 1;
        if children.len() == old_childcount
        {
            j = 0;
            token_i = token_start;
            children.clear();
            i += 1;
            if i >= forms.len() { cache.insert((gp_id, token_start), None); return None; }
            terms = &forms[i].matching_terms;
        }
    }
    let ret = Some(Rc::new(RefCell::new(PackratASTNode {
        text : Rc::clone(&g.points[gp_id].name),
        token_start : token_start,
        token_count : token_i - token_start,
        children : Some(children)
    })));
    cache.insert((gp_id, token_start), ret.clone());
    ret
}
pub fn packrat_parse_impl(_cache : &mut HashMap<(usize, usize), Option<Rc<RefCell<PackratASTNode>>>>, g : &Grammar, _gp_id : usize, tokens : &[Token], _token_start : usize) -> Result<Rc<RefCell<PackratASTNode>>, String>
{
    // _cache_ and _token_start are only included in the arg list for API parity with the recursive implementation
    let mut cache = HashMap::new();
    let mut work_started = HashSet::new();
    struct ASTBuilderData<'a> {
        children : Vec<Rc<RefCell<PackratASTNode>>>, forms : &'a Vec<Alternation>, terms : &'a Vec<MatchingTerm>,
        gp_id : usize, token_start : usize, token_i : usize, i : usize, j : usize,
    }
    impl<'a> ASTBuilderData<'a> {
        fn start_identity_tuple(&self) -> (usize, usize)
        {
            (self.gp_id, self.token_start)
        }
    }
    
    let _forms = &g.points[_gp_id].forms;
    let mut ctx = ASTBuilderData {
        children : Vec::new(),
        terms : &_forms[0].matching_terms,
        forms : _forms,
        gp_id : _gp_id,
        i : 0,
        j : 0,
        token_i : 0,
        token_start : 0,
    };
    
    let mut stash : Vec<ASTBuilderData> = Vec::new();
    
    while (ctx.i < ctx.forms.len() && ctx.j < ctx.terms.len() && ctx.token_i <= tokens.len())
        || !stash.is_empty()
    {
        if ctx.i == 0 && ctx.j == 0 { work_started.insert(ctx.start_identity_tuple()); }
        if !stash.is_empty() && !(ctx.i < ctx.forms.len() && ctx.j < ctx.terms.len() && ctx.token_i <= tokens.len())
        {
            cache.insert((ctx.gp_id, ctx.token_start), Some(Rc::new(RefCell::new(PackratASTNode {
                text : Rc::clone(&g.points[ctx.gp_id].name),
                token_start : ctx.token_start,
                token_count : ctx.token_i - ctx.token_start,
                children : Some(ctx.children.clone())
            }))));
            ctx = stash.pop().unwrap();
            continue;
        }
        
        let term = &ctx.terms[ctx.j];
        if let MatchingTerm::Rule(id) = term && !cache.contains_key(&(*id, ctx.token_i))
        {
            let token_i = ctx.token_i;
            stash.push(ctx);
            let forms = &g.points[*id].forms;
            ctx = ASTBuilderData {
                children : Vec::new(),
                terms : &forms[0].matching_terms,
                forms,
                gp_id : *id,
                i : 0,
                j : 0,
                token_i,
                token_start : token_i,
            };
            if work_started.contains(&ctx.start_identity_tuple())
            {
                //return Err(format!("Left recursion in {}", g.points[ctx.gp_id].name));
                cache.insert((ctx.gp_id, ctx.token_start), None);
                ctx = stash.pop().unwrap();
            }
            continue;
        }
        
        let old_childcount = ctx.children.len();
        let mut token_match = false;
        match term
        {
            MatchingTerm::Rule(id) =>
            {
                let cached = cache.get(&(*id, ctx.token_i)).unwrap();
                if let Some(child) = cached
                {
                    let child = child.clone();
                    ctx.token_i += child.borrow().token_count;
                    ctx.children.push(child);
                }
            }
            MatchingTerm::TermLit(lit) =>
                token_match = ctx.token_i < tokens.len() && tokens[ctx.token_i].text == *lit,
            MatchingTerm::TermRegex(regex) =>
                token_match = ctx.token_i < tokens.len() && regex.is_match(&tokens[ctx.token_i].text),
        }
        if token_match
        {
            ctx.children.push(Rc::new(RefCell::new(PackratASTNode {
                text : Rc::clone(&tokens[ctx.token_i].text),
                children : None, token_start : ctx.token_i, token_count : 1,
            })));
            ctx.token_i += 1;
        }
        
        ctx.j += 1;
        if ctx.children.len() == old_childcount
        {
            ctx.j = 0;
            ctx.token_i = ctx.token_start;
            ctx.children.clear();
            ctx.i += 1;
            if ctx.i >= ctx.forms.len()
            {
                if stash.len() > 0
                {
                    cache.insert((ctx.gp_id, ctx.token_start), None);
                    ctx = stash.pop().unwrap();
                    continue;
                }
                else
                {
                    return Err("Failed to parse root level grammar rule".into());
                }
            }
            ctx.terms = &ctx.forms[ctx.i].matching_terms;
        }
    }
    let ret = Ok(Rc::new(RefCell::new(PackratASTNode {
        text : Rc::clone(&g.points[ctx.gp_id].name),
        token_start : ctx.token_start,
        token_count : ctx.token_i - ctx.token_start,
        children : Some(ctx.children)
    })));
    ret
    
}
pub fn packrat_parse(g : &Grammar, root_rule_name : &str, tokens : &[Token]) -> Result<Rc<RefCell<PackratASTNode>>, String>
{
    let gp_id = g.by_name.get(root_rule_name).unwrap();
    let mut cache = HashMap::new();
    let ret = packrat_parse_impl(&mut cache, g, *gp_id, tokens, 0);
    if let Ok(ret) = ret
    {
        if ret.borrow().token_count == tokens.len() { return Ok(ret); }
        println!("? {} {}", ret.borrow().token_count, tokens.len());
        return Err("Failed to match entire input string".into());
    }
    ret
}
