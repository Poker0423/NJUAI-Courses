import numpy as np

from p3_models import NeuralNetworkClassifier

if __name__ == "__main__":
    X_train = np.loadtxt("X_train.txt", dtype=np.float32)
    y_train = np.loadtxt("y_train.txt", dtype=np.int32)
    # X_test = np.loadtxt("X_test.txt", dtype=np.float32) # In reality, you may NOT have access to these files :(
    # y_test = np.loadtxt("y_test.txt", dtype=np.int32)

    print("X_train.shape:", X_train.shape)
    print("y_train.shape:", y_train.shape)

    clf = NeuralNetworkClassifier(learning_rate=0.01, max_epoch=10) # You can pass hyper-parameters here
    # clf = NeuralNetworkClassifier() # We would test your model like this

    clf.fit(X_train, y_train)
    score = clf.score(X_train, y_train) # Print accuracy on the training set
    print(f"Accuracy on the training set: {score:.4f}")

    # score = clf.score(X_test, y_test) # Print accuracy on the test set
    # print(f"Accuracy on the testing set: {score:.4f}")

    


    