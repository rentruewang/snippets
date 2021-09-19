from abc import ABC, abstractmethod
from functools import wraps


class Base:
    def method(self):
        print("base")

    def call(self):
        self.method()


class Derived(Base):
    def method(self):
        print("derived")


class DDerived(Derived):
    def method(this):
        print("derived twice")


class StaticDerived(Base):
    @staticmethod
    def method():
        print("static derived")


class Abstract(ABC):
    @abstractmethod
    def __init__(self) -> None:
        super().__init__()
        print("this is abstract init")

    @abstractmethod
    def absmethod(self):
        print("this is abstract")


class Concrete(Abstract):
    def __init__(self) -> None:
        super().__init__()
        print("this is concrete init")

    def absmethod(self):
        return super().absmethod()

    def conmethod(self):
        self.absmethod()
        print("concrete method")


if __name__ == "__main__":
    d = Derived()
    d.call()

    dd = DDerived()
    dd.call()

    sd = StaticDerived()
    sd.call()

    print()
    c = Concrete()
    c.conmethod()
