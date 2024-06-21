import numpy as np

from sklearn.tree import DecisionTreeClassifier as dtclf
from sklearn.metrics import roc_auc_score

class RandomForestClassifier:
    def __init__(self, T=10, max_depth=4):
        self.T = T
        self.max_depth = max_depth

        # You may add more fields as needed here.
        self.clf_list = list()

    def fit(self, X, y):
        size, n_features = X.shape

        for iteration in range(self.T):
            rng = np.random.RandomState(iteration)

            # Randomly sample with bootstrapping
            bs_index = rng.randint(0, size, (size,))
            new_X = [X[idx] for idx in bs_index]
            new_y = [y[idx] for idx in bs_index]

            clf = dtclf(random_state=iteration, max_depth=self.max_depth, max_features="log2")
            clf.fit(new_X, new_y)

            self.clf_list.append(clf)

    def predict_proba(self, X):
        """
        Return the probability of each sample being class 1
        Args:
            X: np.array of shape (n_samples, n_features)
        Returns:
            proba: np.array of shape (n_samples,) where each value is the probability of the sample being class 1
        """

        result = np.zeros((len(X), 2))

        for i in range(len(self.clf_list)):
            result += (self.clf_list[i].predict_proba(X) / len(self.clf_list))

        return result[:, 1]

    # ======== DO NOT MODIFY THIS ========
    def evaluate(self, X_train, y_train, X_eval, y_eval):
        self.fit(X_train, y_train)
        proba = self.predict_proba(X_eval)
        return roc_auc_score(y_true=y_eval, y_score=proba)
    # ====================================

    # You may implement some other utility methods if necessary