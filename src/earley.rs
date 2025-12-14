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
    pub rule : u32, // What Rule are we looking at?
    pub alt : u16, // Which alternation of it?
    pub pos : u16, // Earley "dot position"
}

pub fn chart_fill(g : &Grammar, root_rule_name : &str, tokens : &[Token]) -> Vec<VecSet<StateItem>>
{
    let mut chart = vec!(VecSet::default());
    
    let root_id = g.by_name[root_rule_name];
    for i in 0..g.points[root_id].forms.len()
    {
        chart[0].insert(StateItem { rule : root_id as u32, alt : i as u16, pos : 0, start : 0 });
    }
    
    // Origin set, used to bypass the "linear scan" step of finding parents to advance when children complete.
    // (start col, rule) -> set(parent row)
    let mut origin_sets : HashMap<(usize, usize), HashSet<usize>> = <_>::default();
    
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
                for i in 0..rule.forms.len()
                {
                    let new_item = StateItem { rule : *id as u32, alt : i as u16, pos : 0, start : col };
                    chart[col].insert(new_item);
                    origin_sets.get_mut(&(col, *id)).unwrap().insert(row);
                }
            }
            // Scan
            else
            {
                let matched = match mt
                {
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

#[allow(unused)]
pub fn earley_recognize(g : &Grammar, root_rule_name : &str, tokens : &[Token]) -> Result<(), usize>
{
    let chart = chart_fill(g, root_rule_name, tokens);
    
    let root_id = g.by_name[root_rule_name];
    for i in 0..g.points[root_id].forms.len()
    {
        let pos = g.points[root_id].forms[i].matching_terms.len();
        let expected = StateItem { rule : root_id as u32, alt : i as u16, pos : pos as u16, start : 0 };
        if chart.last().unwrap().s.contains_key(&expected)
        {
            return Ok(());
        }
    }
    Err(chart.len())
}
