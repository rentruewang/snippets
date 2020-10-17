import dataclasses
import json
import os
from os import path as os_path


class Word:
    def __init__(self, meaning, parent, children=()):
        self.meaning = meaning
        self.parent = set(parent)
        self.children = set(children)

    def dump(self):
        return json.dumps([self.meaning, list(self.parent), list(self.children)])

    @classmethod
    def load(cls, string):
        [m, p, c] = json.loads(string)
        p = set(p)
        c = set(c)
        return cls(m, p, c)

    @property
    def isroot(self):
        return len(self.children) != 0

    def __str__(self):
        meaning = f"Meaning: {self.meaning}"
        parent = f"Parents: {list(self.parent)}"
        children = f"Children: {list(self.children)}"

        return f"{meaning}, {parent}, {children}"


class DataBase:
    def __init__(self, file="data.json", path="database", enc="utf-8"):
        os.makedirs(path, exist_ok=True)

        self.file = os_path.expanduser(os_path.join(path, file))
        self.enc = enc
        try:
            with open(self.file, mode="r+", encoding=self.enc) as f:
                # data: Dict[str, str]
                data: dict = json.load(f)
        except IOError:
            data = {}
        self.data = {k: Word.load(v) for (k, v) in data.items()}

    def Add(self, word: str, meaning: str, roots=()):
        for root in roots:
            assert self.Has(root)
            self.data[root].children.add(word)

        if word in self.data.keys():
            # python is copy by reference
            w: Word = self.data[word]
            w.meaning = meaning
            w.parent.update(roots)
        else:
            self.data[word] = Word(meaning, roots)

    def Del(self, word: str = "", also_root=True):
        if word == "":
            self.data = {}

        assert self.Has(word)

        w: Word = self.data[word]
        del self.data[word]

        # also delete roots
        if not also_root:
            return

        for root in w.parent:
            assert self.Has(root)

            r: Word = self.data[root]
            r.children.remove(word)
            if not r.isroot:
                self.Del(root)
                assert not self.Has(root)

    def Has(self, word: str):
        return word in self.data.keys()

    def Get(self, word: str):
        assert self.Has(word)
        return self[word]

    def All(self, word: str = ""):
        return {k: str(v) for (k, v) in self.data.items() if word in k}

    def __del__(self):
        data = {k: v.dump() for (k, v) in self.data.items()}

        with open(self.file, mode="w+", encoding=self.enc) as f:
            json.dump(data, f)
