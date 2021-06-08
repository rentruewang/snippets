// TypeScript doesn't seem to support this natively. Using JS:

import { spawn, Thread, Worker } from "threads";

(async () => {
  const auth = await spawn(new Worker("./worker"));
  const hashed = await auth.hashPassword!("Super secret password", "1234");

  console.log("Hashed password:", hashed);

  await Thread.terminate(auth);
})();
