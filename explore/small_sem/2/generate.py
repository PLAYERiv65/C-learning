#从/model加载模型，生成手写数字图片
import torch
from GAN_train import Generator
import numpy as np
import os
import matplotlib.pyplot as plt
import torchvision.utils as vutils
from torchvision import transforms
from PIL import Image
INPUT_SIZE = 100

def generate(epoch, num, device):
    # 加载模型
    model = Generator(INPUT_SIZE).to(device)
    model.load_state_dict(torch.load(f'model/generator-{epoch}.ckpt'))#根据epoch选择模型参数
    model.eval()#使用评估模式
    
    # 生成图片，与训练时流程类似
    noise = torch.randn(num, INPUT_SIZE).to(device)
    fake_imgs = model(noise)
    
    # 用plt显示图片
    plt.figure(figsize=(4, 4))
    plt.axis("off")
    plt.title("Generated Images")
    plt.gca().set_axis_off()
    grid_img = vutils.make_grid(fake_imgs.to('cpu'), nrow=4, padding=2, normalize=True)
    plt.imshow(np.transpose(grid_img.cpu(), (1, 2, 0)))
    plt.show()
    
if __name__ == '__main__':
    num = input('input num：')
    epoch = input('input epoch：') 
    device = torch.device('cuda')
    generate(int(epoch), int(num), device)