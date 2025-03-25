from modules import d_k, d_model, d_v
import torch

class InputGenerator():
    def __init__(self, batch_size=64, seq_len=d_model) -> None:
        self.batch_size = batch_size
        self.seq_len = seq_len

    def generate(self):
        output = torch.ones(self.batch_size, self.seq_len, d_model).float()
        # Make it incremental
        for i in range(1, self.seq_len):
            output[:, i] = output[:, i-1] + 1
        return output
    
class Trainer():
    def __init__(self,
                 lr=1e-3,
                 epochs=10,
                 batch_size=64,
                 seq_len=d_model,
                 ):
        self.lr = lr
        self.epochs = epochs
        self.batch_size = batch_size
        self.seq_len = seq_len

    def train(self, model, optimizer, criterion, train_loader, val_loader):
        for epoch in range(self.epochs):