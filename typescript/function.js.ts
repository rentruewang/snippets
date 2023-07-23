// @ts-nocheck
"use strict";

function thisIsAFunc(param) {
  console.log(param);
}

thisIsAFunc();

function showMessage(from, text) {
  from = "*" + from + "*"; // make "from" look nicer

  console.log(from + ": " + text);
}

const from = "Ann";

showMessage(from, "Hello");
console.log(from);

showMessage("Ann");
showMessage();

function defValue(array = []) {
  array.push(0);
  console.log(array);
}

defValue();
defValue();

// Using function declaration before defined
// https://stackoverflow.com/questions/261599/why-can-i-use-a-function-before-its-defined-in-javascript
sayHi();

function sayHi() {
  console.log("Hi");
}

// Cannot use function expression before defined.
// Cannot access before initialization.
// sayHello();

const sayHello = function () {
  console.log("Hello");
};

// console.log(sayHi);

const saySth = () => console.log("Something");
saySth();

const getSth = () => {
  const thing = "something";
  return thing;
};

console.log(getSth());

function f(...a) {
  console.log(a);
}
console.log(f.length);

function say() {
  console.log(this.name);
}

const user = { name: "John", say };
const admin = { name: "Admin", say };

// func.call(obj, arg1, arg2) is equal to obj.func(arg1, arg2) is equal to func.apply(obj, [arg1, arg2])
admin.say.call(user);
user.say();
user.say.apply(admin, []);
admin.say();

const group = {
  title: "Our Group",
  students: ["John", "Pete", "Alice"],

  showList() {
    // this.students.forEach(function (student) {
    //   Error. In this case, this is the global context.
    //   console.log(this.title + ": " + student);
    // });
    this.students.forEach((student) => console.log(student));
  },
};

group.showList();

function func1js() {}

function func2js(a, b) {}

console.log(func1js.length);
// expected output: 0

console.log(func2js.length);
// expected output: 2
