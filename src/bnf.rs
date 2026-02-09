type HashMap<K, V> = std::collections::HashMap::<K, V, crate::HashBuilder>;
type HashSet<K> = std::collections::HashSet::<K, crate::HashBuilder>;
use std::rc::Rc;
use std::cell::RefCell;
use regex::Regex as Regex;
//use regex::bytes::Regex as Regex;
//use pcre2::bytes::Regex as Regex;

// Yes this is normal for low-level parsers.
// No the rust stdlib does not have an equivalent function.
pub (crate) fn get_char_at_byte(s : &str, i : usize) -> char
{
    s[i..].chars().next().unwrap()
}
/// One-to-one wrapper around Regex::new().
pub fn new_regex(s : &str) -> Result<Regex, regex::Error>
//pub (crate) fn new_regex(s : &str) -> Result<Regex, pcre2::Error>
{
    Regex::new(s)
    //regex::RegexBuilder::new(s).unicode(false).build()
    //pcre2::bytes::RegexBuilder::new().jit(true).build(s)
}

pub (crate) fn regex_find<'a>(r : &Regex, s : &'a str) -> Option<regex::Match<'a>>
//pub (crate) fn regex_find<'a>(r : &Regex, s : &'a str) -> Option<pcre2::bytes::Match<'a>>
//pub (crate) fn regex_find<'a>(r : &Regex, s : &'a str) -> Option<regex::bytes::Match<'a>>
{
    //r.find(s.as_bytes())
    //r.find(s.as_bytes()).unwrap()
    r.find(s)
}
pub (crate) fn regex_is_match<'a>(r : &Regex, s : &'a str) -> bool
{
    //r.is_match(s.as_bytes())
    //r.is_match(s.as_bytes()).unwrap()
    r.is_match(s)
}


#[derive(Debug, Clone, Hash)]
pub (crate) struct K<T> {
    pub (crate) k : Rc<T>
}

impl<T : PartialEq> PartialEq for K<T> {
    fn eq(&self, other: &Self) -> bool {
        if Rc::as_ptr(&self.k) == Rc::as_ptr(&other.k) { return true; }
        self.k == other.k
    }
}
impl<T : Eq> Eq for K<T> { }

#[derive(Debug, Clone)]
pub struct RegexCacher {
    r : Regex,
    cache : Rc<RefCell<HashMap<K<String>, bool>>>,
    cache2 : Rc<RefCell<HashMap<u32, bool>>>,
}

impl RegexCacher {
    /// Wrap a Regex with a fast-path cache that checks if a given known input is already known.
    ///
    /// This is faster than whatever caching Regex does internally because of string interning.
    #[allow(unused)]
    pub fn new(r : Regex) -> RegexCacher
    {
        let cache = Rc::new(RefCell::new(HashMap::default()));
        let cache2 = Rc::new(RefCell::new(HashMap::default()));
        RegexCacher { r, cache, cache2 }
    }
    pub (crate) fn new_with_pool(r : Regex, cache_pool : &mut HashMap<String, (Rc<RefCell<HashMap<K<String>, bool>>>, Rc<RefCell<HashMap<u32, bool>>>)>) -> RegexCacher
    {
        let s = r.as_str().to_string();
        let mut cache = Rc::new(RefCell::new(HashMap::default()));
        let mut cache2 = Rc::new(RefCell::new(HashMap::default()));
        if let Some(cached) = cache_pool.get(&s)
        {
            cache = Rc::clone(&cached.0);
            cache2 = Rc::clone(&cached.1);
        }
        else
        {
            cache_pool.insert(s.clone(), (cache.clone(), cache2.clone()));
        }
        
        RegexCacher { r, cache, cache2 }
    }
    /// Does the regex match the string?
    pub fn is_match(&self, s : &Rc<String>) -> bool
    {
        let mut cache = self.cache.borrow_mut();
        let k = K { k : Rc::clone(s) };
        if let Some(result) = cache.get(&k) { return *result; }
        let ret = regex_is_match(&self.r, &*s);
        cache.insert(k, ret);
        ret
    }
    /// Does the regex match the string based on its interned ID? See also: [`Grammar::string_cache_inv`]
    pub fn is_match_interned(&self, i : u32, string_cache_inv : &Vec<Rc<String>>) -> bool
    {
        let mut cache = self.cache2.borrow_mut();
        if let Some(result) = cache.get(&i) { return *result; }
        let s = &string_cache_inv[i as usize];
        let ret = regex_is_match(&self.r, &*s);
        cache.insert(i, ret);
        ret
    }
}

#[derive(Default)]
/// Produced by [`bnf_to_grammar`].
///
/// Next step: [`tokenize`].
pub struct Grammar {
    /// Arena for all grammar points in the grammar.
    pub points: Vec<GrammarPoint>,
    /// Lookup table for grammar point IDs (indexes in the arena) by their name.
    pub by_name: HashMap<String, usize>,
    
    pub (crate) literals: Vec<String>,
    pub (crate) regexes: Vec<(Regex, RegexCacher)>,
    
    /// String interning cache: from string to interned ID.
    pub string_cache : HashMap<String, u32>,
    /// Inverse string interning cache. Index = string ID. The given `Rc<String>` is the canonical object for that interned string.
    pub string_cache_inv : Vec<Rc<String>>,
    
    pub (crate) bracket_pairs : Vec<(String, String)>,
    pub (crate) comments : Vec<String>,
    pub (crate) comment_pairs : Vec<(String, String)>,
    pub (crate) comment_pairs_nested : Vec<(String, String)>,
    pub (crate) comment_regexes : Vec<Regex>,
    pub (crate) reserved : Option<Regex>,
}

#[derive(Debug, Clone)]
/// A grammar rule.
/// 
/// More specifically, every production/alternation associated with a given name, in order. Alternations are stored and tested in the same order as written in the grammar.
pub struct GrammarPoint {
    /// Name of the grammar point (LHS).
    pub name: Rc<String>,
    /// ID of the grammar point (index in [`Grammar::points`]).
    pub name_id: u32,
    /// List of productions/alternations under this grammar point's LHS
    pub forms: Vec<Alternation>,
    pub (crate) recover: Option<(RegexCacher, bool)>,
}

#[derive(Debug, Clone)]
/// A particular production of a grammar rule.
///
/// Named "Alternation" because they're tested in order.
pub struct Alternation {
    /// List of terms, in order, for this alternation.
    pub matching_terms: Vec<MatchingTerm>,
    /// Does this alternation want terminals to be added to it, or dropped?
    pub (crate) pruned: bool,
}

#[derive(Debug, Clone)]
pub(crate) enum MatchDirective {
    Any, Become, BecomeAs, Hoist, HoistIfUnit, Drop, DropIfEmpty, Rename,
}

#[derive(Debug, Clone)]
/// Intentionally opaque for API stability reasons. Don't worry, it's just a single enum internally.
pub struct MatchingTerm { pub(crate) t : MatchingTermE }

#[derive(Debug, Clone)]
#[non_exhaustive]
pub(crate) enum MatchingTermE {
    Rule(usize),
    TermLit(u32),
    TermRegex(RegexCacher),
    Directive(MatchDirective),
    Hook(Rc<String>),
    _AutoTemp,
    
    Eof,
    Peek(isize, u32),
    PeekR(isize, RegexCacher),
    PeekRes(isize, RegexCacher),
    Guard(Rc<String>),
}
impl MatchingTermE { pub(crate) fn to(self) -> MatchingTerm { MatchingTerm { t : self } } }

/// Look up a string in the string interning cache.
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
/// Look up a string in the string interning cache, but skip the `Rc::clone()` overhead because we only need the ID.
pub fn string_cache_lookup_id(
    string_cache : &mut HashMap<String, u32>,
    string_cache_inv : &mut Vec<Rc<String>>,
    s : &str) -> u32
{
    if let Some(sn) = string_cache.get(s)
    {
        return *sn;
    }
    let rc = Rc::new(s.to_string());
    let n = string_cache_inv.len().try_into().unwrap();
    string_cache.insert(s.to_string(), n);
    string_cache_inv.push(rc);
    n
}

pub (crate) fn bnf_parse(input: &str) -> Result<Vec<(String, Vec<Vec<String>>)>, String>
{
    let mut rules = Vec::new();
    
    let mut metalist = Vec::new();
    let mut current = Vec::new();
    
    let mut name : Option<String> = None;
    let mut found_separator = false;
    
    let lines = input.lines().map(|x| x.to_string()).collect::<Vec<_>>();
    let mut lines2 : Vec<String> = vec!();
    for l in lines
    {
        if let Some(l0) = lines2.last_mut()
        {
            if l0.ends_with("\\")
            {
                *l0 = format!("{}{l}", &l0[..l0.len()-1]);
                continue;
            }
        }
        
        lines2.push(l);
    }
    for (mut linenum, rest) in lines2.iter().enumerate()
    {
        let mut rest : &str = rest;
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
            else if rest.starts_with("r`") || rest.starts_with("R`") || rest.starts_with("A`")
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

pub (crate) fn grammar_convert(input: &Vec<(String, Vec<Vec<String>>)>) -> Result<Grammar, String>
{
    let mut by_name = HashMap::default();
    for (name, _) in input.iter()
    {
        if matches!(&**name, "__BRACKET_PAIRS" | "__COMMENT_PAIRS" | "__COMMENT_PAIRS_NESTED" | "__COMMENT_REGEXES" | "__COMMENTS" | "__RESERVED_WORDS") { continue; }
        if by_name.insert(name.clone(), by_name.len()).is_some()
        {
            return Err(format!("Duplicate rule {name}; use alternations (e.g. x ::= a | b), not additional definitions (like x ::= a [...] x ::= b)"));
        }
    }
    
    let mut string_cache = HashMap::default();
    let mut string_cache_inv = Vec::new();
    let mut points = Vec::new();
    let mut literals = HashSet::default();
    let mut lex_regexes = HashMap::default();
    
    let mut bracket_pairs = Vec::new();
    let mut comment_pairs = Vec::new();
    let mut comment_pairs_nested = Vec::new();
    let mut comment_regexes = Vec::new();
    let mut comments = Vec::new();
    
    let mut cache_pool = HashMap::<String, _>::default();
    
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
        if name == "__BRACKET_PAIRS" || name == "__COMMENT_PAIRS" || name == "__COMMENT_PAIRS_NESTED"
        {
            for raw_alt in raw_forms
            {
                match (raw_alt.get(0), raw_alt.get(1))
                {
                    (Some(l), Some(r)) =>
                    {
                        if name == "__BRACKET_PAIRS" { bracket_pairs.push((l.clone(), r.clone())); }
                        if name == "__COMMENT_PAIRS" { comment_pairs.push((l.clone(), r.clone())); }
                        if name == "__COMMENT_PAIRS_NESTED" { comment_pairs_nested.push((l.clone(), r.clone())); }
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
                    let re = new_regex(&pattern).map_err(|e| format!("Invalid regex '{}': {}", pattern, e))?;
                    comment_regexes.push(re);
                }
                if name == "__COMMENTS" && s.starts_with("\"") && s.ends_with("\"") && s.len() >= 3
                {
                    let pattern = &s[1..s.len() - 1];
                    comments.push(pattern.to_string());
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
            let mut pruned = false;
            
            let mut i = 0;
            while i < raw_alt.len()
            {
                let term_str = &raw_alt[i];
                i += 1;
                
                if term_str.starts_with('"') && term_str.ends_with('"') && term_str.len() >= 2
                {
                    let literal = term_str[1..term_str.len() - 1].replace("\\\"", "\"").replace("\\\\", "\\").replace("\\n", "\n");
                    matching_terms.push(MatchingTermE::TermLit(string_cache_lookup_id(&mut string_cache, &mut string_cache_inv, &literal)).to());
                    
                    literals.insert(literal.clone());
                    continue;
                }
                if term_str.starts_with("r`") && term_str.ends_with("`r") && term_str.len() >= 4
                {
                    let pattern = &term_str[2..term_str.len() - 2];
                    let pattern_all = format!("\\A(?:{pattern})\\z"); // full match (for parsing)
                    let pattern = format!("\\A(?:{pattern})"); // at start (for tokenization)
                    let re2 = new_regex(&pattern_all).map_err(|e| format!("Invalid regex '{}': {}", pattern_all, e))?;
                    let re2 = RegexCacher::new_with_pool(re2, &mut cache_pool);
                    lex_regexes.insert(pattern, re2.clone());
                    matching_terms.push(MatchingTermE::TermRegex(re2).to());
                    continue;
                }
                // non-tokenizing regex (optimization: hide redundant regexes from the tokenizer)
                if term_str.starts_with("R`") && term_str.ends_with("`r") && term_str.len() >= 4
                {
                    let pattern = &term_str[2..term_str.len() - 2];
                    let pattern_all = format!("\\A(?:{pattern})\\z"); // full match (for parsing)
                    let re2 = new_regex(&pattern_all).map_err(|e| format!("Invalid regex '{}': {}", pattern_all, e))?;
                    matching_terms.push(MatchingTermE::TermRegex(RegexCacher::new_with_pool(re2, &mut cache_pool)).to());
                    continue;
                }
                if term_str.starts_with("A`") && term_str.ends_with("`r") && term_str.len() >= 4
                {
                    let pattern = &term_str[2..term_str.len() - 2];
                    let pattern_all = format!("\\A(?:{pattern})");
                    let re2 = new_regex(&pattern_all).map_err(|e| format!("Invalid regex '{}': {}", pattern_all, e))?;
                    matching_terms.push(MatchingTermE::TermRegex(RegexCacher::new_with_pool(re2, &mut cache_pool)).to());
                    continue;
                }
                if matches!(&**term_str, "@RECOVER" | "@recover" | "@RECOVER_BEFORE" | "@recover_before") && i < raw_alt.len()
                {
                    let pattern = &raw_alt[i];
                    if !(pattern.starts_with("r`") || pattern.starts_with("R`") || pattern.starts_with("A`"))
                        || !pattern.ends_with("`r")
                    {
                        Err(format!("@recover guards only accept regex strings"))?
                    }
                    let no_z = pattern.starts_with("A`");
                    let pattern = &pattern[2..pattern.len() - 2];
                    let mut pattern_all = format!("\\A(?:{})\\z", pattern);
                    if no_z { pattern_all = format!("\\A(?:{})", pattern); }
                    let re2 = new_regex(&pattern_all).map_err(|e| format!("Invalid regex '{}': {}", pattern_all, e))?;
                    // TODO: make regex cachers use interior mutability and share the cache
                    if recover.is_some() { Err(format!("Rule {name} has multiple @recover items. Only one is supported."))? }
                    recover = Some((RegexCacher::new_with_pool(re2, &mut cache_pool), matches!(&**term_str, "@RECOVER" | "@recover")));
                    i += 1;
                    continue;
                }
                if matches!(&**term_str, "@EOF" | "@eof")
                {
                    matching_terms.push(MatchingTermE::Eof.to());
                    continue;
                }
                if matches!(&**term_str, "@AUTO" | "@auto")
                {
                    matching_terms.push(MatchingTermE::_AutoTemp.to());
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
                        let s = string_cache_lookup_id(&mut string_cache, &mut string_cache_inv, &literal);
                        matching_terms.push(MatchingTermE::Peek(n, s).to());
                    }
                    else
                    {
                        let pattern = &raw_alt[i+3];
                        if !(pattern.starts_with("r`") || pattern.starts_with("R`") || pattern.starts_with("A`"))
                            || !pattern.ends_with("`r")
                        {
                            Err(format!("@recover guards only accept regex strings"))?
                        }
                        let no_z = pattern.starts_with("A`");
                        let pattern = &pattern[2..pattern.len() - 2];
                        let mut pattern_all = format!("\\A(?:{})\\z", pattern);
                        if no_z { pattern_all = format!("\\A(?:{})", pattern); }
                        
                        let re2 = new_regex(&pattern_all).map_err(|e| format!("Invalid regex '{}': {}", pattern_all, e))?;
                        // TODO: make regex cachers use interior mutability and share the cache
                        if term_str == "@PEEKRES" || term_str == "@peekres"
                        {
                            matching_terms.push(MatchingTermE::PeekRes(n, RegexCacher::new_with_pool(re2, &mut cache_pool)).to());
                        }
                        else
                        {
                            matching_terms.push(MatchingTermE::PeekR(n, RegexCacher::new_with_pool(re2, &mut cache_pool)).to());
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
                    matching_terms.push(MatchingTermE::Guard(s).to());
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
                    matching_terms.push(MatchingTermE::Hook(s).to());
                    i += 3;
                    continue;
                }
                if matches!(&**term_str, "$BECOME" | "$become")
                {
                    matching_terms.push(MatchingTermE::Directive(MatchDirective::Become).to());
                    continue;
                }
                if matches!(&**term_str, "$BECOME_AS" | "$become_as")
                {
                    matching_terms.push(MatchingTermE::Directive(MatchDirective::BecomeAs).to());
                    continue;
                }
                if matches!(&**term_str, "$HOIST" | "$hoist")
                {
                    matching_terms.push(MatchingTermE::Directive(MatchDirective::Hoist).to());
                    continue;
                }
                if matches!(&**term_str, "$HOIST_UNIT" | "$hoist_unit")
                {
                    matching_terms.push(MatchingTermE::Directive(MatchDirective::HoistIfUnit).to());
                    continue;
                }
                if matches!(&**term_str, "$DROP" | "$drop")
                {
                    matching_terms.push(MatchingTermE::Directive(MatchDirective::Drop).to());
                    continue;
                }
                if matches!(&**term_str, "$DROP_EMPTY" | "$drop_empty")
                {
                    matching_terms.push(MatchingTermE::Directive(MatchDirective::DropIfEmpty).to());
                    continue;
                }
                if matches!(&**term_str, "$RENAME" | "$rename")
                {
                    matching_terms.push(MatchingTermE::Directive(MatchDirective::Rename).to());
                    continue;
                }
                if matches!(&**term_str, "$ANY" | "$any")
                {
                    matching_terms.push(MatchingTermE::Directive(MatchDirective::Any).to());
                    continue;
                }
                if matches!(&**term_str, "$PRUNED" | "$pruned")
                {
                    pruned = true;
                    continue;
                }
                let id = by_name.get(term_str).ok_or_else(|| format!("Not a defined grammar rule: '{term_str}' (context: '{name}')"))?;
                matching_terms.push(MatchingTermE::Rule(*id).to());
            }
            if matching_terms.len() > 60000
            {
                Err(format!("More than 60k items in an alternation of {name}. Factor them out, dummy!"))?
            }
            if let Some(MatchingTermE::_AutoTemp) = matching_terms.get(0).map(|x| &x.t)
            {
                match matching_terms.get(1).map(|x| &x.t)
                {
                    Some(MatchingTermE::TermLit(s)) =>
                    {
                        matching_terms[0] = MatchingTermE::Peek(0, *s).to();
                        matching_terms[1] = MatchingTermE::Directive(MatchDirective::Any).to();
                    }
                    Some(MatchingTermE::TermRegex(r)) =>
                    {
                        let r = r.clone();
                        matching_terms[0] = MatchingTermE::PeekR(0, r).to();
                        matching_terms[1] = MatchingTermE::Directive(MatchDirective::Any).to();
                    }
                    _ => Err(format!("@auto must be followed by a string literal or regex literal (context: {name})"))?
                }
            }
            // TODO: check for illegally-placed become, becomeas, hoist
            forms.push(Alternation { matching_terms, pruned });
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
                && matches!(x.t, MatchingTermE::Peek(_, _) | MatchingTermE::PeekR(_, _) | MatchingTermE::Guard(_) | MatchingTermE::Eof) { true } else { false })
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
    for (r, r2) in lex_regexes
    {
        regexes.push((new_regex(&r).map_err(|e| format!("Invalid regex '{}': {}", r, e))?, r2));
    }
    Ok(Grammar { points, by_name, literals, regexes, string_cache, string_cache_inv, bracket_pairs, comments, comment_pairs, comment_regexes, reserved, comment_pairs_nested })
}

/// Turns a BNF string into a [`Grammar`]. See the comments at [the crate root](super) for syntax notes. The basic parts are standard BNF.
///
/// Next step: [`tokenize`].
pub fn bnf_to_grammar(s : &str) -> Result<Grammar, String>
{
    grammar_convert(&bnf_parse(s)?)
}

#[derive(Debug, Clone, Default)]
/// Produced by [`tokenize`].
///
/// Next step: [`ast::parse`](`super::ast::parse`).
pub struct Token {
    /// Interned string ID, see [`Grammar::string_cache_inv`]
    pub text : u32,
    /// For bracket pairs: how far away, in which direction, is the paired bracket? In terms of tokens.
    pub pair : isize,
}

// Sort literals from grammar by length and combine them into a single match-longest regex.
pub (crate) fn build_literal_regex(literals : &Vec<String>, terminated : bool) -> Regex
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
    let text_token_regex = new_regex(&text_token_regex_s).unwrap();
    text_token_regex
}

/// Tokenizer error state.
#[derive(Clone, Debug)]
pub struct TokError {
    /// Human-readable error message. Format is not guaranteed and may change arbitrarily.
    #[allow(unused)] pub err_message : String,
    /// Number of tokens produced so far.
    #[allow(unused)] pub produced : usize,
    /// At what byte index in the input string did tokenization fail to continue?
    #[allow(unused)] pub location : usize,
    /// Is `Some` if tokenization failed because of failing to pair brackets:
    ///
    /// - `String`: responsible token text
    /// - `bool`: openness
    ///
    /// If the bool is true, then the failed pairing is "open", like the string `()(`. Otherwise, it's "closed", like `())`.
    ///
    /// The responsible token is the token where the error was noticed, not the token that's "missing". E.g. for `())` it's `")"`.
    ///
    /// It is currently unspecified whether non-nested overlaps like `( { ) }` trigger an error.
    ///
    /// KNOWN BUG: "open" failed pairings like `()(` do not currently produce errors. They will become errors in a future version.
    #[allow(unused)] pub pairing_error : Option<(String, bool)>,
}

/// Scans the given string and produces a stream of [`Token`]s.
///
/// Next step: [`ast::parse`](`super::ast::parse`).
///
/// The scanner performs maximal munch between all string literals and r``r terminals in the grammar. It also skips whitespace, and comments (as defined in the grammar). The produced tokens use string interning and can be bracket-paired. See [the crate root](super) for more details.
pub fn tokenize(
    g : &mut Grammar,
    mut s : &str
) -> Result<Vec<Token>, TokError>
{
    let s_orig = s;
    let mut tokens = Vec::<Token>::new();
    tokens.reserve(s.len()/16 + 1);
    
    let mut lit_filtered = Vec::new();
    for l in g.literals.iter()
    {
        let mut covered = false;
        for r in &g.regexes
        {
            if let Some(loc) = regex_find(&r.0, l).map(|x| x.end() - x.start())
            {
                if loc == l.len()
                {
                    covered = true;
                    break;
                }
            }
        }
        if !covered
        {
            lit_filtered.push(l.clone());
        }
    }
    let all_literals_regex = if lit_filtered.len() > 0
    {
        Some(build_literal_regex(&lit_filtered, false))
    }
    else
    {
        None
    };
    //println!("{}", all_literals_regex);
    
    for text in g.literals.iter()
    {
        string_cache_lookup_id(&mut g.string_cache, &mut g.string_cache_inv, text);
    }
    for point in g.points.iter()
    {
        string_cache_lookup_id(&mut g.string_cache, &mut g.string_cache_inv, &point.name);
    }
    
    let mut openers = HashSet::default();
    let mut closers = HashMap::default();
    let mut stacks = HashMap::default();
    let mut any_paired = false;
    for (l, r) in &g.bracket_pairs
    {
        let lsc = string_cache_lookup_id(&mut g.string_cache, &mut g.string_cache_inv, &l);
        let rsc = string_cache_lookup_id(&mut g.string_cache, &mut g.string_cache_inv, &r);
        openers.insert(lsc);
        closers.insert(rsc, lsc);
        stacks.insert(lsc, Vec::<usize>::new());
        any_paired = true;
    }
    
    /*
    println!("num regexes to check: {}", g.regexes.len());
    for r in &g.regexes
    {
        println!("{:?}", r.as_str());
    }
    */
    
    'top: while !s.is_empty()
    {
        if get_char_at_byte(s, 0) as u32 <= 0x20
        {
            if matches!(get_char_at_byte(s, 0), ' ' | '\r' | '\n' | '\t')
            {
                while !s.is_empty() && matches!(get_char_at_byte(s, 0), ' ' | '\r' | '\n' | '\t')
                {
                    s = &s[1..]; // ascii whitespace is always 1 byte long
                }
                if s.is_empty() { break; }
                continue 'top;
            }
        }
        
        // Pure regex comments
        for re in &g.comment_regexes
        {
            if let Some(x) = regex_find(re, s)
            {
                //s = &s[x.len()..];
                s = &s[x.end() - x.start()..];
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
                    if s.len() > 0
                    {
                        s = &s[get_char_at_byte(s, 0).len_utf8()..];
                    }
                }
                continue 'top;
            }
        }
        // Pair comments with nesting
        for (l, r) in &g.comment_pairs_nested
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
        // Pair comments without nesting
        for (l, r) in &g.comment_pairs
        {
            if s.starts_with(l)
            {
                s = &s[l.len()..];
                while s.len() > 0 && !s.starts_with(r)
                {
                    s = &s[get_char_at_byte(s, 0).len_utf8()..];
                }
                s = &s[r.len()..];
                continue 'top;
            }
        }
        // Maximal munch: Regex pass
        let mut longest = 0;
        //let mut found_regex = None;
        for r in &g.regexes
        {
            if let Some(loc) = regex_find(&r.0, s)
            {
                let len = loc.end() - loc.start();
                //found_regex = Some(&r.1);
                longest = longest.max(len);
            }
        }
        // Literals pass.
        if let Some(all_literals_regex) = &all_literals_regex && let Some(loc) = regex_find(&all_literals_regex, s)
        {
            let len = loc.end() - loc.start();
            //found_regex = None;
            longest = longest.max(len);
        }
        if longest == 0
        {
            let sn : String = s.chars().take(5).collect();
            return Err(TokError {
                err_message: format!("Failed to tokenize at index {}:{}[...]", s_orig.len()-s.len(), sn),
                produced : tokens.len(),
                location : s_orig.len() - s.len(),
                pairing_error : None,
            });
        }
        
        //let text_info = string_cache_lookup(&mut g.string_cache, &mut g.string_cache_inv, &s[..longest]);
        //let text = text_info.1;
        let text = string_cache_lookup_id(&mut g.string_cache, &mut g.string_cache_inv, &s[..longest]);
        let mut token = Token { text, pair : 0 };
        
        /*
        if let Some(r2) = found_regex
        {
            r2.cache2.borrow_mut().insert(text, true);
            r2.cache.borrow_mut().insert(text_info.0, true);
        }
        */
        
        if any_paired
        {
            if openers.contains(&text) && let Some(s) = stacks.get_mut(&text)
            {
                s.push(tokens.len());
            }
            if let Some(l) = closers.get(&text) && let Some(stack) = stacks.get_mut(l)
            {
                let n = match stack.pop() {
                    Some(n) => n,
                    None => Err(TokError {
                        err_message: format!("Unmatched delimiter at {}: {}", s_orig.len() - s.len(), g.string_cache_inv.get(text as usize).unwrap()),
                        produced : tokens.len(),
                        location : s_orig.len() - s.len(),
                        pairing_error : Some((s[..longest].to_string(), false)),
                    })?,
                };
                //.ok_or_else(|| )?;
                
                let me = tokens.len();
                let diff = match me.checked_signed_diff(n) {
                    Some(n) => n,
                    None => Err(TokError {
                        err_message: format!("Input too long"),
                        produced : tokens.len(),
                        location : s_orig.len() - s.len(),
                        pairing_error : None,
                    })?,
                };
                token.pair = -diff;
                tokens[n].pair = diff;
            }
        }
        
        s = &s[longest..];
        tokens.push(token);
    }
    Ok(tokens)
}
