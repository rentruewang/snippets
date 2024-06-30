# Copyright (c) 2024 RenChu Wang - All Rights Reserved


class CustomIter:
    def __iter__(self):
        return iter(range(3))


# https://github.com/python/cpython/blob/d636d7dfe714e7168b342c7ea5f9f9d3b3569ed0/Objects/dictobject.c#L2807
# Per CPython 3.10, **kwargs calls dict_merge(..., kwargs, 2),
# no key collision dict merging.
# This means that only PyMapping_Keys and PyObject_GetItem are called on the kwargs.
class CustomMapping:
    def keys(self) -> map[str]:
        return map(str, range(3))

    def __getitem__(self, key: str) -> str:
        return str(int(key) + 1)


def print_args_kwargs(*args, **kwargs):
    print(args)
    print(kwargs)


print_args_kwargs(*CustomIter(), **CustomMapping())
