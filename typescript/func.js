function map(arr, func) {
  return arr.map(func);
}
var parsed = map(["1", "2", "3"], function (n) {
  return parseInt(n);
});
console.log(parsed);
function longest(a, b) {
  if (a.length >= b.length) {
    return a;
  } else {
    return b;
  }
}
var longerArray = longest([1, 2], [1, , 3]);
console.log(longerArray);
function f(x) {
  console.log(x);
}
f();
f(10);
function makeDate(mOrTimestamp, d, y) {
  if (d !== undefined && y !== undefined) {
    return new Date(y, mOrTimestamp, d);
  } else {
    return new Date(mOrTimestamp);
  }
}
var d1 = makeDate(12345678);
var d2 = makeDate(5, 5, 5);
// function getDB(): {
//   users: User[];
//   filterUsers: (filter: (this: User) => boolean) => User[];
// } {
//   return {
//     users: [],
//     filterUsers(filter: (this: User) => boolean) {
//       return this.users.filter((user: User) => filter.call(user));
//     },
//   };
// }
function getDB() {
  var obj = {
    users: [],
    filterUsers: function (filter) {
      return this.users.filter(function (user) {
        return filter.call(user);
      });
    },
  };
  return obj;
}
var db = getDB();
var admins = db.filterUsers(function () {
  return this.admin;
});
var args = [8, 5];
// const args = [8, 5];
var angle = Math.atan2.apply(Math, args);
function identity(value) {
  return value;
}
var myIdentity = identity;
var myObjIdentity = identity;
var genI = identity;
// These are the same types.
myIdentity = myObjIdentity;
myObjIdentity = genI;
function somef() {
  return { x: 10, y: 3 };
}
console.log(typeof somef);
// parameter destructuring in JavaScript
// function showMenu({ title = "Menu", width = 100, height = 200 } = {}) {
//   console.log(`${title} ${width} ${height}`);
// }
function showMenu(_a, nullable, deftrue) {
  var title = _a.title,
    width = _a.width,
    _b = _a.height,
    height = _b === void 0 ? 33 : _b;
  if (deftrue === void 0) {
    deftrue = true;
  }
  console.log(
    title + " " + width + " " + height + ", " + nullable + ", " + deftrue
  );
}
showMenu({ title: "a title" });
