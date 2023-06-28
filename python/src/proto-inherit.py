from abc import abstractmethod
from typing import Protocol


class SuperProtocol:
    # If Protocol is one of __bases__,
    # the __init__ would be set automatically,
    # one that doesn't call super()
    __init_subclass__ = Protocol.__init_subclass__


class BaseClass:
    def __init__(self) -> None:
        print("init of base is called")


class QuackNoInit(Protocol):
    def quack(self):
        print("i am a duck")


class QuackParent(SuperProtocol):
    def quack(self):
        print("i am a duck with parent")


class QuackNoInitMixin(QuackNoInit):
    def __init__(self) -> None:
        super().__init__()

        print("i am derived but no parent")


class QuackMixin(QuackParent):
    def __init__(self) -> None:
        super().__init__()

        print("i am derived and i have parent")


class MultiInheritNoParent(QuackNoInitMixin, BaseClass):
    def __init__(self) -> None:
        super().__init__()

        print("i inherit so much")


class MultiInherit(QuackMixin, BaseClass):
    def __init__(self) -> None:
        super().__init__()

        print("i inherit so much")


MultiInheritNoParent()
print()
print()
MultiInherit()

print()


class A(Protocol):
    @abstractmethod
    def __init__(self) -> None:
        print("A.__init__")

    @abstractmethod
    def f(self):
        print("A.f")


class B(A):
    def __init__(self) -> None:
        super().__init__()
        print("B.__init__")

    def f(self):
        super().f()
        print("B.f")
