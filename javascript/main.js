#! /usr/bin/env node

"use strict";

// How to write good comments:
// https://javascript.info/comments

console.log("hello world");

const jsCamelCase = true;
console.log("javascript uses camel case:", jsCamelCase);

console.log("Hello");
[2, 1, 1].forEach((elem) => console.log(elem));
// This is a comment

// console.log(x);
const isStrict = (function () {
  return !this;
})();
console.log(isStrict);

const user = "John";
const age = 25;
const message = "Hello";
console.log(user, age, message);
