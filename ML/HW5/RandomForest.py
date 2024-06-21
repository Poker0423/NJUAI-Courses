import numpy as np

from sklearn.tree import DecisionTreeClassifier as dtclf
from sklearn.metrics import roc_auc_score

class RandomForestClassifier:
    def __init__(self, T=10, max_depth=4):
        self.T = T
        self.max_depth = max_depth

        # You may add more fields as needed here.
        self.max_features = 'sqrt'
        self.trees = []
        self.bootstrap_samples = []

    def fit(self, X, y):
        size, n_features = X.shape

        # TODO: Implement the `fit` method here

        for _ in range(self.T):
            indices = np.random.choice(size, size, replace=True)
            self.bootstrap_samples.append(indices)
            X_sample, y_sample = X[indices], y[indices]

            tree = dtclf(max_depth=self.max_depth, max_features=self.max_features)
            tree.fit(X_sample, y_sample)
            self.trees.append(tree)



    def predict_proba(self, X):
        """
        Return the probability of each sample being class 1
        Args:
            X: np.array of shape (n_samples, n_features)
        Returns:
            proba: np.array of shape (n_samples,) where each value is the probability of the sample being class 1
        """

        # TODO: Implement the `predict_proba` method here
        predictions = np.zeros((X.shape[0], self.T))

        for i, tree in enumerate(self.trees):
            proba = tree.predict_proba(X)[:, 1]
            predictions[:, i] = proba  #使用正例

        proba = np.mean(predictions, axis=1)
        return proba




    # ======== DO NOT MODIFY THIS ========
    def evaluate(self, X_train, y_train, X_eval, y_eval):
        self.fit(X_train, y_train)
        proba = self.predict_proba(X_eval)
        return roc_auc_score(y_true=y_eval, y_score=proba)
    # ====================================

    # You may implement some other utility methods if necessary