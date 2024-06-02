import math
import random
import numpy as np
import pandas as pd
from tqdm import tqdm
from matplotlib import pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.metrics import roc_curve, auc
from sklearn.preprocessing import normalize


def load_data(path):
    """
    Load data from a csv file, and return the feature vectors and the ground-truth labels.
    """

    df = pd.read_csv(path, encoding="utf-8")

    # Print the dataframe to see the data structure
    print(f"Loading Dataframe:\n{df}\n")

    # "black" is the true label, and the rest are feature vectors
    y = df["black"].to_numpy(dtype=np.int32)
    X = df.drop(columns=["black"]).to_numpy(dtype=np.float64)

    # Normalize the feature vectors to avoid overflow problem
    X = normalize(X, axis=0, norm="max")

    return X, y



class MyLogisticRegression:
    def __init__(self, iter_num=10):
        assert iter_num > 0, "iter_num should be a positive integer"
        self.iter_num = iter_num
        self.beta = None
    
    @staticmethod
    def _insert_one(X):
        """
        Insert a column of ones into the feature matrix X, making x-hat
        """
        return np.concatenate([np.ones((X.shape[0], 1)), X], axis=1)

    @staticmethod
    def _partial_l(beta, X, y):
        """
        Compute the gradient of l(beta) w.r.t. beta, i.e., equation (3.30) in textbook
        """

        p = 1 / (1 + math.e ** (-X @ beta))
        result = -X.T @ (y - p)

        return result

    @staticmethod
    def _partial_2_l(beta, X, y):
        """
        Compute the Hessian matrix of l(beta) w.r.t. beta, i.e., equation (3.31) in textbook
        """

        # TODO: (Problem 5.1) Compute the Hessian matrix of l(beta) w.r.t. beta, i.e., equation (3.31) in textbook
        # ==== START OF YOUR CODE (DO NOT DELETE THIS LINE) ====

        p = 1 / (1 + math.e ** (-X @ beta))
        p=p.reshape(1,-1)[0]
        result = X.T @ np.diag(p * (1 - p)) @ X

        # ==== END OF YOUR CODE (DO NOT DELETE THIS LINE) ====

        return result

    def _newton_iterate_step(self, X, y):
        """
        Solving the minimizer for log-likelihood in Logistic Regression, i.e., equation (3.29) in textbook
        """
        # TODO: (Problem 5.2) Update parameter `self.beta` using Newton's method
        # Hint: use `self._partial_l(self.beta, X, y)` and `self._partial_2_l(self.beta, X, y)` in your code
        # ==== START OF YOUR CODE (DO NOT DELETE THIS LINE) ====

        # Update parameter `self.beta` using Newton's method
        new_beta = self.beta - np.linalg.inv(self._partial_2_l(self.beta, X, y)) @ self._partial_l(self.beta, X, y)

        # ==== END OF YOUR CODE (DO NOT DELETE THIS LINE) ====

        self.beta = new_beta

    def fit(self, X, y):
        """
        Fit the model according to the given training data.
        :param X: array-like, shape (n_samples, n_features)
            The training input samples.
        :param y: array-like, shape (n_samples,)
            The target values.
        """
        # Insert a column of ones into the feature matrix X, making x-hat
        X = self._insert_one(X)
        y = y.reshape(-1, 1)

        # initialize w randomly
        self.beta = np.random.randn(X.shape[1], 1)  

        # iterate for `self.iter_num` times
        for index in tqdm(range(self.iter_num), desc="Training"):
            self._newton_iterate_step(X, y)

        return self

    def predict_proba(self, X):
        """
        Predict label probability for new data `X`
        :param X: array-like, shape (n_samples, n_features)
            The input samples.
        :return: array-like, shape (n_samples,)
            The predicted probability of the sample in class `1`.
        """
        # Insert a column of ones into the feature matrix X, making x-hat
        X = self._insert_one(X)

        # TODO: (Problem 5.3) Predict classification probability for new data `X`
        # Hint: return the probability vector P(X=1), rather than 0-1 vector of labels
        # ==== START OF YOUR CODE (DO NOT DELETE THIS LINE) ====
        p = 1 / (1 + math.e ** (-X @ self.beta))

        y_prob = np.copy(p)

        # ==== END OF YOUR CODE (DO NOT DELETE THIS LINE) ====
        return y_prob

    def predict(self, X):

        y_prob = self.predict_proba(X)
        y_pred = np.round(y_prob)

        return y_pred

def plot_roc(y_prob, y_test):
    """
    Draw the ROC curve using matplotlib, then return auc score
    :param y_prob: array-like, shape (n_samples,), elements in [0, 1]
        The predicted probability of the sample in class `1`.
    :param y_test: array-like, shape (n_samples,), elements are binary
        The ground-truth labels.
    """

    fig = plt.figure(dpi=200)

    # TODO: (Problem 5.4) Draw the ROC curve using matplotlib, then return auc score
    # Hint: You are allowed to use the `roc_curve` and `auc` functions in sklearn.metrics
    # Hint: Figure 2.4 in textbook may work as a reference
    # ==== START OF YOUR CODE (DO NOT DELETE THIS LINE) ====
    fpr, tpr, thresholds = roc_curve(y_test, y_prob)
    auc_value = auc(fpr, tpr)

    plt.plot(fpr, tpr, label='ROC curve' % auc_value)
    plt.xlabel('FPR')
    plt.ylabel('TPR')
    plt.title('ROC Curve')
    plt.legend(loc="lower right")
    
    # ==== END OF YOUR CODE (DO NOT DELETE THIS LINE) ====

    fig.savefig("roc.png")
    print("ROC plot is saved as roc.png")

    return auc_value
    

if __name__ == "__main__":
    # Fix the random seed for reproducibility
    random.seed(42)
    np.random.seed(42)

    DATASET_PATH = "data.csv"

    # Load dataset, and print the shape of the feature vectors and the true labels
    X, y = load_data(DATASET_PATH)
    print("Shape of X:", X.shape)
    print("Shape of y:", y.shape)

    # Split the 80% of the dataset as the training set, and the rest as the test set
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)
    print("Shape of X_train:", X_train.shape)
    print("Shape of y_train:", y_train.shape)
    print("Shape of X_test:", X_test.shape)
    print("Shape of y_test:", y_test.shape)

    # If you successfully implement the `MyLogisticRegression` class, DO NOT edit the following code
    # Otherwise, you can import and initialize a LogisticRegression model from sklearn.
    # In either case, use default hyperparameters for the model.
    # Hint: this model is described in https://scikit-learn.org/stable/modules/classes.html#module-sklearn.linear_model
    # ==== START OF YOUR CODE (DO NOT DELETE THIS LINE) ====

    model = MyLogisticRegression()
    # model = ??? 

    # ==== END OF YOUR CODE (DO NOT DELETE THIS LINE) ====

    # Train the model on the training set
    model.fit(X_train, y_train)

    # Generate predictions on the test set
    y_prob = model.predict_proba(X_test)

    # Fix for sklearn model, where predict_proba returns an array with shape (N_test, 2)
    if y_prob.shape[1] == 2:
        y_prob = y_prob[:, 1]

    # Plot the ROC curve, and calculate the AUC score
    auc_value = plot_roc(y_prob, y_test)

    print(f"AUC in test set: {auc_value:.4f}")