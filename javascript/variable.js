// var and let have different scoping rules
{
  var a = undefined;
  console.log(a);

  var a;
  //   Already declared.
  //   let a;

  let b;
  // Already declared
  // let b;
  // Already declared
  // var b;
  console.log(b);

  var x = 3;
  let y = 4;

  x = "8";
  console.log(x, y);
}

console.log(x);
// Reference error
// console.log(y);

const bigInt = 1234567890123456789012345678901234567890n;
console.log(bigInt);

let v;
// null == undefined but not other values
console.log(v == undefined, v === undefined, 0 == undefined, 0 === undefined);
console.log(v == null, v === null, 0 == null, 0 === null);
v = v ?? 9;
console.log(v);

console.log(["1", 2, 3, 3, 4].join(" "));

console.log([12, 2, 3, 45].slice(1, -1), [32321][-1], [12, 3, 4, 5, 6].length);

for (let char of [12, , 5252, 1]) {
  console.log(char);
}

// Error: not iterable
// for (let item of { key: "value" }) {
//   console.log(item);
// }

let obj = { [-1]: 7, 1: 4, 2: 3, [0]: 0, key: "value", length: 2 };
let arr = Array.from(obj);
console.log(arr);
for (let item of arr) {
  console.log("item", item);
}
