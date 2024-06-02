import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import roc_curve, auc

# 数据
y_true = np.array([0, 1, 0, 1, 0, 1, 0])
y_scores = np.array([0.32, 0.89, 0.63, 0.32, 0.25, 0.66, 0.48])

# 添加正类样本x8的预测值
y_true = np.append(y_true, 1)
y_scores = np.append(y_scores, 0.8)

# 计算不同阈值下的TPR和FPR
fpr, tpr, thresholds = roc_curve(y_true, y_scores)

# 绘制ROC曲线
plt.plot(fpr, tpr, label='ROC curve (area = %0.2f)' % auc(fpr, tpr))
plt.plot([0, 1], [0, 1], 'k--')
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('Receiver Operating Characteristic')
plt.legend(loc="lower right")
plt.show()

# 计算AUC值
auc_value = auc(fpr, tpr)
print("AUC值为：", auc_value)


