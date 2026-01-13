//use std::collections::{HashMap, HashSet};
use std::rc::Rc;

use rustc_hash::FxBuildHasher;
type HashMap<K, V> = std::collections::HashMap::<K, V, FxBuildHasher>;

use crate::bnf::*;

#[derive(Clone, Debug, Default)]
pub struct BFASTNode {
    pub text : Rc<String>,
    pub children : Option<Vec<Box<BFASTNode>>>,
    pub token_start : usize,
    pub token_count : usize,
    pub which_gp : usize,
    pub which_alt : usize,
}

// ASTs can be deeply recursive, so we need to avoid destroying them recursively.
// Collect all transitive children into self.
impl Drop for BFASTNode {
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

/// For reference/testing only. Do not use.
pub fn brute_force_parse_impl_recursive(
    reentries : &mut HashMap<(usize, usize), usize>, validity_memo : &mut HashMap<(usize, usize), bool>,
    g : &Grammar, gp_id : usize, tokens : &[Token], depth : usize,
    mut passed_info : (usize, Vec<Box<BFASTNode>>, usize, bool)
) -> Option<Box<BFASTNode>>
{
    validity_memo.entry((gp_id, passed_info.2)).or_insert(true);
    if *validity_memo.get(&(gp_id, passed_info.2)).unwrap() == false
    {
        /* this reduces the exponential blowup slightly (not entirely) for grammars like:
            S ::= AX S | AX
            AX ::= A "x"
            A ::= A A | "a"
            B ::= "b"
        */
        return None;
    }
    
    reentries.entry((gp_id, passed_info.2)).or_insert(0);
    if *reentries.get_mut(&(gp_id, passed_info.2)).unwrap() > tokens.len() + 2
    {
        // println!("{}Left recursion exceeded limit.", " ".repeat(depth));
        // must check this before incrementing so we don't need to decrement it
        return None;
    }
    
    *reentries.get_mut(&(gp_id, passed_info.2)).unwrap() += 1;
    
    let g_item = &g.points[gp_id];
    
    let was_first_entry = !passed_info.3;
    
    for (alt_id, alt) in g_item.forms.iter().enumerate()
    {
        if alt_id < passed_info.0 { continue; }
        // println!("{}checking {}_{} at {} (depth {})", " ".repeat(depth), g.points[gp_id].name, alt_id, passed_info.2, depth);
        let mut c : Vec<Box<BFASTNode>> = std::mem::take(&mut passed_info.1);
        
        let mut i = passed_info.2;
        
        let mut failed = false;
        if passed_info.3 { failed = true; passed_info.3 = false; }
        while c.len() < alt.matching_terms.len() || failed
        {
            let mut resume_info = (0, vec!(), i, false);
            if failed
            {
                // println!("{}while doing {} alt {} need another alt level", " ".repeat(depth), g.points[gp_id].name, passed_info.0);
                while c.len() > 0 && c.last().as_ref().unwrap().children.is_none()
                {
                    let child = c.pop().unwrap();
                    i = child.token_start;
                }
                if c.len() == 0 { break; }
                let mut child = c.pop().unwrap();
                resume_info.0 = child.which_alt;
                resume_info.1 = std::mem::take(&mut child.children.as_mut().unwrap());
                i = child.token_start;
                resume_info.2 = i;
                resume_info.3 = true;
                // println!("{}found alt level {} for {}", " ".repeat(depth), resume_info.0, g.points[child.which_gp].name);
            }
            if c.len() >= alt.matching_terms.len() { failed = true; continue; }
            failed = false;
            
            let clen_start = c.len();
            let term = &alt.matching_terms[c.len()];
            match term {
                MatchingTerm::Rule(id) =>
                {
                    if let Some(child) = brute_force_parse_impl_recursive(reentries, validity_memo, g, *id, tokens, depth + 1, resume_info)
                    {
                        i += child.token_count;
                        c.push(child);
                    }
                }
                MatchingTerm::TermLit(lit) => if i < tokens.len() && tokens[i].text == *lit
                {
                    c.push(Box::new(BFASTNode {
                        text : tokens[i].text.clone(), children : None,
                        token_start : i, token_count : 1, which_gp : 0, which_alt : 0
                    }));
                    i += 1;
                }
                MatchingTerm::TermRegex(regex) => if i < tokens.len() && regex.is_match(&tokens[i].text)
                {
                    c.push(Box::new(BFASTNode {
                        text : tokens[i].text.clone(), children : None,
                        token_start : i, token_count : 1, which_gp : 0, which_alt : 0
                    }));
                    i += 1;
                }
            }
            if c.len() == clen_start { failed = true; }
            if c.len() == alt.matching_terms.len() && depth == 0 && i < tokens.len() { failed = true; }
        }
        if failed
        {
            //println!("{}!failed. next alternation", " ".repeat(depth));
            continue;
        }
        
        *reentries.get_mut(&(gp_id, passed_info.2)).unwrap() -= 1;
        return Some(Box::new(BFASTNode {
            text : g_item.name.clone(),
            children : Some(c),
            token_start : passed_info.2,
            token_count : i - passed_info.2,
            which_gp : gp_id,
            which_alt : alt_id,
        }));
    }
    // println!("{}!failed. ran out of alternations.", " ".repeat(depth));
    
    *reentries.get_mut(&(gp_id, passed_info.2)).unwrap() -= 1;
    if was_first_entry
    {
        *validity_memo.get_mut(&(gp_id, passed_info.2)).unwrap() = false;
    }
    return None;
}
#[allow(unused)]
pub fn brute_force_parse(g : &Grammar, root_rule_name : &str, tokens : &[Token]) -> Result<Box<BFASTNode>, String>
{
    let gp_id = g.by_name.get(root_rule_name).unwrap();
    let mut reentries = HashMap::default();
    let mut validity_memo = HashMap::default();
    let ret = brute_force_parse_impl_recursive(&mut reentries, &mut validity_memo, g, *gp_id, tokens, 0, (0, vec!(), 0, false));
    if let Some(ret) = ret
    {
        return Ok(ret);
    }
    return Err("Failed to find a match".into());
}


#[allow(unused)]
pub fn print_ast_brute_force(ast : &BFASTNode, indent : usize)
{
    print!("{}", " ".repeat(indent));
    if let Some(c) = &ast.children
    {
        println!("{} {{", ast.text);
        for c in c
        {
            print_ast_brute_force(c, indent+1);
        }
        print!("{}", " ".repeat(indent));
        println!("}}");
    }
    else
    {
        println!("{}", ast.text);
    }
}
