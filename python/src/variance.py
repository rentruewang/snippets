from __future__ import annotations

import abc
from typing import Generic, Protocol, TypeVar

# Java is THE OOP language, so let's see how it handles generics and inheritance.
# https://docs.oracle.com/javase/tutorial/java/generics/inheritance.html
# https://docs.oracle.com/javase/tutorial/java/generics/bounded.html


def g_ng():
    print("generic inherit from non generic")

    class NonGeneric:
        def f(self, i: int) -> int:
            return i

    Cov = TypeVar("Cov", covariant=True, bound=int)
    Cont = TypeVar("Cont", contravariant=True, bound=int)

    # error: Cannot use a covariant type variable as a parameter
    # class Generic1(NonGeneric, Generic[Cov]):
    #     def f(self, i: Cov) -> int:
    #         return i

    # error: Argument 1 of "f" is incompatible with supertype "NonGeneric";
    # supertype defines the argument type as "int"
    # class Generic2(NonGeneric, Generic[Cont]):
    #     def f(self, i: Cont) -> int:
    #         return i

    class Generic3(NonGeneric, Generic[Cov]):
        def f(self, i: int) -> Cov:
            raise ValueError

    # error: Cannot use a contravariant type variable as return type
    # class Generic4(NonGeneric, Generic[Cont]):
    #     def f(self, i: int) -> Cont:
    #         raise ValueError

    # error: Incompatible return value type (got "Cont", expected "Cov")
    # class Generic5(NonGeneric, Generic[Cov, Cont]):
    #     def f(self, i: Cont) -> Cov:
    #         return i

    # error: Argument 1 of "f" is incompatible with supertype "NonGeneric";
    # supertype defines the argument type as "int"
    # class Generic6(NonGeneric, Generic[Cov, Cont]):
    #     def f(self, i: Cont) -> Cov:
    #         raise ValueError


def ng_g():
    print("non generic inherit from generic")

    class BaseClass:
        pass

    class SubClass(BaseClass):
        pass

    Cov = TypeVar("Cov", covariant=True, bound=BaseClass)
    Cont = TypeVar("Cont", contravariant=True, bound=BaseClass)

    class GenericBase(Generic[Cont, Cov]):
        def f(self, i: Cont) -> Cov:
            raise ValueError

    class NonGeneric1(GenericBase[BaseClass, BaseClass]):
        def f(self, i: BaseClass) -> BaseClass:
            return i

    # Has to subclass from GenericBase[Subclass, BaseClass] because Cont is contravariant.
    class NonGeneric2(GenericBase[SubClass, BaseClass]):
        def f(self, i: BaseClass) -> BaseClass:
            raise ValueError

    class NonGeneric3(GenericBase[BaseClass, BaseClass]):
        def f(self, i: BaseClass) -> SubClass:
            raise ValueError

    class NonGeneric4(GenericBase[SubClass, SubClass]):
        def f(self, i: BaseClass) -> SubClass:
            raise ValueError


def g_g():
    print("generic inherit from generic")

    class BaseClass:
        pass

    class SubClass(BaseClass):
        pass

    Cov = TypeVar("Cov", covariant=True, bound=BaseClass)
    Cont = TypeVar("Cont", contravariant=True, bound=BaseClass)

    SubCov = TypeVar("SubCov", covariant=True, bound=SubClass)
    SubCont = TypeVar("SubCont", contravariant=True, bound=SubClass)

    class GenericBase(Protocol[Cov, Cont]):
        @abc.abstractmethod
        def cov(self) -> Cov: ...

        @abc.abstractmethod
        def cont(self, sub: Cont) -> None: ...

    # Not all that useful, because now if I want to use generic,
    # I have to specify the reference type to be the broadest type.
    # Something like reference: GenericBase[SubClass, SubClass] = ...
    # in order not to break hierarchy. It's great for sharing code though.
    # In some way, python generic is similar to C++ templates (text replacement).
    class GenericSub(GenericBase[SubCov, SubCont]):
        @abc.abstractmethod
        def cov(self) -> SubCov: ...

        @abc.abstractmethod
        def cont(self, sub: SubCont) -> None: ...


def codependent():
    class A:
        def attack(self, b: B) -> None:
            print(self, "attacking", b)

        def __str__(self):
            return "A"

    class B:
        def defend(self, a: A) -> None:
            print(self, "defending", a)

        def __str__(self):
            return "B"

    class SubA(A):
        # error: Argument 1 of "attack" is incompatible with supertype "A";
        # supertype defines the argument type as "B"
        #
        # def attack(self, b: SubB) -> None:
        #     b.sub_b_specific()
        #     super().attack(b)

        def attack(self, b: B) -> None:
            return super().attack(b)

        def sub_a_specific(self) -> None:
            print("hello world from sub a")

    class SubB(B):
        # error: Argument 1 of "defend" is incompatible with supertype "B";
        # supertype defines the argument type as "A"
        #
        # def defend(self, a: SubA) -> None:
        #     a.sub_a_specific()
        #     super().defend(a)

        def defend(self, a: A) -> None:
            return super().defend(a)

        def sub_b_specific(self) -> None:
            print("hello world from sub b")

    a = A()
    b = B()

    sa = SubA()
    sb = SubB()

    a.attack(b)
    b.defend(a)

    sa.attack(sb)
    sb.defend(sa)

    # NOTE: How to make SubA use things only SubB has?
    print()
    print("B is now part of A")

    # 1. Make B part of A (or vice versa)
    class B1:
        def defend(self, a: A1) -> None:
            print(self, "defending", a)

        def __str__(self):
            return "B1"

    class A1:
        b: B1

        def attack(self) -> None:
            print(self, "attacking", self.b)

        def attack_and_defend(self) -> None:
            self.attack()
            self.b.defend(self)

        def __str__(self):
            return "A1"

    class SubB1(B1):
        # NOTE: Still a problem here:
        # error: Argument 1 of "defend" is incompatible with supertype "B1";
        # supertype defines the argument type as "A1"
        #
        # def defend(self, a: SubA1) -> None:
        #     a.sub_a1_specific()
        #     print(self, "defending", a)

        def sub_b1_specific(self) -> None:
            print("hello world from sub b1")

    class SubA1(A1):
        b: SubB1

        def attack(self) -> None:
            self.b.sub_b1_specific()
            print(self, "attacking", self.b)

        def attack_and_defend(self) -> None:
            self.attack()
            self.b.defend(self)

        # This cannot be called from B1 because of the issue above.
        def sub_a1_specific(self) -> None:
            print("hello world from sub a1")

        def __str__(self):
            return "SubA1"

    # 2. Make a common manager C that has both A and B
    print()
    print("C owns both A and B break off inheritance between A, B and subclasses.")

    class A2:
        def attack(self, b: B2) -> None:
            print(self, "attacking", b)

        def __str__(self):
            return "A2"

    class B2:
        def defend(self, a: A2) -> None:
            print(self, "defending", a)

        def __str__(self):
            return "B2"

    # error: Argument 1 of "attack" is incompatible with supertype "A2";
    # supertype defines the argument type as "B2"
    # class SubA2(A2):
    #     def attack(self, b: SubB2) -> None:
    #         b.sub_b2_specific()
    #         super().attack(b)

    #     def __str__(self):
    #         return "SubA2"

    #     def sub_a2_specific(self) -> None:
    #         print("hello world from sub a2")

    # error: Argument 1 of "defend" is incompatible with supertype "B2";
    # supertype defines the argument type as "A2"
    # class SubB2(B2):
    #     def defend(self, a: SubA2) -> None:
    #         a.sub_a2_specific()
    #         super().defend(a)

    #     def __str__(self):
    #         return "SubB2"

    #     def sub_b2_specific(self) -> None:
    #         print("hello world from sub b2")

    class SubA2:
        def attack(self, b: SubB2) -> None:
            b.sub_b2_specific()
            print(self, "attacking", b)

        def __str__(self):
            return "SubA2"

        def sub_a2_specific(self) -> None:
            print("hello world from sub a2")

    class SubB2:
        def defend(self, a: SubA2) -> None:
            a.sub_a2_specific()
            print(self, "defending", a)

        def __str__(self):
            return "SubB2"

        def sub_b2_specific(self) -> None:
            print("hello world from sub b2")

    # Attempt 1:
    #
    # error: Incompatible types in assignment
    #
    # class C:
    #     a: A2
    #     b: B2

    #     def attack_and_defend(self) -> None:
    #         self.a.attack(self.b)
    #         self.b.defend(self.a)

    # class SubC(C):
    #     a: SubA2
    #     b: SubB2

    # Attempt 2: make private (python has no real private!)
    #
    # class C:
    #     _a: A2
    #     _b: B2

    #     def attack_and_defend(self) -> None:
    #         self._a.attack(self._b)
    #         self._b.defend(self._a)

    # class SubC(C):
    #     _a: SubA2
    #     _b: SubB2

    # Attempt 3: make __private (this would prevent name clashing at least)
    class C:
        __a: A2
        __b: B2
        _member: int
        _cls_member: int = 42

        def __init__(self, a: A2, b: B2) -> None:
            self.__a = a
            self.__b = b
            self._member = 666

        def attack_and_defend(self) -> None:
            self.__a.attack(self.__b)
            self.__b.defend(self.__a)

    class SubC(C):
        __a: SubA2
        __b: SubB2

        def __init__(self, a: SubA2, b: SubB2) -> None:
            # Not calling super, so super's __a, __b are not set.
            self.__a = a
            self.__b = b

            # Incompatible type
            # super().__init__(a, b)

            # AttributeError because didn't call super.
            # print(self._member)

        def attack_and_defend(self) -> None:
            # Need to redefine because of name mangling.
            self.__a.attack(self.__b)
            self.__b.defend(self.__a)

    c = C(A2(), B2())
    c.attack_and_defend()

    sc = SubC(SubA2(), SubB2())
    sc.attack_and_defend()

    # _cls_member shows up, but _member does not.
    print(dir(C))
    print(dir(SubC))

    # Attempt 4: Just break inheritance and use interface bridge / visitor pattern.
    # Since SubA1 and SubB1 need to know each other,
    # instead of SubA1 checking types of every B1 and call `specific_b1_method`,
    # just use a visitor pattern that "modifies and adds" specific functionality.
    # So SubA1 would do `b.accept(self)`,
    # and SubB1 would do `specific_sub_b1` inside its own visit.
    class ProtoA(Protocol):
        def accept(self, b: ProtoB) -> None:
            b.visit(a=self)

        def attack(self, b: ProtoB) -> None:
            print(self, "attacking", b)

        @abc.abstractmethod
        def visit(self, b: ProtoB) -> None: ...

    class ProtoB(Protocol):
        def accept(self, a: ProtoA) -> None:
            a.visit(b=self)

        def defend(self, a: ProtoA) -> None:
            print(self, "defending", a)

        @abc.abstractmethod
        def visit(self, a: ProtoA) -> None: ...

    class DA1(ProtoA):
        def attack(self, b: ProtoB) -> None:
            super().attack(b)

        def __str__(self):
            return "DA1"

        def visit(self, b: ProtoB) -> None:
            pass

    class DB1(ProtoB):
        def defend(self, a: ProtoA) -> None:
            super().defend(a)

        def __str__(self):
            return "DB1"

        def visit(self, a: ProtoA) -> None:
            pass

    class DA2(ProtoA):
        def attack(self, b: ProtoB) -> None:
            print("da2 attacking db2")
            self.visit(b)
            super().attack(b)
            print()

        def da2_specific(self):
            print("specific to da2")

        def __str__(self):
            return "DA2"

        def visit(self, b: ProtoB) -> None:
            self.da2_specific()

    class DB2(ProtoB):
        def defend(self, a: ProtoA) -> None:
            print("db2 defending da2")
            self.visit(a)
            super().defend(a)
            print()

        def db2_specific(self):
            print("specific to db2")

        def __str__(self):
            return "DB2"

        def visit(self, a: ProtoA) -> None:
            self.db2_specific()

    class D:
        a: ProtoA
        b: ProtoB

        def attack_and_defend(self) -> None:
            self.a.attack(self.b)
            self.b.defend(self.a)


if __name__ == "__main__":
    g_ng()
    ng_g()
    g_g()

    # A <---> B
    # ʌ       ʌ
    # |       |
    # |       |
    # C <---> D
    #
    # System in question:
    # A, B codepends, C, D codepends, C depends on A, D depends on B.
    # C must use D specific stuff and vice versa.

    print()
    print("co dependent generics")
    codependent()
