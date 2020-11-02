import sys
from collections import defaultdict

groups = defaultdict(list)

for line in sys.stdin:
    (key, val) = line.strip().split("\t", maxsplit=1)
    groups[key].append(val)

for (key, val) in groups.items():
    print("{}\t{}".format(key, len(val)), file=sys.stdout)
