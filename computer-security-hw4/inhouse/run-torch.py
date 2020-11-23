import numpy as np
import torch
from torch import optim
from tqdm import tqdm

from load import load_name

(label, feat) = load_name("./data/data_banknote_authentication.txt")

label = torch.tensor(label, dtype=torch.int32)
feat = torch.tensor(feat, dtype=torch.float32)

print(label.shape, feat.shape)

weight = torch.randn(feat.shape[1]).requires_grad_()
bias = torch.randn(1).requires_grad_()

print(weight, bias)

sgd = optim.SGD(params=[weight, bias], lr=1e-6)


def model(feat):
    return feat @ weight + bias


for _ in tqdm(range(10000)):
    pred = model(feat)
    diff = (pred - label) ** 2
    loss = diff.sum()

    sgd.zero_grad()
    loss.backward()
    sgd.step()


with torch.no_grad():
    pre = model(feat)
    err = pre.round().int()

    print("Error Rate =", (label != err).sum().item() / len(label))
