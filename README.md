Earley parser in pure Rust, written in a way that's meant to be "tutorializable".

This is a 99% solution: you should copy it into your own codebase and adapt it, not use it as a library. **It fully works as-is**, but the exact way your program/library should implement Earley will depend on what else you have going on, so you should copy it and adapt.

You may use this code under any of the following licenses, at your choice: CC0, Unlicense, BSD-0, WTFPL. Optionally, I would appreciate a shoutout or "thanks" wherever the best place to put one is, if there is an appropriate place for one. Consider also thanking other existing Earley work if it's relevant to how you use this.

Earley is a parsing algorithm that handles "pathological" grammars well. The implementation here has all the necessary modernizations to avoid the original 1968 version's problems: right recursion fix (1), nullability pre-advancement (2), reduction pointers (3), and pre-scanning (4).

Also, this is a "scannerful" implementation (i.e. it has a lexer/tokenizer): your tokenization needs are probably going to be slightly different, which is more reason that you should "copy paste and adapt" this. (And you *probably* shouldn't be using ambiguity-preserving algos like Earley for scannerless parsing; the extra costs associated with preserving ambiguity across lexical items makes everything way, way slower, so you should only go scannerless over ambiguity if it's absolutely necessary.)

Even with this grammar, on the input string `a a a a a a ......`, this parser has no issues:

```bnf
program ::= B B A
A ::= "a" A | "a" | "b" | "c" | "d" | "e" | "f" | "g"
B ::= #intentionally empty
```

Recommended reading:

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

(4) (Pre-scanning is a bespoke single-item, single-depth lookahead optimization that doesn't affect the structure of the algorithm at all, unlike other lookahead optimizations. If it has another name, I don't know it.)
