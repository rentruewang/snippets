# Snippets

Snippets is a repository that stores snippets from languages I want to work on.

[![format-code](https://github.com/rentruewang/quirks/actions/workflows/format.yaml/badge.svg)](https://github.com/rentruewang/quirks/actions/workflows/format.yaml)

## What does this repository contain?

It contains concepts and features, in programming languages (that I use), with which I sometimes get confused.

## What languages are you interested in working on?

I'm only interested in Python, Go, C/C++/CUDA, JavaScript/TypeScript. In fact, I'm only intereseted in writing stuff that makes me happy 😀.

Basically all software has been implemented with one of those technologies, so there is not a lot of need to acutally learn anything else (and I force myself not to jump at fancy things e.g. a rewrite in some particular language). Instead, algorithms are always more important than languages themselves anyways.

Languages outside of those mentioned before will never make this list.

Here's a question I ask myself when considering this list: When I start a company, do I want to see this language used? If so, put it here. Or else no matter how much I love it, it's a waste of my time.

After all, why would I want to spend time on a language that'll probably die anyways?

## But do you know other languages?

Yes. See the notable languages that don't make the list. However, instead of languages, I (at least try to) focus on making better technology (architecture, algorithm etc).

## Details of Languages that made the list:

🐍 Python: Simple yet beautiful, it's **my favorite language**. Besides, it's an awesome glue language that exposes lots of C / C++ libraries, especially in machine learning. Really no alternative.

🇨 C: Simple to use, however quite dangerous. The language is also super fast. I'll use it for small programs where I don't need objects.

🛠️ C++: Complicated but useful. Super fast. Preferred when **performance** is needed. Modern C++ is also pleasant to write, except for debugging template errors.

🦫 Go: Simple and easy to use, yet fast. Vibrant ecosystem. **Go routines** make it so easy to spawn "threads" and it's perfect for that kind of work. Seen as a modern replacement for Java. It's also my second favorite language.

📜 JavaScript: Really no alternative when **frontend / UI** is concered.

⌨️ TypeScript: A better all around JavaScript. Love it.

## What I use those languages for:

🐍 Python: machine learning, scripting, glue language for C++ libraries

🇨 C: subset of C++

🛠️ C++: high performance computing, desktop UI, improve Python performance

🦫 Go: high concurrency stuff, web backend, command line tools

📜 JavaScript: subset of TypeScript

⌨️ TypeScript: Web frontend, mobile (react native)

## Notable other languages that didn't make the list:

- Java: Easy to use, and fast (contrary to many's impression, JVM is awesomely fast). Also, has the last mover advantage, and **Java 14+ is just awesome** to write. The only complaint I have regarding this language is its package system and build tools, which I'm not very productive with.
- Dart: **Flutter** is its killer application of this language. It also looks just like Java, which means it's simple and intuitive. However, popularity wise, it cannot compete with JS/TS.
- Rust: This is an interesting case. I loved a lot about the language,however, the constant barrage of "rewrites" from enthusiasts are super annoying, as well as bragging about how difficult it is to learn. It also doesn't offer performance advantages against its main competitor, C++ (unlike Go which has a significantly lower foot print and goroutines baked into the language against compared to its rival Java). It also is quite funny how to appreciate Rust, you must be somewhat decent at C++ already, how does that help replace C++?. It has [no killer application](https://www.reddit.com/r/programmingcirclejerk/comments/hdqdjd/rust_is_the_wrong_solution_for_almost_everything/), high profile devs are leaving, would [never kill C++](https://www.quora.com/Will-Rust-replace-C++), and ugly syntax. Modern C++ also solves a lot of issues of older versions of C++, and I love it. Also, when performance is concered, Go/Java are already quite fast with managed memory, so unfortunately I don't really see a future where Rust will be mainstream.
- Kotlin: Tried it, however, compared to Java's simplicity, it's complicated. I prefer simplicity. Also, most of its use is in Android, so I don't really need it (I could use Flutter).
- Lua: Fast, efficient, and has an awesome JIT compiler / C interface. However, index starts at 1.
- Scala: Has a killer application: Spark. However, it's trying to replace a simple language though (Java), and I prefer simplicity.
- Carbon: Really depends on whether its package manager / ecosystem is good. Since it's just (C++)++ (100% compatible). Will probably kill Rust if it's much better than modern C++ (at least in enterprise, not in the hearts of enthusiasts).
