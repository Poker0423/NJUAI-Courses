import numpy as np

def analyze_scale(scale_value):
    np.random.seed(0)
    avg = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
    scale = scale_value
    #生成数据
    data = np.random.randn(5000, 10) + np.tile(avg * scale, (5000, 1))
    #计算均值
    m = np.mean(data, axis=0)
    #未中心化SVD
    _, S, V = np.linalg.svd(data)
    e1 = V[0, :]
    # 中心化SVD
    newdata = data - np.tile(m, (5000, 1))
    _, S, V = np.linalg.svd(newdata)
    new_e1 = V[0, :]
    #标准化向量
    avg_norm = avg - np.mean(avg)
    avg_norm = avg_norm / np.linalg.norm(avg_norm)
    
    e1 = e1 - np.mean(e1)
    e1 = e1 / np.linalg.norm(e1)
    print("right eigenvectors :",new_e1)
    new_e1 = new_e1 - np.mean(new_e1)
    new_e1 = new_e1 / np.linalg.norm(new_e1)
    #计算相关性
    corr1 = np.abs(np.dot(avg_norm, e1))
    corr2 = np.abs(np.dot(e1, new_e1))
    
    return corr1, corr2, new_e1

#测试不同的scale值
scale_values = [1, 0.5, 0.1, 0.05, 0.01, 0.005, 0.001, 0.0005, 0.0001]
results = [analyze_scale(s) for s in scale_values]
corr1_values = [r[0] for r in results]
corr2_values = [r[1] for r in results]
print("avg and vec w/o centralization:",corr1_values)
print("vec corr between w/ and w/o centralization:",corr2_values)

