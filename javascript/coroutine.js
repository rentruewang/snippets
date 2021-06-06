"use strict";

const resolvedProm = Promise.resolve(-11);

const thenProm = resolvedProm.then((value) => {
  console.log("this gets called after the end of the main stack:", value);
  return value;
});
console.log(thenProm);
const ttProm = thenProm.then((value) => {
  console.log("this value is", value);
  return value;
});

console.log(ttProm);

async function f() {
  const promise = new Promise((resolve, reject) => {
    setTimeout(() => resolve("done!"), 1000);
  });

  const result = await promise;
  console.log(result);
}

f();

class Thenable {
  constructor(num) {
    this.num = num;
  }

  then(resolve, reject) {
    console.log(resolve);
    setTimeout(() => resolve(this.num * 2), 1000); // (*)
  }
}

async function g() {
  const result = await new Thenable(1);
  console.log(result);
}

g();

function* generateSequence() {
  yield 1242342;
  yield 21122389;
  return 31083470172856;
}
const seq = generateSequence();
console.log("seq:", seq.next());
console.log("seq:", seq.next());
console.log("seq:", seq.next());

for (const v of generateSequence()) {
  console.log(v);
}

function* gen() {
  const result = yield "2 + 2 = ?";
  console.log(result);
}

async function* agen() {
  const result = yield "2 + 2 = ?";
  console.log(result);
}

const generator = gen();

const question = generator.next().value;
console.log(question);
for (const g of gen()) {
  console.log("sync", g);
}

generator.next(4);
(async () => {
  for await (const g of agen()) {
    console.log("async", g);
  }
})();
