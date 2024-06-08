from sklearn import svm
import numpy as np

def svm_kernel_linear(X, Y):
    clf = svm.SVC(kernel='linear')
    clf.fit(X, Y)
    return clf

def svm_kernel_rbf(X, Y):
    clf = svm.SVC(kernel='rbf')
    clf.fit(X, Y)
    return clf

def custom_kernel(X, Y):
    return 1 / (1 + np.sum((np.expand_dims(X, 1) - np.expand_dims(Y, 0)) ** 2, -1))

def svm_kernel_custom(X, Y):
    clf = svm.SVC(kernel=custom_kernel)
    clf.fit(X, Y)
    return clf