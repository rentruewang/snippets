# Copyright (c) 2024 RenChu Wang - All Rights Reserved

import dataclasses as dcls


@dcls.dataclass(frozen=True)
class DataClass:
    name: str
    value: int


class MissingMatcher:
    __match_args__ = "hello", "world"

    @property
    def hello(self):
        return "hello"


@dcls.dataclass(frozen=True)
class Nested:
    item: DataClass


class CustomMatcher:
    @property
    def __match_args__(self):
        # Property is ok as well.
        return "hello", "world"

    @property
    def hello(self):
        return "hello"

    @property
    def world(self):
        return "world"


if __name__ == "__main__":
    dc = DataClass(name="name", value=3)

    match dc:
        case DataClass(name=n, value=v):
            print(n, v)
        case _:
            raise ValueError

    # mm = MissingMatcher()

    # match mm:
    #     # Not matching
    #     case MissingMatcher(hello=h, world=w):
    #         print(h, w)
    #     case _:
    #         raise ValueError

    cm = CustomMatcher()

    match cm:
        case CustomMatcher(hello=h, world=w):
            print(h, w)
        case _:
            raise ValueError

    nested = Nested(dc)

    match nested:
        case Nested(item=DataClass(value=val, name=nam)):
            print(val, nam)
