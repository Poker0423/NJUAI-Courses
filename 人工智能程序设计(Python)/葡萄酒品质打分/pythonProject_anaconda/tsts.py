#导入所需软件包
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
import sklearn
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import f1_score


# 加载数据集，注意sep参数表示更换分隔符
dataset = pd.read_csv("wine.csv")
# 前4000句作为训练集，4001到末尾作为验证集
train_dataset = dataset.head(4000)
valid_dataset = dataset.tail(-4000)

# 计算数据集的协方差矩阵
df_corr = train_dataset.corr()
sns.heatmap(df_corr, vmax=1, vmin=-1, center=0)
# 绘制热力图，实现数据可视化
plt.show()
print(df_corr[u'quality'])
df1=df_corr[u'quality']
df1.plot.bar()
# 计算不同方法的相关系数矩阵并绘制条形图，反映单个特征对分类结果的贡献
df2=train_dataset.corr(method='kendall')[u'quality']
df2.plot.bar()
print("kendall方法相关系数:")
print(df2)
print("spearman方法相关系数:")
df3 = train_dataset.corr(method='spearman')[u'quality']
print(df3)
df3.plot.bar()
y = train_dataset.iloc[:, [11]].values
x = train_dataset.iloc[:, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]]
X = dataset.iloc[:, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]]
Y = dataset.iloc[:, [11]].values
X_train, X_test, y_train, y_test = train_test_split(X, Y, test_size=0.5, random_state=42)
print('训练集测试及参数：')
print('X_train.shape={}\n y_train.shape ={}\n X_test.shape={}\n y_test.shape={}'.format(X_train.shape, y_train.shape,X_test.shape,y_test.shape))

#线性回归模型
linreg = LinearRegression() # 建立模型对象
# 训练模型并输出模型参数和权重
model = linreg.fit(X_train, y_train)
print('模型参数：')
print(model) # 输出线性回归模型的参数信息
print('参数权重：')
print(linreg.coef_) # 输出线性回归模型的权重信息
y_pred = linreg.predict(X_test) # 利用测试集对模型进行预测并返回预测结果列表
# 手算RMSE
sum_mean = 0
for i in range(len(y_pred)):
    sum_mean += (y_pred[i] - y_test[i]) ** 2
sum_err = np.sqrt(sum_mean / len(y_pred)) # RMSE计算公式：均方误差开方根
print("RMSE by hand:", sum_err)
y_pred = np.around(y_pred,0).astype(int)
f1_micro=sklearn.metrics.f1_score(y_test, y_pred, average='micro')
print(f'线性回归：F1_score_micro:{f1_micro}')

#决策树模型
clf=DecisionTreeClassifier()
clf.fit(X_train, y_train)
y_pred=clf.predict(X_test)
y_pred = np.around(y_pred,0).astype(int)
f2_micro=sklearn.metrics.f1_score(y_test, y_pred, average='micro')
print(f'决策树：F1_score_micro:{f2_micro}')