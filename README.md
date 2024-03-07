# Snippets

Snippets is a repository that stores snippets from languages I want to work on.

[![Code Formatted](https://github.com/rentruewang/quirks/actions/workflows/format.yaml/badge.svg)](https://github.com/rentruewang/quirks/actions/workflows/format.yaml)

## What does this repository contain?

It contains concepts and features, in programming languages (that I use), with which I sometimes get confused.

## Since when do languages of a project matter?

**It doesn't**. [Any performant system comes down to algorithms and engineering](https://stackoverflow.com/a/4911818), and programming languages is just a small part of engineering (e.g. less than architecture design). Users care about the end product, rather than how things are written. Still, some languages are better at certain things than others. For me, I would like the minimum possible to be able to do everything I want to do. This is why I have a list of languages that I use.

## What languages are you interested in working on?

I'm only interested in Python, Go, Modern C++/C/CUDA, Dart. In fact, I'm only intereseted in writing stuff that makes me happy 😀.

Basically all software has been implemented with one of those technologies, so there is not a lot of need to acutally learn anything else (and I force myself not to jump at fancy things e.g. a rewrite in some particular language). Instead, algorithms are always more important than languages themselves anyways.

**Languages outside of those mentioned before will never make this list. Note that I only included general purpose langauges above because those have the most utility. I treat languages not making the list as domain specific and use them from time to time, but those aren't my focus.**

Here's a question I ask myself when considering this list: When I start a company, do I want to see this language used? If so, put it here. Or else it's a waste of my time.

After all, why would I want to spend time on a language that'll probably die anyways?

## Resources for learning those languages?

See the concepts for [Python](./python/README.md), [Go](./go/README.md), [Modern C++](./cxx/README.md), [Dart](./dart/README.md)

## But do you know other languages?

Yes. See the notable languages that don't make the list. However, instead of languages, I (at least try to) focus on making better technology (architecture, algorithm etc).

## Details of Languages that made the list:

🐍 Python:

Simple yet beautiful, it's **my favorite language**. Besides, it's an awesome glue language that exposes lots of C / C++ libraries, especially in machine learning. Really no alternative.

Usage: prototyping, machine learning, scripting, glue language for C++ libraries, not-so-performant solution for quick and easy tools / services

🦫 Go:

Simple and easy to use, yet fast. Vibrant ecosystem. **Go routines** make it so easy to spawn "threads" and it's perfect for that kind of work. Seen as a modern replacement for Java. It's also my second favorite language.

Usage: high concurrency stuff, web backend, IO bound CLI tools, performant solution for short-ish running tools / services

🛠️ Modern C++ (Old C++, C, Cuda):

Complicated but useful. Super fast (bascially the 1x on benchmarks). Preferred when **performance** is needed. Modern C++ is also pleasant to write, except for debugging template errors.

Usage: high performance computing, desktop UI, games, improve Python performance, computing bound CLI tools, performant solution for long running tools / services, any sort of low level stuff


## Notable other languages that didn't make the list:

- Java: Easy to write, fast, and Java 14+ has lots of QOL change. However, package system and build tools ecosystem is cumbersome and not very productive. Also, I find myself caring about C++ level performance optimization when writing Java, so I might as well write C++ `¯\_(ツ)_/¯`.
- JavaScript / TypeScript: It's ok and widely adopted, but personally I prefer **Flutter** for UI and `Node.js` not a real replacement for backend stuff so I don't see me using JS/TS a lot in the future.
- Dart: One killer application: Flutter.
- Lua: Fast, efficient, and has an awesome JIT compiler / C interface. However, uses 1-based arrays.
- R: Simple and straightforward. data.table is amazing. However, not a lot of use cases outside statistics.
- Rust: This is an interesting case. I loved a lot about the language, however, the constant barrage of "rewrites" from enthusiasts are super annoying, as well as bragging about how difficult it is to learn. It also doesn't offer performance advantages against its main competitor, C++ (unlike Go which has a significantly lower foot print and goroutines baked into the language against compared to its rival Java). It also is quite amusing that for the most part, you must be somewhat decent at C++ already in order to appreciate Rust, which does not help replace C++. It has [no killer application](https://www.reddit.com/r/programmingcirclejerk/comments/hdqdjd/rust_is_the_wrong_solution_for_almost_everything/) for anything of real value, high profile devs are leaving, would [never](https://www.quora.com/Will-Rust-replace-C++) [replace](https://news.ycombinator.com/item?id=29905917) [C++](https://www.reddit.com/r/rust/comments/12xgxfa/comment/jhjbtep/), ugly syntax, and perhaps too [abstract](https://www.reddit.com/r/CUDA/comments/ns8mi1/comment/h0l17rw/). Modern C++ also solves a lot of issues of older versions of C++, and I love it. Also, when performance is concered, Go/Java are already quite fast with managed memory, so unfortunately I don't really see a future where Rust will be mainstream.
- Kotlin: Tried it, however, compared to Java's simplicity, it's complicated. I prefer simplicity. Also, most of its use is in Android, so I don't really need it (I could use Flutter or React Native).
- Scala: Has a killer application: Spark. However, it's more complicated than the language it's trying to replace (Java), and I prefer simplicity.
- Carbon: Really depends on whether its package manager / ecosystem is good. Since it's just (C++)++ (100% compatible). Will probably kill Rust if it's much better than modern C++ (at least in enterprise, not in the hearts of enthusiasts).
