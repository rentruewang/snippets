let person = {
  name: "class",
  hello: function (thing) {
    console.log(this.name + " : " + thing);
  },
};

person.hello(1);
person.hello.call({ name: "call" }, 2);
person.hello.apply({ name: "apply" }, [3]);

let another = person.hello.bind({ name: "bind" });
another(4);
