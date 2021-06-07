// Anonymous object types
function greet1(person: { name: string; age: number }) {
  return "Hello " + person.name;
}

// Named
interface Person1 {
  name: string;
  age: number;
}

function greet2(person: Person1) {
  return "Hello " + person.name;
}

type Person2 = {
  name: string;
  age: number;
};

function greet3(person: Person2) {
  return "Hello " + person.name;
}

declare class Person3 {
  name: string;
  age: number;
}

function greet4(person: Person3) {
  return `Hello ${person.name}`;
}

greet4({ name: "human", age: 3 });

interface PaintOptions {
  shape: Shape;
  xPos?: number;
  yPos?: number;
}

function getShape(): Shape {
  return {
    kind: "circle",
    radius: 10,
    area() {
      return Math.PI * Math.pow(this.radius, 2);
    },
  };
}

function paintShape(opts: PaintOptions) {
  console.log(opts.shape, opts.shape.area(), opts.xPos, opts.yPos);
}

const shape = getShape();
paintShape({ shape });
paintShape({ shape, xPos: 100 });
paintShape({ shape, yPos: 100 });
paintShape({ shape, xPos: 100, yPos: 100 });

const roArray: ReadonlyArray<string> = ["red", "green", "blue"];
console.log(roArray);
// roArray[0] = "purple";

function doSomething(pair: [string, number]) {
  let [a, b] = pair;
  a = "4";
  pair[1] = 8;
  console.log(a, b, pair);
}
const pair = ["hello", 83] as [string, number];
doSomething(pair);
console.log(pair);
// doSomething(["hello", 83, 2]);

type Either2dOr3d = [number, number, number?];

function setCoordinate(coo: Either2dOr3d) {
  const [x, y, z] = coo;
  if (z != undefined) {
    console.log(`Provided coordinates had ${coo.length} dimensions`, x, y, z);
  } else {
    console.log("it's 2d");
  }
}

setCoordinate([1, 2, 3]);
setCoordinate([1, 4]);
// setCoordinate([1]);
// setCoordinate([1, 8, 2, 2]);

function create<Type>(c: { new (): Type }): Type {
  return new c();
}

const array = [1, 2, 3, 4];
const slice = array.slice(0, 2);
const copy = array;
console.log(array, slice, copy);
slice[0] = -8;
slice[1] += 3;
++copy[3];
++copy[3];
++copy[3];
++copy[3];
console.log(array, slice, copy);
