"use strict";

import sha256 from "js-sha256";
import { expose } from "threads/worker";

expose({
  hashPassword(password, salt) {
    return sha256(password + salt);
  },
});
