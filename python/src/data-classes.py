import dataclasses as dcls


@dcls.dataclass(frozen=True)
class Base:
    based: str


@dcls.dataclass(frozen=True)
class Sub1(Base):
    sub: str


class Sub2(Base):
    sub: str


if __name__ == "__main__":
    s1 = Sub1(based="based", sub="sub")
    print(s1)

    # Not a dataclass, so that the fields are not overwritten.
    s2 = Sub2(based="based")
    print(s2)
