from utils import verify_sha256, load_coil20
from utils import LDAMeta, RidgeMeta
from utils import lda_sanity_check, classifier_2_sanity_check, classifier_n_sanity_check

import multiprocessing as mp

import tqdm
import numpy as np
import matplotlib.pyplot as plt

# NOTE 你可能会用到这两个函数
from scipy.linalg import pinv, eig
from scipy.linalg import svd

COIL20_ZIP_PATH = "./coil-20-proc.zip"
COIL20_HASH_STR = "517c5594820eb40066ba0ff6842e7f09392bf7fde849bf9cb9c28445b0f29e88"


class LDA(LDAMeta):
    """LDA 类, 提供 fit 和 transform 两个方法"""

    def __init__(self, n_dimension: int) -> None:
        """
        初始化超参数

        参数
            n_dimension: int
                需要降维到的维度
        """

        assert n_dimension > 0
        self.n_dimension = n_dimension

    def fit(self, x: np.ndarray, y: np.ndarray) -> None:
        """
        训练模型

        参数
            x: np.ndarray
                形状为 (train_size, dimension) 图像数据, 类型 np.float32
            y: np.ndarray
                形状为 (train_size,) 标签数据, 顺序对应于 x, 类型为 np.int32

        返回
            无返回值
        """

        # n 是类别个数; m 是训练样本数量; d 是样例维度.
        n = y.max() + 1
        m, d = x.shape

        # TODO
        # 计算全局平均向量
        mean_overall = np.mean(x, axis=0)
        # 初始化类内散度矩阵和类间散度矩阵
        S_W = np.zeros((d, d))
        S_B = np.zeros((d, d))

        for i in range(n):
            x_i = x[y == i]
            mean_i = np.mean(x_i, axis=0)
            S_W += np.dot((x_i - mean_i).T, (x_i - mean_i))
            n_i = x_i.shape[0]
            mean_diff = (mean_i - mean_overall).reshape(d, 1)
            S_B += n_i * np.dot(mean_diff, mean_diff.T)

        # 求解 S_W^(-1)S_B 的特征值和特征向量
        eig_vals, eig_vecs = np.linalg.eig(np.linalg.inv(S_W).dot(S_B))
        # 仅保留特征值和特征向量的实部
        eig_vals = eig_vals.real
        eig_vecs = eig_vecs.real

        # 对特征值进行排序，并找到最大的n_dimension个特征值对应的特征向量
        eig_list = [(np.abs(eig_vals[i]), eig_vecs[:, i]) for i in range(len(eig_vals))]
        eig_list = sorted(eig_list, key=lambda x: x[0], reverse=True)
        self.w = np.array([eig_list[i][1] for i in range(self.n_dimension)]).T

    def transform(self, x: np.ndarray) -> np.ndarray:
        """
        测试模型

        参数
            x: np.ndarray
                形状为 (test_size, dimension) 图像数据, 类型 np.float32

        返回
            y: np.ndarray
                形状为 (test_size, 2) 标签数据, 顺序对应于 x, 类型为 np.float32
        """

        # n 是类别个数; m 是训练样本数量; d 是样例维度.
        m, d = x.shape

        # TODO
        y = np.dot(x, self.w).astype(np.float32)
        return y

class Ridge2(RidgeMeta):
    """Ridge2 类, 提供 fit 和 predict 两个方法"""

    def __init__(self, Lambda: float) -> None:
        """
        初始化超参数

        参数
            Lambda: float
                正则化系数 λ
        """

        assert Lambda > 0.0
        self.Lambda = Lambda

    def fit(self, x: np.ndarray, y: np.ndarray) -> None:
        """
        训练模型

        参数
            x: np.ndarray
                形状为 (train_size, dimension) 图像数据, 类型 np.float32
            y: np.ndarray
                形状为 (train_size,) 标签数据, 顺序对应于 x, 类型为 np.int32

        返回
            无返回值
        """

        # n 是类别个数; m 是训练样本数量; d 是样例维度.
        n = y.max() + 1
        m, d = x.shape

        # 这里约定只有两类
        assert n == 2


        # TODO
        y_transformed = np.where(y == 0, -1, 1)
        # 计算权重向量 w
        self.w = np.linalg.solve(x.T @ x + self.Lambda * np.eye(x.shape[1]), x.T @ y_transformed)

    def predict(self, x: np.ndarray) -> np.ndarray:
        """
        测试模型

        参数
            x: np.ndarray
                形状为 (test_size, dimension) 图像数据, 类型 np.float32

        返回
            y: np.ndarray
                形状为 (test_size,) 标签数据, 顺序对应于 x, 类型为 np.int32
        """

        # n 是类别个数; m 是训练样本数量; d 是样例维度.
        m, d = x.shape
        # TODO
        y_pred = np.dot(x, self.w)
        y_pred = np.where(y_pred >= 0, 1, 0)
        return y_pred.astype(np.int32)

class RidgeN(RidgeMeta):
    """RidgeN 类, 提供 fit 和 predict 两个方法"""

    def __init__(self, Lambda: float) -> None:
        """
        初始化超参数

        参数
            Lambda: float
                正则化系数 λ
        """

        assert Lambda > 0.0
        self.Lambda = Lambda

    def fit(self, x: np.ndarray, y: np.ndarray) -> None:
        """
        训练模型

        参数
            x: np.ndarray
                形状为 (train_size, dimension) 图像数据, 类型 np.float32
            y: np.ndarray
                形状为 (train_size,) 标签数据, 顺序对应于 x, 类型为 np.int32

        返回
            无返回值
        """

        # n 是类别个数; m 是训练样本数量; d 是样例维度.
        n = y.max() + 1
        m, d = x.shape

        self.n = n
        self.ridge2_pool = [Ridge2(self.Lambda) for k in range(n)]

        # TODO
        for k in range(n):
            y_binary = (y == k).astype(np.int32)
            self.ridge2_pool[k].fit(x, y_binary)

    def predict(self, x: np.ndarray) -> np.ndarray:
        """
        测试模型

        参数
            x: np.ndarray
                形状为 (test_size, dimension) 图像数据, 类型 np.float32

        返回
            y: np.ndarray
                形状为 (test_size,) 标签数据, 顺序对应于 x, 类型为 np.int32
        """

        # n 是类别个数; m 是训练样本数量; d 是样例维度.
        m, d = x.shape

        # TODO
        y_pred = np.zeros((m, self.n), dtype=np.float32)
        for k in range(self.n):
            y_pred[:, k] = self.ridge2_pool[k].predict(x)

        y_pred_argmax = y_pred.argmax(axis=1)
        y_pred_argmax = y_pred_argmax.astype(np.int32)
        return y_pred_argmax

def main():
    verify_sha256(COIL20_ZIP_PATH, COIL20_HASH_STR)
    x_train, y_train, x_test, y_test = load_coil20(COIL20_ZIP_PATH)

    # 检查输入输出格式

    lda_sanity_check(LDA)
    classifier_2_sanity_check(Ridge2)
    classifier_n_sanity_check(RidgeN)

    # 把训练数据降至两维并绘制散点图

    lda = LDA(n_dimension=2)
    lda.fit(x_train, y_train)
    x_train_2d = lda.transform(x_train)

    # TODO
    # 绘制散点图
    plt.figure(figsize=(10, 5))
    for i in np.unique(y_train):
        plt.scatter(x_train_2d[y_train == i, 0], x_train_2d[y_train == i, 1], label=f'Train Class {i}')
    plt.title('LDA')
    plt.xlabel('LDA x')
    plt.ylabel('LDA y')
    plt.legend()
    plt.show()

    # 把测试数据降至两维并绘制散点图

    lda = LDA(n_dimension=2)
    lda.fit(x_train, y_train)
    x_test_2d = lda.transform(x_test)

    # TODO
    # 绘制散点图
    plt.figure(figsize=(10, 5))
    for i in np.unique(y_train):
        plt.scatter(x_test_2d[y_test == i, 0], x_test_2d[y_test == i, 1], label=f'Test Class {i}')
    plt.title('LDA')
    plt.xlabel('LDA x')
    plt.ylabel('LDA y')
    plt.legend()
    plt.show()
    # 训练错误率和测试错误率随 λ 变化的折线图

    Lambda_seq = np.logspace(start=-4, stop=4, num=9).tolist()

    train_errors = []
    test_errors = []
    for Lambda in Lambda_seq:
        model = RidgeN(Lambda)
        model.fit(x_train, y_train)
        train_pred = model.predict(x_train)
        test_pred = model.predict(x_test)
        train_error = np.mean(train_pred != y_train)
        test_error = np.mean(test_pred != y_test)
        train_errors.append(train_error)
        test_errors.append(test_error)

    plt.figure(figsize=(10, 5))
    plt.plot(Lambda_seq, train_errors, label='Train Error', marker='o')
    plt.plot(Lambda_seq, test_errors, label='Test Error', marker='s')
    plt.xscale('log')
    plt.xlabel('Lambda')
    plt.ylabel('Error Rate')
    plt.title('Error Rate vs. Lambda')
    plt.legend()
    plt.show()

    # TODO



if __name__ == "__main__":
    main()
