import dataclasses
import json
import os
from os import path as os_path


class Word:
    def __init__(self, meaning, parents=(), children=()):
        self.meaning = meaning
        self.parents = set(parents)
        self.children = set(children)

    def dump(self):
        return json.dumps([self.meaning, list(self.parents), list(self.children)])

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
        parents = f"Parents: {list(self.parents)}"
        children = f"Children: {list(self.children)}"

        return f"{meaning}, {parents}, {children}"


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

    @staticmethod
    def concat_iterable(func, words):
        return set().union(words, *(func(w) for w in words))

    def Anc(self, word: str) -> set:
        "Get the ancestors of a word"
        assert self.Has(word)
        parents = self.data[word].parents
        ans = self.concat_iterable(self.Anc, parents)
        parents.update(ans)
        return parents

    def Dec(self, word: str) -> set:
        "Get the decendants of a word"
        assert self.Has(word)
        children = self.data[word].children
        ans = self.concat_iterable(self.Dec, children)
        children.update(ans)
        return children

    def Add(self, word: str, info: Word):
        "Add a word to graph"

        self.data[word] = info

        assert self.Check(word)

        ancestors = self.Anc(word)
        for wordroot in ancestors:
            assert self.Has(wordroot)
            self.data[wordroot].children.add(word)

        decendants = self.Dec(word)
        for longword in decendants:
            assert self.Has(longword)
            self.data[longword].parents.add(word)

        print("{}|{}|{}|{}".format(word, info, ancestors, decendants, end="\n\n"))

        if word in self.data.keys():
            # python is copy by reference
            info.parents.update(self.data[word].parents)

        self.data[word] = info

    def Del(self, word: str = "", also_root=False):
        if word == "":
            self.data = {}

        assert self.Has(word)

        w: Word = self.data[word]
        del self.data[word]

        for wordroot in w.parents:
            assert self.Has(wordroot)

            r: Word = self.data[wordroot]
            r.children.remove(word)
            # also delete roots
            if also_root and not r.isroot:
                self.Del(wordroot)
                assert not self.Has(wordroot)

        for longword in w.children:
            assert self.Has(longword)

            l: Word = self.data[longword]
            l.parents.remove(word)

    def Has(self, word: str):
        return word in self.data.keys()

    def Get(self, word: str):
        assert self.Has(word)
        return self[word]

    def Check(self, word: str):
        return (
            self.Has(word)
            and all(self.Check(p) for p in self.data[word].parents)
            and all(self.Check(d) for d in self.data[word].children)
        )

    def All(self, word: str = ""):
        return {k: str(v) for (k, v) in self.data.items() if word in k}

    def __del__(self):
        data = {k: v.dump() for (k, v) in self.data.items()}

        with open(self.file, mode="w+", encoding=self.enc) as f:
            json.dump(data, f)
