# Wearley

Earley parser in pure Rust, written in a way that's meant to be "tutorializable". It's both **ready to use** and **educational**. Everything you need to get started is here, including BNF parsing and an AST type, and the structure of the code was designed for comprehensibility and adaptability.

This is a 99% solution: you should copy it into your own codebase and adapt it, not use it as a library. **It fully works as-is**, but the exact way your program/library should implement Earley will depend on what else you have going on, so trying to provide a one-size-fits-all library API would cause problems.

You may use this code under any of the following licenses, at your choice: CC0, Unlicense, BSD-0, WTFPL. Optionally, I would appreciate a shoutout or "thanks" wherever the best place to put one is, if there is an appropriate place for one. Consider also thanking other existing Earley work if it's relevant to how you use this.

Earley is a parsing algorithm that handles "pathological" grammars well. The implementation here has all the necessary modernizations to avoid the original 1968 version's problems: a simplified version of Leo's right recursion fix (1), nullability pre-advancement (2), reduction pointers (3), and pre-scanning (4).

Even with this grammar, on the input string `a a a a a a ......`, Wearley has no issues and parses at ~600k tokens per second (not insanely fast, but reasonable) on my system:

```bnf
program ::= B B A
A ::= "a" A | "a" | "b" | "c" | "d" | "e" | "f" | "g"
B ::= #intentionally empty
```

Extra note 1: Despite being mostly top-down, Earley parsing prefers left-recursion over right-recursion. If you get to pick between the two for a given rule, pick left recursion.

Extra note 2: This implementation produces a syntax tree, but the necessary information for producing SPPFs (e.g. using Elizabeth Scott's algorithm) is all present and preserved. If you need an SPPF, you can adapt the code to produce one without much pain.

Extra note 3: This is a "scannerful" implementation, which means that it has a lexer/tokenizer. Your tokenization needs are probably going to be slightly different, which is more reason that you should "copy paste and adapt" this.

Extra note 4: You *probably* shouldn't use ambiguity-preserving algos like Earley for scannerless parsing; the extra costs associated with preserving ambiguity across the insides of lexical items makes everything way, way slower, so you should only go scannerless over ambiguity if it's absolutely necessary. You can adapt this to be scannerless if you're in one of those rare necessary situations, though: it's easier to go from scannerful to scannerless than the other way around.

### Who should use Earley parsing?

If you're writing your own grammar, or parsing something with a simple grammar like JSON, you should not use Earley; instead, use a shift-reduce, or recursive descent, or Packrat-with-left-recursion-extensions parser, and adjust your grammar to work with that parser.

There are lots of situations where Earley is really useful, though:

- You're designing a grammar and don't know if you want to use ambiguous constructs yet
- You're iteratively reverse engineering a grammar from examples and don't know if it's ambiguous yet
- Your grammar is mostly unambiguous but has two or three annoying ambiguities that you just want to gloss over
- Your parser of choice falls apart because the grammar requires too much lookahead or preprocessing, and other off-the-shelf parsers don't work with it
- You want to use tree-sitter but can't
- You're parsing based on untrusted input and exponential preprocessing isn't acceptable -- most efficient parsers have exponential or cubic setup cost on arbitrary grammars, Earley doesn't

Depending on the exact input and grammar, Earley varies from 2x to 10x slower than recursive descent. On modern systems this isn't a problem for most use cases, but it can be a problem for syntax highlighting. For syntax highlighting you should use tree-sitter, which uses LR whenever possible and only falls back to GLR (something similar to Earley, but that plays nicely with LR) when it's forced to, minimizing the overhead.

### Recommended reading

- Earley: An Efficient Context-Free Parsing Algorithm (1968)
- (1) Leo: A general context-free parsing algorithm running in linear time on every LR(k) grammar without using lookahead (1991)
- (2) Aycock and Horspool: Practical Earley Parsing (2002)
- (3) Elizabeth Scott: SPPF-Style Parsing From Earley Recognisers (2008)
- Kegler: Marpa, A practical general parser: the recognizer (2019)
- Loup: [Earley Parsing Explained](https://loup-vaillant.fr/tutorials/earley-parsing/) (Multiple years)
- D.W.: [Computer Science Stack Exchange answer on the time complexity of nullable symbol detection](https://cs.stackexchange.com/questions/164696) (2023) (it's linear btw)
- Me: [It is actually surprising that Earley can efficiently parse C, ambiguities and all](https://wareya.wordpress.com/2025/09/25/it-is-actually-surprising-that-earley-can-efficiently-parse-c-ambiguities-and-all/) (2025)
- Me: [Earley Parsing Is Cheap in Principle and Practice: Motivation and Implementation](https://wareya.wordpress.com/2025/09/26/earley-parsing-is-cheap-in-principle-and-practice-motivation-and-implementation/) (2025)
- Me: [Short bit: Converting EBNF to BNF](https://wareya.wordpress.com/2025/12/16/short-bit-converting-ebnf-to-bnf/) (2025)

(4) (Pre-scanning is a bespoke single-item, single-depth lookahead optimization that doesn't affect the structure of the algorithm at all, unlike other lookahead optimizations. If it has another name, I don't know it. It's just, "if the item we're about to put in the chart is immediately a dead end, don't add it".)

The given numeric citations are not necessarily the earliest written examples of the given referenced technique, however they are generally the most widely-discussed. In particular, reduction pointers existed before ES's 2008 paper, but it was the one that brought them all the way across the finish line to complete, low-cost SPPF construction.

### Recommended changes

- Your tokenizer should probably be aware of comments. Mine isn't.
- Earley works on BNF, not EBNF. You'lll have to convert any EBNF rules to BNF. You can do this on the fly in code; see the recommended reading.
- The API I implemented gives error locations, but not the error state set. You'll have to add extra structure around that part (instead of just returning the error location) to implement full error reporting, which differs a lot depending on how you're using it.
- Earley charts can only be walked right-to-left, despite being built left-to-right. For the sake of learnability, my implementation has an arbitrary-choice right-to-left disambiguation strategy. This is OK for grammars where ambiguity is an accident instead of a feature. If you need to fix it, my blog posts cover how to get left-to-right disambiguation with specific disambiguation rules. Basically, both of the following (not just one or the other):
  - The Earley chart can only be safely walked right-to-left, so ambiguities can only be disambiguiated right-to-left. This is a semantic error for e.g. the C grammar. This is a known problem. If you need left-to-right disambiguation, you need to do one of the following:
    1) Reverse the grammar and input token stream before parsing (in code). If the parse fails, unreverse them and parse again before producing error messages. This is smarter than writing a reversed copy of the parser algorithm. This has one downside: most grammars are locally unambiguous from left to right even if they're locally ambiguous from right to left. Grammars that become more ambiguous when reversed will parse slower with this method. But it's guaranteed to be safe.
    2) [Loup proposes reversing the chart](https://loup-vaillant.fr/tutorials/earley-parsing/parser) instead of the grammar and token list, and this definitely works for most grammars, but IMO it's fragile and easy to implement wrong. If you have any doubts about whether your grammar is compatible with this technique, I recommend the dual reversal method. However, it doesn't have the RTL ambiguity speed drawback that dual reversal does.
    3) Parse into a right-to-left Shared Packed Parse Forest (SPPF) and reverse that SPPF before disambiguating. This is much harder and slower than it sounds. I don't recommend it. As far as I know, there isn't yet a widely known way to directly build a left-to-right SPPF from an Earley chart.
  - If you need specific disambiguation rules, look at the data under each reduction pointer in a given list of reduction pointers, and apply your disambiguation rules to that data.
- You probably want to move the various dual-index HashMaps into the chart as single-index HashMaps, for a marginal performance boost. The way they're implemented here is meant to make it easier to understand what each item is doing.
- As implemented, scan checks do a full string comparison. This isn't strictly necessary; the string interning done by the tokenizer means that an `Rc` pointer value comparison would work and be faster. But for the sake of "yeah this is obviously correct" when looking at it, I left it as a string comparison. You can change it to a pointer comparison if you want.
  - You might want to do the same thing for regexes, but doing it for regexes requires adding stuff to the grammar loader and tokenizer to prepare a bunch of regex match tables over the interned strings, and regex tokens are usually not most tokens in an input text, so it's up to you to decide whether it's worth it.
- I produce a "stringly-typed" AST where node types are differentiated with (interned) strings instead of using enums or trait objects. This is by necessity because the grammar is loaded dynamically. If you have a set-in-stone grammar, you might want to produce a typed AST instead, though stringly-typed ASTs aren't as bad as you might think.
- The lexer/tokenizer/scanner is also "typeless" - it produces an array of (interned) strings, not an array of enums. (Yes, this is still a tokenizer.) This is for the same reason as the AST being "stringly typed". You probably don't need to change this even if you think you should, but for some specific grammars where token type is super important, you might want to.
- Particularly complex quasi-context-sensitive grammars like C and C++ will need to thread extra context through the parser to reject some state items and might need to run the parser multiple times. My "...can efficiently parse C..." blog post covers this.
- The right recursion optimization works as implemented, but generates additional never-used data that it doesn't need to, for the sake of simplicity: it is spread between the "prediction" step, where it doesn't know if it needs the data yet, and the "completion" step, where it actually uses that data. The "optimal" version takes the code that's currently added to the "prediction" step, and moves it to the "completion" step; however, doing this requires using reduction pointers to figure out item predecessors, so it depends on reduction pointers and isn't "independent". I implemented it in this slightly suboptimal way for the sake of comprehensibility and independence, but a fully optimized parser should do the reduction-pointer-dependent version entirely in the completion step. This can give you a ten-ish-percent (probably) speed boost if your grammar has a LOT of right recursion. However, the implementation given here works and is fast enough despite being suboptimal.
- My right recursion optimization is *inspired by* Leo's optimizations, not directly based on them. It is very similar in spirit, but my version is meant to be minimally invasive and "just" fix right recursion, which in turn means that my version is easier to understand and see where it modifies the original algorithm. You don't *need* specifically Leo's version, but if you decide to use Leo's version instead and find the version in the paper to be very different from mine, this is why.
