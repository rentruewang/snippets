"use strict";

const alert = console.log;

class User {
  name = "default";

  constructor(name) {
    if (Boolean(name)) {
      this.name = name;
    }
  }
  sayHi() {
    alert(this.name);
  }
}

function User1() {
  this.value = "Mary";
}

alert(typeof User);
alert(new User("Mary"));
alert(new User(""));
alert(new User1("Mary"));

// Does not work under strict mode
// User1("Ma");
// User("");

class Button {
  constructor(value) {
    this.value = value;
  }

  click() {
    alert(this);
    alert(this.value);
  }
}

let button = new Button("hello");

// setTimeout(button.click, 1000);

class Animal {
  constructor(name, ...args) {
    alert(args);
    this.speed = 0;
    this.name = name;
  }
  run(speed) {
    this.speed = speed;
    alert(`${this.name} runs with speed ${this.speed}.`);
  }
  stop() {
    alert("Animal stop:", this);
    this.speed = 0;
    alert(`${this.name} stands still.`);
  }
}

class Rabbit extends Animal {
  constructor(...args) {
    super(...args);
  }
  hide() {
    alert(`${this.name} hides!`);
  }
  stop() {
    alert("Rabbit stop:", this);
    super.stop();
    this.hide();
  }
}

let rabbit = new Rabbit("rab", "bit");
rabbit.stop();

class CoffeeMachine {
  #waterLimit = 200;

  #fixWaterAmount(value) {
    if (value < 0) return 0;
    if (value > this.#waterLimit) return this.#waterLimit;
  }

  setWaterAmount(value) {
    this.#waterLimit = this.#fixWaterAmount(value);
  }
}

let coffeeMachine = new CoffeeMachine();
// alert(coffeeMachine.#waterLimit);

alert(Object.prototype, typeof Object.prototype, {}.prototype);

let sayMixin = {
  say(phrase) {
    alert(phrase);
  },
};

let sayHiMixin = {
  __proto__: sayMixin, // (or we could use Object.setPrototypeOf to set the prototype here)

  sayHi() {
    // call parent method
    super.say(`Hello ${this.name}`); // (*)
  },
  sayBye() {
    super.say(`Bye ${this.name}`); // (*)
  },
};

class Person {
  constructor(name) {
    this.name = name;
  }
}

Object.assign(Person.prototype, sayHiMixin);
alert(Person, Person.prototype, Person.constructor.name, new Person().name);
class MyError extends Error {
  constructor(message) {
    super(message);
    this.name = this.constructor.name;
  }
}
alert(new MyError("message").name);
