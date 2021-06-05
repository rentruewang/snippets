"use strict";

const resolvedProm = Promise.resolve(-11);

let thenProm = resolvedProm.then((value) => {
  console.log("this gets called after the end of the main stack:", value);
  return value;
});
console.log(thenProm);
let ttProm = thenProm.then((value) => {
  console.log("this value is", value);
  return value;
});

console.log(ttProm);

async function f() {
  let promise = new Promise((resolve, reject) => {
    setTimeout(() => resolve("done!"), 1000);
  });

  let result = await promise;
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
  let result = await new Thenable(1);
  console.log(result);
}

g();

function* generateSequence() {
  yield 1242342;
  yield 21122389;
  return 31083470172856;
}
let seq = generateSequence();
console.log("seq:", seq.next());
console.log("seq:", seq.next());
console.log("seq:", seq.next());

for (let v of generateSequence()) {
  console.log(v);
}

function* gen() {
  let result = yield "2 + 2 = ?";
  console.log(result);
}

async function* agen() {
  let result = yield "2 + 2 = ?";
  console.log(result);
}

let generator = gen();

let question = generator.next().value;
console.log(question);
for (let g of gen()) {
  console.log("sync", g);
}

generator.next(4);
(async () => {
  for await (let g of agen()) {
    console.log("async", g);
  }
})();
