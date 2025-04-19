# Copyright (c) RenChu Wang - All Rights Reserved

import json
from collections.abc import Mapping
from typing import Any


class SomeClass:
    """
    Represents a bounding box as well as other metadata.
    This is the output of the layout parser,
    and supports various operations used on bounding boxes.
    """

    __slots__ = "field", "extra"

    def __init__(self, field: int, extra: dict[str, Any] | None = None):
        self.field = field
        self.extra = extra or {}

    def __repr__(self):
        return json.dumps(self.__dict__, sort_keys=True, default=vars)

    @property
    def __dict__(self) -> dict[str, Any]:
        return {"field": self.field, **self.extra}

    def __hash__(self):
        return hash(repr(self))

    def __iter__(self):
        yield self.field
        yield from self.extra.values()

    def __getattr__(self, key):
        return self[key]

    def __setattr__(self, name, value):
        self[name] = value

    def __eq__(self, other: Mapping) -> bool:
        return {**self} == {**other}

    def keys(self):
        yield "field"
        yield from self.extra.keys()

    def __getitem__(self, key: str):
        if key in self.__slots__:
            return super().__getattribute__(key)

        if key in self.extra:
            return self.extra[key]

        raise AttributeError(f"Invalid key: {key}")

    def __setitem__(self, key: str, value):
        if key in self.__slots__:
            super().__setattr__(key, value)
            return

        if key in self.extra:
            self.extra[key] = value
            return

        raise AttributeError(f"Invalid key: {key}")


if __name__ == "__main__":
    sc = SomeClass(1, {"a": 2, "b": 3})

    # {"field": 1, "a": 2, "b": 3}
    print(sc)

    sc.a = 4
    sc.b = 5

    # {"field": 1, "a": 4, "b": 5}
    print(sc)

    # Raise AttributeError
    sc.c = 6
