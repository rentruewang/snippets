// interface Shape {
//   kind: "circle" | "square";
//   radius?: number;
//   sideLength?: number;
// }

interface Circle {
  kind: "circle";
  radius: number;

  area: () => number;
}
interface Square {
  kind: "square";
  length: number;

  area: () => number;
}

interface Rectangle {
  kind: "rect";
  width: number;
  height: number;

  area: () => number;
}

type Shape = Circle | Square | Rectangle;

function isCircle(shape: Shape): boolean {
  return shape.kind == "circle";
}

function isSquare(shape: Shape): boolean {
  return shape.kind == "square";
}

function square2Rect(square: Square): Rectangle {
  return {
    kind: "rect",
    width: square.length,
    height: square.length,
    area: () => getArea(square),
  };
}

function isRect(shape: Shape): boolean {
  return shape.kind == "rect";
}

function getArea(shape: Shape): number {
  switch (shape.kind) {
    case "circle":
      return Math.PI * Math.pow(shape.radius, 2);
    case "square":
      return Math.pow(shape.length, 2);
    case "rect":
      return shape.width * shape.height;
    default:
      let unreachable: never = shape;
      return unreachable;
  }
}

let area;
{
  let square = {
    kind: "square" as "square",
    length: 9,
    area: () => Math.pow(square.length, 2),
  };
  let rect = square2Rect(square);
  console.log(rect, rect.area());
  area = rect.area;
}
console.log(area());

type PersonType = { age: number; name: string; alive: boolean };
type Age = PersonType["age"];
type All = PersonType[keyof PersonType];
interface Animal {
  live(): void;
}
interface Dog extends Animal {
  woof(): void;
}

type Example1 = Dog extends Animal ? number : string;
type Example2 = RegExp extends Animal ? number : string;

type Flatten0<T> = T extends any[] ? T[number] : T;
type Flatten1<Type> = Type extends Array<infer Item> ? Item : Type;
type Flatten2<Type, Item> = Type extends Array<Item> ? Item : Type;

type Str = Flatten1<string[]>;
type Num = Flatten1<number>;
// infer can save the second type parameter.
type Num1 = Flatten2<number, number>;

// string[number] is the same as string because string is indexed with number
type isItStr = string[number];

type GetReturnType<Type> = Type extends (...args: never[]) => infer Return
  ? Return
  : never;

type Num2 = GetReturnType<() => number>;
type Str2 = GetReturnType<(x: string) => string>;
type Bools = GetReturnType<(a: boolean, b: boolean) => boolean[]>;

type ToArray<Type> = Type extends any ? Type[] : never;
type StrArrOrNumArr = ToArray<string | number>;
type ToArrayNonDist<Type> = [Type] extends [any] ? Type[] : never;
type StrOrNumArr = ToArrayNonDist<string | number>;

const StrOrNumArr = [];
type Horse = {};
type OnlyBoolsAndHorses = {
  [key: string]: boolean | Horse;
};

const conforms: OnlyBoolsAndHorses = {
  del: true,
  rodney: false,
};
type OptionsFlags<Type> = {
  [Property in keyof Type]: boolean;
};

type FeatureFlags = {
  darkMode: () => boolean;
  newUserProfile: () => boolean;
};

type FeatureOptions = OptionsFlags<FeatureFlags>;
type CreateMutable<Type> = {
  -readonly [Property in keyof Type]: Type[Property];
};

type LockedAccount = {
  readonly id: string;
  readonly name: string;
};

type UnlockedAccount = CreateMutable<LockedAccount>;
type Concrete<Type> = {
  [Property in keyof Type]-?: Type[Property];
};

type MaybeUser = {
  id: string;
  name?: string;
  age?: number;
};

type Ussr = Concrete<MaybeUser>;
type Getters<Type> = {
  [Property in keyof Type as `get${Capitalize<
    string & Property
  >}`]: () => Type[Property];
};

interface Human {
  name: string;
  age: number;
  location: string;
}

type LazyHuman = Getters<Human>;
type RemoveKindField<Type> = {
  [Property in keyof Type as Exclude<Property, "kind">]: Type[Property];
};

type KindlessCircle = RemoveKindField<Circle>;
type ExtractPII<Type> = {
  [Property in keyof Type]: Type[Property] extends { pii: true } ? true : false;
};

type DBFields = {
  id: { format: "incrementing" };
  name: { type: string; pii: true };
};

type ObjectsNeedingGDPRDeletion = ExtractPII<DBFields>;
const list = ["a", "b", "c"] as const;
type NeededUnionType = typeof list[number];
