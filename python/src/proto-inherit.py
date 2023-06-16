from typing import Protocol


class SuperProtocol:
    __init_subclass__ = Protocol.__init_subclass__

    def __init__(self, *args, **kwargs) -> None:
        super().__init__(*args, **kwargs)


class BaseClass:
    def __init__(self) -> None:
        print("init of base is called")


class QuackNoParent(Protocol):
    def quack(self):
        print("i am a duck")


class QuackParent(SuperProtocol):
    def __init__(self) -> None:
        super().__init__()

    def quack(self):
        print("i am a duck with parent")


class QuackNoParentMixin(QuackNoParent):
    def __init__(self) -> None:
        super().__init__()

        print("i am derived but no parent")


class QuackMixin(QuackParent):
    def __init__(self) -> None:
        super().__init__()

        print("i am derived and i have parent")


class MultiInheritNoParent(QuackNoParentMixin, BaseClass):
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
