def predict(X):
    return w * X + b

def loss(X, Y):
    return np.average((predict(X) - Y) ** 2)

def gradient(X, Y):
    w_g = np.average(2 * (predict(X) - Y) * X)
    b_g = np.average(2 * (predict(X) - Y))
    return w_g, b_g

def sgd(X, Y, lr=0.05, epochs=100, batch_size=1):
    global w, b #需要修改
    for epoch in tqdm(range(epochs), desc='SGD'):
        indexes = np.random.choice(range(len(X)), batch_size)
        w_g, b_g = gradient(X[indexes], Y[indexes])
        w -= lr * w_g
        b -= lr * b_g
        if epoch % 100 == 0:
            print('epoch', epoch, 'loss', loss(X, Y))