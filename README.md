# Pred Recdec

Predicated recursive descent parsing framework. Write 90% of your grammar in plain BNF, skip the boilerplate, and write the remaining 10% as hooks. Supports most slightly context-sensitive grammars, including typedefs. Basic lookahead and "optimized tail calls" are built in, so you don't have to add hooks for super basic LL(k) functionality, just write the peek statements. This mirrors how most high-performance parsers are written today, just in a BNF shell.

As soft proof, I wrote a working C99 grammar (src/grammar.txt). It successfully parses the preprocessor output of both gcc and clang `#include`-ing a kitchen sink worth of stdlib headers.

**Performance**: Roughly the same parsing time as Clang and GCC `-fsyntax-only -ftime-report` on a 5.6MB C source file, tested with the included grammar (src/grammar.txt).

Features:

- BNF syntax and automatic AST contruction: keep your grammar low-boilerplate
- Legible, easy-to-learn non-BNF parts
- Support for dirty parsing hooks like the "typedef" hack, etc
- Error recovery support
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
