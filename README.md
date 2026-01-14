# Pred Recdec

"Predicated" recursive descent parsing framework. Write 90% of your grammar in plain BNF, ignore all the boilerplate, and write the remaining 10% as hooks. Supports many highly context-sensitive grammars.

This lets you write a "grammar" that has the same capabilities as a handwritten recursive descent parser. You can do computations on lookahead, skip around brackets and braces, update and query symbol tables, etc. You can even do loops by tail-calling into subrules, again, while writing 90% of your grammar in BNF.

Currently a prototype.
