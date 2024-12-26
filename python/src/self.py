# Copyright (c) RenChu Wang - All Rights Reserved

import abc
from collections.abc import Sequence
from typing import Protocol, TypeVar

T = TypeVar("T", bound="HasChildren", covariant=True)


class HasChildren(Protocol[T]):
    @abc.abstractmethod
    def children(self) -> Sequence[T]: ...


class HasSelfAsChildren(HasChildren["HasSelfAsChildren"]):
    # It does autocomplete. Seems fine.
    def children(self) -> Sequence["HasSelfAsChildren"]:
        return []
