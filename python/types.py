from typing import TypeVar

Real = TypeVar("Real", int, float)


def f(n: float):
    print(n)


f(int(3))


def fnum(a: Real, b: Real) -> None:
    print(a, b, a + b)


fnum(int(1), int(2))
fnum(float(1), float(2))
# ints can be casted to floats. Will pass.
fnum(int(1), float(2))

AnyStr = TypeVar("AnyStr", str, bytes)


def fstr(a: AnyStr, b: AnyStr) -> None:
    print(a, b, a + b)


fstr("hello", "world")
fstr(b"hello", b"world")
# bytes cannot be casted to string. Will fail.
fstr(b"hello", "world")
