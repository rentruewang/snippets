from typing import Protocol


class Proto(Protocol):
    member: int

    @property
    def prop(self) -> int:
        ...


class A(Proto):
    @property
    def member(self) -> int:
        return 42

    @property
    def prop(self) -> int:
        return 65


class B(Proto):
    member = 18

    prop = 32


def pt(p: Proto) -> None:
    print(p.member, p.prop)


pt(A())
pt(B())
