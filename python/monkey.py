# Copyright (c) RenChu Wang - All Rights Reserved

from types import MethodType


class I:
    i: int

    def __init__(self, i):
        self.i = i

    def method(self):
        return f"I({self.i})"

    def __str__(self):
        return f"Magic I({self.i})"


class PatchI1:
    def __init__(self, i):
        self.i = i
        self.i.method = MethodType(self.string, self.i)

    def string(self, iself):
        return f"Injected 1({iself.i})"


class PatchI2:
    def __init__(self, i):
        self.i = i
        self.i.method = MethodType(lambda self: f"Injected 2({self.i})", self.i)


class PatchI3:
    def __init__(self, i):
        self.i = i
        # This does not work because python does not look up magic methods on the instances.
        # See: https://stackoverflow.com/a/10376655
        self.i.__str__ = MethodType(lambda self: f"Injected 3({self.i})", self.i)


if __name__ == "__main__":
    i = I(10)
    print(i.method())

    pi1 = PatchI1(I(10))
    print(pi1.i.method())

    pi2 = PatchI2(I(10))
    print(pi2.i.method())

    pi3 = PatchI3(I(100))
    print(pi3.i)
