import torch
from torch import nn
import numpy as np
import tqdm
import matplotlib.pyplot as plt

MAX_LEN = 125
EPOCHS = 50
BATCH_SIZE = 256
EMB_DIM = 128
HID_DIM = 256

class PoetryModel(nn.Module):
    def __init__(self, voc_size, emb_dim, hid_dim, model_type):
        super().__init__()
        self.model_type = model_type
        self.hid_dim = hid_dim  # 隐层数量
        self.embeddings = nn.Embedding(voc_size, emb_dim)  # 嵌入层
        if self.model_type == 'L':
            self.rnn = nn.LSTM(emb_dim, self.hid_dim, num_layers=2)
        elif self.model_type == 'G':
            self.rnn = nn.GRU(emb_dim, self.hid_dim, num_layers=2)
        self.linear = nn.Linear(self.hid_dim, voc_size)  # 全连接层

    def forward(self, input, hidden=None):
        seq_len, batch_size = input.size()
        if hidden is None:
            if self.model_type == 'L':
                h_0 = input.data.new(2, batch_size, self.hid_dim).fill_(0).float()
                c_0 = input.data.new(2, batch_size, self.hid_dim).fill_(0).float()
                hidden = (h_0, c_0)
            elif self.model_type == 'G':
                h_0 = input.data.new(2, batch_size, self.hid_dim).fill_(0).float()
                hidden = h_0
        
        embeds = self.embeddings(input)
        if self.model_type == 'L':
            output, hidden = self.rnn(embeds, hidden)
        elif self.model_type == 'G':
            output, hidden = self.rnn(embeds, hidden)
        
        output = self.linear(output.view(seq_len * batch_size, -1))
        return output, hidden

def getData(pklfile):
    data = np.load(pklfile, allow_pickle=True)
    data, word2id, id2word = data['data'], data['word2id'].item(), data['id2word'].item()
    return data, word2id, id2word
    
if __name__ == '__main__':
    device = torch.device('cuda')
    data, word2id, id2word = getData('poem_data.npz')
    dataloader = torch.utils.data.DataLoader(data, batch_size=BATCH_SIZE, shuffle=True)
    model = PoetryModel(len(word2id), EMB_DIM, HID_DIM, 'G')
    model.to(device)
    
    optimizer = torch.optim.Adam(model.parameters(), lr=1e-3)
    criterion = nn.CrossEntropyLoss()
    
    losses = []
    for epoch in range(EPOCHS):
        model.train()
        total_loss = 0
        for i, batch in tqdm.tqdm(enumerate(dataloader)):
            batch = batch.long().transpose(1, 0).contiguous().to(device)
            input, target = batch[:-1, :].contiguous(), batch[1:, :].contiguous()
            optimizer.zero_grad()
            output, _ = model(input)
            loss = criterion(output, target.view(-1))
            loss.backward()
            optimizer.step()
            total_loss += loss.item()
        print(f'Epoch {epoch + 1}, Loss: {total_loss / len(dataloader)}')
        losses.append(total_loss / len(dataloader))
        
        if (epoch+1)%10 == 0:
            if model.model_type == 'L':
                torch.save(model.state_dict(), f'poetry_gen_{epoch+1}_LSTM.pth')
            elif model.model_type == 'G':
                torch.save(model.state_dict(), f'poetry_gen_{epoch+1}_GRU.pth')
    
    #绘制loss曲线
    plt.plot(losses)
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.title('Training Loss')
    plt.show()