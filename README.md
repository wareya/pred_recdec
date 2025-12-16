# Wearley

Earley parser in pure Rust, written in a way that's meant to be "tutorializable".

This is a 99% solution: you should copy it into your own codebase and adapt it, not use it as a library. **It fully works as-is**, but the exact way your program/library should implement Earley will depend on what else you have going on, so you should copy it and adapt. Everything you need to get started is here, including BNF parsing and an AST type.

You may use this code under any of the following licenses, at your choice: CC0, Unlicense, BSD-0, WTFPL. Optionally, I would appreciate a shoutout or "thanks" wherever the best place to put one is, if there is an appropriate place for one. Consider also thanking other existing Earley work if it's relevant to how you use this.

Earley is a parsing algorithm that handles "pathological" grammars well. The implementation here has all the necessary modernizations to avoid the original 1968 version's problems: a simplified version of Leo's right recursion fix (1), nullability pre-advancement (2), reduction pointers (3), and pre-scanning (4).

Even with this grammar, on the input string `a a a a a a ......`, this parser has no issues:

```bnf
program ::= B B A
A ::= "a" A | "a" | "b" | "c" | "d" | "e" | "f" | "g"
B ::= #intentionally empty
```

Extra note 1: This implementation produces a syntax tree, but the necessary information for producing SPPFs (e.g. using Elizabeth Scott's algorithm) is all present and preserved. If you need an SPPF, you can adapt the code to produce one without much pain.

Extra note 2: this is a "scannerful" implementation (i.e. it has a lexer/tokenizer): your tokenization needs are probably going to be slightly different, which is more reason that you should "copy paste and adapt" this.

Extra note 3: You *probably* shouldn't use ambiguity-preserving algos like Earley for scannerless parsing; the extra costs associated with preserving ambiguity across the insides of lexical items makes everything way, way slower, so you should only go scannerless over ambiguity if it's absolutely necessary. You can adapt this to be scannerless if you're in one of those rare necessary situations, though: it's easier to go from scannerful to scannerless than the other way around.

### Recommended reading

- Earley: An Efficient Context-Free Parsing Algorithm (1968)
- (1) Leo: A general context-free parsing algorithm running in linear time on every LR(k) grammar without using lookahead (1991)
- (2) Aycock and Horspool: Practical Earley Parsing (2002)
- (3) Elizabeth Scott: SPPF-Style Parsing From Earley Recognisers (2008)
- Kegler: Marpa, A practical general parser: the recognizer (2019)
- Loup: [Earley Parsing Explained](https://loup-vaillant.fr/tutorials/earley-parsing/) (Multiple years)
- D.W.: [Computer Science Stack Exchange answer on the time complexity of nullable symbol detection](https://cs.stackexchange.com/questions/164696) (2023)
- Me: [It is actually surprising that Earley can efficiently parse C, ambiguities and all](https://wareya.wordpress.com/2025/09/25/it-is-actually-surprising-that-earley-can-efficiently-parse-c-ambiguities-and-all/) (2025)
- Me: [Earley Parsing Is Cheap in Principle and Practice: Motivation and Implementation](https://wareya.wordpress.com/2025/09/26/earley-parsing-is-cheap-in-principle-and-practice-motivation-and-implementation/) (2025)
- Me: [Short bit: Converting EBNF to BNF](https://wareya.wordpress.com/2025/12/16/short-bit-converting-ebnf-to-bnf/) (2025)

(4) (Pre-scanning is a bespoke single-item, single-depth lookahead optimization that doesn't affect the structure of the algorithm at all, unlike other lookahead optimizations. If it has another name, I don't know it. It's just, "if the item we're about to put in the chart is immediately a dead end, don't add it".)

The given numeric citations are not necessarily the earliest written examples of the given referenced technique, however they are generally the most widely-discussed. In particular, reduction pointers existed before ES's 2008 paper, but it was the one that brought them all the way across the finish line to complete, low-cost SPPF construction.

### Recommended changes

- Your tokenizer should probably be aware of comments. Mine isn't.
- The API I implemented gives error locations, but not the error state set. You'll have to add extra structure around that part (instead of just returning the error location) to implementing full error reporting, which differs a lot depending on how you're using it.
- This implementation has an arbitrary, right-to-left disambiguation strategy. This is OK for languages where ambiguity is an accident instead of a feature. If you need to fix it, my blog posts cover how to get left-to-right disambiguation with specific disambiguation rules. Basically:
- - If you need left-to-right disambiguation, you'll need to reverse the grammar and input token stream before parsing. If the parse fails, unreverse them and parse again before producing error messages.
- - If you need specific disambiguation rules, look at the data under each reduction pointer in a given list of reduction pointers, and apply your disambiguation rules to that data.
- You probably want to move the various dual-index HashMaps into the chart as single-index HashMaps, for a marginal performance boost. The way they're implemented here is meant to make it easier to understand what each item is doing.
- I produce a "stringly-typed" AST. This is the right move for generic parsing, but if you have a set-in-stone grammar, you might want to produce a typed AST instead.
- Particularly complex quasi-context-sensitive grammars like C and C++ will need to thread extra context through the parser to reject some state items and might need to run the parser multiple times. My "...can efficiently parse C..." blog post covers this.
