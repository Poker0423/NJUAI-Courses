import numpy as np

# 生成10维样本
d = 10
samples = np.random.randn(20, d)
norms = np.linalg.norm(samples, axis=1)

mean_norm = np.mean(norms)
min_norm = np.min(norms)
max_norm = np.max(norms)

print(f"10维：均值={mean_norm:.4f}, 最小值={min_norm:.4f}, 最大值={max_norm:.4f}")


#不同维度
dims = [100, 1000, 10000, 100000]
for d in dims:
    samples = np.random.randn(20, d)
    norms = np.linalg.norm(samples, axis=1)
    print(f"维度 {d}: 均值={norms.mean():.4f}, 最小值={norms.min():.4f}, 最大值={norms.max():.4f}")

