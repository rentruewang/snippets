"use strict";

let map = new Map(
  Object.entries({
    hello: "world",
  })
);

console.log(map["hello"]);
console.log(Array.from(map.entries()));
let no = map.get("no");
let yes = map.get("hello");
console.log(no, yes);

let prices = {
  banana: 1,
  orange: 2,
  meat: 4,
};

let doublePrices = Object.fromEntries(
  Object.entries(prices).map(([key, value]) => [key, value * 2])
);

console.log(doublePrices);
let [a, b] = [1, 2, 3];
[a, b] = [2, 3, 4];
console.log(a, b);
let [c, d, e] = [1];
console.log(c, d, e);

let { p, o, s, meat } = prices;
console.log(p, o, s, meat);

function showMenu({ title = "Menu", width = 100, height = 200 } = {}) {
  console.log(`${title} ${width} ${height}`);
}
showMenu({});
let student = {
  name: "John",
  age: 30,
  isAdmin: false,
  courses: ["html", "css", "js"],
  wife: null,
};

let json = JSON.stringify(student);
console.log(json);

let arr = [1, 2, 3];

let arrCopy = [...arr];

console.log(JSON.stringify(arr) === JSON.stringify(arrCopy));

console.log(arr === arrCopy, arr == arrCopy);

// Objects are compared by reference values
console.log([1, 2, 3] == [1, 2, 3], [1, 2, 3] === [1, 2, 3]);
console.log(Object.is([1, 2, 3], [1, 2, 3]));

let obj = { a: 1, b: 2, c: 3 };

let objCopy = { ...obj };
console.log(JSON.stringify(obj) === JSON.stringify(objCopy));
