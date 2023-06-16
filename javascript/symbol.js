const user = {};
const s1 = Symbol.for("11ww");
const s2 = Symbol("11ww");
user[s1] = 9;
user[s2] = 99;
console.log(user);

const sym = Symbol.for("11ww");
console.log(s1 == sym, s1 === sym, s2 == sym, s2 === sym);
console.log(Symbol.keyFor(s2), Symbol.keyFor(s1));
