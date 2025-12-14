#![allow(unused)]

use std::collections::HashMap;
use std::rc::Rc;
use regex::Regex;

// Rust doesn't have these functions: check if a given byte index in a string is utf-8 or not.
// (And if it is, return it.)
// I promise that in the context of parsing, this is not unusual. It is in fact the "correct" way
//  of handling utf-8 strings without turning them into char arrays or byte arrays.
pub fn check_char_at_byte(s : &str, i : usize) -> Option<char>
{
    s.get(i..).and_then(|s| s.chars().next())
}
// "trust me bro" version
pub fn get_char_at_byte(s : &str, i : usize) -> char
{
    s[i..].chars().next().unwrap()
}

#[derive(Debug, Default)]
pub struct Grammar {
    pub points: Vec<GrammarPoint>,
    pub by_name: HashMap<String, usize>,
    
    pub literals: Vec<String>,
    pub regexes: Vec<Regex>,
}

#[derive(Debug, Clone)]
pub struct GrammarPoint {
    pub name: String,
    pub id: usize,
    pub forms: Vec<Alternation>,
}

#[derive(Debug, Clone)]
pub struct Alternation {
    pub matching_terms: Vec<MatchingTerm>,
}

#[derive(Debug, Clone)]
pub enum MatchingTerm {
    Rule(usize),
    TermLit(String),
    TermRegex(Regex),
}

pub fn bnf_parse(input: &str) -> Result<Vec<(String, Vec<Vec<String>>)>, String>
{
    let mut rules = Vec::new();

    for (linenum, line) in input.lines().enumerate()
    {
        let mut rest = &line[..];
        
        let mut name : Option<String> = None;
        let mut found_separator = false;
        
        let mut metalist = Vec::new();
        let mut current = Vec::new();
        while !rest.is_empty()
        {
            // skip extra whitespace
            if get_char_at_byte(rest, 0).is_whitespace()
            {
                rest = rest.trim_start();
            }
            // comment
            else if rest.starts_with("#")
            {
                break;
            }
            // literal
            else if rest.starts_with("\"")
            {
                if !found_separator { return Err(format!("Missing ::= on line {linenum}")); }
                let mut len = 1;
                let mut in_escape = false;
                let mut found_exit = false;
                while len < rest.len()
                {
                    let c = get_char_at_byte(rest, len);
                    len += c.len_utf8();
                    if !in_escape && c == '\\'
                    {
                        in_escape = true;
                        continue;
                    }
                    if !in_escape && c == '"' { found_exit = true; break; }
                    in_escape = false;
                }
                if !found_exit || len == 2 { return Err(format!("Broken literal text rule on line {linenum}")); }
                current.push(rest[..len].to_string());
                rest = &rest[len..];
            }
            // regex
            else if rest.starts_with("rx%")
            {
                if !found_separator { return Err(format!("Missing ::= on line {linenum}")); }
                let end = rest[3..].find("%rx").expect(&format!("Unterminated regex on line {linenum}"));
                let len = end + 6;
                current.push(rest[..len].to_string());
                rest = &rest[len..];
            }
            // split
            else if rest.starts_with("::=")
            {
                if found_separator { return Err(format!("Unexpected ::= on line {linenum}")); }
                if name.is_none() { return Err(format!("missing name on line {linenum}")); }
                found_separator = true;
                rest = &rest[3..];
            }
            // alternation
            else if rest.starts_with("|")
            {
                if !found_separator { return Err(format!("Missing ::= on line {linenum}")); }
                metalist.push(current);
                current = vec!();
                rest = &rest[1..];
            }
            // name
            else
            {
                let mut end = rest.len();
                for (i, ch) in rest.char_indices()
                {
                    if ch.is_whitespace() || ch == '|' || ch == '"' || ch == '#'
                        || rest[i..].starts_with("::=") || rest[i..].starts_with("rx%")
                    {
                        end = i;
                        break;
                    }
                }
                if name.is_none()
                {
                    name = Some(rest[..end].to_string());
                }
                else
                {
                    if !found_separator { return Err(format!("Missing ::= on line {linenum}")); }
                    current.push(rest[..end].to_string());
                }
                rest = &rest[end..];
            }
        }
        if !found_separator { continue; }
        metalist.push(current);
        if name.is_none() { continue; }
        rules.push((name.unwrap(), metalist));
    }
    Ok(rules)
}

pub fn grammar_convert(input: &Vec<(String, Vec<Vec<String>>)>) -> Result<Grammar, String>
{
    let mut by_name = HashMap::new();
    for (index, (name, _)) in input.iter().enumerate()
    {
        if by_name.insert(name.clone(), index).is_some()
        {
            return Err(format!("Duplicate rule {name}; use alternations (e.g. x ::= a | b), not additional definitions (like x ::= a [...] x ::= b)"));
        }
    }
    
    let mut points = Vec::new();
    let mut literals = Vec::new();
    let mut regexes = Vec::new();
    for (index, (name, raw_forms)) in input.iter().enumerate()
    {
        let mut forms = Vec::new();
        
        for raw_alt in raw_forms
        {
            let mut matching_terms = Vec::new();
            
            for term_str in raw_alt
            {
                if term_str.starts_with('"') && term_str.ends_with('"') && term_str.len() >= 2
                {
                    let mut literal = term_str[1..term_str.len() - 1].to_string();
                    literal = literal.replace("\\\"", "\"");
                    literal = literal.replace("\\\\", "\\");
                    matching_terms.push(MatchingTerm::TermLit(literal.clone()));
                    literals.push(literal.clone());
                    continue;
                }
                if term_str.starts_with("rx%") && term_str.ends_with("%rx") && term_str.len() >= 6
                {
                    let pattern = &term_str[3..term_str.len() - 3];
                    let pattern_all = format!("\\A{pattern}\\z"); // full match only
                    let pattern = format!("\\A{pattern}"); // at start only
                    let re = Regex::new(&pattern).map_err(|e| format!("Invalid regex '{}': {}", pattern, e))?;
                    let re2 = Regex::new(&pattern_all).map_err(|e| format!("Invalid regex '{}': {}", pattern_all, e))?;
                    regexes.push(re.clone());
                    matching_terms.push(MatchingTerm::TermRegex(re2));
                    continue;
                }
                let id = by_name.get(term_str).ok_or_else(|| format!("Not a defined grammar rule: '{}'", term_str))?;
                matching_terms.push(MatchingTerm::Rule(*id));
            }
            if matching_terms.len() > 60000
            {
                return Err(format!("More than 60k items in an alternation of {name}. Factor them out, dummy!"));
            }
            forms.push(Alternation { matching_terms });
        }
        if forms.len() > 60000
        {
            return Err(format!("More than 60k alternations in {name}. Factor them out, dummy!"));
        }
        points.push(GrammarPoint
        {
            name: name.clone(),
            id: index,
            forms,
        });
    }
    if points.len() > 4000000000
    {
        return Err(format!("More than 4 billion grammar terms in grammar. What are you doing??? STOP!!!!! (╯°□°）╯︵ ┻━┻"));
    }
    
    Ok(Grammar { points, by_name, literals, regexes })
}

pub fn bnf_to_grammar(s : &str) -> Result<Grammar, String>
{
    grammar_convert(&bnf_parse(s)?)
}

#[derive(Debug, Clone, Default)]
pub struct Token {
    pub text : Rc<String>,
}

// Sort literals from grammar by length and combine them into a single match-longest regex.
pub fn build_literal_regex(g : &Grammar) -> Regex
{
    let mut text_token_regex_s = "^(".to_string();
    
    let mut lits = g.literals.clone();
    lits.sort_by(|a, b| b.len().cmp(&a.len()));
    for text in lits.iter()
    {
        let s2 = regex::escape(&text);
        text_token_regex_s += &s2;
        text_token_regex_s += "|";
    }
    text_token_regex_s.pop();
    text_token_regex_s += ")";
    let text_token_regex = Regex::new(&text_token_regex_s).unwrap();
    text_token_regex
}

pub fn tokenize(g : &Grammar, mut s : &str) -> Result<Vec<Token>, String>
{
    let s_orig = s;
    let mut tokens = vec!();
    
    let all_literals_regex = build_literal_regex(g);
    
    let mut string_cache : HashMap<String, Rc<String>> = HashMap::new();
    let mut make_token = |s : &str|
    {
        if let Some(s) = string_cache.get(s)
        {
            return Token { text: Rc::clone(s) };
        }
        let rc = Rc::new(s.to_string());
        string_cache.insert(s.to_string(), Rc::clone(&rc));
        Token { text: rc }
    };
    
    for text in g.literals.iter()
    {
        make_token(text);
    }
    
    while !s.is_empty()
    {
        if get_char_at_byte(s, 0).is_whitespace()
        {
            while !s.is_empty() && get_char_at_byte(s, 0).is_whitespace()
            {
                s = &s[get_char_at_byte(s, 0).len_utf8()..];
            }
            if s.is_empty() { break; }
        }
        
        let mut longest = 0;
        for r in &g.regexes
        {
            if let Some(loc) = r.find(s).map(|x| x.len())
            {
                longest = longest.max(loc);
            }
        }
        if let Some(loc) = all_literals_regex.find(s).map(|x| x.len())
        {
            longest = longest.max(loc);
        }
        if longest == 0
        {
            return Err(format!("Failed to tokenize at index {}", s_orig.len()-s.len()));
        }
        
        tokens.push(make_token(&s[..longest]));
        s = &s[longest..];
    }
    Ok(tokens)
}
