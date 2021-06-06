interface Fish {
  swim: () => void;
}
interface Bird {
  fly: () => void;
}

function move(animal: Fish | Bird) {
  if ("swim" in animal) {
    return animal.swim();
  }

  return animal.fly();
}

function isFish(animal: Fish | Bird): animal is Fish {
  return (animal as Fish).swim != undefined;
}

const MyArray = [
  { name: "Alice", age: 15 },
  { name: "Bob", age: 23 },
  { name: "Eve", age: 38 },
];

type MyPerson = typeof MyArray[number];
// type MyPerson = {
//   name: string;
//   age: number;
// };

type Age = typeof MyArray[number]["age"];
// type Age = number;

type ArrVal = MyPerson[keyof MyPerson];

type Age2 = MyPerson["age"];
// type Age2 = number;
