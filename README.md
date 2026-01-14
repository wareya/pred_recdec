# Pred Recdec

"Predicated" recursive descent parsing framework. Write 90% of your grammar in plain BNF, ignore all the boilerplate, and write the remaining 10% as hooks. Supports many highly context-sensitive grammars.

This lets you write a "grammar" that has the same capabilities as a handwritten recursive descent parser. You can do computations on lookahead, skip around brackets and braces, update and query symbol tables, etc. You can even do loops by tail-calling into subrules, again, while writing 90% of your grammar in BNF.

This leaves the easy 90% of your grammar in a highly maintainable format, makes it easier to change technologies or languages, and makes it much simpler to write verification or testing rigs.

Currently a prototype. Example grammar snippets:

Stateful symbol table management:
```r
STATEMENT ::=
"@GUARD found_typedef" "!HOOK process_typedef"
| "@GUARD no_invalid_types" TYPENAMELIST BINDING ";"
| FUNCCALL ";"

FUNCCALL ::=
IDENT "(" FUNCARGLIST ")"

BINDING ::=
"@PEEK 0 (" "(" BINDING ")"
| IDENT
```

Dangling else:
```r
S ::= statement
statement ::= "@PEEK 0 if" ifcond | expr ";"
ifcond ::= "if" expr block else_maybe
else_maybe ::= "@PEEK 0 else" "else" block | #intentionally empty
expr ::= 
    "@PEEK 0 true" "true"
    | "@PEEK 0 false" "false"
    | rx%[0-9]+%rx
block ::= "@PEEK 0 {" "{" statement "}" | statement
"####;
```

Almost Pratt parsing (without the table):
```r
S ::= expr5
expr5 ::= expr0 "$BECOME" expr5_tail
expr5_tail ::=
    "@PEEKR 0 [*%/]" rx%[*%/]%rx expr0 "$BECOME" expr5_tail
    | #intentionally empty
expr0 ::= rx%[0-9]+%rx
```

Dumb-as-rocks custom guards and hooks:
```r
S ::= expr5 unarify
expr5 ::= expr0 expr5_tail
expr5_tail ::=
    "@GUARD odd" expr0
    | #intentionally empty
expr0 ::= rx%[0-9]+%rx
unarify ::= "!HOOK unary"
```
