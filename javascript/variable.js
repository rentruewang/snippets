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
