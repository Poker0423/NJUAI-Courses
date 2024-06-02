import cvxpy as cp % 建议使用cvxpy 1.4版本, 其他版本也可以
from sklearn.datasets import make_classification

m = 100
r = 1.
d = int(m * r)

# 创建一个包含m个样本，每个样本特征维度为d的二分类数据集
X, y = make_classification(m, d)
# 将标记从{0,1}映射至{-1,1}
y = (y * 2 - 1)
C = 1

def solve_primal(X, y, C):
    '''
    :参数 X: ndarray, 形状为(m, d), 样例矩阵
    :参数 y: ndarray, 形状为(m), 样例标签向量
    :参数 C: 标量, 含义与教材式(6.35)中C相同
    :返回: w, b, SVM的权重与偏置
    '''
    m, d = X.shape
    y_ = y.reshape(-1, 1)

    w = cp.Variable((d, 1))
    b = cp.Variable()
    xi = cp.Variable((m, 1))

    loss = cp.sum(xi)
    reg = cp.sum_squares(w)

    # 定义CVXPY优化问题
    prob = cp.Problem(
    	cp.Minimize(0.5 * reg + C * loss), # 目标函数
        [cp.multiply(y_, X @ w + b) >= 1 - xi, xi >= 0] # 约束 
        )

    prob.solve()
    return w, b
