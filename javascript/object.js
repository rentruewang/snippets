"use strict";

const k = 5;

const someObj = {
  // computed properties
  4: 3,
  [k]: 11,
  name: "John",
  "age is": 30,
  k,
  6: k,
  5: k + 1,
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
for (const field in someObj) {
  console.log(field, someObj[field]);
}
// console.log("field=", field);

const vars = [{ key: "key", value: "value" }];
vars[0].key = "newkey";
vars[0].value = "newvalue";
vars[1] = { key: "kk", value: "vv" };

console.log(vars, vars[1]);

const codes = {
  49: "Germany",
  41: "Switzerland",
  44: "Great Britain",
  // ..,
  1: "USA",
};

for (const code in codes) {
  console.log(typeof code, Number(code), code); // 1, 41, 44, 49
}

const array = [302942, 198352, 123141, 235292];
for (const i in array) {
  console.log(typeof i, Number(i), i, typeof array[i]);
}

const a = {};
const b = {};
console.log(a == b, a === b);

const c = Object.assign({}, a);
console.log(c == a, c === a);

const perm = { name: "John" };

const permissions1 = { canView: true };
const permissions2 = { canEdit: true };

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

const clone = Object.assign({}, user);

console.log(user.sizes === clone.sizes);

++user.sizes.width;
console.log(clone.sizes.width);
user.sayHi();

const method = user.sayHi;

const hijack = {
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
const human = {
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

for (const field of Object.entries(human)) {
  console.log(field);
}

human.screamingName = "jonathan";
console.log(human.fullName);

let user1 = {
  name: "user1",
  callThis,
};

const user2 = {
  name: "user2",
  callThis,
};

const callbackAnon = () => user1.callThis();

callbackAnon();
user1 = user2;
// Anonymous function uses this in the context.
callbackAnon();
