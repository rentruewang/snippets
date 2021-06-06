interface User {
  id: number;
  admin: boolean;
}

interface DB {
  filterUsers(filter: (this: User) => boolean): User[];
}

const DBObj: {
  allUsers: User[];
  filterUsers(filter: (this: User) => boolean): User[];
} = {
  allUsers: [
    { id: 0, admin: false },
    { id: 1, admin: true },
  ],
  filterUsers(filter: (this: User) => boolean): User[] {
    return this.allUsers.filter(filter);
  },
};

const getDB: () => DB = function () {
  return DBObj;
};

const newdb = getDB();
const newAdmins = newdb.filterUsers(function (this: User) {
  console.log(this);
  return this.admin;
});

console.log(newAdmins);

type GConstructor<T = {}> = new (...args: any[]) => T;
