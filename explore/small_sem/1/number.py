#加载手写数字数据
import numpy as np
import time
from sklearn import datasets
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.metrics import classification_report 
from sklearn.metrics import confusion_matrix
dataset = datasets.load_digits()
data_size = len(dataset.data)
indices = np.arange(data_size)
np.random.RandomState(1).shuffle(indices)#确保结果可重现
scores = {}

#数据处理
X, y = dataset.data[indices], dataset.target[indices]
#X = StandardScaler().fit_transform(X)
X_train,X_test,y_train,y_test=train_test_split(X,y,test_size=0.3,random_state=1) 

def evaluate(model):
    model_name = type(model).__name__
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)
    #储存结果到scores
    scores[model_name] = accuracy_score(y_test, y_pred)
    print(f"{model_name:<25} accuracy: {scores[model_name]*100:.2f}%")
    
#使用逻辑回归分类器
from sklearn.linear_model import LogisticRegression
start_time = time.time()
logistic_model = LogisticRegression(max_iter=10000)
logistic_model.fit(X_train, y_train)
evaluate(logistic_model)
end_time = time.time()
print(f"Time used: {end_time-start_time:.2f}s")

#同上，但使用贝叶斯分类器
from sklearn.naive_bayes import GaussianNB
start_time = time.time()
bayes_model = GaussianNB()
bayes_model.fit(X_train, y_train)
evaluate(bayes_model)
end_time = time.time()
print(f"Time used: {end_time-start_time:.2f}s")

#同上，但使用支持向量机分类器
from sklearn.svm import SVC
start_time = time.time()
svm_model = SVC()
svm_model.fit(X_train, y_train)
evaluate(svm_model)
end_time = time.time()
print(f"Time used: {end_time-start_time:.2f}s")

#同上，但使用决策树分类器
from sklearn.tree import DecisionTreeClassifier
start_time = time.time()
tree_model = DecisionTreeClassifier()
tree_model.fit(X_train, y_train)
evaluate(tree_model)
end_time = time.time()
print(f"Time used: {end_time-start_time:.2f}s")

#排名并输出
sorted_scores = sorted(scores.items(), key=lambda x: x[1], reverse=True)
print("\nRanking:")
for model_name, score in sorted_scores:
    print(f"{model_name:<25} accuracy: {score*100:.2f}%")