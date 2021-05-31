"""
This experiment asks an important question:
Can numbers easily be understood by Bert?

On one hand, Bert is a transformer and it only knows how to process text.
On the other, it must have read through a lot of numbers, so it should
be able to have a decent understanding about numbers.

This experiment asks the model to map a number's text representation
(two) to its value (2). The output of [CLS] is taken and passed through
a linear layer. The idea is: if information is correctly processed,
the very simple model (one linear layer) should be able to predict
the number, or at least show some correspondence between
the input number and the output.

Long story short, this doesn't work. The output looks like noise.
"""

import num2words as n2w
import torch
from torch import no_grad
from torch.nn import Linear
from tqdm import tqdm
from transformers import AdamW, BertConfig, BertModel, BertTokenizerFast

if __name__ == "__main__":
    model_name = "bert-base-uncased"
    bert = BertModel.from_pretrained(model_name)
    config = BertConfig()
    linear = Linear(config.hidden_size, 1)
    tokenizer = BertTokenizerFast.from_pretrained(model_name)
    optimizer = AdamW(linear.parameters())

    # Only the linear layer is trained. Bert is used for preprocessing.
    number = 1000
    sentences = [n2w.num2words(i) for i in range(number)]
    tensors = tokenizer(sentences, padding=True, return_tensors="pt")
    embeddings = bert(**tensors).last_hidden_state[:, 0].detach()
    target = torch.arange(number)

    for i in tqdm(range(1000)):
        out = linear(embeddings)
        loss = (out - target).pow(2).sum()

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

    with no_grad():
        out = linear(embeddings)
    print(out)
