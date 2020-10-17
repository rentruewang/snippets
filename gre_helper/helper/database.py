import json
import os
from collections import defaultdict
from os import path as os_path


class DataBase(object):
    def __init__(
        self,
        directory="database",
        words_file="words.json",
        roots_file="roots.json",
        encoding="utf-8",
    ):
        os.makedirs(directory, exist_ok=True)

        self.words_file = os_path.join(directory, words_file)
        self.roots_file = os_path.join(directory, roots_file)
        self.encoding = encoding

        try:
            wf = open(self.words_file, "r", encoding=encoding)
            rf = open(self.roots_file, "r", encoding=encoding)

            words = json.load(wf)
            roots = json.load(rf)

            words = {k: set(v) for (k, v) in words.items()}
            roots = {k: set(v) for (k, v) in roots.items()}

            self.words = defaultdict(set, **words)
            self.roots = defaultdict(set, **roots)
        # OSError thrown by open
        except OSError:
            print("Error encoutered. Creating file")

            wf = open(self.words_file, "w+", encoding=encoding)
            rf = open(self.roots_file, "w+", encoding=encoding)

            self.words = defaultdict(set)
            self.roots = defaultdict(set)
        # closing files
        finally:
            wf.close()
            rf.close()

    def add(self, word: str, *roots):
        # words add root as their prefixes
        self.words[word].update(roots)
        # roots add word to their associated words
        for root in roots:
            self.roots[root].add(word)

    def get(self, word: str) -> set:
        roots = self.words[word]

        for root in roots:
            assert word in self.roots[root]

        return roots

    def delete(self, word: str):
        # remove entry
        roots = self.words[word]
        del self.words[word]

        # doesn't matter if in the final state root is empty
        # defaultdict will return an empty set anyways
        for root in roots:
            self.roots[root].discard(word)

    def __del__(self):
        try:
            wf = open(self.words_file, "w+", encoding=self.encoding)
            rf = open(self.roots_file, "w+", encoding=self.encoding)

            words = {k: list(v) for (k, v) in self.words.items() if len(v) != 0}
            roots = {k: list(v) for (k, v) in self.roots.items() if len(v) != 0}

            json.dump(words, wf)
            json.dump(roots, rf)
        except OSError:
            print(f"Writing to file {self.words_file} and {self.roots_file} failed")
            print(f"Words: {self.words}")
            print(f"Roots: {self.roots}")
        finally:
            wf.close()
            rf.close()
