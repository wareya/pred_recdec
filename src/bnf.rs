use std::collections::{HashMap, HashSet};
use std::rc::Rc;
use std::cell::RefCell;
use regex::Regex;

// Yes this is normal for low-level parsers.
// No the rust stdlib does not have an equivalent function.
pub fn get_char_at_byte(s : &str, i : usize) -> char
{
    s[i..].chars().next().unwrap()
}

#[derive(Debug, Clone)]
pub struct RegexCacher {
    r : Regex,
    cache : Rc<RefCell<HashMap<Rc<String>, bool>>>,
    cache2 : Rc<RefCell<HashMap<u32, bool>>>,
}

impl RegexCacher {
    pub fn new(r : Regex, cache_pool : Option<&mut HashMap<String, (Rc<RefCell<HashMap<Rc<String>, bool>>>, Rc<RefCell<HashMap<u32, bool>>>)>>) -> RegexCacher
    {
        let s = r.as_str().to_string();
        let mut cache = Rc::new(RefCell::new(HashMap::default()));
        let mut cache2 = Rc::new(RefCell::new(HashMap::default()));
        if let Some(c) = cache_pool
        {
            if let Some(cached) = c.get(&s)
            {
                cache = Rc::clone(&cached.0);
                cache2 = Rc::clone(&cached.1);
            }
            else
            {
                c.insert(s.clone(), (cache.clone(), cache2.clone()));
            }
        }
        
        RegexCacher { r, cache, cache2 }
    }
    pub fn is_match(&self, s : &Rc<String>) -> bool
    {
        let mut cache = self.cache.borrow_mut();
        if let Some(result) = cache.get(s) { return *result; }
        let ret = self.r.is_match(&*s);
        cache.insert(Rc::clone(s), ret);
        ret
    }
    pub fn is_match_2(&self, i : u32, string_cache_inv : &Vec<Rc<String>>) -> bool
    {
        let mut cache = self.cache2.borrow_mut();
        if let Some(result) = cache.get(&i) { return *result; }
        let s = &string_cache_inv[i as usize];
        let ret = self.r.is_match(&*s);
        cache.insert(i, ret);
        ret
    }
}

#[derive(Debug, Default)]
pub struct Grammar {
    pub points: Vec<GrammarPoint>,
    pub by_name: HashMap<String, usize>,
    
    pub literals: Vec<String>,
    pub regexes: Vec<Regex>,
    
    pub string_cache : HashMap<String, u32>,
    pub string_cache_inv : Vec<Rc<String>>,
    
    pub bracket_pairs : Vec<(String, String)>,
    pub comments : Vec<String>,
    pub comment_pairs : Vec<(String, String)>,
    pub comment_regexes : Vec<Regex>,
    pub reserved : Option<Regex>,
}

#[derive(Debug, Clone)]
pub struct GrammarPoint {
    pub name: Rc<String>,
    pub name_id: u32,
    //pub id: u32,
    pub forms: Vec<Alternation>,
    pub recover: Option<(RegexCacher, bool)>,
}

#[derive(Debug, Clone)]
pub struct Alternation {
    pub matching_terms: Vec<MatchingTerm>,
}

#[derive(Debug, Clone)]
pub enum MatchDirective {
    Become, BecomeAs, Hoist, Any, Drop, DropIfNull, Pruned,
}

#[derive(Debug, Clone)]
pub enum MatchingTerm {
    Rule(usize),
    TermLit(u32),
    TermRegex(RegexCacher),
    
    Eof,
    Peek(isize, u32),
    PeekR(isize, RegexCacher),
    PeekRes(isize, RegexCacher),
    Guard(Rc<String>),
    Hook(Rc<String>),
    Directive(MatchDirective),
    _AutoTemp,
}

pub fn string_cache_lookup(
    string_cache : &mut HashMap<String, u32>,
    string_cache_inv : &mut Vec<Rc<String>>,
    s : &str) -> (Rc<String>, u32)
{
    if let Some(sn) = string_cache.get(s)
    {
        return (Rc::clone(&string_cache_inv[*sn as usize]), *sn);
    }
    let rc = Rc::new(s.to_string());
    let n = string_cache_inv.len().try_into().unwrap();
    string_cache.insert(s.to_string(), n);
    string_cache_inv.push(Rc::clone(&rc));
    (rc, n)
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
            else if rest.starts_with("r`") || rest.starts_with("R`")
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
    for (name, _) in input.iter()
    {
        if matches!(&**name, "__BRACKET_PAIRS" | "__COMMENT_PAIRS" | "__COMMENT_REGEXES" | "__COMMENTS" | "__RESERVED_WORDS") { continue; }
        if by_name.insert(name.clone(), by_name.len()).is_some()
        {
            return Err(format!("Duplicate rule {name}; use alternations (e.g. x ::= a | b), not additional definitions (like x ::= a [...] x ::= b)"));
        }
    }
    
    let mut string_cache = HashMap::new();
    let mut string_cache_inv = Vec::new();
    let mut points = Vec::new();
    let mut literals = HashSet::new();
    let mut lex_regexes = HashSet::new();
    
    let mut bracket_pairs = Vec::new();
    let mut comment_pairs = Vec::new();
    let mut comment_regexes = Vec::new();
    let mut comments = Vec::new();
    
    let mut cache_pool = HashMap::<String, _>::new();
    
    let mut reserved = None;
    for (name, raw_forms) in input.iter()
    {
        if name == "__RESERVED_WORDS"
        {
            let mut set = Vec::new();
            for s in raw_forms.iter().map(|x| x.iter()).flatten()
            {
                set.push(s.clone());
            }
            reserved = Some(build_literal_regex(&set, true));
            continue;
        }
        if name == "__BRACKET_PAIRS" || name == "__COMMENT_PAIRS"
        {
            for raw_alt in raw_forms
            {
                match (raw_alt.get(0), raw_alt.get(1))
                {
                    (Some(l), Some(r)) =>
                    {
                        if name == "__BRACKET_PAIRS" { bracket_pairs.push((l.clone(), r.clone())); }
                        if name == "__COMMENT_PAIRS" { comment_pairs.push((l.clone(), r.clone())); }
                    }
                    _ => Err(format!("Alternations of __BRACKET_PAIRS must all contain two bare string items"))?
                }
            }
            continue;
        }
        if name == "__COMMENT_REGEXES" || name == "__COMMENTS"
        {
            for s in raw_forms.iter().map(|x| x.iter()).flatten()
            {
                if name == "__COMMENT_REGEXES" && s.starts_with("r`") && s.ends_with("`r") && s.len() >= 4
                {
                    let pattern = &s[2..s.len() - 2];
                    let pattern = format!("\\A{pattern}");
                    let re = Regex::new(&pattern).map_err(|e| format!("Invalid regex '{}': {}", pattern, e))?;
                    comment_regexes.push(re);
                }
                if name == "__COMMENTS" && s.len() >= 1
                {
                    comments.push(s.clone());
                }
            }
            continue;
        }
        let index = *by_name.get(name).unwrap();
        
        let mut forms = Vec::new();
        let mut recover = None;
        
        for raw_alt in raw_forms
        {
            //println!("{:?}", raw_alt);
            let mut matching_terms = Vec::new();
            
            let mut i = 0;
            while i < raw_alt.len()
            {
                let term_str = &raw_alt[i];
                i += 1;
                
                if term_str.starts_with('"') && term_str.ends_with('"') && term_str.len() >= 2
                {
                    let literal = term_str[1..term_str.len() - 1].replace("\\\"", "\"").replace("\\\\", "\\").replace("\\n", "\n");
                    matching_terms.push(MatchingTerm::TermLit(string_cache_lookup(&mut string_cache, &mut string_cache_inv, &literal).1));
                    
                    literals.insert(literal.clone());
                    continue;
                }
                if term_str.starts_with("r`") && term_str.ends_with("`r") && term_str.len() >= 4
                {
                    let pattern = &term_str[2..term_str.len() - 2];
                    let pattern_all = format!("\\A(?:{pattern})\\z"); // full match (for parsing)
                    let pattern = format!("\\A(?:{pattern})"); // at start (for tokenization)
                    lex_regexes.insert(pattern);
                    let re2 = Regex::new(&pattern_all).map_err(|e| format!("Invalid regex '{}': {}", pattern_all, e))?;
                    matching_terms.push(MatchingTerm::TermRegex(RegexCacher::new(re2, Some(&mut cache_pool))));
                    continue;
                }
                // non-tokenizing regex (optimization: hide redundant regexes from the tokenizer)
                if term_str.starts_with("R`") && term_str.ends_with("`r") && term_str.len() >= 4
                {
                    let pattern = &term_str[2..term_str.len() - 2];
                    let pattern_all = format!("\\A(?:{pattern})\\z"); // full match (for parsing)
                    let re2 = Regex::new(&pattern_all).map_err(|e| format!("Invalid regex '{}': {}", pattern_all, e))?;
                    matching_terms.push(MatchingTerm::TermRegex(RegexCacher::new(re2, Some(&mut cache_pool))));
                    continue;
                }
                if matches!(&**term_str, "@RECOVER" | "@recover" | "@RECOVER_BEFORE" | "@recover_before") && i < raw_alt.len()
                {
                    let pattern = &raw_alt[i];
                    if !pattern.starts_with("r`") || !pattern.ends_with("`r") { Err(format!("@recover guards only accept regex strings"))? }
                    let pattern = &pattern[2..pattern.len() - 2];
                    let pattern_all = format!("\\A(?:{})\\z", pattern);
                    let re2 = Regex::new(&pattern_all).map_err(|e| format!("Invalid regex '{}': {}", pattern_all, e))?;
                    // TODO: make regex cachers use interior mutability and share the cache
                    if recover.is_some() { Err(format!("Rule {name} has multiple @recover items. Only one is supported."))? }
                    recover = Some((RegexCacher::new(re2, Some(&mut cache_pool)), matches!(&**term_str, "@RECOVER" | "@recover")));
                    i += 1;
                    continue;
                }
                if matches!(&**term_str, "@EOF" | "@eof")
                {
                    matching_terms.push(MatchingTerm::Eof);
                    continue;
                }
                if matches!(&**term_str, "@AUTO" | "@auto")
                {
                    matching_terms.push(MatchingTerm::_AutoTemp);
                    continue;
                }
                if (term_str == "@PEEK" || term_str == "@peek"
                    || term_str == "@PEEKR" || term_str == "@peekr"
                    || term_str == "@PEEKRES" || term_str == "@peekres") && i + 4 < raw_alt.len()
                {
                    if raw_alt[i] != "(" || raw_alt[i+2] != "," || raw_alt[i+4] != ")" { Err(format!("Invalid peek syntax: must be @peek(num, str)"))? }
                    let n = raw_alt[i+1].parse::<isize>().map_err(|_| format!("Not a supported peek distance: {}", raw_alt[i+1]))?;
                    if term_str == "@PEEK" || term_str == "@peek"
                    {
                        let literal = &raw_alt[i+3];
                        if literal.len() < 2 || !literal.starts_with("\"") || !literal.ends_with("\"")
                        {
                            return Err(format!("@peek guards only accept plain strings"));
                        }
                        let literal = literal[1..literal.len() - 1].replace("\\\"", "\"").replace("\\\\", "\\").replace("\\n", "\n");
                        let s = string_cache_lookup(&mut string_cache, &mut string_cache_inv, &literal).1;
                        matching_terms.push(MatchingTerm::Peek(n, s));
                    }
                    else
                    {
                        let pattern = &raw_alt[i+3];
                        if !pattern.starts_with("r`") || !pattern.ends_with("`r") { Err(format!("@peekr guards only accept regex strings"))? }
                        let pattern = &pattern[2..pattern.len() - 2];
                        let pattern_all = format!("\\A(?:{})\\z", pattern);
                        let re2 = Regex::new(&pattern_all).map_err(|e| format!("Invalid regex '{}': {}", pattern_all, e))?;
                        // TODO: make regex cachers use interior mutability and share the cache
                        if term_str == "@PEEKRES" || term_str == "@peekres"
                        {
                            matching_terms.push(MatchingTerm::PeekRes(n, RegexCacher::new(re2, Some(&mut cache_pool))));
                        }
                        else
                        {
                            matching_terms.push(MatchingTerm::PeekR(n, RegexCacher::new(re2, Some(&mut cache_pool))));
                        }
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
                    let s = string_cache_lookup(&mut string_cache, &mut string_cache_inv, &literal).0;
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
                    let s = string_cache_lookup(&mut string_cache, &mut string_cache_inv, &literal).0;
                    matching_terms.push(MatchingTerm::Hook(s));
                    i += 3;
                    continue;
                }
                if matches!(&**term_str, "$BECOME" | "$become")
                {
                    matching_terms.push(MatchingTerm::Directive(MatchDirective::Become));
                    continue;
                }
                if matches!(&**term_str, "$BECOME_AS" | "$become_as")
                {
                    matching_terms.push(MatchingTerm::Directive(MatchDirective::BecomeAs));
                    continue;
                }
                if matches!(&**term_str, "$ANY" | "$any")
                {
                    matching_terms.push(MatchingTerm::Directive(MatchDirective::Any));
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
                        matching_terms[0] = MatchingTerm::Peek(0, *s);
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
        let mut num_nonguards = 0;
        for f in &forms
        {
            if num_nonguards != 0
            {
                eprintln!("!!!!!!\n!!!!!! Warning: rule {name} has at least one alternation that is inaccessible!\n!!!!!!");
                break;
            }
            if !(if let Some(x) = f.matching_terms.get(0) // early 2026: working around not-yet-supported syntax
                && matches!(x, MatchingTerm::Peek(_, _) | MatchingTerm::PeekR(_, _) | MatchingTerm::Guard(_) | MatchingTerm::Eof) { true } else { false })
            { num_nonguards += 1; }
        }
        
        if index > 4000000000
        {
            Err(format!("More than 4 billion grammar terms in grammar. What are you doing??? STOP!!!!! (╯°□°）╯︵ ┻━┻"))?
        }
        let (name, name_id) = string_cache_lookup(&mut string_cache, &mut string_cache_inv, &name);
        points.push(GrammarPoint
        {
            name,
            name_id,
            //id: index as u32,
            forms,
            recover,
        });
    }
    
    let mut literals = literals.into_iter().collect::<Vec<_>>();
    literals.sort();
    
    let mut regexes = Vec::new();
    for r in lex_regexes
    {
        regexes.push(Regex::new(&r).map_err(|e| format!("Invalid regex '{}': {}", r, e))?);
    }
    Ok(Grammar { points, by_name, literals, regexes, string_cache, string_cache_inv, bracket_pairs, comments, comment_pairs, comment_regexes, reserved })
}

pub fn bnf_to_grammar(s : &str) -> Result<Grammar, String>
{
    grammar_convert(&bnf_parse(s)?)
}

#[derive(Debug, Clone, Default)]
pub struct Token {
    pub text : u32,
    pub pair : isize,
}

// Sort literals from grammar by length and combine them into a single match-longest regex.
pub fn build_literal_regex(literals : &Vec<String>, terminated : bool) -> Regex
{
    let mut text_token_regex_s = "\\A(?:".to_string();
    
    let mut lits = literals.clone();
    lits.sort_by(|a, b| b.len().cmp(&a.len()));
    for text in lits.iter()
    {
        let s2 = regex::escape(&text);
        text_token_regex_s += &s2;
        text_token_regex_s += "|";
    }
    if lits.len() > 0 { text_token_regex_s.pop(); }
    text_token_regex_s += ")";
    if terminated { text_token_regex_s += "\\z"; }
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
    
    let all_literals_regex = build_literal_regex(&g.literals, false);
    
    for text in g.literals.iter()
    {
        string_cache_lookup(&mut g.string_cache, &mut g.string_cache_inv, text);
    }
    for point in g.points.iter()
    {
        string_cache_lookup(&mut g.string_cache, &mut g.string_cache_inv, &point.name);
    }
    
    let mut openers = HashSet::new();
    let mut closers = HashMap::new();
    let mut stacks = HashMap::new();
    for (l, r) in &g.bracket_pairs
    {
        let lsc = string_cache_lookup(&mut g.string_cache, &mut g.string_cache_inv, &l);
        openers.insert(lsc.1);
        closers.insert(string_cache_lookup(&mut g.string_cache, &mut g.string_cache_inv, &r).1, lsc.1);
        stacks.insert(lsc.1, Vec::<usize>::new());
    }
    
    println!("num regexes to check: {}", g.regexes.len());
    for r in &g.regexes
    {
        println!("{:?}", r.as_str());
    }
    
    'top: while !s.is_empty()
    {
        if get_char_at_byte(s, 0).is_ascii_whitespace()
        {
            while !s.is_empty() && get_char_at_byte(s, 0).is_ascii_whitespace()
            {
                s = &s[get_char_at_byte(s, 0).len_utf8()..];
            }
            if s.is_empty() { break; }
            continue 'top;
        }
        
        // Pure regex comments
        for re in &g.comment_regexes
        {
            if let Some(x) = re.find(s)
            {
                s = &s[x.len()..];
                continue 'top;
            }
        }
        // Comments with escapable newline handling
        for c in &g.comments
        {
            if s.starts_with(c)
            {
                s = &s[c.len()..];
                while s.len() > 0 && get_char_at_byte(s, 0) != '\n'
                {
                    if get_char_at_byte(s, 0) == '\\'
                    {
                        s = &s[get_char_at_byte(s, 0).len_utf8()..]; // extra skip
                    }
                    if c.len() > 0
                    {
                        s = &s[get_char_at_byte(s, 0).len_utf8()..];
                    }
                }
                continue 'top;
            }
        }
        // Comments with nesting
        for (l, r) in &g.comment_pairs
        {
            if s.starts_with(l)
            {
                s = &s[l.len()..];
                let mut nest = 1;
                while s.len() > 0 && nest > 0
                {
                    if s.starts_with(l) { nest += 1; }
                    s = &s[get_char_at_byte(s, 0).len_utf8()..];
                    if s.starts_with(r) { nest -= 1; }
                }
                if s.starts_with(r) { s = &s[r.len()..]; }
                continue 'top;
            }
        }
        // Maximal munch: Regex pass
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
            return Err(format!("Failed to tokenize at index {}:{}[...]", s_orig.len()-s.len(), &s[..5.min(s.len())]));
        }
        
        let text = string_cache_lookup(&mut g.string_cache, &mut g.string_cache_inv, &s[..longest]);
        let mut token = Token { text : text.1, pair : 0 };
        if openers.contains(&text.1) && let Some(s) = stacks.get_mut(&text.1)
        {
            s.push(tokens.len());
        }
        if let Some(l) = closers.get(&text.1) && let Some(s) = stacks.get_mut(l)
        {
            let n = s.pop().ok_or_else(|| format!("Unmatched delimiter at {}: {}", s_orig.len() - s.len(), text.0))?;
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
