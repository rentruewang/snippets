# Copyright (c) 2024 RenChu Wang - All Rights Reserved

__something = "something"


class A:
    __x = "x"

    def __init__(self):
        print(self.__x)

        # This is also mangled.
        print(__something)


class B:
    def __init__(self):
        self.__stupid = "stupid"
        print(self.__stupid)


if __name__ == "__main__":
    B()
    A()
