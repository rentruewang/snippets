from dataclasses import dataclass
from types import MethodType
from typing import Any


@dataclass
class C1:
    def method(self, *args: Any, **kwds: Any) -> Any:
        print("c1 method", self, args, kwds)

    def __call__(self, *args: Any, **kwds: Any) -> Any:
        print("c1 call", self, args, kwds)


@dataclass
class C2:
    method = lambda self, *args, **kwds: print("c2 method", self, args, kwds)
    __call__ = lambda self, *args, **kwds: print("c2 call", self, args, kwds)


@dataclass
class C3:
    pass


C3.method = lambda self, *args, **kwds: print("c3 method", self, args, kwds)
C3.__call__ = lambda self, *args, **kwds: print("c3 call", self, args, kwds)


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
        lambda self, *args, **kwds: print("c4 call", self, args, kwds), c4
    )
    c4.method = MethodType(
        lambda self, *args, **kwds: print("c4 method", self, args, kwds), c4
    )

    c1.method("a", "b", c="c")
    c1("a", "b", c="c")

    c2.method("a", "b", c="c")
    c2("a", "b", c="c")

    c3.method("a", "b", c="c")
    c3("a", "b", c="c")

    c4.method("a", "b", c="c")
    # c4("a", "b", c="c")
