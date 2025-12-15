use std::collections::{HashMap, HashSet};

use crate::bnf::*;

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
    fn index(&self, i : usize) -> &T
    {
        self.v.index(i)
    }
}

#[derive(Clone, Default, Debug, Hash, PartialEq, Eq)]
// Sizes chosen to keep the size of StateItem at 16 bytes, 1/4th of a cache line.
pub struct StateItem {
    pub start : usize, // What column is the corresponding zero-pos item in?
    pub rule : u32, // What grammar rule are we looking at?
    pub alt : u16, // Which alternation of it?
    pub pos : u16, // Earley "dot position"
}

pub fn chart_fill(g : &Grammar, root_rule_name : &str, tokens : &[Token]) -> Vec<VecSet<StateItem>>
{
    // The actual chart.
    let mut chart = vec!(VecSet::default());
    
    let root_id = g.by_name[root_rule_name];
    for i in 0..g.points[root_id].forms.len()
    {
        chart[0].insert(StateItem { rule : root_id as u32, alt : i as u16, pos : 0, start : 0 });
    }
    
    // For preemptive nullable completion, we need to know what the nullables are.
    let nullables = find_nullables(g).iter().map(|x| x.0).collect::<HashSet<_>>();
    
    // Origin set, used to bypass the "linear scan" step of finding parents to advance when children complete.
    // (start col, rule) -> set(parent row)
    let mut origin_sets : HashMap<(usize, usize), HashSet<usize>> = <_>::default();
    
    // Right recursion hack: This part lets up avoid creating quadratically many state items on right recursion.
    let mut tailret : HashMap<(usize, usize), (usize, usize)> = <_>::default();
    // Right recursion hack: This part will be necessary to reconstructing the AST.
    let mut taildown : HashMap<(usize, usize), HashSet<(usize, usize)>> = <_>::default();
    
    let mut col = 0;
    let mut row = 0;
    while col < chart.len()
    {
        if row >= chart[col].len() { col += 1; row = 0; continue; }
        let item = chart[col][row].clone();
        let terms = &g.points[item.rule as usize].forms[item.alt as usize].matching_terms;
        if item.pos as usize >= terms.len()
        {
            // Completion
            if let Some(set) = origin_sets.get(&(item.start, item.rule as usize))
            {
                // Right recursion hack:
                // The right recursion hack itself. ctrl+f: "Setup for the right-recursion hack"
                if set.len() == 1 && let Some(tailret_target) = tailret.get(&(item.start, *set.iter().next().unwrap()))
                {
                    let mut new_target = chart[tailret_target.0][tailret_target.1].clone();
                    new_target.pos += 1;
                    let new_row = chart[col].insert(new_target);
                    
                    // Without these, we would be unable to reconstruct which items returned to which.
                    if !taildown.contains_key(&(col, new_row))
                    {
                        taildown.insert((col, new_row), <_>::default());
                    }
                    taildown.get_mut(&(col, new_row)).unwrap().insert((col, row));
                    
                    row += 1;
                    continue;
                }
                // Normal completion.
                for parent_row in set
                {
                    let mut new_parent = chart[item.start][*parent_row].clone();
                    new_parent.pos += 1;
                    chart[col].insert(new_parent);
                }
            }
        }
        else if col < tokens.len()
        {
            let mt = &terms[item.pos as usize];
            // Prediction
            if let MatchingTerm::Rule(id) = mt
            {
                let rule = &g.points[*id as usize];
                if !origin_sets.contains_key(&(col, *id))
                {
                    origin_sets.insert((col, *id), <_>::default());
                }
                origin_sets.get_mut(&(col, *id)).unwrap().insert(row);
                let is_nullable = nullables.contains(id);
                
                // Prediction itself.
                for i in 0..rule.forms.len()
                {
                    let new_item = StateItem { rule : *id as u32, alt : i as u16, pos : 0, start : col };
                    chart[col].insert(new_item);
                }
                
                // For nullables, preemptively perform their completion.
                // This addresses an operation ordering edge case that breaks grammars like:
                //     program ::= A A "a"
                //     A ::= #intentionally empty
                if is_nullable
                {
                    let mut next_item = item.clone();
                    next_item.pos += 1;
                    chart[col].insert(next_item);
                }
                
                // Right recursion hack:
                // Setup for the right-recursion hack: if the items produced by this prediction would cause US to complete ...
                // ... set up a summarized upwards-return-sequence for them.
                if !is_nullable && item.pos as usize + 1 == terms.len()
                {
                    if let Some(set) = origin_sets.get(&(item.start, item.rule as usize))
                    {
                        if set.len() == 1
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
                }
            }
            // Scan
            else
            {
                let matched = match mt {
                    MatchingTerm::TermLit(text) => *tokens[col].text == *text,
                    MatchingTerm::TermRegex(regex) => regex.is_match(&*tokens[col].text),
                    _ => false,
                };
                if matched
                {
                    let mut new_item = item.clone();
                    new_item.pos += 1;
                    if col + 1 >= chart.len()
                    {
                        chart.push(<_>::default());
                    }
                    chart[col + 1].insert(new_item);
                }
            }
        }
        row += 1;
    }
    
    chart
}

pub fn earley_recognize(g : &Grammar, root_rule_name : &str, tokens : &[Token]) -> Result<u16, (usize, bool)>
{
    let chart = chart_fill(g, root_rule_name, tokens);
    
    let root_id = g.by_name[root_rule_name];
    for i in 0..g.points[root_id].forms.len()
    {
        let pos = g.points[root_id].forms[i].matching_terms.len();
        let expected = StateItem { rule : root_id as u32, alt : i as u16, pos : pos as u16, start : 0 };
        if chart.last().unwrap().s.contains_key(&expected)
        {
            if chart.len() != tokens.len() + 1 { return Err((chart.len(), true)); }
            return Ok(i as u16);
        }
    }
    Err((chart.len(), false))
}
