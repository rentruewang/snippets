# Computation fundamentals

There are 2 main components in computing, data (measured by space complexity) and compute (measured by time complexity).

I theorize that
Data = entities, storage, intrinsically exists
Compute = mutation on data

Data is more fundamental than computation, because computation are performed on data (data = symbol, compute = instruction in Turning machine).

Think of the types of data as Markov, then a library / app is just moving on a path on this Markov state / graph. This state is exactly a Turing machine’s state as I can ask TM to simulate a function for me.

Even transmitting a packet counts as computation, because it's changing state (location) of a piece of data.

How do abstractions come into play?

- I think it's just types of data and the type of compute (abstract, reasoned with invariance) that can be performed on them. Considering that every function is data -> compute -> data, abstraction in terms of breaking down functions are just composing data into intermediate representation, and abstract interfaces are shared traits of different data + specialized compute for each kind of data.
- Abstractions are just using computation to transform underlying data into the same mathematic model. Compiler optimizing this away = 0 cost. Some data structures might happen to have a better complexity but those are implementation details.
