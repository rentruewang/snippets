async function mylog(str: string, sec: number): Promise<void> {
  return new Promise((resolve) => setTimeout(() => resolve(str), sec)).then(
    (val) => console.log(val)
  );
}

async function first(): Promise<void> {
  await mylog("b", 3000);
  await mylog("c", 1000);
}

async function second(): Promise<void> {
  await mylog("a", 2000);
}

async function main(): Promise<void> {
  first();
  second();
}

main();
