# Snippets

Snippets is a repository that stores snippets from languages I want to work on.

[![Code Formatted](https://github.com/rentruewang/snippets/actions/workflows/format.yaml/badge.svg)](https://github.com/rentruewang/snippets/actions/workflows/format.yaml)

## What does this repository contain?

It contains concepts and features, in programming languages (that I use), with which I sometimes get confused.

## What languages are you interested in working on?

I'm only interested in Python, and Modern C++/C/CUDA. [Any performant system comes down to algorithms and engineering](https://stackoverflow.com/a/4911818), and programming languages is just a small part of engineering (e.g. less than architecture design). These are more than enough to cover my use cases (I do not build too much frontend).

Personally, I treat all other languages as domain specific and use them from time to time, but those aren't my focus. **Languages are the same anyways, so they can be picked up easily**.

## Resources for learning those languages?

See the concepts for [Python](./python/README.md), [Modern C++](./cxx/README.md)

## What do I use Python and C++ for?

🐍 Python:

Simple and beautiful, it's **my favorite language**. Besides, it's an awesome glue language that exposes lots of C / C++ libraries, especially in machine learning. Really no alternative. My favorite scripting language.

Usage: prototyping, machine learning, scripting, glue language for C++ libraries, not-so-performant solution for quick and easy tools / services

🛠️ Modern C++ (Old C++, C, Cuda):

Complicated but useful. Super fast (bascially the 1x on benchmarks). Preferred when **performance** is needed. Modern C++ is also pleasant to write, except for debugging template errors.

Usage: high performance computing, desktop UI, games, improve Python performance, computing bound CLI tools, performant solution for long running tools / services, any sort of low level stuff

**NOTE** Python and C++ are ubiquitous and don't have a lot of [deficiencies](https://softwareengineering.stackexchange.com/questions/329728/are-design-patterns-frowned-upon). They also don't have very few overalpping use cases.

## Since when do languages of a project matter?

**It doesn't**. [Any performant system comes down to algorithms and engineering](https://stackoverflow.com/a/4911818), and programming languages is just a small part of engineering (e.g. less than architecture design). Users care about the end product, rather than how things are written. Still, some languages are better at certain things than others. For me, I would like the minimum possible to be able to do everything I want to do. This is why I use these.

## My thoughts on good designs

Quoting Wikipedia on [Turing Machine](https://en.wikipedia.org/wiki/Turing_machine):

> The machine operates on an infinite memory tape divided into discrete cells, each of which can hold a single symbol drawn from a finite set of symbols called the alphabet of the machine. It has a "head" that, at any point in the machine's operation, is positioned over one of these cells, and a "state" selected from a finite set of states. At each step of its operation, the head reads the symbol in its cell. Then, based on the symbol and the machine's own present state, the machine writes a symbol into the same cell, and moves the head one step to the left or the right, or halts the computation. The choice of which replacement symbol to write, which direction to move the head, and whether to halt is based on a finite table that specifies what to do for each combination of the current state and the symbol that is read. Like a real computer program, it is possible for a Turing machine to go into an infinite loop which will never halt.

and [Turing Completeness](https://en.wikipedia.org/wiki/Turing_completeness)

> In computability theory, a system of data-manipulation rules (such as a model of computation, a computer's instruction set, a programming language, or a cellular automaton) is said to be Turing-complete or computationally universal if it can be used to simulate any Turing machine.

[Church–Turing thesis](https://en.wikipedia.org/wiki/Church%E2%80%93Turing_thesis)https://en.wikipedia.org/wiki/Church%E2%80%93Turing_thesis states that **any function that is computable by an algorithm is a [computable function](https://en.wikipedia.org/wiki/Computable_function)**.




[Computational Theory](https://en.wikipedia.org/wiki/Computability_theory) states that:

> A set of natural numbers is said to be a computable set (also called a decidable, recursive, or Turing computable set) if there is a Turing machine that, given a number n, halts with output 1 if n is in the set and halts with output 0 if n is not in the set.

With all these information, one can conclude that anything that is computable must be able to be compiled (transformed) to an algorithm running on a Turing machine.

Csondiering that

> A related concept is that of Turing equivalence – two computers P and Q are called equivalent if P can simulate Q and Q can simulate P. The Church–Turing thesis conjectures that any function whose values can be computed by an algorithm can be computed by a Turing machine, and therefore that if any real-world computer can simulate a Turing machine, it is Turing equivalent to a Turing machine. A universal Turing machine can be used to simulate any Turing machine and by extension the purely computational aspects of any possible real-world computer.


As a [compiler](https://en.wikipedia.org/wiki/Compiler) is simply a translator between different languages, the best transformation (best software desgin) is therefore the best transformation from the source (map domain, physics domain etc) to the language understood by the Turing machine (your software), with structures mimicking the problems in the domains we aim to solve.
