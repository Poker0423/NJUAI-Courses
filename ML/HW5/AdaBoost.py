import numpy as np

from sklearn.tree import DecisionTreeClassifier as dtclf
from sklearn.metrics import roc_auc_score

class AdaBoostClassifier:
    def __init__(self, T=10, max_depth=4):
        self.T = T
        self.max_depth = max_depth

        # You may add more fields as needed here.
        self.alphas = np.zeros(self.T)
        self.models = []

    def fit(self, X, y):
        y = np.where(y == 0, -1, 1)  # 转换标签为-1和1
        size = X.shape[0]
        weights = np.ones(size) / size

        for t in range(self.T):
            model = dtclf(max_depth=self.max_depth)
            model.fit(X, y, sample_weight=weights)
            predictions = model.predict(X)
            misclassified = predictions != y
            error = np.sum(weights[misclassified])
            if error > 0.5:
                continue  # 避免错误率过高的情况
            alpha = 0.5 * np.log((1 - error) / error)
            self.alphas[t] = alpha
            weights *= np.exp(-alpha * y * predictions)
            weights /= np.sum(weights)
            self.models.append(model)


    def predict_proba(self, X):
        """
        Return the probability of each sample being class 1
        Args:
            X: np.array of shape (n_samples, n_features)
        Returns:
            proba: np.array of shape (n_samples,) where each value is the probability of the sample being class 1
        """

        # TODO: Implement the `predict_proba` method here
        proba = np.zeros(X.shape[0])
        for alpha, model in zip(self.alphas, self.models):
            proba += alpha * model.predict(X)
        return 1 / (1 + np.exp(-2 * proba))
        # return 1 / (1 + np.exp(-proba)) 需要将其转换为[0, 1]之间的概率值


    # ======== DO NOT MODIFY THIS ========
    def evaluate(self, X_train, y_train, X_eval, y_eval):
        self.fit(X_train, y_train)
        proba = self.predict_proba(X_eval)
        return roc_auc_score(y_true=y_eval, y_score=proba)
    # ====================================

    # You may implement some other utility methods if necessary