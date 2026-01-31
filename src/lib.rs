//! # Predicated Recursive Descent
//! 
//! aka pred recdec
//! 
//! It is **VERY HIGHLY RECOMMENDED** that you use the mimalloc crate (or some other high-performance memory allocator) if you use this library:
//!
//! ```rust
//! use mimalloc::MiMalloc;
//! #[global_allocator]
//! static GLOBAL: MiMalloc = MiMalloc;
//! ```
//!
//! You want:
//! - [bnf::bnf_to_grammar]
//! - [bnf::Grammar]
//! - [bnf::tokenize]
//! - [bnf::Token]
//! - [ast::ASTNode]
//! - [ast::parse]
//! 
//! This library provides a way to write and run [BNF](https://en.wikipedia.org/wiki/Backus–Naur_form) grammars with annotations that make them behave like a handwritten recursive descent parser.
//!
//! The structure of the BNF corresponds to the structure of the resulting ASTs. Tokenization is handled automatically; you do not need to write a lexical grammar. The tokenizer handles comments, whitespace, maximal munch, and even regex tests. Unless you're trying to do something silly like how Lua uses context-sensitive long brackets for comments, that's all you need.
//! 
//! The resulting parser is scannerful but tolerant of soft keywords. It performs no memoization or backtracking. Impure hooks are safe. There's no lookahead generation or guessing: the parser only does exactly what you specify in the BNF, in order.
//! 
//! This is strong enough to parse C. Yes, the language with the super horrible grammar that needs arbitrary lookahead and state munging to parse correctly.
//! 
//! This is *not* a PEG or packrat thing.
//!
//! Performance: varies between 50% and 400% slower than a native machine code handwritten parser. For more complex grammars, the performance loss is less. Totally usable!
//! 
//! Simple example (totally not lisp), capable of parsing the input `(a b (q x)kfwaiei i  9 (af0f1a) () () )`:
//! 
//! ```text
//! S ::= @peek(0, "(") parenexpr
//! parenexpr ::=
//!     @peek(1, ")") "(" ")"
//!     | "(" itemlist ")"
//! itemlist ::=
//!     @peek(0, ")") #end of list
//!     | item $become itemlist
//! item ::=
//!     @peek(0, "(") parenexpr
//!     | @auto r`[a-zA-Z_][a-zA-Z_0-9]*|[0-9\.]*`r
//! ```
//!
//! ## Example usage
//!
//! ```rust
//! let mut g = bnf_to_grammar(&grammar_source).unwrap();
//! let tokens = tokenize(&mut g, &test_source);
//! let tokens = tokens.unwrap();
//! 
//! use std::rc::Rc;
//! let ast = parse(&g,
//!     "S", // Name of your root-most rule
//!     &tokens[..],
//!     Rc::new(<_>::default()), // guards (see test in `src/c.rs` for a detailed usage example)
//!     Rc::new(<_>::default()) // hooks (same)
//! );
//! 
//! if let Ok(ast) = &ast
//! {
//!     print_ast_pred_recdec(ast, &g.string_cache_inv, 0);
//! }
//! drop(ast.unwrap());
//! ```
//!
//! ## BNF Extensions
//!
//! Mini glossary: nonterminal = "call of another rule", terminal = "immediate match of a token's contents".
//!
//! Common EBNF syntax like `[]` or `()?` is not supported. Don't worry, you can make flat lists just fine.
//! 
//! Extensions from pure BNF are:
//! 
//! `\` - End-of-line escaping with `\`, so you can write multiline regexes.
//!
//! `#` - Comments until the end of the line, outside of strings/regexes.
//!
//! `"...` - Terms starting with `"` are inline strings. They register with the tokenizer and check the entire body of a token. (Strings are interned, so this is O(1).)
//! 
//! Terms starting with ```r`...```, ```R`...```, or ```A`...``` are inline regexes:
//! - ```r`...`r``` registers with the tokenizer and does a full token match (i.e. it's given an implicit trailing `\z` during token matching).
//! - ```R`...`r``` DOES NOT register with the tokenizer, but does a full token match (i.e. it's given an implicit trailing `\z`). This is provided as an optimization: sometimes you want to combine tokenizer regexes into a single regex for performance reasons, which should be done manually.
//! - ```A`...`r``` DOES NOT register with the tokenizer, and only checks against the start of the token. This is only provided as an optimization: ```R``r``` is strictly more powerful.
//!
//! Regex results are cached, so checking them is amortized O(1).
//!
//! Terms beginning with `!` currently only have one kind:
//! - `!hook`, e.g. `!hook(fix_infix_expr)`, are calls to user-provided code. This is **allow to be impure**, e.g. management of **typedef symbol tables**.
//!
//! Terms beginning with `@` are guards/predicates. They determine, at the start of a given alternation/production, whether it is valid. If true, that production is taken, and none of the others will be attempted (at this location). Remember, there's no backtracking or magic.
//! - `@peek(N, STRING)` - Checks if, relative to the parse position, the given token contains the given text.
//! - `@peekr(N, REGEX)` - Same, but only for regexes.
//! - `@auto item` - Desugars to `@peek(0, item) item` or `@peekr(0, item) item` automatically.
//! - `@guard(name)` - Calls user-provided code to determine if the production is accepted.
//! - `@recover` - Pseudo-guard, is never attempted. Instead, it tells the associated grammar rule that if it fails, it's allowed to recover (into a poisoned state) by seeking for a particular set of tokens.
//! - `@recover_before` - Same, but stops right before accepting any seek token instead of consuming it.
//! 
//! Terms starting with `$` are directives:
//! - `$become nonterminal` performs a tail call, keeping the current AST node name. This can be used to build lists without smashing the stack.
//! - `$become_as nonterminal` performs a tail call, replacing the current AST node's name with that of the target.
//! - `$any` matches and includes any one token as a terminal.
//! - `$pruned` specifies that this particular production doesn't generate AST nodes for bare terminals. This is useful for reducing AST bloat. For example, `@peek(1, ")") "(" ")" $pruned` is a non-empty production but produces zero AST nodes.
//! - TODO: `$hoist`, `$drop`, `$dropifempty`, `$rename`
//! 
//! You'll note that there's no "negative rule-match-check predicate" extension (e.g. no "parse A, but only if it doesn't also parse B"). This is by design. Rule-level negation is way too powerful, and requires an extremely sophisticated parser generator (e.g. packrat) to handle properly. For any reasonably simple implementation, it would be incompatible with impure hooks. `__RESERVED_WORDS`, described below, is the only exception, because it's easy to define in a sane way.
//!
//! For negative token predicates (peeks), you can refactor the grammar slightly, or if it's a particularly complicated peek, write a custom guard. So this isn't a limitation.
//!
//! ## Magic pseudo-rules
//!
//! The following magic pseudo rule names are available (e.g. `__COMMENTS ::= //`):
//!
//! - `__BRACKET_PAIRS` e.g. `::= ( ) | { }` - Tell the tokenizer to pair-up these tokens with each other so that hooks can skip over their contents in O(1) time.
//! - `__COMMENTS` e.g. `::= "//" | "#"` -- Tell the tokenizer that this is a kind of single-line comment.
//! - `__COMMENT_PAIRS` e.g. `::= /* */` - Tell the tokenizer that this is a kind of pair-based comment.
//! - `__COMMENT_PAIRS_NESTED` - Same, but nesting, like in Rust.
//! - `__COMMENT_REGEXES` - Same, but formed as a regex. These are slower than the above, because the Rust `regex` crate doesn't have a JIT.
//! - `__RESERVED_WORDS` - e.g. `::= auto break case` - Specifies a list of token contents that are not allowed to be "accepted" by regex terminals like ```r`[a-zA-Z_]+`r```

pub mod bnf;
pub mod ast;
mod json;
mod c;

// Thing
pub (crate) use rustc_hash::FxBuildHasher as HashBuilder;

#[cfg(test)]
mod test {
    #[test]
    fn test_lib() {
        use crate::*;
        pub use bnf::*;
        pub use ast::*;
        
        let grammar_source = r#"
    S ::= @peek(0, "(") parenexpr
    parenexpr ::=
        @peek(1, ")") "(" ")" $pruned
        | "(" $become itemlist $pruned
    itemlist ::=
        @peek(0, ")") $pruned ")"
        | @peek(0, "(") parenexpr $become itemlist
        | @auto r`[a-zA-Z_][a-zA-Z_0-9]*|[0-9\.]*`r $become itemlist
        "#;
        
        let test_source = r#"
        (a b (q x)kfwaiei i  9 (af0f1a) () () )
        "#;
        
        let mut g = bnf_to_grammar(&grammar_source).unwrap();
        let tokens = tokenize(&mut g, &test_source);
        let tokens = tokens.unwrap();
        
        use std::rc::Rc;
        let ast = parse(&g, "S", &tokens[..], Rc::new(<_>::default()), Rc::new(<_>::default()));
        
        if let Ok(ast) = &ast
        {
            print_ast_pred_recdec(ast, &g.string_cache_inv, 0);
        }
        drop(ast.unwrap());
    }
}