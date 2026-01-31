
## Pred Recdec

Predicated recursive descent parsing framework. Write 90% of your grammar in plain BNF, skip the boilerplate, and write the remaining 10% as hooks. Supports most slightly context-sensitive grammars, including typedefs. Basic lookahead and "optimized tail calls" are built in, so you don't have to add hooks for super basic LL(k) functionality, just write the peek statements. This mirrors how most high-performance parsers are written today, just in a BNF shell.

As soft proof, I wrote a working C99 grammar (src/grammar.txt). It successfully parses the preprocessor output of both gcc and clang `#include`-ing a kitchen sink worth of stdlib headers.

**Performance**: Roughly the same parsing time as Clang and GCC `-fsyntax-only -ftime-report` on a 5.6MB C source file, tested with the included grammar (src/grammar.txt).

Features:

- BNF syntax and automatic AST contruction: keep your grammar low-boilerplate
- Legible, easy-to-learn non-BNF parts
- Fully safe support for dirty parsing hooks like the "typedef" hack, etc
- Error recovery support (@recover, @recover_before)
- Built-in tokenizer that doesn't choke on "soft keywords"
- Built-in comment handling, both nested and non-nested comments
- Always perfect linear O(n) parse time unless you specifically write a worse-than-linear hook yourself
- Support for "optimized tail calls" and LR-like "reductions" with $become and $become_as (respectively)

The last point is interesting. It makes the core BNF functionality slightly stronger than LL(k), because left factoring no longer breaks the structure of the grammar. Maybe something like "Immediate Decision Grammar".

This lets you write a "grammar" that has the same capabilities as a handwritten recursive descent parser. You can do computations on lookahead, skip around brackets and braces, update and query symbol tables, etc. There's no risk of backtracking (unless you do so yourself inside of a hook), so you can make your hooks as impure and stateful as you want. The tokenizer is non-lexing, meaning that it doesn't assign lexical identities to tokens and only performs the maximal munch step and creates a token stream, so you don't need to worry about writing a lexical grammar or avoiding lexical ambiguity; it's handled automatically based on what literals and regexes you use in the grammar.

Keeping as much in BNF as possible leaves the easy 90% of your grammar in a highly maintainable format, makes it easier to change technologies or languages, and makes it much simpler to write verification or testing rigs. The way that non-BNF extensions are written in the BNF is "you can learn it by looking at examples" instead of being symbol stew.

Currently a prototype. Actually works, but not finished. Example grammar snippets:

JSON grammar (you should use a "real" parser like serde_json, I only wrote a JSON grammar because it's a good example):
```r
# Predicated Recursive Descent grammar for JSON
# Simpler, slightly slower version
# Passes all of the parsing tests in https://github.com/nst/JSONTestSuite
json ::= element $become EOF
EOF ::= @eof

element ::=
   @peek(0, "{") object | @peek(0, "[") array
   # A``r regex strings match any token that starts with the contained regex
   | @peekr(0, A`"`r) string
   | @auto "true" | @auto "false" | @auto "null"
   | number

object ::= @peek(1, "}") "{" "}" | "{" members "}"
members ::= member $become memberlist
memberlist ::= @auto "," member $become memberlist | #empty
member ::= string ":" element

array ::= @peek(1, "]") "[" "]" | "[" elements "]"
# Lookahead/predicates are necessary for any non-final alternation. Alternations are attempted in order, and never backtracked/memoized.
# Example: this would never attempt to match the "elements" production: array ::= "[" "]" | "[" elements "]"

elements ::= element $become elementlist
elementlist ::= @auto "," element $become elementlist | #empty
# NOTE: #empty is just a comment. It's not a magical way of writing epsilons.

# r``r regex strings both perform a match test at parse time (cached) and Also register themselves with the tokenizer.
# R``r do the same, but WITHOUT registering themselves with the tokenizer. A``r also do not register with the tokenizer.
string ::= r`"(?:[ !#-\[\]-\u{10ffff}]|\\["\\\/bfnrt]|\\u[a-fA-F0-9]{4})*"`r
number ::= r`[-]?(?:[1-9][0-9]+|[0-9])(?:\.[0-9]+)?(?:[eE][-+]?[0-9]+)?`r
```

## Mini documentation

aka pred recdec

It is **VERY HIGHLY RECOMMENDED** that you use the mimalloc crate (or some other high-performance memory allocator) if you use this library:

```rust
use mimalloc::MiMalloc;
#[global_allocator]
static GLOBAL: MiMalloc = MiMalloc;
```

You want:
- [bnf::bnf_to_grammar]
- [bnf::Grammar]
- [bnf::tokenize]
- [bnf::Token]
- [ast::ASTNode]
- [ast::parse]

This library provides a way to write and run [BNF](https://en.wikipedia.org/wiki/Backus–Naur_form) grammars with annotations that make them behave like a handwritten recursive descent parser.

The structure of the BNF corresponds to the structure of the resulting ASTs. Tokenization is handled automatically; you do not need to write a lexical grammar. The tokenizer handles comments, whitespace, maximal munch, and even regex tests. Unless you're trying to do something silly like how Lua uses context-sensitive long brackets for comments, that's all you need.

The resulting parser is scannerful but tolerant of soft keywords. It performs no memoization or backtracking. Impure hooks are safe. There's no lookahead generation or guessing: the parser only does exactly what you specify in the BNF, in order.

This is strong enough to parse C. Yes, the language with the super horrible grammar that needs arbitrary lookahead and state munging to parse correctly.

This is *not* a PEG or packrat thing.

Performance: varies between 50% and 400% slower than a native machine code handwritten parser. For more complex grammars, the performance loss is less. Totally usable!

Simple example (totally not lisp), capable of parsing the input `(a b (q x)kfwaiei i  9 (af0f1a) () () )`:

```text
S ::= @peek(0, "(") parenexpr
parenexpr ::=
    @peek(1, ")") "(" ")"
    | "(" itemlist ")"
itemlist ::=
    @peek(0, ")") #end of list
    | item $become itemlist
item ::=
    @peek(0, "(") parenexpr
    | @auto r`[a-zA-Z_][a-zA-Z_0-9]*|[0-9\.]*`r
```

## Example usage

```rust
let mut g = bnf_to_grammar(&grammar_source).unwrap();
let tokens = tokenize(&mut g, &test_source);
let tokens = tokens.unwrap();

use std::rc::Rc;
let ast = parse(&g,
    "S", // Name of your root-most rule
    &tokens[..],
    Rc::new(<_>::default()), // guards (see test in `src/c.rs` for a detailed usage example)
    Rc::new(<_>::default()) // hooks (same)
);

if let Ok(ast) = &ast
{
    print_ast_pred_recdec(ast, &g.string_cache_inv, 0);
}
drop(ast.unwrap());
```

## BNF Extensions

Mini glossary: nonterminal = "call of another rule", terminal = "immediate match of a token's contents".

Common EBNF syntax like `[]` or `()?` is not supported. Don't worry, you can make flat lists just fine.

Extensions from pure BNF are:

`\` - End-of-line escaping with `\`, so you can write multiline regexes.

`#` - Comments until the end of the line, outside of strings/regexes.

`"...` - Terms starting with `"` are inline strings. They register with the tokenizer and check the entire body of a token. (Strings are interned, so this is O(1).)

Terms starting with ```r`...```, ```R`...```, or ```A`...``` are inline regexes:
- ```r`...`r``` registers with the tokenizer and does a full token match (i.e. it's given an implicit trailing `\z` during token matching).
- ```R`...`r``` DOES NOT register with the tokenizer, but does a full token match (i.e. it's given an implicit trailing `\z`). This is provided as an optimization: sometimes you want to combine tokenizer regexes into a single regex for performance reasons, which should be done manually.
- ```A`...`r``` DOES NOT register with the tokenizer, and only checks against the start of the token. This is only provided as an optimization: ```R``r``` is strictly more powerful.

Regex results are cached, so checking them is amortized O(1).

Terms beginning with `!` currently only have one kind:
- `!hook`, e.g. `!hook(fix_infix_expr)`, are calls to user-provided code. This is **allow to be impure**, e.g. management of **typedef symbol tables**.

Terms beginning with `@` are guards/predicates. They determine, at the start of a given alternation/production, whether it is valid. If true, that production is taken, and none of the others will be attempted (at this location). Remember, there's no backtracking or magic.
- `@peek(N, STRING)` - Checks if, relative to the parse position, the given token contains the given text.
- `@peekr(N, REGEX)` - Same, but only for regexes.
- `@auto item` - Desugars to `@peek(0, item) item` or `@peekr(0, item) item` automatically.
- `@guard(name)` - Calls user-provided code to determine if the production is accepted.
- `@recover` - Pseudo-guard, is never attempted. Instead, it tells the associated grammar rule that if it fails, it's allowed to recover (into a poisoned state) by seeking for a particular set of tokens.
- `@recover_before` - Same, but stops right before accepting any seek token instead of consuming it.

Terms starting with `$` are directives:
- `$become nonterminal` performs a tail call, keeping the current AST node name. This can be used to build lists without smashing the stack.
- `$become_as nonterminal` performs a tail call, replacing the current AST node's name with that of the target.
- `$any` matches and includes any one token as a terminal.
- `$pruned` specifies that this particular production doesn't generate AST nodes for bare terminals. This is useful for reducing AST bloat. For example, `@peek(1, ")") "(" ")" $pruned` is a non-empty production but produces zero AST nodes.
- TODO: `$hoist`, `$drop`, `$dropifempty`, `$rename`

You'll note that there's no "negative predicate" extension. This is by design. Negation is way too powerful, and requires an extremely sophisticated parser generator (e.g. packrat) to handle properly. For any reasonably simple implementation, it would be incompatible with impure hooks. `__RESERVED_WORDS`, described below, is the only exception, because it's easy to define in a sane way.

## Magic pseudo-rules

The following magic pseudo rule names are available (e.g. `__COMMENTS ::= //`):

- `__BRACKET_PAIRS` e.g. `::= ( ) | { }` - Tell the tokenizer to pair-up these tokens with each other so that hooks can skip over their contents in O(1) time.
- `__COMMENTS` e.g. `::= "//" | "#"` -- Tell the tokenizer that this is a kind of single-line comment.
- `__COMMENT_PAIRS` e.g. `::= /* */` - Tell the tokenizer that this is a kind of pair-based comment.
- `__COMMENT_PAIRS_NESTED` - Same, but nesting, like in Rust.
- `__COMMENT_REGEXES` - Same, but formed as a regex. These are slower than the above, because the Rust `regex` crate doesn't have a JIT.
- `__RESERVED_WORDS` - e.g. `::= auto break case` - Specifies a list of token contents that are not allowed to be "accepted" by regex terminals like ```r`[a-zA-Z_]+`r```

## More examples

Stateful symbol table management:
```r
STATEMENT ::=
@guard(found_typedef) !hook(process_typedef)
    | @guard(no_invalid_types) TYPENAMELIST BINDING ";"
    | FUNCCALL ";"

FUNCCALL ::=
    IDENT "(" FUNCARGLIST ")"

BINDING ::=
    @auto "(" BINDING ")"
    | IDENT
```

Dangling else:
```r
S ::= statement
statement ::= @peek(0, "if") ifcond | expr ";"
ifcond ::= "if" expr block else_maybe
else_maybe ::= @auto "else" block | #intentionally empty
expr ::= 
    @auto "true"
    | @auto "false"
    | r`[0-9]+`r
block ::= @auto "{" statement "}" | statement
```
Example output for `if true if true 555; else 555;`:
```r
S {
 statement {
  ifcond {
   if
   expr {
    true
   }
   block {
    statement {
     ifcond {
      if
      expr {
       true
      }
      block {
       statement {
        expr {
         555
        }
        ;
       }
      }
      else_maybe {
       else
       block {
        statement {
         expr {
          555
         }
         ;
        }
       }
      }
     }
    }
   }
   else_maybe {
   }
  }
 }
}
```

Almost Pratt parsing (without the table):
```r
S ::= expr5
expr5 ::= expr0 $become expr5_tail
expr5_tail ::=
    @peekr(0, r`[*%/]`r) r`[*%/]`r expr0 $become expr5_tail
    | #intentionally empty
expr0 ::= r`[0-9]+`r
```
Example output for a `5 * 2 * 5 * 1 * 2 * 9153`:
```r
S {
 expr5 {
  expr0 {
   5
  }
  *
  expr0 {
   2
  }
  *
  expr0 {
   5
  }
  *
  expr0 {
   1
  }
  *
  expr0 {
   2
  }
  *
  expr0 {
   9153
  }
 }
}
```

Dumb-as-rocks custom guards and hooks:
```r
S ::= expr5 unarify
expr5 ::= expr0 expr5_tail
expr5_tail ::=
    @guard(odd) expr0
    | #intentionally empty
expr0 ::= r`[0-9]+`r
unarify ::= !hook(unary)
```
Example output of the "custom guards/hooks" example for `9152 5 3`:
```r
S {
 expr5 {
  expr0 {
   9152
  }
  expr5_tail {
   expr0 {
    5
   }
  }
 }
 unarify {
  1
  1
  1
 }
}
```

TODO:

- $hoist, $skip, $drop, $dropifempty, $rename
