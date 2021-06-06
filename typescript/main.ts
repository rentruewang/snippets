class Student {
  fullName: string;
  constructor(
    public firstName: string,
    public middleInitial: string,
    public lastName: string
  ) {
    this.fullName = firstName + " " + middleInitial + " " + lastName;
  }
}

interface Person {
  firstName: string;
  lastName: string;
}

function greeter(person: Person) {
  return "Hello, " + person.firstName + " " + person.lastName;
}

let user = new Student("Jane", "M.", "User");

function greet(person: Person, date: Date) {
  console.log(`Hello ${person}, today is ${date}!`);
}

greet(user, new Date());

let obj: any = { x: 0 };
// obj.foo();
// obj();
obj.bar = 100;
obj = "hello";
const nn: number = obj;
function printName(obj: { first: string; last?: string }) {
  console.log(obj.first, obj.last ?? "");
}
printName({ first: "Bob" });
printName({ first: "Alice", last: "Alisson" });

type Point = {
  x: number;
  y: number;
};

function printCoord(pt: Point) {
  console.log("The coordinate's x value is " + pt.x);
  console.log("The coordinate's y value is " + pt.y);
}

const point: Point = { x: 100, y: 100 } as const;

printCoord(point);
const hundred: bigint = 100n;
console.log(hundred);

function printAll(strs?: string | string[]) {
  if (typeof strs === "object") {
    for (const s of strs) {
      console.log(s);
    }
  } else if (typeof strs === "string") {
    console.log(strs);
  } else {
    // do nothing
  }
}
