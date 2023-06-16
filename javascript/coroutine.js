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
  const promise = new Promise((resolve, _reject) => {
    setTimeout(() => resolve("done!"), 1000);
  });

  const result = await promise;
  console.log("result", result);
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
  console.log("gen", result);
}

async function* agen() {
  const result = yield "2 + 2 = ?";
  console.log("agen", result);
}

const generator = gen();

const question = generator.next().value;
console.log(question);
for (const g of gen()) {
  console.log("sync", g);
}

generator.next(4);
(async () => {
  const ag = gen();
  console.log("out of generator", ag.next(10).value);
  for await (const g of agen()) {
    console.log("async", g);
  }
})();

// Copied from MDN
async function MDN() {
  console.log();
  console.log("The following code is copied from MDN");
  console.log();
  setTimeout(() => {}, 5000);

  function resolveAfter2Seconds() {
    console.log("starting slow promise");
    return new Promise((resolve) => {
      setTimeout(function () {
        resolve("slow");
        console.log("slow promise is done");
      }, 2000);
    });
  }

  function resolveAfter1Second() {
    console.log("starting fast promise");
    return new Promise((resolve) => {
      setTimeout(function () {
        resolve("fast");
        console.log("fast promise is done");
      }, 1000);
    });
  }

  async function sequentialStart() {
    console.log("==SEQUENTIAL START==");

    // 1. Execution gets here almost instantly
    const slow = await resolveAfter2Seconds();
    console.log(slow); // 2. this runs 2 seconds after 1.

    const fast = await resolveAfter1Second();
    console.log(fast); // 3. this runs 3 seconds after 1.
  }

  async function concurrentStart() {
    console.log("==CONCURRENT START with await==");
    const slow = resolveAfter2Seconds(); // starts timer immediately
    const fast = resolveAfter1Second(); // starts timer immediately

    // 1. Execution gets here almost instantly
    console.log(await slow); // 2. this runs 2 seconds after 1.
    console.log(await fast); // 3. this runs 2 seconds after 1., immediately after 2., since fast is already resolved
  }

  function concurrentPromise() {
    console.log("==CONCURRENT START with Promise.all==");
    return Promise.all([resolveAfter2Seconds(), resolveAfter1Second()]).then(
      (messages) => {
        console.log(messages[0]); // slow
        console.log(messages[1]); // fast
      }
    );
  }

  async function parallel() {
    console.log("==PARALLEL with await Promise.all==");

    // Start 2 "jobs" in parallel and wait for both of them to complete
    await Promise.all([
      (async () => console.log(await resolveAfter2Seconds()))(),
      (async () => console.log(await resolveAfter1Second()))(),
    ]);
  }

  sequentialStart(); // after 2 seconds, logs "slow", then after 1 more second, "fast"

  // wait above to finish
  setTimeout(concurrentStart, 4000); // after 2 seconds, logs "slow" and then "fast"

  // wait again
  setTimeout(concurrentPromise, 7000); // same as concurrentStart

  // wait again
  setTimeout(parallel, 10000); // truly parallel: after 1 second, logs "fast", then after 1 more second, "slow"
}

MDN();
