import numpy as np

from sklearn.tree import DecisionTreeClassifier as dtclf
from sklearn.metrics import roc_auc_score

class AdaBoostClassifier:
    def __init__(self, T=10, max_depth=4):
        self.T = T
        self.max_depth = max_depth

        # You may add more fields as needed here.
        self.clf_list = list()
        self.clf_weights = list()

    def fit(self, X, y):
        size, n_features = X.shape

        example_weights = np.array([1.0/size for item in range(size)])
        y = np.array([1 if item==1 else -1 for item in y])

        for iteration in range(self.T):
            clf = dtclf(random_state=iteration, max_depth=self.max_depth)
            clf.fit(X, y, sample_weight=example_weights)

            prediction = clf.predict(X)

            eps = np.sum([example_weights[i] for i in range(size) if prediction[i]!=y[i]], axis=0)
            if (eps > 0.5):
                break

            alpha = np.math.log((1.0-eps)/eps) * 0.5

            for i in range(size):
                example_weights[i] *= np.math.exp(-1 * alpha * y[i] * prediction[i])
            example_weights /= np.sum(example_weights, axis=0)

            self.clf_list.append(clf)
            self.clf_weights.append(alpha)

    def predict_proba(self, X):
        """
        Return the probability of each sample being class 1
        Args:
            X: np.array of shape (n_samples, n_features)
        Returns:
            proba: np.array of shape (n_samples,) where each value is the probability of the sample being class 1
        """

        result = np.zeros((len(X), 2))

        normalized_clf_weights = np.array(self.clf_weights) / np.sum(self.clf_weights)

        for i in range(len(self.clf_list)):
            result += (self.clf_list[i].predict_proba(X) * normalized_clf_weights[i])

        return result[:, 1]

    # ======== DO NOT MODIFY THIS ========
    def evaluate(self, X_train, y_train, X_eval, y_eval):
        self.fit(X_train, y_train)
        proba = self.predict_proba(X_eval)
        return roc_auc_score(y_true=y_eval, y_score=proba)
    # ====================================

    # You may implement some other utility methods if necessary