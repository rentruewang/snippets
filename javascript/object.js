"use strict";

let k = 5;

let someObj = {
  // computed properties
  4: 3,
  [k]: 11,
  name: "John",
  "age is": 30,
  k,
  [6]: k,
  [5]: k + 1,
};

console.log(someObj);
someObj["likes birds"] = true;
someObj.isAdmin = true;
// console.log(someObj);
someObj[3] = 4;
// someObj.1 = 0;
delete someObj.name;
console.log(someObj, "likes birds" in someObj);

// Can't do this in strict mode
// for (field in someObj) {
for (let field in someObj) {
  console.log(field, someObj[field]);
}
// console.log("field=", field);

let vars = [{ key: "key", value: "value" }];
vars[0].key = "newkey";
vars[0].value = "newvalue";
vars[1] = { key: "kk", value: "vv" };

console.log(vars, vars[1]);

let codes = {
  49: "Germany",
  41: "Switzerland",
  44: "Great Britain",
  // ..,
  1: "USA",
};

for (let code in codes) {
  console.log(typeof code, Number(code), code); // 1, 41, 44, 49
}

let array = [302942, 198352, 123141, 235292];
for (let i in array) {
  console.log(typeof i, Number(i), i, typeof array[i]);
}

let a = {};
let b = {};
console.log(a == b, a === b);

let c = Object.assign({}, a);
console.log(c == a, c === a);

let perm = { name: "John" };

let permissions1 = { canView: true };
let permissions2 = { canEdit: true };

Object.assign(perm, permissions1, permissions2);

console.log(perm);

let user = {
  name: "John",
  sizes: {
    height: 182,
    width: 50,
  },
  sayHi() {
    console.log("Hi,", this.name, this);
  },
};

let clone = Object.assign({}, user);

console.log(user.sizes === clone.sizes);

++user.sizes.width;
console.log(clone.sizes.width);
user.sayHi();

let method = user.sayHi;

let hijack = {
  name: 382934,
  method,
  // arrowed function's this does not work the same way
  method2: () => {
    console.log(this);
  },
};
hijack.method();
hijack.method2();

user.method2 = hijack.method2;
user.method2();

function callBack(func) {
  func();
}

function callThis() {
  console.log(this);
}

// callBack(callThis);

function User(name) {
  this.name = name;
  this.isAdmin = false;

  this.sayHi = function () {
    console.log(this.name, "say hi.");
  };
}

user = new User("Jack");
console.log(user);

user.sayHi();
console.log(user.nonExistent);

console.log(user == new User("Jack"), user === new User("Jack"));
let human = {
  name: "John",
  surname: "Smith",

  get fullName() {
    return `${this.name} ${this.surname}`;
  },

  get lowerName() {
    return this.name.toLowerCase();
  },

  set screamingName(value) {
    this.name = value.toUpperCase();
  },
};

for (let field of Object.entries(human)) {
  console.log(field);
}

human.screamingName = "jonathan";
console.log(human.fullName);

let user1 = {
  name: "user1",
  callThis,
};

let user2 = {
  name: "user2",
  callThis,
};

let callbackAnon = () => user1.callThis();

callbackAnon();
user1 = user2;
// Anonymous function uses this in the context.
callbackAnon();
