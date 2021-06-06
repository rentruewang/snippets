type GreetFunction = (a: string) => void;
function geter(fn: GreetFunction) {}

interface CallOrConstruct {
  new (s: string): Date;
  (n?: number): number;
}

function fn(ctor: CallOrConstruct) {
  return new ctor("hello");
}

function firstElement<Type>(arr: Type[]): Type | undefined {
  return arr[0];
}

type hasLength = {
  length: number;
};

function longest<Type extends { length: number }>(a: Type, b: Type) {
  if (a.length >= b.length) {
    return a;
  } else {
    return b;
  }
}

function shorter<Type extends hasLength>(a: Type, b: Type): Type {
  return a.length <= b.length ? a : b;
}

const longerArray = longest([1, 2], [1, 2, 3]);

function takeOptional(opt: number, x: number = 0) {}

takeOptional(1);

function makeDate(timestamp: number): Date;
function makeDate(m: number, d: number, y: number): Date;
function makeDate(mOrTimestamp: number, d?: number, y?: number): Date {
  if (d !== undefined && y !== undefined) {
    return new Date(y, mOrTimestamp, d);
  } else {
    return new Date(mOrTimestamp);
  }
}

function fnbs(x: boolean): void;
function fnbs(x: string): void;
function fnbs(x: boolean | string): void {
  console.log(x);
}

const userr = {
  id: 123,

  admin: false,
  becomeAdmin: function () {
    this.admin = true;
  },
};

function identity<Type>(arg: Type): Type {
  return arg;
}

let myIdentity: { <Type>(arg: Type): Type } = identity;
