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
