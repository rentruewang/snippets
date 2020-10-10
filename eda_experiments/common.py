import dataclasses


@dataclasses.dataclass
class Pair:
    first: int
    second: int


class Location(Pair):
    @property
    def x(self):
        return self.first

    @property
    def y(self):
        return self.second
