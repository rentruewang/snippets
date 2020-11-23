import numpy as np
from numpy import ndarray


def load_name(fname: str) -> (ndarray, ndarray):
    with open(fname) as f:
        lines = f.readlines()

    label = []
    data = []

    for line in lines:
        feats = [float(v) for v in line.split(",")]
        label.append(feats[-1])
        data.append(feats[:-1])

    assert len(label) == len(data) == len(lines)

    return (np.array(label), np.array(data))
