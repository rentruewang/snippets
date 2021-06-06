"use strict";

// Defined to allow copy paste from sources using alert
const alert = console.log;

function thisIsAFunc(param) {
  alert(param);
}

thisIsAFunc();

function showMessage(from, text) {
  from = "*" + from + "*"; // make "from" look nicer

  alert(from + ": " + text);
}

const from = "Ann";

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

const sayHello = function () {
  alert("Hello");
};

// alert(sayHi);

const saySth = () => alert("Something");
saySth();

const getSth = () => {
  const thing = "something";
  return thing;
};

alert(getSth());

function f(...a) {
  console.log(a);
}
console.log(f.length);

function say() {
  alert(this.name);
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
