import type { Cat, Wolf } from "./module.js";

type Animals = Cat | Wolf;

let myName: string = "Alice";

function greet(name: string) {
  console.log("Hello, " + name.toUpperCase() + "!!");
}
greet(myName);
// greet(33);

function getFavoriteNumber(): number {
  return 37;
}
// myName = getFavoriteNumber();

// A type alias
type Point = { x: number; y: number };
interface PointInterface {
  x: number;
  y: number;
}

function printPoint(pt: PointInterface) {
  let other = pt;
  console.log("x value is " + pt.x, other.x);
  console.log("y value is " + pt.y, other.y);
}
printPoint({ x: 3, y: 7 });

function printId(id: number | string) {
  console.log("Your ID is: " + id);
}
printId(101);
printId("202");
// printId({ myID: 22342 });
