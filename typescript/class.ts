class BeeKeeper {
  hasMask: boolean = true;
}

class ZooKeeper {
  nametag: string = "Mikle";
}

class Animal {
  numLegs: number = 4;
}

class Bee extends Animal {
  keeper: BeeKeeper = new BeeKeeper();
}

class Lion extends Animal {
  keeper: ZooKeeper = new ZooKeeper();
}

function createInstance<A extends Animal>(c: new () => A): A {
  return new c();
}

createInstance(Lion).keeper.nametag;
createInstance(Bee).keeper.hasMask;

class Sprite {
  name = "";
  x = 0;
  y = 0;

  constructor(name: string) {
    this.name = name;
  }

  setPos(x: number, y: number) {
    [this.x, this.y] = [x, y];
  }
}

type Constructor = new (...args: any[]) => {};

function Scale<TBase extends Constructor>(Base: TBase) {
  return class Scaling extends Base {
    _scale = 1;

    setScale(scale: number) {
      this._scale = scale;
    }

    get scale(): number {
      return this._scale;
    }
  };
}

const ScaledSprite = Scale(Sprite);

console.log(new Sprite("sprite"), new ScaledSprite("sprite"));

type GConstructor<T = {}> = new (...args: any[]) => T;

type Positionable = GConstructor<{ setPos: (x: number, y: number) => void }>;
type Spritable = GConstructor<typeof Sprite>;
type Loggable = GConstructor<{ print: () => void }>;

function Jumpable<TBase extends Positionable>(Base: TBase) {
  return class Jumpable extends Base {
    jump() {
      this.setPos(0, 20);
    }
  };
}
const JumpableSprite = Jumpable(ScaledSprite);
const js = new JumpableSprite("jump");
js.jump();
console.log(js);

const Pausable = (target: typeof Player) => {
  return class Pausable extends target {
    shouldFreeze = false;
  };
};

@Pausable
class Player {
  x = 0;
  y = 0;
}

class TwoD {
  // This is the default value of a member.
  x: number = 0;
  y: number = 0;

  constructor(x: number, y: number) {
    this.x = -x;
    this.y = -y;
  }
}

const pt = new TwoD(8, 1);
pt.x = 0;
pt.y = 0;
class GoodGreeter {
  name: string;

  constructor() {
    this.name = "hello";
  }
}

class OKGreeter {
  // Not initialized, but no error
  // Only use this when the field is really initialized
  name!: string;
}

console.log(new OKGreeter().name);

class C {
  _length = 0;
  get length() {
    return this._length;
  }
  set length(value) {
    this._length = value;
  }
}
class D {
  _length = 0;
  get length() {
    return this._length;
  }
}
class MyClass {
  [s: string]: boolean | ((s: string) => boolean);

  // Not allowed
  // num: number;

  check(s: string) {
    return this[s] as boolean;
  }
}

interface Pingable {
  ping(): void;
}

class Sonar implements Pingable {
  ping() {
    console.log("ping!");
  }
}

// class Ball implements Pingable {
//   pong() {
//     console.log("pong!");
//   }
// }

interface I1 {
  field: number;
}
interface I2 {
  field: boolean;
}
// Doesn't work
// interface I3 extends I1, I2 {}

type T1 = { field: number };
type T2 = { field: boolean };
// T3 is never
type T3 = T1 & T2;

// This part is ok. However, prettier doesn't yet support `override` keyword so I'm commenting out this part.
// class Base {
//   greet() {
//     console.log("Hello, world!");
//   }
// }

// class Derived extends Base {
//   override greet(name?: string) {
//     if (name === undefined) {
//       super.greet();
//     } else {
//       console.log(`Hello, ${name.toUpperCase()}`);
//     }
//   }
// }

// const d = new Derived();
// d.greet();
// d.greet("reader");

// class Base {
//   name = "base";
//   constructor() {
//     console.log("My name is " + this.name);
//   }
// }

// class Derived extends Base {
//   override name = "derived";
// }
// const d = new Derived();

class MsgError extends Error {
  constructor(m: string) {
    super(m);
  }
  sayHello() {
    return "hello " + this.message;
  }
}

console.log(new MsgError("abc").sayHello());
class Greeter {
  public greet() {
    console.log("Hello, " + this.getName());
  }
  protected getName() {
    return "hi";
  }
}

class SpecialGreeter extends Greeter {
  public howdy() {
    console.log("Howdy, " + this.getName());
  }
}
const g = new SpecialGreeter();
g.greet();
// getName is protected
// g.getName();

class MySafe {
  private secretKey: number;
  constructor(num: number) {
    this.secretKey = num;
  }
  get key() {
    return this.secretKey;
  }
  static x = 0;
  static printX() {
    console.log(MySafe.x);
  }
}
console.log(new MySafe(8796));

class Box<Type> {
  contents: Type;
  constructor(value: Type) {
    this.contents = value;
  }
}

const b = new Box("hello!");
console.log(b);
class MyC {
  name = "MyC";
  getName() {
    return this.name;
  }
}
const c = new MyC();
const obj = {
  name: "obj",
  getName: c.getName,
};

// Prints "obj", not "MyC"
console.log(obj.getName());

class MyC2 {
  name = "MyC2";
  getName = () => {
    return this.name;
  };
}
const c2 = new MyC2();
const g2 = c2.getName;
// Prints "MyC2" instead of crashing
console.log(g2());

class MyC3 {
  name = "MyC3";
  getName(this: MyC3) {
    return this.name;
  }
}
const c3 = new MyC3();
// OK
c3.getName();

// Error, would crash
// const g3 = c3.getName;
// console.log(g3());

class MyC4 {
  name = "MyC4";
  getName(this: MyC4) {
    console.log(this);
    // return this.name;
  }
}
const c4 = new MyC4();
// OK
c4.getName();

// Error, can crash if using this.method
// const g4 = c4.getName;
// console.log("g4");
// g4();
const g4 = c4.getName.bind(c4);
console.log("g4");
g4();

class MyC5 {
  name = "MyC5";
  getName() {
    console.log("myc5", this);
  }
}
const c5 = new MyC5();
// OK
c5.getName();

const g5 = c5.getName;
console.log(g5());

class MyCThis {
  name = "MyCThis";
  getName(this: this) {
    console.log("This type!", this);
    return this.name;
  }
}
const cthis = new MyCThis();
// OK
cthis.getName();
c5.getName = cthis.getName;
c5.getName();

// Error, would crash
// const gthis = cthis.getName;
// console.log(gthis());

class ThisBox {
  contents: string = "";
  setTo(value: string) {
    console.log(value);
    this.contents = value;
    return this;
  }
}

class ClearableBox extends ThisBox {
  clear() {
    this.contents = "";
  }
}
const a = new ClearableBox();
const whatType = a.setTo("hello");

class SameBox {
  content: string = "";
  sameAs(other: this) {
    return other.content === this.content;
  }
}
class DerivedBox extends SameBox {
  otherContent: string = "?";
}
const sameBox = new SameBox();
const derivedBox = new DerivedBox();
// Javascript duck typing makes the first 3 cases valid, but 4 will fail.
console.log(sameBox.sameAs(sameBox));
console.log(sameBox.sameAs(derivedBox));
console.log(derivedBox.sameAs(derivedBox));
// console.log(derivedBox.sameAs(sameBox));

class FileSystemObject {
  // These `a is b`s are type hints for control flow analysis
  isFile(): this is FileRep {
    return this instanceof FileRep;
  }
  isDirectory(): this is Directory {
    return this instanceof Directory;
  }
  isNetworked(): this is Networked & this {
    return this.networked;
  }
  constructor(public path: string, private networked: boolean) {}
}

class FileRep extends FileSystemObject {
  constructor(path: string, public content: string) {
    super(path, false);
  }
}

class Directory extends FileSystemObject {
  children: FileSystemObject[] = [];
}

interface Networked {
  host: string;
}

const fso: FileSystemObject = new FileRep("foo/bar.txt", "foo");

if (fso.isFile()) {
  fso.content;
} else if (fso.isDirectory()) {
  fso.children;
} else if (fso.isNetworked()) {
  fso.host;
}

class CoolBox<T> {
  value?: T;

  hasValue(): this is { value: T } {
    return this.value !== undefined;
  }
}

const box = new CoolBox();
box.value = "Gameboy";

box.value;

if (box.hasValue()) {
  box.value;
}
class Params {
  constructor(
    public readonly x: number,
    protected y: number,
    private z: number
  ) {}

  get all(): number {
    return this.x + this.y + this.z;
  }
}
const param = new Params(1, 2, 3);
console.log(param.x, param.all);
// console.log(param.z);
const someClass = class<Type> {
  content: Type;
  constructor(value: Type) {
    this.content = value;
  }
};

const m = new someClass("Hello, world");
abstract class Base {
  abstract getName(): string;

  printName() {
    console.log("Hello, " + this.getName());
  }
}

// No, you cant create an instance of abstract class
// const b = new Base();
// function gt(ctor: typeof Base) {
//   const instance = new ctor();
//   instance.printName();
// }

function gt(ctor: new (...args: any[]) => Base) {
  const instance = new ctor();
  return instance;
}

class Point1 {
  x = 0;
  y = 0;
}

class Point2 {
  x = 0;
  y = 0;
}

// OK
const p: Point1 = new Point2();

class PersonN {
  name: string = "";
  age: number = 0;
}

class EmployeeN {
  name: string = "";
  age: number = 0;
  salary: number = 0;
}

// OK
const ps: PersonN = new EmployeeN();
ps.age = 3;
// ps.salary;
// Same as go's interface{}
class Empty {}

function fn(x: Empty) {
  console.log(x);
}

fn(1);
fn(ps);
fn(a);
fn({});
