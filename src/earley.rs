//use std::collections::{HashMap, HashSet};
use std::rc::Rc;

use rustc_hash::FxBuildHasher;
type HashMap<K, V> = std::collections::HashMap::<K, V, FxBuildHasher>;
type HashSet<T> = std::collections::HashSet::<T, FxBuildHasher>;

use crate::bnf::*;

/// Ordered set that rejects pushing/inserting items that already exist in it.
#[derive(Debug, Default)]
pub struct VecSet<T> { 
    pub v : Vec<T>,
    pub s : HashMap<T, usize>,
}

impl<T : Clone + Eq + std::hash::Hash> VecSet<T>
{
    pub fn insert(&mut self, item : T) -> usize
    {
        if let Some(i) = self.s.get(&item) { return *i; }
        self.v.push(item.clone());
        self.s.insert(item, self.v.len() - 1);
        self.v.len() - 1
    }
    pub fn len(&self) -> usize { self.v.len() }
}
impl<T> std::ops::Index<usize> for VecSet<T>
{
    type Output = T;
    fn index(&self, i : usize) -> &T { self.v.index(i) }
}

#[derive(Clone, Default, Debug, Hash, PartialEq, Eq)]
// Sizes chosen to keep the size of StateItem at 16 bytes, 1/4th of a cache line.
pub struct StateItem {
    pub start : usize, // What column is the corresponding zero-pos item in?
    pub rule : u32, // What grammar rule are we looking at?
    pub alt : u16, // Which alternation of it?
    pub pos : u16, // Earley "dot position"
}

impl StateItem { fn clone_progressed(&self) -> Self { let mut ret = self.clone(); ret.pos += 1; ret } }

#[derive(Debug, Default)]
pub struct ChartColumn {
    c : VecSet<StateItem>,
    // Reduction pointers: necessary to be able to reconstruct an AST or SPPF from most parses.
    // Pointers from parent row to child row in same column, at time of completion.
    reductions : Box<HashMap<usize, HashSet<usize>>>,
    //reductions : Box<HashMap<usize, usize>>,
}
impl std::ops::Index<usize> for ChartColumn
{
    type Output = StateItem;
    fn index(&self, i : usize) -> &StateItem { self.c.index(i) }
}

pub struct ChartData {
    chart : Vec<ChartColumn>,
    taildown : HashMap<(usize, usize), HashSet<usize>>,
    origin_sets : HashMap<(usize, usize), HashSet<usize>>,
}

// Prescan optimization: only add state items if they are not a scan that's going to immediately fail.
// This reduces the total amount of Stuff that the chart filler needs to process, saving a bit of time.
pub fn chart_add_if_not_invalid(g : &Grammar, tokens : &[Token], chart : &mut Vec<ChartColumn>, col : usize, item : StateItem) -> Option<usize>
{
    if col > tokens.len() { return None; }
    let terms = &g.points[item.rule as usize].forms[item.alt as usize].matching_terms;
    let mut matched = true;
    if (item.pos as usize) < terms.len() && col < tokens.len()
    {
        let mt = &terms[item.pos as usize];
        match mt {
            // Strings are semi-interned by deduplicating them with an Rc table. Including grammar strings.
            // This makes a ptr comparison equivalent to a string comparison.
            MatchingTerm::TermLit(text) => matched = Rc::ptr_eq(&tokens[col].text, text),
            MatchingTerm::TermRegex(regex) => matched = regex.is_match(&tokens[col].text),
            _ => matched = true,
        };
    }
    if !matched { return None; }
    if col >= chart.len()
    {
        chart.resize_with(col + 1, || <_>::default());
    }
    Some(chart[col].c.insert(item))
}
pub fn chart_fill(g : &Grammar, root_rule_name : &str, tokens : &[Token]) -> ChartData
{
    // The actual chart.
    let mut chart = vec!(ChartColumn::default());
    
    // Set up every possible starting state, based on root_rule_name.
    let root_id = g.by_name[root_rule_name];
    for i in 0..g.points[root_id].forms.len()
    {
        chart[0].c.insert(StateItem { rule : root_id as u32, alt : i as u16, pos : 0, start : 0 });
    }
    
    // For preemptive nullable completion, we need to know what the nullables are.
    let nullables = find_nullables(g).iter().map(|x| x.0).collect::<HashSet<_>>();
    
    // Origin set, used to bypass the "linear scan" step of finding parents to advance when children complete.
    // (start col, rule) -> set(parent row)
    let mut origin_sets : HashMap<(usize, usize), HashSet<usize>> = <_>::default();
    // Right recursion hack: This part will be necessary to reconstructing the AST.
    // Pointers from parent (col, row) to child row in same column, at time of completion.
    let mut taildown : HashMap<(usize, usize), HashSet<usize>> = <_>::default();
    // Right recursion hack: This part lets up avoid creating quadratically many state items on right recursion.
    // Pointers from child (col, row) to parent (col, row), at time of prediction.
    let mut tailret : HashMap<(usize, usize), (usize, usize)> = <_>::default();
    
    // IMPLEMENTATION NOTE: In an optimized implementation, the above hashmaps should be "per column", not global.
    // But for the sake of readability I've left them as global
    
    let mut col = 0;
    let mut row = 0;
    while col < chart.len()
    {
        // End of this column? Go to the next one.
        if row >= chart[col].c.len()
        {
            // Set up reduction pointers. These are necessary for disambiguation.
            // We do this here instead of during completion because handling nullable rules is a lot simpler this way.
            // If you want maximum performance instead: do it during completion, and also when preemptively completing nullables.
            
            let mut reductions = HashMap::<usize, HashSet<usize>>::default();
            for (row, item) in chart[col].c.v.iter().enumerate()
            {
                let terms = &g.points[item.rule as usize].forms[item.alt as usize].matching_terms;
                if item.pos as usize >= terms.len() && let Some(set) = origin_sets.get(&(item.start, item.rule as usize))
                {
                    for parent_row in set
                    {
                        if let Some(&new_row) = chart[col].c.s.get(&chart[item.start][*parent_row].clone_progressed())
                        {
                            let item = chart[col].c[row].clone();
                            let e = reductions.entry(new_row).or_insert_with(|| <_>::default());
                            let prev_best = if let Some(&r) = e.iter().next() { chart[col].c[r].alt } else { item.alt };
                            if item.alt < prev_best { e.clear(); }
                            
                            if item.alt <= prev_best { e.insert(row); }
                        }
                    }
                }
            }
            chart[col].reductions = Box::new(reductions);
            
            /*
            let mut reductions = HashMap::<usize, usize>::default();
            for (next, item) in chart[col].c.v.iter().enumerate()
            {
                let terms = &g.points[item.rule as usize].forms[item.alt as usize].matching_terms;
                if item.pos as usize >= terms.len() && let Some(set) = origin_sets.get(&(item.start, item.rule as usize))
                {
                    for parent_row in set
                    {
                        if let Some(&new_row) = chart[col].c.s.get(&chart[item.start][*parent_row].clone_progressed())
                        {
                            if let Some(&best) = reductions.get(&new_row)
                            {
                                let best_item = chart[col][best].clone();
                                let item = chart[col][next].clone();
                                if item.alt < best_item.alt { reductions.insert(new_row, next); continue; }
                                // TODO: we're tied. check child / reduction target alt values now.
                                // TODO: -- too complicated to write. do a length preference fallback for now.
                                if item.alt == best_item.alt && item.start < best_item.start { reductions.insert(new_row, next); continue; }
                            }
                            else
                            {
                                reductions.insert(new_row, next);
                                continue;
                            }
                        }
                    }
                }
            }
            chart[col].reductions = Box::new(reductions);
            */
            
            col += 1;
            row = 0;
            continue;
        }
        
        // Not at the end of the column: handle the current row in this column
        
        let item = chart[col][row].clone();
        let terms = &g.points[item.rule as usize].forms[item.alt as usize].matching_terms;
        
        // Completion
        if item.pos as usize >= terms.len()
        {
            if let Some(set) = origin_sets.get(&(item.start, item.rule as usize))
            {
                // Right recursion hack:
                // The right recursion hack itself. ctrl+f: "Setup for the right-recursion hack"
                if set.len() == 1 && let Some(tailret_target) = tailret.get(&(item.start, *set.iter().next().unwrap()))
                {
                    let new_item = chart[tailret_target.0][tailret_target.1].clone_progressed();
                    
                    if let Some(new_row) = chart_add_if_not_invalid(g, tokens, &mut chart, col, new_item)
                    {
                        // Without these, we would be unable to reconstruct which items returned to which.
                        taildown.entry((col, new_row)).or_insert_with(|| <_>::default()).insert(row);
                    }
                    row += 1;
                    continue;
                }
                // Normal completion.
                for parent_row in set
                {
                    let new_item = chart[item.start][*parent_row].clone_progressed();
                    chart_add_if_not_invalid(g, tokens, &mut chart, col, new_item);
                }
            }
        }
        else if col <= tokens.len()
        {
            let mt = &terms[item.pos as usize];
            // Prediction
            if let MatchingTerm::Rule(id) = mt
            {
                let rule = &g.points[*id as usize];
                origin_sets.entry((col, *id)).or_insert_with(|| <_>::default()).insert(row);
                let is_nullable = nullables.contains(id);
                
                // Prediction itself.
                for i in 0..rule.forms.len()
                {
                    let new_item = StateItem { rule : *id as u32, alt : i as u16, pos : 0, start : col };
                    chart_add_if_not_invalid(g, tokens, &mut chart, col, new_item);
                }
                
                // For nullables, preemptively perform their completion.
                // This addresses an operation ordering edge case that breaks grammars like:
                //     program ::= B B "a"
                //     A ::= #intentionally empty
                if is_nullable
                {
                    chart_add_if_not_invalid(g, tokens, &mut chart, col, item.clone_progressed());
                }
                
                // Right recursion hack setup:
                // Setup for the right-recursion hack: if the items produced by this prediction would cause US to complete ...
                // ... set up a summarized upwards return sequence for them.
                if !is_nullable && item.pos as usize + 1 == terms.len()
                    && let Some(set) = origin_sets.get(&(item.start, item.rule as usize)) && set.len() == 1
                {
                    let parent_row = set.iter().next().unwrap();
                    let parent = chart[item.start][*parent_row].clone();
                    // Is this optimization definitely safe?
                    if parent.pos as usize + 1 == g.points[parent.rule as usize].forms[parent.alt as usize].matching_terms.len()
                        && !nullables.contains(&(parent.rule as usize))
                    {
                        let mut tailret_target = (item.start, *parent_row);
                        tailret_target = *tailret.get(&tailret_target).unwrap_or(&tailret_target);
                        assert!(!tailret.contains_key(&(col, row)));
                        tailret.insert((col, row), tailret_target);
                    }
                }
            }
            // Scan
            else if col < tokens.len()
            {
                // Because of the prescan optimization (only adding scan items that aren't going to fail their scan phase),
                //  we already know that scan items in the chart have to be valid, so we check validity on the progressed version instead.
                chart_add_if_not_invalid(g, tokens, &mut chart, col + 1, item.clone_progressed());
            }
        }
        row += 1;
    }
    
    ChartData { chart, taildown, origin_sets }
}

#[allow(unused)]
pub fn earley_recognize(g : &Grammar, root_rule_name : &str, tokens : &[Token]) -> Result<u16, (usize, bool)>
{
    let data = chart_fill(g, root_rule_name, tokens);
    let chart = &data.chart;
    
    let root_id = g.by_name[root_rule_name];
    for i in 0..g.points[root_id].forms.len()
    {
        let pos = g.points[root_id].forms[i].matching_terms.len();
        let expected = StateItem { rule : root_id as u32, alt : i as u16, pos : pos as u16, start : 0 };
        if chart.last().unwrap().c.s.contains_key(&expected)
        {
            if chart.len() != tokens.len() + 1 { return Err((chart.len(), true)); }
            return Ok(i as u16);
        }
    }
    Err((chart.len(), false))
}

#[derive(Clone, Debug, Default)]
pub struct ASTNode {
    #[allow(unused)]
    pub text : Rc<String>,
    pub children : Option<Vec<Box<ASTNode>>>,
    pub token_start : usize,
    #[allow(unused)]
    pub token_count : usize,
}

// ASTs can be deeply recursive, so we need to avoid destroying them recursively.
// Collect all transitive children into self.
impl Drop for ASTNode {
    fn drop(&mut self)
    {
        if let Some(collected) = self.children.as_mut()
        {
            let mut i = 0;
            while i < collected.len()
            {
                if let Some(c) = collected[i].children.as_mut()
                {
                    let mut c = std::mem::take(c);
                    collected.append(&mut c);
                }
                i += 1;
            }
        }
    }
}

pub fn fix_missing_reductions(g : &Grammar, tokens : &[Token], data : &mut ChartData, col : usize, row : usize)
{
    if let Some(bottoms) = data.taildown.get(&(col, row))
    {
        // Find the bottom of the tailcall.
        for bottom in bottoms
        {
            let mut item = data.chart[col][*bottom].clone();
            let mut row = *bottom;
            // Work our way up, generating each reduction pointer as we go.
            while let Some(set) = data.origin_sets.get(&(item.start, item.rule as usize)) && set.len() == 1
            {
                for parent_row in set
                {
                    let new_parent = data.chart[item.start][*parent_row].clone_progressed();
                    let new_row = chart_add_if_not_invalid(g, tokens, &mut data.chart, col, new_parent).unwrap();
                    
                    let chart = &mut data.chart[col];
                    let e = chart.reductions.entry(new_row).or_insert_with(|| <_>::default());
                    let prev_best = if let Some(&r) = e.iter().next() { chart.c[r].alt } else { item.alt };
                    if item.alt < prev_best { e.clear(); }
                    
                    if item.alt <= prev_best { e.insert(row); }
                    /*
                    // FIXME: do actual disambiguation
                    data.chart[col].reductions.insert(new_row, row);
                    */
                    row = new_row;
                    item = data.chart[col][new_row].clone();
                }
            }
        }
    }
}

pub fn build_ast_node(g : &Grammar, tokens : &[Token], data : &mut ChartData, col : usize, row : usize) -> Box<ASTNode>
{
    struct ASTBuilderData<'a> {
        children : Vec<Box<ASTNode>>, name : Rc<String>, gp_alt : &'a Alternation,
        col_start : usize, col : usize, row : usize, pos : usize, pos_limit : usize,
    }
    
    let base_item = &data.chart[col][row];
    let gp = &g.points[base_item.rule as usize];
    
    // Current building context.
    let mut ctx = ASTBuilderData {
        children : Vec::new(), name : Rc::clone(&gp.name), gp_alt : &gp.forms[base_item.alt as usize],
        col_start : col, col : col, row : row, pos : 0, pos_limit : base_item.pos as usize,
    };
    
    // This is where we put nodes that are waiting for their children to be done.
    let mut stash : Vec<ASTBuilderData> = Vec::new();
    let mut prepared_child : Option<Box<ASTNode>> = None;
    
    // As long as we haven't reached the end of the rootmost node...
    while !(ctx.pos == ctx.pos_limit && stash.len() == 0)
    {
        // If we're at the end of a lazily-dispatched child, prepare it and unstash the parent.
        if ctx.pos == ctx.pos_limit && stash.len() > 0
        {
            ctx.children.reverse();
            prepared_child = Some(Box::new(ASTNode {
                text : Rc::clone(&ctx.name), children : Some(ctx.children), token_start : ctx.col, token_count : ctx.col_start - ctx.col,
            }));
            ctx = stash.pop().unwrap();
            continue;
        }
        
        // If we're about to need an unprepared child, stash ourselves and dispatch its building.
        let i = ctx.pos_limit - ctx.pos - 1;
        if prepared_child.is_none() && let MatchingTerm::Rule(_) = &ctx.gp_alt.matching_terms[i]
        {
            // We need to fix right-recursion reductions at the last possible opportunity (i.e. now).
            // If any earlier, the chart gets bloated.
            fix_missing_reductions(g, tokens, data, ctx.col, ctx.row);
            
            // For now we arbitrarily pick whichever reduction is in the front.
            let child_row = *data.chart[ctx.col].reductions.get(&ctx.row).unwrap().iter().next().unwrap();
            //let child_row = *data.chart[ctx.col].reductions.get(&ctx.row).unwrap();
            
            let child_item = &data.chart[ctx.col][child_row];
            let gp = &g.points[child_item.rule as usize];
            
            let next_data = ASTBuilderData {
                children : Vec::new(), name : Rc::clone(&gp.name), gp_alt : &gp.forms[child_item.alt as usize],
                col_start : ctx.col, col : ctx.col, row : child_row, pos : 0, pos_limit : child_item.pos as usize,
            };
            stash.push(ctx);
            ctx = next_data;
            continue;
        }
        
        // If we got here, we're ready to add a new child to the current node.
        
        ctx.pos += 1;
        let mut prev_parent_item = data.chart[ctx.col][ctx.row].clone();
        prev_parent_item.pos -= 1;
        
        match &ctx.gp_alt.matching_terms[i] {
            MatchingTerm::Rule(_) =>
            {
                // If it's a nonterminal, get it from the preparation area.
                ctx.col = prepared_child.as_ref().unwrap().token_start;
                ctx.children.push(prepared_child.take().unwrap());
            }
            MatchingTerm::TermLit(_) | MatchingTerm::TermRegex(_) =>
            {
                // If it's a terminal, generate it directly.
                ctx.col -= 1;
                ctx.children.push(Box::new(ASTNode {
                    text : Rc::clone(&tokens[ctx.col].text), children : None, token_start : ctx.col, token_count : 1
                }));
            }
        }
        
        ctx.row = *data.chart[ctx.col].c.s.get(&prev_parent_item).unwrap(); // Go to row of previous version of parent.
    }
    
    ctx.children.reverse();
    Box::new(ASTNode {
        text : Rc::clone(&ctx.name), children : Some(ctx.children),
        token_start : ctx.col, token_count : ctx.col_start - ctx.col,
    })
}

#[allow(unused)]
pub fn earley_parse(g : &Grammar, root_rule_name : &str, tokens : &[Token]) -> Result<Box<ASTNode>, (usize, bool)>
{
    let mut data = chart_fill(g, root_rule_name, tokens);
    let chart = &data.chart;
    
    let root_id = g.by_name[root_rule_name];
    let mut chosen = None;
    for i in 0..g.points[root_id].forms.len()
    {
        let pos = g.points[root_id].forms[i].matching_terms.len();
        let expected = StateItem { rule : root_id as u32, alt : i as u16, pos : pos as u16, start : 0 };
        if chart.last().unwrap().c.s.contains_key(&expected)
        {
            if chart.len() != tokens.len() + 1 { return Err((chart.len(), true)); }
            chosen = Some(expected);
            break;
        }
    }
    if let Some(chosen) = chosen
    {
        let chosen_col = chart.len() - 1;
        let chosen_row = *chart[chosen_col].c.s.get(&chosen).unwrap();
        return Ok(build_ast_node(g, tokens, &mut data, chosen_col, chosen_row));
    }
    Err((chart.len(), false))
}

#[allow(unused)]
pub fn print_ast_earley(ast : &ASTNode, indent : usize)
{
    print!("{}", " ".repeat(indent));
    if let Some(c) = &ast.children
    {
        println!("{} {{", ast.text);
        for c in c
        {
            print_ast_earley(c, indent+1);
        }
        print!("{}", " ".repeat(indent));
        println!("}}");
    }
    else
    {
        println!("{}", ast.text);
    }
}