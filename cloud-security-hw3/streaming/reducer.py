import sys
from collections import defaultdict

groups = defaultdict(int)

for line in sys.stdin:
    (key, _) = line.strip().split("\t", maxsplit=1)
    groups[key] += 1

for (key, count) in groups.items():
    print("{}\t{}".format(key, count), file=sys.stdout)
