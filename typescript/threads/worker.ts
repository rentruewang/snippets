import { sha256 } from "js-sha256";
import { expose } from "threads/worker";

expose({
  hashPassword(password, salt): any {
    return sha256(password + salt);
  },
});
