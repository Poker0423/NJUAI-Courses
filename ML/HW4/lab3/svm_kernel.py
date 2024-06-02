import numpy as np
import matplotlib.pyplot as plt

from svm_kernel_solution import svm_kernel_linear, svm_kernel_rbf, svm_kernel_custom

def generate_data():
    np.random.seed(0)
    # 随机生成服从标准高斯分布的样本，特征维度为2
    X = np.random.randn(300, 2)
    # 计算标记，两个特征符号相同时为0不同时为1
    Y = np.logical_xor(X[:, 0] > 0, X[:, 1] > 0)
    return X, Y

def plot_data():
    plt.figure()
    plt.scatter(X[Y == 0, 0], X[Y == 0, 1], color='red', label='Label 0')
    plt.scatter(X[Y == 1, 0], X[Y == 1, 1], color='blue', label='Label 1')
    plt.title('XOR Classification')
    plt.xlabel('Feature 1')
    plt.ylabel('Feature 2')
    plt.legend()
    plt.grid(True)
    plt.savefig('XOR_data.png')

def plot_boundary(clf, clf_name):
    h = .02  # step size in the mesh
    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))

    # Plot the decision boundary by assigning a color to each point in the mesh [x_min, x_max]x[y_min, y_max]
    Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)
    
    plt.figure()
    plt.contourf(xx, yy, Z, cmap=plt.cm.coolwarm, alpha=0.8)
    plt.scatter(X[:, 0], X[:, 1], c=Y, cmap=plt.cm.coolwarm, edgecolors='k')
    plt.xlim(xx.min(), xx.max())
    plt.ylim(yy.min(), yy.max())
    plt.savefig(clf_name + '.jpg')

if __name__ == '__main__':
    X, Y = generate_data()
    plot_data()

    # 定义并训练线性核SVC分类器, 并绘制决策边界
    clf_linear = svm_kernel_linear(X, Y)
    plot_boundary(clf_linear, 'clf_linear')

    # 定义并训练高斯核(RBF核)SVC分类器, 并绘制决策边界
    clf_rbf = svm_kernel_rbf(X, Y)
    plot_boundary(clf_rbf, 'clf_rbf')

    # 定义并训练自定义核SVC分类器, 并绘制决策边界
    clf_custom = svm_kernel_custom(X, Y)
    plot_boundary(clf_custom, 'clf_custom')
