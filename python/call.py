from dataclasses import dataclass
from types import MethodType
from typing import Any


@dataclass
class C1:
    def __call__(self, *args: Any, **kwds: Any) -> Any:
        print("c1", self, args, kwds)


@dataclass
class C2:
    __call__ = lambda self, *args, **kwds: print("c2", self, args, kwds)


@dataclass
class C3:
    pass


C3.__call__ = lambda self, *args, **kwds: print("c3", self, args, kwds)


@dataclass
class C4:
    pass


if __name__ == "__main__":
    c1 = C1()
    c2 = C2()
    c3 = C3()
    c4 = C4()

    # This will not work because magic methods are called on the classes.
    c4.__call__ = MethodType(
        lambda self, *args, **kwds: print("c4", self, args, kwds), c4
    )

    c1("a", "b", c="c")
    c2("a", "b", c="c")
    c3("a", "b", c="c")
    # c4("a", "b", c="c")
