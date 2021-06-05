#! /usr/bin/env node

"use strict";

console.log("hello world");

const jsCamelCase = true;
console.log("javascript uses camel case:", jsCamelCase);

console.log("Hello");
[2, 1, 1].forEach((elem) => console.log(elem));
// This is a comment

// console.log(x);
let isStrict = (function () {
  return !this;
})();
console.log(isStrict);

let user = "John",
  age = 25,
  message = "Hello";
console.log(user, age, message);
