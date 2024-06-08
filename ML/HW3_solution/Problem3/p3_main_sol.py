import numpy as np

from p3_models_sol import NeuralNetworkClassifier
from sklearn.model_selection import KFold

if __name__ == "__main__":
    X_train = np.loadtxt("p3_X_train.txt", dtype=np.float32)
    y_train = np.loadtxt("p3_y_train.txt", dtype=np.int32)
    # X_test = np.loadtxt("p3_X_test.txt", dtype=np.float32) # In reality, you may NOT have access to these files :(
    # y_test = np.loadtxt("p3_y_test.txt", dtype=np.int32)

    print("X_train.shape:", X_train.shape)
    print("y_train.shape:", y_train.shape)

    learning_rates = np.logspace(-3, 0, 6)
    max_epochs = np.logspace(1, 2, 5)
    kf = KFold(n_splits=5)

    best_params = None
    best_accuracy = 0

    for learning_rate, max_epoch in zip(learning_rates, max_epochs):
        max_epoch = round(max_epoch)

        clf = NeuralNetworkClassifier(learning_rate=learning_rate, max_epoch=max_epoch)

        accuracies = []
        for train_index, test_index in kf.split(X_train):
            clf.fit(X_train[train_index], y_train[train_index])
            accuracies.append(clf.score(X_train[test_index], y_train[test_index]))

        accuracy = np.mean(accuracies)

        print(f"LR = {learning_rate:.4f}, Epochs = {max_epoch:d} => Accuracy = {accuracy:.3f}")

        if accuracy > best_accuracy:
            best_params = (learning_rate, max_epoch)
            best_accuracy = accuracy
    
    print(f"Best params: {best_params}, Best validation accuracy: {best_accuracy:.4f}")
    # Best params: (2.5118864315095796e-01, 100), Best validation accuracy: 0.8906


    


    