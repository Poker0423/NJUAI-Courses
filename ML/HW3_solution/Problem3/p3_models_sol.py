import numpy as np

class BaseClassifier:
    """Base class for all classifiers, DO NOT MODIFY THIS"""
    def __init__(self):
        pass

    def fit(self, X, y):
        # see the docstring of NeuralNetworkClassifier.fit
        assert 0, "No need to implement for base class"

    def predict_item(self, x):
        # see the docstring of NeuralNetworkClassifier.predict_item
        assert 0, "No need to implement for base class"

    def predict(self, X):
        """
        Predict the label of each sample in X
        Args:
            X: np.ndarray, shape=(n_samples, n_features)
        Returns:
            y: np.ndarray, shape=(n_samples,)
        """
        assert len(X.shape) == 2, "X.shape expected: (n_samples, n_features), but got: " + str(X.shape)
        return np.round(np.apply_along_axis(self.predict_item, 1, X))

    def score(self, X, y):
        """
        Compute the accuracy of the classifier
        Args:
            X: np.ndarray, shape=(n_samples, n_features)
            y: np.ndarray, shape=(n_samples,)
        Returns:
            accuracy: float
        """
        return float(np.mean(self.predict(X) == y))

def sigmoid(x):
    """
    The sigmoid function
    Args: x: float
    Returns: float, the value of sigmoid function at x
    """

    return 1.0 / (1 + np.exp(-x)) # TODO: implement the sigmoid function

def deriv_sigmoid(x):
    """
    The derivative of the sigmoid function
    Args: x: float
    Returns: float, the derivative of sigmoid function at x
    """

    return sigmoid(x) * (1 - sigmoid(x)) # TODO: implement the derivative of the sigmoid function

# MSE loss function
def mse_loss(y_true, y_pred):
    """
    Compute the mean squared error loss
    Args:
        y_true: np.ndarray, shape=(n_samples,), the true labels
        y_pred: np.ndarray, shape=(n_samples,), the predicted labels
    Returns:
        loss: float, the mean squared error loss
    """

    return np.mean(np.square(y_true - y_pred)) # TODO: implement the mean squared error loss

class NeuralNetworkClassifier(BaseClassifier):
    """A simple neural network classifier, with 2 input nodes, 2 hidden nodes (1 layer), and 1 output node"""
    def __init__(self, learning_rate=0.25, max_epoch=100): # TODO: Update these default parameters, after parameter-tuning.
        super().__init__()
        rng = np.random.RandomState(42)

        self.learning_rate = learning_rate
        self.max_epoch = max_epoch

        # initialize weights
        self.w1 = rng.normal()
        self.w2 = rng.normal()
        self.w3 = rng.normal()
        self.w4 = rng.normal()
        self.w5 = rng.normal()
        self.w6 = rng.normal()

        # initialize biases
        self.b1 = rng.normal()
        self.b2 = rng.normal()
        self.b3 = rng.normal()

    def fit(self, X, y):
        """
        Fit the classifier to the training data
        Args:
            X: np.ndarray, shape=(n_samples, n_features)
            y: np.ndarray, shape=(n_samples,)
        returns:
            None
        """

        assert len(X.shape) == 2
        n_samples, n_features = X.shape
        assert n_features == 2
        assert y.shape == (n_samples, )

        for epoch in range(self.max_epoch):
            for x, y_true in zip(X, y):

                # Forward
                sum_h1 = x[0]*self.w1 + x[1]*self.w2 # TODO: the weighted sum of the inputs to "node h1"
                h1 = sigmoid(sum_h1 + self.b1)       # TODO: the output of "node h1"

                sum_h2 = x[0]*self.w3 + x[1]*self.w4 # TODO: the weighted sum of the inputs to :node h2"
                h2 = sigmoid(sum_h2 + self.b2)       # TODO: the output of "node h2"

                sum_o1 =  h1*self.w5 + h2*self.w6    # TODO: the weighted sum of the inputs to "node o1:
                o1 =  sigmoid(sum_o1 + self.b3)      # TODO: the output of "node o1"

                y_pred = o1 # We directly use o1 as the probability that the example belongs to class 1

                # Backpropagation: computing gradients
                d_L_d_y_pred = 2.0 * (y_pred - y_true)                    # TODO: the gradient of squared error loss w.r.t. y_pred

                d_y_pred_d_w5 = deriv_sigmoid(sum_o1 + self.b3) * h1      # TODO: the gradient of y_pred w.r.t. w5
                d_y_pred_d_w6 = deriv_sigmoid(sum_o1 + self.b3) * h2      # TODO: the gradient of y_pred w.r.t. w6
                d_y_pred_d_b3 = deriv_sigmoid(sum_o1 + self.b3)           # TODO: the gradient of y_pred w.r.t. b3
                d_y_pred_d_h1 = deriv_sigmoid(sum_o1 + self.b3) * self.w5 # TODO: the gradient of y_pred w.r.t. h1
                d_y_pred_d_h2 = deriv_sigmoid(sum_o1 + self.b3) * self.w6 # TODO: the gradient of y_pred w.r.t. h2

                # Gradients for hidden layer parameters
                d_h1_d_w1 =  deriv_sigmoid(sum_h1 + self.b1) * x[0]       # TODO: the gradient of h1 w.r.t. w1
                d_h1_d_w2 =  deriv_sigmoid(sum_h1 + self.b1) * x[1]       # TODO: the gradient of h1 w.r.t. w2
                d_h1_d_b1 =  deriv_sigmoid(sum_h1 + self.b1)              # TODO: the gradient of h1 w.r.t. b1

                d_h2_d_w3 =  deriv_sigmoid(sum_h2 + self.b2) * x[0]       # TODO: the gradient of h2 w.r.t. w3
                d_h2_d_w4 =  deriv_sigmoid(sum_h2 + self.b2) * x[1]       # TODO: the gradient of h2 w.r.t. w4
                d_h2_d_b2 =  deriv_sigmoid(sum_h2 + self.b2)              # TODO: the gradient of h2 w.r.t. b2

                # Update weights and biases with Gradient Descent
                self.w5 -=  self.learning_rate * d_L_d_y_pred * d_y_pred_d_w5 # TODO: update w5
                self.w6 -=  self.learning_rate * d_L_d_y_pred * d_y_pred_d_w6 # TODO: update w6
                self.b3 -=  self.learning_rate * d_L_d_y_pred * d_y_pred_d_b3 # TODO: update b3

                self.w1 -=  self.learning_rate * d_L_d_y_pred * d_y_pred_d_h1 * d_h1_d_w1 # TODO: update w1
                self.w2 -=  self.learning_rate * d_L_d_y_pred * d_y_pred_d_h1 * d_h1_d_w2 # TODO: update w2
                self.b1 -=  self.learning_rate * d_L_d_y_pred * d_y_pred_d_h1 * d_h1_d_b1 # TODO: update b1

                self.w3 -=  self.learning_rate * d_L_d_y_pred * d_y_pred_d_h2 * d_h2_d_w3 # TODO: update w3
                self.w4 -=  self.learning_rate * d_L_d_y_pred * d_y_pred_d_h2 * d_h2_d_w4 # TODO: update w4
                self.b2 -=  self.learning_rate * d_L_d_y_pred * d_y_pred_d_h2 * d_h2_d_b2 # TODO: update b2

            # Every 10 epochs, print the MSE loss on the training data
            if epoch % 10 == 0:
                y_preds = np.apply_along_axis(self.predict_item, 1, X)
                loss = mse_loss(y, y_preds)
                print("Epoch {:d} loss: {:.3f}".format(epoch, loss))

    def predict_item(self, x):
        """
        Predict the label of a single sample
        Args:
            x: np.ndarray, shape=(n_features,). In this homework, n_features=2
        Returns:
            y: float, the probability of the sample belonging to class 1
        """

        assert x.shape == (2, ), "Invalid x shape: " + str(x.shape)

        # Hint: refer to the forward-pass procedure in fit()

        h1 = sigmoid(self.w1 * x[0] + self.w2 * x[1] + self.b1) # TODO: the output of "node h1"
        h2 = sigmoid(self.w3 * x[0] + self.w4 * x[1] + self.b2) # TODO: the output of "node h2"
        o1 = sigmoid(self.w5 * h1 + self.w6 * h2 + self.b3) # TODO: the output of "node o1"

        return o1