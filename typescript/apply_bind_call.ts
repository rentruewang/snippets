type SomePerson = {
  name: string;
  hello: (thing: number) => void;
};

type SomePerson1 = {
  name: string;
  hello(thing: number): void;
};

class SomePersonClass {
  name: string;

  constructor(name: string) {
    this.name = name;
  }

  hello(thing: number): void {
    console.log(this.name + " : " + thing);
  }
}

let person: SomePersonClass = {
  name: "class",
  hello: function (thing: number) {
    console.log(this.name + " : " + thing);
  },
};

function use_person(person: SomePerson) {
  person.hello(1);
  person.hello.call({ name: "call" }, 2);
  person.hello.apply({ name: "apply" }, [3]);

  let another = person.hello.bind({ name: "bind" });
  another(4);
}

use_person(person);
