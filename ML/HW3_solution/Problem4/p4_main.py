import torch
from torch import nn
import numpy as np

from p4_utils import load_FashionMNIST, make_plot, get_device
from p4_models_sol import FashionClassifier
from p4_trainer import Trainer

# Fix random seed for reproducibility
torch.manual_seed(42)

device = get_device()
print(f"Using device: {device}")

train_dataloader = load_FashionMNIST("train.npz")
test_dataloader = load_FashionMNIST("test.npz")

# # Check shape of the data
# X, y = next(iter(train_dataloader))
# print(f"Shape of X [N, C, H, W]: {X.shape}")
# print(f"Shape of y: {y.shape} {y.dtype}")

model = FashionClassifier().to(device)
trainer = Trainer(model, train_dataloader, test_dataloader, device)

train_loss_list = []
test_loss_list = []
test_accuracy_list = []

for t in range(trainer.MAX_EPOCH):
    train_loss = trainer.train_step()
    test_loss, accuracy = trainer.test()

    print(f"Epoch {t:2d}, Train Loss: {train_loss:.4f}, Test Loss: {test_loss:.4f}, Test Accuracy: {accuracy:.4f}")

    train_loss_list.append(train_loss)
    test_loss_list.append(test_loss)
    test_accuracy_list.append(accuracy)

make_plot(train_loss_list, test_loss_list, test_accuracy_list)
