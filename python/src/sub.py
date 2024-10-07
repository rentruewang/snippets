# Copyright (c) 2024 RenChu Wang - All Rights Reserved

from typing import Any


class Super1:
    @classmethod
    def __init_subclass__(cls, **kwargs: Any) -> None:
        print(cls, kwargs)


class Sub1(Super1):
    pass


class Sub2(Super1, param="hello", argument=123):
    pass


class Super2:
    @classmethod
    def __init_subclass__(cls, required: str) -> None:
        print(cls, required)


# Would fail:
# TypeError: Super2.__init_subclass__() missing 1 required positional argument: 'required'
# class Sub3(Super2):
#     pass


class Sub4(Super2, required="yes"):
    pass


if __name__ == "__main__":
    Sub1()
    Sub2()
    # Sub3()
    Sub4()
