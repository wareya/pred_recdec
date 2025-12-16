Earley parser in pure Rust, written in a way that's meant to be "tutorializable".

This is a 99% solution: you should copy it into your own codebase and adapt it, not use it as a library.

You may use this code under any of the following licenses, at your choice: CC0, Unlicense, BSD-0, WTFPL. Optionally, I would appreciate a shoutout or "thanks" wherever the best place to put one is, if there is an appropriate place for one. Consider also thanking other existing Earley work if it's relevant to how you use this.

Recommended reading:

- Earley: An Efficient Context-Free Parsing Algorithm (1968)
- Leo: A general context-free parsing algorithm running in linear time on every LR(k) grammar without using lookahead (1991)
- Elizabeth Scott: SPPF-Style Parsing From Earley Recognisers (2008)
- Kegler: Marpa, A practical general parser: the recognizer (2019)
- Loup: [Earley Parsing Explained](https://loup-vaillant.fr/tutorials/earley-parsing/) (Multiple years)
- D.W.: [Computer Science Stack Exchange answer on the time complexity of nullable symbol detection](https://cs.stackexchange.com/questions/164696) (2023)
- Me: [It is actually surprising that Earley can efficiently parse C, ambiguities and all](https://wareya.wordpress.com/2025/09/25/it-is-actually-surprising-that-earley-can-efficiently-parse-c-ambiguities-and-all/) (2025)
- Me: [Earley Parsing Is Cheap in Principle and Practice: Motivation and Implementation](https://wareya.wordpress.com/2025/09/26/earley-parsing-is-cheap-in-principle-and-practice-motivation-and-implementation/) (2025)
