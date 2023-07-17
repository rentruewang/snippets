// @ts-nocheck
"use strict";

const map2 = new Map(
  Object.entries({
    hello: "world",
  })
);

console.log(map2.hello);
console.log(Array.from(map2.entries()));
const no = map2.get("no");
const yes = map2.get("hello");
console.log(no, yes);

const prices = {
  banana: 1,
  orange: 2,
  meat: 4,
};

const doublePrices = Object.fromEntries(
  Object.entries(prices).map(([key, value]) => [key, value * 2])
);

console.log(doublePrices);
let [a, b] = [1, 2, 3];
[a, b] = [2, 3, 4];
console.log(a, b);
const [c, d, e] = [1];
console.log(c, d, e);

const { p, o, s, meat } = prices;
console.log(p, o, s, meat);

function showMenuJS({ title = "Menu", width = 100, height = 200 } = {}) {
  console.log("show menu 1");
  console.log(`${title} ${width} ${height}`);
}
showMenuJS({});

function showMenuJS2({ title, width }) {
  console.log("show menu 2");
  console.log(`${title} ${width}`);
}
showMenuJS2({ title: "title", width: 8 });
showMenuJS2({ width: 8 });

function showMenuJS3({ title, width = 1 }) {
  console.log("show menu 3");
  console.log(`${title} ${width}`);
}
showMenuJS3({ title: "title" });

function showMenuJS4({ title = "some title", width }) {
  console.log("show menu 4");
  console.log(`${title} ${width}`);
}
showMenuJS4({ width: 9 });

const student = {
  name: "John",
  age: 30,
  isAdmin: false,
  courses: ["html", "css", "js"],
  wife: null,
};

const json = JSON.stringify(student);
console.log(json);

const arr = [1, 2, 3];

const arrCopy = [...arr];

console.log(JSON.stringify(arr) === JSON.stringify(arrCopy));

console.log(arr === arrCopy, arr == arrCopy);

// Objects are compared by reference values
console.log([1, 2, 3] == [1, 2, 3], [1, 2, 3] === [1, 2, 3]);
console.log(Object.is([1, 2, 3], [1, 2, 3]));

const obj = { a: 1, b: 2, c: 3 };

const objCopy = { ...obj };
console.log(JSON.stringify(obj) === JSON.stringify(objCopy));
