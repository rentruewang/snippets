"""
This file contains the net that is defined recursively
Using the top-down then bottom-up approach
"""
from common import Location


class Node:
    def __init__(self):
        self._loc = Location()


class Net:
    def __init__(self):
        # used to store all nodes
        self._elements = []
