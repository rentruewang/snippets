# Copyright (c) RenChu Wang - All Rights Reserved


class CoopFoo:
    def __init__(self, **kwargs):
        super().__init__(**kwargs)  # forwards all unused arguments
        self.foo = "foo"
        print(kwargs)

    def f(self):
        super().f()
        print("coopfoo")


class CoopBar:
    def __init__(self, bar, **kwargs):
        super().__init__(**kwargs)  # forwards all unused arguments
        self.bar = bar
        print(kwargs)

    def f(self):
        print("coopbar")


class CoopFooBar(CoopFoo, CoopBar):
    def __init__(self, bar="bar"):
        super().__init__(bar=bar)

    def f(self):
        super().f()
        print("cfb f")


class First(object):
    def __init__(self):
        super().__init__()
        print("first")

    def some(self):
        print("s first")


class Second(object):
    def __init__(self):
        super().__init__()
        print("second")

    def some(self):
        print("s second")


class Third(First, Second):
    def __init__(self):
        super().__init__()
        print("third")

    def some(self):
        super().some()
        print("s third")


class Base:
    def __init__(self) -> None:
        print("base")


class Fourth(Base):
    pass


if __name__ == "__main__":
    cfb = CoopFooBar()
    cfb.f()

    print()
    print()

    th = Third()
    th.some()

    print()
    print()

    Fourth()
