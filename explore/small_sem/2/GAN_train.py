import torch
from torch import nn
from torchvision import transforms, datasets
from PIL import Image
import numpy as np
import os
BATCH_SIZE = 2048
EPOCHS = 200
INPUT_SIZE = 100
d_losses = []
g_losses = []

class Generator(nn.Module):
    def __init__(self, input_size=10):
        super(Generator, self).__init__()
        self.fc = nn.Sequential(
            nn.Linear(input_size, 1024),
            nn.ReLU(True),
            nn.BatchNorm1d(1024),
            nn.Linear(1024, 128*7*7),
            nn.ReLU(True),
            nn.BatchNorm1d(128*7*7)
        )

        self.conv = nn.Sequential(
            nn.ConvTranspose2d(128, 64, 4, 2, padding=1),
            nn.ReLU(True),
            nn.BatchNorm2d(64),
            nn.ConvTranspose2d(64, 1, 4, 2, padding=1),
            nn.Tanh()
        )

    def forward(self, x):
        x = self.fc(x)
        x = x.view(x.shape[0], 128, 7, 7)  # reshape 通道是 128，大小是 7x7
        x = self.conv(x)
        return x
    
class Discriminator(nn.Module):
    def __init__(self):
        super(Discriminator, self).__init__()
        self.conv = nn.Sequential(
            nn.Conv2d(1, 32, 5, 1),
            nn.LeakyReLU(0.01),
            nn.MaxPool2d(2, 2),
            nn.Conv2d(32, 64, 5, 1),
            nn.LeakyReLU(0.01),
            nn.MaxPool2d(2, 2)
        )
        self.fc = nn.Sequential(
            nn.Linear(1024, 1024),
            nn.LeakyReLU(0.01),
            nn.Linear(1024, 1)
        )

    def forward(self, x):
        x = self.conv(x)
        x = x.view(x.shape[0], -1)
        x = self.fc(x)
        return x
    
def gloss(scores_fake):
    loss = 0.5 * ((scores_fake - 1) ** 2).mean()
    return loss

def dloss(scores_real, scores_fake):
    loss = 0.5 * ((scores_real - 1) ** 2).mean() + 0.5 * (scores_fake ** 2).mean()
    return loss

def load_data(batch_size):
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize([0.5], [0.5])
    ])
    mnist = datasets.MNIST('data', train=True, download=True, transform=transform)
    data_loader = torch.utils.data.DataLoader(mnist, batch_size=batch_size, shuffle=True)
    return data_loader

def saveImage(images, filename):  # 按5行5列保存25个图像到一个png文件
    bigImg = np.ones((150, 150))*255  # 先生成宽高均为150的全白大图数组
    for i in range(len(images)):
        row = int(i / 5) * 30  # 计算每个子图在大图中的左上角位置
        col = i % 5 * 30
        img = images[i]
        bigImg[col:col + 28, row:row + 28] = (1-img)*255  # 将子图放入大图中
    f = Image.fromarray(bigImg).convert('L')  # 将数组转换为8位灰度图
    f.save(filename, 'png')  # 保存文件
    
def setKeyObj(generator, discriminator, device):
    device = torch.device('cuda')
    loss = nn.BCELoss().to(device)  # 将损失函数置入合适的计算环境
    optim_G = torch.optim.Adam(generator.parameters(), lr=3e-4, betas=(0.5, 0.999))
    optim_D = torch.optim.Adam(discriminator.parameters(),lr=3e-4,betas=(0.5, 0.999))
    return loss, optim_G, optim_D

torch.manual_seed(7)
if __name__ == '__main__':
    device = torch.device('cuda')
    generator = Generator(INPUT_SIZE).to(device)
    discriminator = Discriminator().to(device)
    loss, optim_G, optim_D = setKeyObj(generator, discriminator, device)
    data_loader = load_data(BATCH_SIZE)
    temp_dlosses = []
    temp_glosses = []
    for epoch in range(EPOCHS):
        for i, (imgs, _) in enumerate(data_loader):
            real_imgs = imgs.to(device)
            real_labels = torch.ones(imgs.size(0), 1).to(device)
            fake_labels = torch.zeros(imgs.size(0), 1).to(device)
            noise = torch.randn(imgs.size(0), INPUT_SIZE).to(device)
            fake_imgs = generator(noise)
            real_scores = discriminator(real_imgs)
            fake_scores = discriminator(fake_imgs)
            d_loss = dloss(real_scores, fake_scores)
            temp_dlosses.append(d_loss.item())
            optim_D.zero_grad()
            d_loss.backward()
            optim_D.step()
            noise = torch.randn(imgs.size(0), INPUT_SIZE).to(device)
            fake_imgs = generator(noise)
            fake_scores = discriminator(fake_imgs)
            g_loss = gloss(fake_scores)
            temp_glosses.append(g_loss.item())
            optim_G.zero_grad()
            g_loss.backward()
            optim_G.step()
        
        #计算平均loss，加入两个总数组
        d_losses.append(sum(temp_dlosses)/len(temp_dlosses))
        g_losses.append(sum(temp_glosses)/len(temp_glosses))
        temp_dlosses = []
        temp_glosses = []
        
        print('Epoch [{}/{}], d_loss: {:.6f}, g_loss: {:.6f}'.format(
            epoch+1, EPOCHS, d_loss.item(), g_loss.item()))
        if (epoch + 1)%10 == 0:
            #保存图像
            saveImage(fake_imgs[:25].cpu().detach().numpy(), 'imgs/fake_images-{}.png'.format(epoch + 1))
            #保存模型到/model，用epoch命名
            torch.save(generator.state_dict(), f'model/generator-{epoch+1}.ckpt')
            
    import matplotlib.pyplot as plt
    from matplotlib.ticker import MaxNLocator
    plt.figure(figsize=(10, 5))
    plt.plot(d_losses, label='Discriminator Loss')
    plt.plot(g_losses, label='Generator Loss')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.legend()
    plt.title('Training Losses')
    plt.gca().xaxis.set_major_locator(MaxNLocator(integer=True))
    plt.show()