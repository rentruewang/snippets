# Copyright (c) RenChu Wang - All Rights Reserved

import dataclasses as dcls


class Meta(type):
    def __call__(self, *args, **kwargs):
        print("meta.__call__", args, kwargs)
        obj = super().__call__(*args, **kwargs)
        return obj


@dcls.dataclass(frozen=True, init=False)
class C(metaclass=Meta):
    i: int
    j: float = 2.0

    def __new__(cls, *args, **kwargs):
        print("new", args, kwargs)
        inst = super().__new__(cls)
        print("new", type(inst))
        inst._init(*args, **kwargs)
        print("new", type(inst), inst)
        return inst

    def _init(self, i, j):
        object.__setattr__(self, "i", i)
        object.__setattr__(self, "j", j)
        print(i, j, "init")


if __name__ == "__main__":
    c = C(1, 2.0)
