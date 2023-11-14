from __future__ import annotations

import abc
import operator
from abc import ABC
from typing import Callable


class Expr(ABC):
    def Add(self, other: Expr) -> Expr:
        return Add(self, other)

    def Sub(self, other: Expr) -> Expr:
        return Sub(self, other)

    def Mul(self, other: Expr) -> Expr:
        return Mul(self, other)

    def simplify(self) -> Expr:
        return self

    @abc.abstractmethod
    def show(self) -> str:
        ...

    def toString(self) -> str:
        return self.show()


class Lit(Expr):
    _data: int

    def __init__(self, data: int) -> None:
        super().__init__()

        self._data = data

    def show(self) -> str:
        return str(self._data)

    @property
    def evaluate(self) -> int:
        return self._data


class Var(Expr):
    _data: str

    def __init__(self, data: str) -> None:
        super().__init__()

        self._data = data

    def show(self) -> str:
        return self._data


Function = Callable[[int, int], int]


class Calc(Expr):
    _left: Expr
    _right: Expr
    _tok: str
    _fn: Function

    def __init__(self, left: Expr, right: Expr, tok: str, fn: Function) -> None:
        super().__init__()

        self._left = left
        self._right = right
        self._tok = tok
        self._fn = fn

    def simplify(self) -> Expr:
        l = self._left.simplify()
        r = self._right.simplify()

        # If the calculation is do-able, simplify it, or else return the graph.
        if isinstance(l, Lit) and isinstance(r, Lit):
            return Lit(self._fn(l.evaluate, r.evaluate))
        else:
            return Calc(l, r, self._tok, self._fn)

    def show(self) -> str:
        l = self._left.show()
        r = self._right.show()
        return f"({l} {self._tok} {r})"


class Add(Calc):
    def __init__(self, left: Expr, right: Expr) -> None:
        super().__init__(left, right, "+", operator.add)


class Sub(Calc):
    def __init__(self, left: Expr, right: Expr) -> None:
        super().__init__(left, right, "-", operator.sub)


class Mul(Calc):
    def __init__(self, left: Expr, right: Expr) -> None:
        super().__init__(left, right, "*", operator.mul)
