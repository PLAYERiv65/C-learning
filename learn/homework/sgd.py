import numpy as np
import matplotlib.pyplot as plt
from tqdm import tqdm
import time

w = 1
b = 0

def input_data():
    year_in = input("Enter the year(separated by space, yyyy): ")
    gdp_in = input("Enter the GDP(separated by space, trillion dollars): ")
    # o stands for original
    oyear = np.array(year_in.split(), dtype=float)
    ogdp = np.array(gdp_in.split(), dtype=float)

    year_mean = oyear.mean()
    gdp_mean = ogdp.mean()
    year_std = oyear.std()
    gdp_std = ogdp.std()
    year = (oyear - year_mean) / year_std
    gdp = (ogdp - gdp_mean) / gdp_std
    assert year.shape == gdp.shape, "Year and GDP should have the same length"
    return year, gdp, oyear, ogdp, year_mean, gdp_mean, year_std, gdp_std


def predict(X):
    return w * X + b

def loss(X, Y):
    return np.average((predict(X) - Y) ** 2)

def gradient(X, Y):
    w_g = np.average(2 * (predict(X) - Y) * X)
    b_g = np.average(2 * (predict(X) - Y))
    return w_g, b_g

def sgd(X, Y, lr=0.01, epochs=1000, batch_size=1):
    global w, b #需要修改
    for epoch in tqdm(range(epochs), desc='SGD'):
        time.sleep(0.01) #智障模拟训练时间
        indexes = np.random.choice(range(len(X)), batch_size)
        w_g, b_g = gradient(X[indexes], Y[indexes])
        w -= lr * w_g
        b -= lr * b_g
        if epoch % 100 == 0:
            lr *= 0.5
            print('epoch', epoch, 'loss', loss(X, Y))

if __name__ == '__main__':
    year, gdp, oyear, ogdp, year_mean, gdp_mean, year_std, gdp_std = input_data()
    b = gdp[0] - w * year[0] #初始化b
    sgd(year, gdp)
    print(f'y = {w * gdp_std / year_std:.2f} * x + {b * gdp_std + gdp_mean - w * year_mean * gdp_std / year_std:.2f}')
    plt.scatter(oyear, ogdp, c='b', label='Real')
    plt.plot(oyear, predict(year) * gdp_std + gdp_mean, c='r', label='Predict')
    plt.legend()
    plt.show()