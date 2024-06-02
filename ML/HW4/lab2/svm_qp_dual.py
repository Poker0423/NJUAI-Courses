def solve_dual(X, y, C):
    '''
    :参数 X: ndarray, 形状为(m, d), 样例矩阵
    :参数 y: ndarray, 形状为(m), 样例标签向量
    :参数 C: 标量, 含义与教材式(6.35)中C相同
    :返回: alpha，SVM的对偶变量
    '''
    m, d = X.shape
    alpha = cp.Variable(m)
    y = y.astype(float).reshape(-1, 1)
    c_ = np.full((m, 1), C)

    K = X @ X.T
    q_1 = np.outer(y, y) * K

    prob = cp.Problem(
        cp.Minimize(0.5 * cp.quad_form(alpha, q_1) - cp.sum(alpha)),  # 目标函数
        [alpha >= 0, alpha <= c_, y.T @ alpha == 0]  # 约束
    )
    prob.solve()
    return alpha.value
