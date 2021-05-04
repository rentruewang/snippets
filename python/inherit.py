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


if __name__ == "__main__":
    d = Derived()
    d.call()

    dd = DDerived()
    dd.call()

    sd = StaticDerived()
    sd.call()
