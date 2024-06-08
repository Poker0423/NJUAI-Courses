import cvxpy as cp

def solve_dual(X, y, C):
    m = X.shape[0]
    alpha = cp.Variable(m)
    y_ = y.reshape(-1, 1)
    Q = y_ * y_.T * (X @ X.T)
    loss = 0.5 * cp.quad_form(alpha, Q) - cp.sum(alpha)
    prob = cp.Problem(cp.Minimize(loss),
                      [cp.sum(cp.multiply(y, alpha)) == 0,
                       alpha >= 0,
                       alpha <= C])
    prob.solve()
    return alpha
