// Predicated Recursive Descent

use std::rc::Rc;

use rustc_hash::FxBuildHasher;
type HashMap<K, V> = std::collections::HashMap::<K, V, FxBuildHasher>;

use crate::bnf::*;

#[derive(Clone, Debug, Default)]
pub struct PrdASTNode {
    pub text : Rc<String>,
    pub children : Option<Vec<Box<PrdASTNode>>>,
    pub token_start : usize,
    pub token_count : usize,
}

// ASTs can be deeply recursive, so we need to avoid destroying them recursively.
// Collect all transitive children into self.
impl Drop for PrdASTNode {
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

pub enum GuardResult {
    Accept,
    Reject,
    HardError(String)
}

pub struct PrdGlobal<'a> {
    pub guards : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize) -> GuardResult>>,
    pub hooks : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize, &mut Vec<Box<PrdASTNode>>) -> Result<usize, String>>>,
    
    #[allow(unused)] pub udata_s : HashMap<String, String>,
    #[allow(unused)] pub udata_i : HashMap<String, i64>,
    #[allow(unused)] pub udata_u : HashMap<String, f64>,
    #[allow(unused)] pub udata_a : HashMap<String, Box<dyn std::any::Any>>,
    
    pub g : &'a Grammar,
}

pub fn pred_recdec_parse_impl_recursive(
    global : &mut PrdGlobal,
    g : &Grammar, gp_id : usize, tokens : &[Token], depth : usize, token_start : usize
) -> Result<Box<PrdASTNode>, String>
{
    let mut g_item = &g.points[gp_id];
    let chosen_name = g_item.name.clone();
    
    let mut children : Vec<Box<PrdASTNode>> = vec!();
    let mut i = token_start;
    
    // Structured this way in preparation for future $BECOME support.
    // 1) We can't use an iterator because then we can't go back to alternation 0.
    // 2) We can't have a "find alt" loop followed by a non-loop process block because then we can't go back to the "find alt" loop during $BECOME.
    let mut alt_id = 0;
    'top: while alt_id < g_item.forms.len()
    {
        let alt = &g_item.forms[alt_id];
        alt_id += 1;
        
        let mut term_idx = 0;
        
        let mut accepted = true;
        match alt.matching_terms.get(0)
        {
            // PROTOTYPE: FIXME: use `@PEEK(0, "a", "b", ...)` syntax instead of `"PEEK 0 a b"` syntax
            Some(MatchingTerm::TermLit(lit)) =>
            {
                if lit.starts_with("@GUARD ")
                {
                    accepted = false;
                    let list = lit.splitn(2, " ").collect::<Vec<_>>();
                    if let Some(n) = list.get(1) && let Some(f) = global.guards.get(*n)
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
                        return Err(format!("Unknown custom guard {:?} inside of {chosen_name}", list.get(1)));
                    };
                    term_idx += 1;
                }
                else if lit.starts_with("@PEEK ") || lit.starts_with("@PEEKR ")
                {
                    accepted = false;
                    let list = lit.splitn(3, " ").collect::<Vec<_>>();
                    if list.len() == 3 && let Ok(loc) = list[1].parse::<isize>()
                    {
                        let loc = (i as isize + loc) as usize;
                        let n = g.string_cache.get(list[2]).unwrap();
                        if loc < tokens.len() && lit.starts_with("@PEEK ") && Rc::ptr_eq(&tokens[loc].text, n)
                        {
                            accepted = true;
                        }
                        else if loc < tokens.len() && lit.starts_with("@PEEKR ") &&
                            let Some(r) = g.random_regex_cache.get(n) && r.is_match(&tokens[loc].text)
                        {
                            accepted = true;
                        }
                    }
                    term_idx += 1;
                }
            }
            _ => {}
        }
        
        if !accepted { continue; }
        
        while term_idx < alt.matching_terms.len()
        {
            let clen_start = children.len();
            let term = &alt.matching_terms[term_idx];
            match term {
                MatchingTerm::Rule(id) =>
                {
                    let child = pred_recdec_parse_impl_recursive(global, g, *id, tokens, depth + 1, i)?;
                    i += child.token_count;
                    children.push(child);
                }
                MatchingTerm::TermLit(lit) =>
                {
                    if lit.starts_with("!HOOK ")
                    {
                        let list = lit.splitn(2, " ").collect::<Vec<_>>();
                        if let Some(n) = list.get(1) && let Some(f) = global.hooks.get(*n)
                        {
                            let f = Rc::clone(&f);
                            match f(global, tokens, i, &mut children)
                            {
                                Ok(consumed) => { i += consumed; }
                                Err(e) => { return Err(e); }
                            }
                        }
                        else
                        {
                            return Err(format!("Unknown custom hook {:?} inside of {chosen_name}", list.get(1)));
                        };
                    }
                    // PROTOTYPE: FIXME: use `$BECOME` instead of `"$BECOME"`
                    else if **lit == "$BECOME" && let Some(MatchingTerm::Rule(id)) = alt.matching_terms.get(term_idx + 1)
                    {
                        g_item = &g.points[*id];
                        alt_id = 0;
                        continue 'top;
                    }
                    else if i < tokens.len() && tokens[i].text == *lit
                    {
                        children.push(Box::new(PrdASTNode {
                            text : tokens[i].text.clone(), children : None,
                            token_start : i, token_count : 1,
                        }));
                        i += 1;
                    }
                }
                MatchingTerm::TermRegex(regex) => if i < tokens.len() && regex.is_match(&tokens[i].text)
                {
                    children.push(Box::new(PrdASTNode {
                        text : tokens[i].text.clone(), children : None,
                        token_start : i, token_count : 1,
                    }));
                    i += 1;
                }
            }
            if children.len() == clen_start
            {
                return Err(format!("Failed to match token at {i} in rule {chosen_name}. Token is `{:?}`", tokens.get(i).map(|x| x.text.clone())));
            }
            if term_idx == alt.matching_terms.len() && depth == 0 && i < tokens.len() { return Err(format!("Incomplete parse. Ended at {i}")); }
            term_idx += 1;
        }
        
        return Ok(Box::new(PrdASTNode {
            text : chosen_name,
            children : Some(children),
            token_start : token_start,
            token_count : i - token_start,
        }));
    }
    
    return Err("FIXME".to_string());
}

#[allow(unused)]
pub fn pred_recdec_force_parse(
    g : &Grammar, root_rule_name : &str, tokens : &[Token],
    guards : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize) -> GuardResult>>,
    hooks : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize, &mut Vec<Box<PrdASTNode>>) -> Result<usize, String>>>,
) -> Result<Box<PrdASTNode>, String>
{
    let gp_id = g.by_name.get(root_rule_name).unwrap();
    let mut global = PrdGlobal {
        guards,
        hooks,
        udata_s : <_>::default(),
        udata_i : <_>::default(),
        udata_u : <_>::default(),
        udata_a : <_>::default(),
        g,
    };
    
    pred_recdec_parse_impl_recursive(&mut global, g, *gp_id, tokens, 0, 0)
}


#[allow(unused)]
pub fn print_ast_pred_recdec(ast : &PrdASTNode, indent : usize)
{
    print!("{}", " ".repeat(indent));
    if let Some(c) = &ast.children
    {
        println!("{} {{", ast.text);
        for c in c
        {
            print_ast_pred_recdec(c, indent+1);
        }
        print!("{}", " ".repeat(indent));
        println!("}}");
    }
    else
    {
        println!("{}", ast.text);
    }
}
