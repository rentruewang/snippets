from __future__ import annotations

from typing import Any, List, Sequence


def match_something(something: Any) -> None:
    match something:
        case ["s", "o", *remains]:
            print("This is reachable", something, remains)
        # SyntaxError: expected ':'
        # case "split".split():
        #     print("splitted", something)
        case ["s", *remains]:
            print("matched", something, remains)
        case ["s", "o", *remains]:
            print("This is unreachable")
        case "string":
            print("hello,", something)
        case _:
            print("default", something)


def match_start(seq: Sequence[int]):
    match seq:
        case (*others, end):
            print(end, others)
        case _:
            print("hi")


def match_end(seq: Sequence[int]):
    match seq:
        case [start, *others]:
            print(start, others)
        case _:
            print("bye")


def alarm(item: List[str]):
    match item:
        case ["evening", action]:
            print(f"It's late! Go {action} now")
        case [("morning" | "afternoon") as time, action]:
            print(f"Good {time}! It is time to {action}!")
        case _:
            print("The time is invalid.")


class Something:
    name: str
    count: int

    __match_args__ = ("name", "count")

    def __init__(self, name: str, count: int) -> None:
        self.name = name
        self.count = count

    def do_match(self) -> None:
        match self:
            case Something("sth", cnt):
                print(f"This is sth, {cnt}")
            case Something("other"):
                print(f"This is other, {self}")
            case Something(name=sth, count=8):
                print(f"Counted {sth} eight times.")
            case _:
                print(self)

    def __str__(self) -> str:
        return str(self.__dict__)


if __name__ == "__main__":
    match_something("string")
    match_something("other")
    match_something(list("something"))
    print()

    # Doesn't matter if the matched expression is tuple or list it seems.
    match_start(list(range(3)))
    match_start(tuple(range(3)))
    print()

    match_end(list(range(3)))
    match_end(tuple(range(3)))
    print()

    alarm(["morning", "wake up"])
    alarm(["evening", "sleep"])
    print()

    Something("sth", 789).do_match()
    Something("other", 666).do_match()
    Something("hello", 8).do_match()
    Something("default", 448).do_match()
