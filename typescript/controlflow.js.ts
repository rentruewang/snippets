// Ok without parenthesis
if (0) console.log(1);
// Better with them.
if (1) {
  console.log(0);
}

const ajs = null;
console.log(ajs ?? 1, ajs || 2);
const bjs = 0;
console.log(bjs ?? 1, bjs || 2);

let ijs = 0;
for (; ijs < 3; ++ijs) { }
console.log(ijs);
