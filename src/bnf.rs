use std::collections::{HashMap, HashSet};
use std::rc::Rc;
use std::cell::RefCell;
use regex::Regex;

// Rust doesn't have these functions: check if a given byte index in a string is utf-8 or not.
// (And if it is, return it.)
// I promise that in the context of parsing, this is not unusual. And it is the "correct" way
//  of codepoint-munching utf-8 strings without turning them into char arrays or byte arrays.
#[allow(unused)]
pub fn check_char_at_byte(s : &str, i : usize) -> Option<char>
{
    s.get(i..).and_then(|s| s.chars().next())
}
// "trust me bro" version
pub fn get_char_at_byte(s : &str, i : usize) -> char
{
    s[i..].chars().next().unwrap()
}

#[derive(Debug, Clone)]
pub struct RegexCacher {
    r : Regex,
    cache : RefCell<HashMap<Rc<String>, bool>>,
}

impl RegexCacher {
    pub fn new(r : Regex) -> RegexCacher { RegexCacher { r, cache : RefCell::new(HashMap::default()) } }
    pub fn is_match(&self, s : &Rc<String>) -> bool
    {
        let mut cache = self.cache.borrow_mut();
        if let Some(result) = cache.get(s) { return *result; }
        let ret = self.r.is_match(&*s);
        cache.insert(Rc::clone(s), ret);
        ret
    }
}

#[derive(Debug, Default)]
pub struct Grammar {
    pub points: Vec<GrammarPoint>,
    pub by_name: HashMap<String, usize>,
    
    pub literals: Vec<String>,
    pub regexes: Vec<Regex>,
    
    pub string_cache : HashMap<String, Rc<String>>,
    
    pub bracket_pairs : Vec<(String, String)>,
}

#[derive(Debug, Clone)]
pub struct GrammarPoint {
    pub name: Rc<String>,
    pub id: usize,
    pub forms: Vec<Alternation>,
}

#[derive(Debug, Clone)]
pub struct Alternation {
    pub matching_terms: Vec<MatchingTerm>,
}

#[derive(Debug, Clone)]
pub enum MatchDirective {
    Become, Hoist, Skip, Drop, Pruned,
}

#[derive(Debug, Clone)]
pub enum MatchingTerm {
    Rule(usize),
    TermLit(Rc<String>),
    TermRegex(RegexCacher),
    
    Peek(isize, Rc<String>),
    PeekR(isize, RegexCacher),
    Guard(Rc<String>),
    Hook(Rc<String>),
    Directive(MatchDirective),
    _AutoTemp,
}

pub fn string_cache_lookup(string_cache : &mut HashMap<String, Rc<String>>, s : &str) -> Rc<String>
{
    if let Some(s) = string_cache.get(s)
    {
        return Rc::clone(s);
    }
    let rc = Rc::new(s.to_string());
    string_cache.insert(s.to_string(), Rc::clone(&rc));
    rc
}

pub fn bnf_parse(input: &str) -> Result<Vec<(String, Vec<Vec<String>>)>, String>
{
    let mut rules = Vec::new();
    
    let mut metalist = Vec::new();
    let mut current = Vec::new();
    
    let mut name : Option<String> = None;
    let mut found_separator = false;
    
    for (mut linenum, mut rest) in input.lines().enumerate()
    {
        linenum += 1; // user-facing line numbers are 1-indexed
        
        let _split = rest.trim().split_whitespace().collect::<Vec<_>>();
        
        if _split.get(1) == Some(&"::=") // ::= is only allowed as the second token on a line and must be space-separated
        {
            if name.is_some()
            {
                metalist.push(current);
                rules.push((name.unwrap(), metalist));
            }
            
            name = None;
            found_separator = false;
            metalist = Vec::new();
            current = Vec::new();
        }
        
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
            else if rest.starts_with("r`")
            {
                if !found_separator { return Err(format!("Missing ::= on line {linenum}")); }
                let end = rest[2..].find("`r").expect(&format!("Unterminated regex on line {linenum}"));
                let len = end + 4;
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
            // operators
            else if  rest.starts_with("(") || rest.starts_with(")") || rest.starts_with(",")
            {
                current.push(rest[0..1].to_string());
                rest = &rest[1..];
            }
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
                    if ch.is_whitespace() || ch == '|' || ch == '(' || ch == ')' || ch == ',' || ch == '"' || ch == '#'
                        || rest[i..].starts_with("::=") || rest[i..].starts_with("r`")
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
    }
    
    if name.is_some()
    {
        metalist.push(current);
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
    
    let mut string_cache = HashMap::new();
    let mut points = Vec::new();
    let mut literals = HashSet::new();
    let mut regexes = Vec::new();
    for (index, (name, raw_forms)) in input.iter().enumerate()
    {
        let mut forms = Vec::new();
        
        for raw_alt in raw_forms
        {
            println!("{:?}", raw_forms);
            let mut matching_terms = Vec::new();
            
            let mut i = 0;
            while i < raw_alt.len()
            {
                let term_str = &raw_alt[i];
                i += 1;
                
                if term_str.starts_with('"') && term_str.ends_with('"') && term_str.len() >= 2
                {
                    let literal = term_str[1..term_str.len() - 1].replace("\\\"", "\"").replace("\\\\", "\\");
                    matching_terms.push(MatchingTerm::TermLit(string_cache_lookup(&mut string_cache, &literal)));
                    
                    literals.insert(literal.clone());
                    continue;
                }
                if term_str.starts_with("r`") && term_str.ends_with("`r") && term_str.len() >= 4
                {
                    let pattern = &term_str[2..term_str.len() - 2];
                    let pattern_all = format!("\\A{pattern}\\z"); // full match (for parsing)
                    let pattern = format!("\\A{pattern}"); // at start (for tokenization)
                    let re = Regex::new(&pattern).map_err(|e| format!("Invalid regex '{}': {}", pattern, e))?;
                    regexes.push(re.clone());
                    let re2 = Regex::new(&pattern_all).map_err(|e| format!("Invalid regex '{}': {}", pattern_all, e))?;
                    matching_terms.push(MatchingTerm::TermRegex(RegexCacher::new(re2)));
                    continue;
                }
                if matches!(&**term_str, "@AUTO" | "@auto")
                {
                    matching_terms.push(MatchingTerm::_AutoTemp);
                    continue;
                }
                if (term_str == "@PEEK" || term_str == "@peek" || term_str == "@PEEKR" || term_str == "@peekr") && i + 4 < raw_alt.len()
                {
                    if raw_alt[i] != "(" || raw_alt[i+2] != "," || raw_alt[i+4] != ")"
                    {
                        return Err(format!("Invalid peek syntax: must be @peek(num, str)"));
                    }
                    let n = raw_alt[i+1].parse::<isize>().map_err(|_| format!("Not a supported peek distance: {}", raw_alt[i+1]))?;
                    if term_str == "@PEEK" || term_str == "@peek"
                    {
                        let literal = &raw_alt[i+3];
                        if literal.len() < 2 || !literal.starts_with("\"") || !literal.ends_with("\"")
                        {
                            return Err(format!("@peek guards only accept plain strings"));
                        }
                        let literal = literal[1..literal.len() - 1].replace("\\\"", "\"").replace("\\\\", "\\");
                        let s = string_cache_lookup(&mut string_cache, &literal);
                        matching_terms.push(MatchingTerm::Peek(n, s));
                    }
                    else
                    {
                        let pattern = &raw_alt[i+3];
                        if !pattern.starts_with("r`") || !pattern.ends_with("`r")
                        {
                            return Err(format!("@peekr guards only accept regex strings"));
                        }
                        let pattern = &pattern[2..pattern.len() - 2];
                        let pattern_all = format!("\\A{}\\z", pattern);
                        let re2 = Regex::new(&pattern_all).map_err(|e| format!("Invalid regex '{}': {}", pattern_all, e))?;
                        matching_terms.push(MatchingTerm::PeekR(n, RegexCacher::new(re2)));
                    }
                    i += 5;
                    continue;
                }
                if (term_str == "@GUARD" || term_str == "@guard") && i + 2 < raw_alt.len()
                {
                    if raw_alt[i] != "(" || raw_alt[i+2] != ")"
                    {
                        return Err(format!("Invalid guard syntax: must be @guard(name)"));
                    }
                    let literal = &raw_alt[i+1];
                    let s = string_cache_lookup(&mut string_cache, &literal);
                    matching_terms.push(MatchingTerm::Guard(s));
                    i += 3;
                    continue;
                }
                if (term_str == "!HOOK" || term_str == "!hook") && i + 2 < raw_alt.len()
                {
                    if raw_alt[i] != "(" || raw_alt[i+2] != ")"
                    {
                        return Err(format!("Invalid hook syntax: must be @hook(name)"));
                    }
                    let literal = &raw_alt[i+1];
                    let s = string_cache_lookup(&mut string_cache, &literal);
                    matching_terms.push(MatchingTerm::Hook(s));
                    i += 3;
                    continue;
                }
                if matches!(&**term_str, "$BECOME" | "$become")
                {
                    matching_terms.push(MatchingTerm::Directive(MatchDirective::Become));
                    continue;
                }
                if matches!(&**term_str, "$BECOME" | "$become")
                {
                    matching_terms.push(MatchingTerm::Directive(MatchDirective::Become));
                    continue;
                }
                let id = by_name.get(term_str).ok_or_else(|| format!("Not a defined grammar rule: '{term_str}' (context: '{name}')"))?;
                matching_terms.push(MatchingTerm::Rule(*id));
            }
            if matching_terms.len() > 60000
            {
                Err(format!("More than 60k items in an alternation of {name}. Factor them out, dummy!"))?
            }
            if let Some(MatchingTerm::_AutoTemp) = matching_terms.get(0)
            {
                match matching_terms.get(1)
                {
                    Some(MatchingTerm::TermLit(s)) =>
                    {
                        let s = Rc::clone(s);
                        matching_terms[0] = MatchingTerm::Peek(0, s);
                    }
                    Some(MatchingTerm::TermRegex(r)) =>
                    {
                        let r = r.clone();
                        matching_terms[0] = MatchingTerm::PeekR(0, r);
                    }
                    _ => Err(format!("@auto must be followed by a string literal or regex literal (context: {name})"))?
                }
            }
            forms.push(Alternation { matching_terms });
        }
        if forms.len() > 60000
        {
            Err(format!("More than 60k alternations in {name}. Factor them out, dummy!"))?
        }
        points.push(GrammarPoint
        {
            name: Rc::new(name.clone()),
            id: index,
            forms,
        });
    }
    if points.len() > 4000000000
    {
        Err(format!("More than 4 billion grammar terms in grammar. What are you doing??? STOP!!!!! (╯°□°）╯︵ ┻━┻"))?
    }
    
    let mut literals = literals.into_iter().collect::<Vec<_>>();
    literals.sort();
    Ok(Grammar { points, by_name, literals, regexes, string_cache, bracket_pairs : Vec::new() })
}

pub fn bnf_to_grammar(s : &str) -> Result<Grammar, String>
{
    grammar_convert(&bnf_parse(s)?)
}

#[derive(Debug, Clone, Default)]
pub struct Token {
    pub text : Rc<String>,
    pub pair : isize,
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
    if lits.len() > 0
    {
        text_token_regex_s.pop();
    }
    text_token_regex_s += ")";
    let text_token_regex = Regex::new(&text_token_regex_s).unwrap();
    text_token_regex
}

pub fn tokenize(
    g : &mut Grammar,
    mut s : &str
) -> Result<Vec<Token>, String>
{
    let s_orig = s;
    let mut tokens = Vec::<Token>::new();
    
    let all_literals_regex = build_literal_regex(g);
    
    for text in g.literals.iter()
    {
        string_cache_lookup(&mut g.string_cache, text);
    }
    
    let mut openers = HashSet::new();
    let mut closers = HashMap::new();
    let mut stacks = HashMap::new();
    for (l, r) in &g.bracket_pairs
    {
        let lsc = string_cache_lookup(&mut g.string_cache, &l);
        openers.insert(Rc::clone(&lsc));
        closers.insert(string_cache_lookup(&mut g.string_cache, &r), Rc::clone(&lsc));
        stacks.insert(lsc, Vec::<usize>::new());
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
        
        let text = string_cache_lookup(&mut g.string_cache, &s[..longest]);
        let mut token = Token { text : Rc::clone(&text), pair : 0 };
        if openers.contains(&text) && let Some(s) = stacks.get_mut(&text)
        {
            s.push(tokens.len());
        }
        if let Some(l) = closers.get(&text) && let Some(s) = stacks.get_mut(l)
        {
            let n = s.pop().ok_or_else(|| format!("Unmatched delimiter at {}: {}", s_orig.len() - s.len(), text))?;
            let me = tokens.len();
            let diff = me.checked_signed_diff(n).ok_or_else(|| format!("Input too long"))?;
            token.pair = -diff;
            tokens[n].pair = diff;
        }
        s = &s[longest..];
        tokens.push(token);
    }
    Ok(tokens)
}

#[allow(unused)]
pub fn find_nullables(g : &Grammar) -> HashSet<(usize, usize)>
{
    // Following from: https://cs.stackexchange.com/questions/164696/
    
    // Building the bipartite graph:
    let mut rhs_to_lhs = HashMap::<_, HashSet<_>>::new();
    let mut lhs_to_rhs = HashMap::<_, HashSet<_>>::new();
    for rule in &g.points
    {
        for (alt_i, alt) in rule.forms.iter().enumerate()
        {
            let lhs = (rule.id, alt_i);
            for item in &alt.matching_terms
            {
                if let MatchingTerm::Rule(child) = item
                {
                    for j in 0..g.points[*child].forms.len()
                    {
                        let rhs = (*child, j);
                        
                        if !rhs_to_lhs.contains_key(&rhs)
                        {
                            rhs_to_lhs.insert(rhs, HashSet::default());
                        }
                        rhs_to_lhs.get_mut(&rhs).unwrap().insert(lhs);
                        
                        if !lhs_to_rhs.contains_key(&lhs)
                        {
                            lhs_to_rhs.insert(lhs, HashSet::default());
                        }
                        lhs_to_rhs.get_mut(&lhs).unwrap().insert(rhs);
                    }
                }
            }
        }
    }
    
    let mut nullable = HashSet::new();
    let mut worklist = Vec::new();
    // Initial population
    for rule in &g.points
    {
        for (alt_i, alt) in rule.forms.iter().enumerate()
        {
            if alt.matching_terms.len() == 0
            {
                nullable.insert((rule.id, alt_i));
                worklist.push((rule.id, alt_i));
            }
        }
    }
    
    // Parent scanning
    while let Some(child) = worklist.pop()
    {
        let parents = rhs_to_lhs.get(&child).cloned();
        if let Some(parents) = parents
        {
            for parent in parents
            {
                if rhs_to_lhs.get(&child).unwrap().contains(&parent)
                {
                    rhs_to_lhs.get_mut(&child).unwrap().remove(&parent);
                    lhs_to_rhs.get_mut(&parent).unwrap().remove(&child);
                    // if parent's right set is now empty, this parent is now known to be nullable
                    if lhs_to_rhs.get_mut(&parent).unwrap().is_empty()
                    {
                        nullable.insert(parent);
                        worklist.push(parent);
                    }
                }
            }
        }
    }
    
    nullable
}
