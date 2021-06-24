function map<Input, Output>(
  arr: Input[],
  func: (arg: Input) => Output
): Output[] {
  return arr.map(func);
}

const parsed = map(["1", "2", "3"], (n) => parseInt(n));

console.log(parsed);

function longest<Type extends { length: number }>(a: Type, b: Type) {
  if (a.length >= b.length) {
    return a;
  } else {
    return b;
  }
}

const longerArray = longest([1, 2], [1, , 3]);
console.log(longerArray);

function f(x?: number) {
  console.log(x);
}
f();
f(10);

function makeDate(timestamp: number): Date;
function makeDate(m: number, d: number, y: number): Date;
function makeDate(mOrTimestamp: number, d?: number, y?: number): Date {
  if (d !== undefined && y !== undefined) {
    return new Date(y, mOrTimestamp, d);
  } else {
    return new Date(mOrTimestamp);
  }
}
const d1 = makeDate(12345678);
const d2 = makeDate(5, 5, 5);
// const d3 = makeDate(1, 3);

interface User {
  name: string;
  admin: boolean;
  becomeAdmin: () => void;
}

interface DB {
  filterUsers(filter: (this: User) => boolean): User[];
}

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
  let obj: {
    users: User[];
    filterUsers: (filter: (this: User) => boolean) => User[];
  } = {
    users: [],
    filterUsers(filter: (this: User) => boolean) {
      return this.users.filter((user: User) => filter.call(user));
    },
  };
  return obj;
}

const db: DB = getDB();
const admins = db.filterUsers(function (this: User) {
  return this.admin;
});

const args = [8, 5] as const;
// const args = [8, 5];
const angle = Math.atan2(...args);

interface GenericIdentityFn {
  <Type>(arg: Type): Type;
}

function identity<Type>(value: Type): Type {
  return value;
}
let myIdentity: <Type>(arg: Type) => Type = identity;
let myObjIdentity: { <Type>(arg: Type): Type } = identity;

let genI: GenericIdentityFn = identity;

// These are the same types.
myIdentity = myObjIdentity;
myObjIdentity = genI;

function somef() {
  return { x: 10, y: 3 };
}
type P = ReturnType<typeof somef>;
console.log(typeof somef);

// parameter destructuring in JavaScript
// function showMenu({ title = "Menu", width = 100, height = 200 } = {}) {
//   console.log(`${title} ${width} ${height}`);
// }
function showMenu(
  {
    title,
    width,
    height = 33,
  }: {
    title: string;
    width?: number;
    height?: number;
  },
  nullable?: boolean,
  deftrue: boolean = true
) {
  console.log(`${title}, ${width} ${height}, ${nullable}, ${deftrue}`);
}
showMenu({ title: "a title" });
