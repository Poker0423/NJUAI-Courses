import torch
import numpy as np
from torch.utils.data import DataLoader, TensorDataset
import matplotlib.pyplot as plt

def get_device():
    device = "cuda" if torch.cuda.is_available() else "cpu"
    return device


def load_FashionMNIST(fname, batch_size=4):

    with np.load(fname) as data:
        X = data["X"].reshape(-1, 1, 28, 28) / 255.0
        y = data["y"]

    X = torch.tensor(X, dtype=torch.float32)
    y = torch.tensor(y, dtype=torch.int64)

    dataset = TensorDataset(X, y)
    dataloader = DataLoader(dataset, batch_size=batch_size, shuffle=True)
    return dataloader

def make_plot(train_loss_list, test_loss_list, test_acc_list):
    assert len(train_loss_list) == len(test_loss_list) == len(test_acc_list)
    epochs = len(train_loss_list)

    color1 = 'tab:blue'
    color2 = 'tab:orange'

    fig, ax1 = plt.subplots(dpi=200)
    ax1.set_xlabel("Epoch")
    ax1.set_title("Loss & Accuracy on FashionMNIST")

    ln1 = ax1.plot(range(epochs), train_loss_list, color=color1, label="Train Loss")
    ln2 = ax1.plot(range(epochs), test_loss_list, color=color1, label="Test Loss", linestyle='dashed')
    ax1.set_ylim([0, 2.5])
    ax1.set_ylabel('Loss', color=color1)
    ax1.tick_params(axis='y', labelcolor=color1)

    ax2 = ax1.twinx()
    ln3 = ax2.plot(range(epochs), test_acc_list, color=color2, label="Test Accuracy")
    ax2.set_ylim([0.4, 0.9])
    ax2.set_ylabel('Accuracy', color=color2)
    ax2.tick_params(axis='y', labelcolor=color2)
    
    # Make legend
    lns = ln1+ln2+ln3
    labs = [l.get_label() for l in lns]
    ax2.legend(lns, labs, loc=3)

    fig.tight_layout()
    plt.savefig("plot.png")

    print("Plot saved as plot.png")