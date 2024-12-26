# Copyright (c) RenChu Wang - All Rights Reserved

import typing
from abc import ABC, abstractmethod


class A(ABC):
    @abstractmethod
    def f(self, a):
        pass


@typing.final
class B(A):
    def f(self, a):
        print(a)


@typing.final
class C(A):
    g = f = lambda a: print(a)
