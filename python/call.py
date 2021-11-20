from dataclasses import dataclass
from types import MethodType
from typing import Any


class SomeCallable:
    def __call__(self, *args, **kwargs):
        print("some callable", args, kwargs)


@dataclass
class C1:
    def method(*args: Any, **kwargs: Any) -> Any:
        print("c1 method", args, kwargs)

    def __call__(*args: Any, **kwargs: Any) -> Any:
        print("c1 call", args, kwargs)


@dataclass
class C2:
    method = lambda *args, **kwargs: print("c2 method", args, kwargs)
    __call__ = lambda *args, **kwargs: print("c2 call", args, kwargs)
    sc = SomeCallable()


@dataclass
class C3:
    pass


C3.method = lambda *args, **kwargs: print("c3 method", args, kwargs)
C3.__call__ = lambda *args, **kwargs: print("c3 call", args, kwargs)
C3.sc = SomeCallable()


@dataclass
class C4:
    pass


if __name__ == "__main__":
    c1 = C1()
    c2 = C2()
    c3 = C3()
    c4 = C4()

    # This will not work because magic methods are called on the classes.
    c4.__call__ = MethodType(lambda *args, **kwargs: print("c4 call", args, kwargs), c4)
    c4.method = MethodType(lambda *args, **kwargs: print("c4 method", args, kwargs), c4)
    c4.sc = MethodType(SomeCallable(), c4)

    c1.method("a", "b", c="c")
    c1("a", "b", c="c")

    c2.method("a", "b", c="c")
    c2("a", "b", c="c")
    c2.sc("a", "b", c="c")

    c3.method("a", "b", c="c")
    c3("a", "b", c="c")
    c3.sc("a", "b", c="c")

    c4.method("a", "b", c="c")
    # c4("a", "b", c="c")
    c4.sc("a", "b", c="c")

    print(c1.method.__get__(c1, C1))
    print(c1.__call__.__get__(c1, C1))

    print(c2.method.__get__(c2, C2))
    print(c2.__call__.__get__(c2, C2))
    # print(c2.sc.__get__(c2, C2))

    print(c3.method.__get__(c3, C3))
    print(c3.__call__.__get__(c3, C3))
    # print(c3.sc.__get__(c3, C3))

    print(c4.method.__get__(c4, C4))
    print(c4.sc.__get__(c4, C4))
