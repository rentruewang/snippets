# Copyright (c) 2024 RenChu Wang - All Rights Reserved

import abc
from typing import Protocol

# https://peps.python.org/pep-0544/#explicitly-declaring-implementation


class SomeDefaults(Protocol):
    @abc.abstractmethod
    def function(self):
        pass

    def call_function(self):
        print("calling call_function")
        self.function()


class HasFunction:
    def function(self):
        print("calling function")


class Inherited(HasFunction, SomeDefaults):
    pass


def call_defaults(sd: SomeDefaults):
    sd.call_function()


if __name__ == "__main__":
    # This doesn't work because call_function is not present on HasFunction
    # call_defaults(HasFunction())

    call_defaults(Inherited())
