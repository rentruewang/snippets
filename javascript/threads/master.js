"use strict";

import { spawn, Thread, Worker } from "threads";

const auth = await spawn(new Worker("./worker"));
const hashed = await auth.hashPassword("Super secret password", "1234");

console.log("Hashed password:", hashed);

await Thread.terminate(auth);
