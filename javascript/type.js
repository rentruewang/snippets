"use strict";

let a = 3;
console.log(a, String(a), Number(String(a)));

let msg = "hello this is not a number";
console.log(Number(msg));

let c = -"3";
console.log(c, 1 + "2", "1" + 2);

console.log("1" == "2", "1" == 1, 0 == "0");
console.log("1" === "2", "1" === 1, 0 === "0");
console.log(Number(null), Number(null) === 0, null == 0, null >= 0);
console.log(undefined == null, undefined === null, undefined === undefined);
console.log(NaN == NaN, NaN === NaN, NaN <= NaN, NaN >= NaN);
