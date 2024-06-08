import torch
from torch import nn

class Trainer(object):
    def __init__(self, model, train_dataloader, test_dataloader, device):
        self.model = model
        self.train_dataloader = train_dataloader
        self.test_dataloader = test_dataloader
        self.device = device

        self.loss_fn = nn.CrossEntropyLoss()
        self.optimizer = torch.optim.Adam(model.parameters(), lr=8e-5, weight_decay=0.005)
        
        self.MAX_EPOCH = 60
    
    def train_step(self):
        size = len(self.train_dataloader.dataset)
        num_batches = len(self.train_dataloader)
        # Set model to training mode
        self.model.train()
        
        train_loss = 0
        for batch, (X, y) in enumerate(self.train_dataloader):
            X, y = X.to(self.device), y.to(self.device)

            pred = self.model(X)
            loss = self.loss_fn(pred, y)

            loss.backward()
            self.optimizer.step()
            self.optimizer.zero_grad()

            train_loss += loss.item()
        
        train_loss /= num_batches
        
        return train_loss

    def test(self):
        size = len(self.test_dataloader.dataset)
        num_batches = len(self.test_dataloader)
        # Set model to evaluation mode
        self.model.eval()

        test_loss, accuracy = 0, 0
        with torch.no_grad(): # No need to compute the gradients in testing
            for X, y in self.test_dataloader:
                X, y = X.to(self.device), y.to(self.device)
                pred = self.model(X)

                test_loss += self.loss_fn(pred, y).item()
                accuracy += (pred.argmax(1) == y).type(torch.float).sum().item()

        test_loss /= num_batches
        accuracy /= size

        return test_loss, accuracy

class BetterTrainer(object):
    def __init__(self, model, train_dataloader, test_dataloader, device):
        #  ==== DO NOT EDIT THESE ====
        self.model = model
        self.train_dataloader = train_dataloader
        self.test_dataloader = test_dataloader
        self.device = device
        # ============================

        self.MAX_EPOCH = 60 # Change this if necessary, but ensure that self.MAX_EPOCH is defined

        pass

    def train_step(self):
        pass

