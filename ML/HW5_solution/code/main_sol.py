import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import StratifiedKFold

from RandomForest_sol import RandomForestClassifier
from AdaBoost_sol import AdaBoostClassifier

def load_dataset():
    X_train = np.genfromtxt('./adult_dataset/X_train.txt', delimiter=' ')
    y_train = np.genfromtxt('./adult_dataset/y_train.txt', delimiter=' ')
    X_test  = np.genfromtxt('./adult_dataset/X_test.txt', delimiter=' ')
    y_test  = np.genfromtxt('./adult_dataset/y_test.txt', delimiter=' ')

    return X_train, y_train, X_test, y_test

def my_cross_val_score(model, X, y, cv=5):

    rng = np.random.RandomState(42)
    skf = StratifiedKFold(n_splits=cv, random_state=rng, shuffle=True)

    auc_list = list()

    for train_index, test_index in skf.split(X, y):
        X_train, X_test = X[train_index], X[test_index]
        y_train, y_test = y[train_index], y[test_index]

        auc = model.evaluate(X_train, y_train, X_test, y_test)
        auc_list.append(auc)
    
    return np.array(auc_list)


def make_plot(X_train, y_train):
    # make sure the generated figure is saved to 'evaluation.png' in the current directory

    fold_num = 5
    max_clf_num = 20

    rf_auc_list = list()
    ad_auc_list = list()
    num_clf_list = list(range(1, max_clf_num+1))

    for clf_type, clf_class, clf_auc_list in [
      ("Random Forest", RandomForestClassifier, rf_auc_list),
      ("AdaBoost", AdaBoostClassifier, ad_auc_list),
    ]:
        auc_list = list()

        for num_clf in num_clf_list:
            clf = clf_class(T=num_clf)
            auc_score = my_cross_val_score(clf, X_train, y_train, cv=fold_num).mean()

            print(f"{clf_type} with {num_clf} base classifiers: {auc_score:.3f}")

            clf_auc_list.append(auc_score)

    fig = plt.figure(figsize=(9, 6))

    plt.plot(num_clf_list, rf_auc_list, label="Random Forest", marker='o')
    plt.plot(num_clf_list, ad_auc_list, label="AdaBoost", marker='*')

    plt.legend()
    plt.xlabel("Number of base classifiers")
    plt.xticks(num_clf_list)
    plt.ylabel("AUC Score")
    plt.title("AUC Score vs Number of Base Classifiers")

    plt.savefig("evaluation.png")


if __name__ == "__main__":

    X_train, y_train, X_test, y_test = load_dataset()

    rf_clf = RandomForestClassifier(T=20)
    result = rf_clf.evaluate(X_train, y_train, X_test, y_test)
    print(f"Random Forest AUC = {result:.3f}")

    ad_clf = AdaBoostClassifier(T=20)
    result = ad_clf.evaluate(X_train, y_train, X_test, y_test)
    print(f"AdaBoost AUC = {result:.3f}")

    # ==== Start of your plotting code ====

    make_plot(X_train, y_train)







