# Copyright (c) RenChu Wang - All Rights Reserved

import dataclasses as dcls
from collections.abc import Callable


@dcls.dataclass(frozen=True)
class Base:
    based: str


@dcls.dataclass(frozen=True)
class Sub1(Base):
    sub: str


class Sub2(Base):
    sub: str


@dcls.dataclass(frozen=True)
class HasMethods:
    field: int = 3

    e = lambda self: print(self)
    f = print
    g: Callable = lambda self: print(self)


if __name__ == "__main__":
    s1 = Sub1(based="based", sub="sub")
    print(s1)

    # Not a dataclass, so that the fields are not overwritten.
    s2 = Sub2(based="based")
    print(s2)

    print(HasMethods(3))
    print(HasMethods(2, None))
    HasMethods(2, None).e()
    print(type(print))
