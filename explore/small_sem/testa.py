from PIL import Image
import numpy as np
import torch
import torch.optim as optim
from torchvision import datasets, transforms
from torchvision.models.mobilenet import mobilenet_v2
from torch.optim.lr_scheduler import StepLR
from torch.nn import CrossEntropyLoss
import pandas as pd

device = torch.device('cuda')
#load from mnist_mobilenet.pt
model = mobilenet_v2()
model.classifier[1] = torch.nn.Linear(in_features=model.classifier[1].in_features, out_features=10)
model.load_state_dict(torch.load('mnist_mobilenet.pt', map_location=device))
model.to(device)

# 打开图像并转换为灰度图像
img = Image.open('a.png').convert('L')
img = img.resize((28, 28))

# 将灰度图像转换为3通道图像
img = np.array(img)
img = np.stack((img,)*3, axis=-1)

# 归一化处理
img = img / 255.0
img = 1-img

# 调整图像形状
img = img.transpose((2, 0, 1))  # 将通道维度移到前面
img = img.reshape(1, 3, 28, 28)

# 转换为PyTorch张量
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
img = torch.from_numpy(img).float().to(device)

# 使用与 transforms.Compose 相同的归一化处理
normalize = transforms.Normalize((0.1307, 0.1307, 0.1307), (0.3081, 0.3081, 0.3081))
img = normalize(img)

# 模型预测
model.eval()
output = model(img)
pred = output.argmax(dim=1, keepdim=True)
print('Prediction:', pred.item())