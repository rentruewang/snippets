"""
This file contains how routing has normally been done
"""

from common import Location


class Node:
    def __init__(self):
        self._loc = Location()


class Net:
    def __init__(self):
        # used to store all nodes
        self._elements = []
