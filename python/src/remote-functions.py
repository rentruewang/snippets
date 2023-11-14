from dataclasses import dataclass

import ray


@ray.remote
def function(data, tag: str):
    print(id(data), data, tag)
    return data


@dataclass
class SomeClass:
    data: int


if __name__ == "__main__":
    ray.init()

    sc = SomeClass(666)
    ref1 = function.remote(sc, "ref1")
    ref2 = function.remote(sc, "ref2")

    print("ref1, ref2", ray.get([ref1, ref2]))

    print("ref1, remote(ref1)", ref1, function.remote(ref1, "ref1'"))

    # f.remote(x) is not equal to f.remote(ray.get(x)) unless x is an objectref
    print("refs")
    refs = [ref1, ref2]
    refrefs = function.remote(refs, "refs")
    print(ray.get(refrefs))
