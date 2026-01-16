// Predicated Recursive Descent

use std::rc::Rc;

use rustc_hash::FxBuildHasher;
type HashMap<K, V> = std::collections::HashMap::<K, V, FxBuildHasher>;

use crate::bnf::*;

#[derive(Clone, Debug, Default)]
pub struct PrdASTNode {
    pub text : Rc<String>,
    pub children : Option<Vec<Box<PrdASTNode>>>,
    #[allow(unused)] pub token_start : usize,
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
    #[allow(unused)] HardError(String)
}

pub struct PrdGlobal<'a> {
    pub guards : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize) -> GuardResult>>,
    pub hooks : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize, &mut Vec<Box<PrdASTNode>>) -> Result<usize, String>>>,
    
    #[allow(unused)] pub udata : HashMap<std::any::TypeId, Box<dyn std::any::Any>>,
    
    #[allow(unused)] pub g : &'a Grammar,
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
            Some(MatchingTerm::Guard(guard)) =>
            {
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
                term_idx += 1;
            }
            Some(MatchingTerm::Peek(loc, tester)) =>
            {
                accepted = false;
                let loc = (i as isize + loc) as usize;
                if loc < tokens.len() && Rc::ptr_eq(&tokens[loc].text, tester)
                {
                    accepted = true;
                }
                term_idx += 1;
            }
            Some(MatchingTerm::PeekR(loc, tester)) =>
            {
                accepted = false;
                let loc = (i as isize + loc) as usize;
                if loc < tokens.len() && tester.is_match(&tokens[loc].text)
                {
                    accepted = true;
                }
                term_idx += 1;
            }
            _ => {}
        }
        
        if !accepted { continue; }
        
        while term_idx < alt.matching_terms.len()
        {
            let term = &alt.matching_terms[term_idx];
            let mut matched = false;
            match term {
                MatchingTerm::Rule(id) =>
                {
                    let child = pred_recdec_parse_impl_recursive(global, g, *id, tokens, depth + 1, i)?;
                    i += child.token_count;
                    children.push(child);
                    matched = true;
                }
                MatchingTerm::TermLit(lit) =>
                {
                    if i < tokens.len() && tokens[i].text == *lit
                    {
                        children.push(Box::new(PrdASTNode {
                            text : tokens[i].text.clone(), children : None,
                            token_start : i, token_count : 1,
                        }));
                        i += 1;
                        matched = true;
                    }
                }
                MatchingTerm::TermRegex(regex) => if i < tokens.len() && regex.is_match(&tokens[i].text)
                {
                    children.push(Box::new(PrdASTNode {
                        text : tokens[i].text.clone(), children : None,
                        token_start : i, token_count : 1,
                    }));
                    i += 1;
                    matched = true;
                }
                MatchingTerm::Directive(d) =>
                {
                    match d
                    {
                        MatchDirective::Become =>
                        {
                            if let Some(MatchingTerm::Rule(id)) = alt.matching_terms.get(term_idx + 1)
                            {
                                g_item = &g.points[*id];
                                alt_id = 0;
                                continue 'top;
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
                        Err(format!("Unknown custom hook {:?} inside of {chosen_name}", name))?
                    }
                    matched = true;
                }
                _ => Err(format!("Term type {:?} not supported in this position in a rule (context: {chosen_name})", term))?
            }
            if !matched
            {
                Err(format!("Failed to match token at {i} in rule {chosen_name} alt {alt_id}. Token is `{:?}`. Rule is {:?}", tokens.get(i).map(|x| x.text.clone()), term))?
            }
            //if term_idx == alt.matching_terms.len() && depth == 0 && i < tokens.len() { return Err(format!("Incomplete parse. Ended at {i}")); }
            term_idx += 1;
        }
        
        return Ok(Box::new(PrdASTNode {
            text : chosen_name,
            children : Some(children),
            token_start : token_start,
            token_count : i - token_start,
        }));
    }
    
    Err(format!("Failed to match rule {chosen_name} at token position {token_start}"))
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
        udata : <_>::default(),
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
        println!("}};");
    }
    else
    {
        println!("{}", ast.text);
    }
}
