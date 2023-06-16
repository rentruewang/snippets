// Ok without parenthesis
if (0) console.log(1);
// Better with them.
if (1) {
  console.log(0);
}

const a = null;
console.log(a ?? 1, a || 2);
const b = 0;
console.log(b ?? 1, b || 2);

let i = 0;
for (; i < 3; ++i) {}
console.log(i);
