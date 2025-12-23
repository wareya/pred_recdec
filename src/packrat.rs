//use std::collections::{HashMap, HashSet};
use std::rc::Rc;

use rustc_hash::FxBuildHasher;
type HashMap<K, V> = std::collections::HashMap::<K, V, FxBuildHasher>;
type HashSet<T> = std::collections::HashSet::<T, FxBuildHasher>;

use crate::bnf::*;

#[derive(Clone, Debug, Default, Eq, PartialEq)]
pub struct PackratASTNode {
    pub text : Rc<String>,
    pub children : Option<Vec<Rc<PackratASTNode>>>,
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
                if let Some(c) = Rc::get_mut(&mut collected[i])
                {
                    if let Some(mut c) = c.children.take()
                    {
                        collected.append(&mut c);
                    }
                }
                i += 1;
            }
        }
    }
}

pub fn packrat_parse_impl(_cache : &mut HashMap<(usize, usize), Option<Rc<PackratASTNode>>>, g : &Grammar, _gp_id : usize, tokens : &[Token], _token_start : usize) -> Result<Rc<PackratASTNode>, String>
{
    // _cache_ and _token_start are only included in the arg list for API parity with the recursive implementation
    let mut cache = HashMap::default();
    let mut work_started = HashSet::default();
    struct ASTBuilderData<'a> {
        children : Vec<Rc<PackratASTNode>>, forms : &'a Vec<Alternation>, terms : &'a Vec<MatchingTerm>,
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
            cache.insert((ctx.gp_id, ctx.token_start), Some(Rc::new(PackratASTNode {
                text : Rc::clone(&g.points[ctx.gp_id].name),
                token_start : ctx.token_start,
                token_count : ctx.token_i - ctx.token_start,
                children : Some(ctx.children.clone())
            })));
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
                    ctx.token_i += child.token_count;
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
            ctx.children.push(Rc::new(PackratASTNode {
                text : Rc::clone(&tokens[ctx.token_i].text),
                children : None, token_start : ctx.token_i, token_count : 1,
            }));
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
    let ret = Ok(Rc::new(PackratASTNode {
        text : Rc::clone(&g.points[ctx.gp_id].name),
        token_start : ctx.token_start,
        token_count : ctx.token_i - ctx.token_start,
        children : Some(ctx.children)
    }));
    ret
}

#[allow(unused)]
pub fn packrat_parse(g : &Grammar, root_rule_name : &str, tokens : &[Token]) -> Result<Rc<PackratASTNode>, String>
{
    let gp_id = g.by_name.get(root_rule_name).unwrap();
    let mut cache = HashMap::default();
    let ret = packrat_parse_impl(&mut cache, g, *gp_id, tokens, 0);
    if let Ok(ret) = ret
    {
        if ret.token_count == tokens.len() { return Ok(ret); }
        println!("? {} {}", ret.token_count, tokens.len());
        return Err("Failed to match entire input string".into());
    }
    ret
}
