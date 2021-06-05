"use strict";

// Defined to allow copy paste from sources using alert
var alert = console.log;

function thisIsAFunc(param) {
  alert(param);
}

thisIsAFunc();

function showMessage(from, text) {
  from = "*" + from + "*"; // make "from" look nicer

  alert(from + ": " + text);
}

let from = "Ann";

showMessage(from, "Hello");
alert(from);

showMessage("Ann");
showMessage();

function defValue(array = []) {
  array.push(0);
  alert(array);
}

defValue();
defValue();

// Using function declaration before defined
sayHi();

function sayHi() {
  alert("Hi");
}

// Cannot use function expression before defined.
// Cannot access before initialization.
// sayHello();

let sayHello = function () {
  alert("Hello");
};

// alert(sayHi);

let saySth = () => alert("Something");
saySth();

let getSth = () => {
  let thing = "something";
  return thing;
};

alert(getSth());
