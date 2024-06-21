import numpy as np
import matplotlib.pyplot as plt
# You can import other methods from sklearn, if needed
from sklearn.model_selection import KFold
from sklearn.metrics import roc_auc_score


from RandomForest import RandomForestClassifier
from AdaBoost import AdaBoostClassifier


def load_dataset():
    X_train = np.genfromtxt('./adult_dataset/X_train.txt', delimiter=' ')
    y_train = np.genfromtxt('./adult_dataset/y_train.txt', delimiter=' ')
    X_test  = np.genfromtxt('./adult_dataset/X_test.txt', delimiter=' ')
    y_test  = np.genfromtxt('./adult_dataset/y_test.txt', delimiter=' ')

    return X_train, y_train, X_test, y_test


def make_plot(X_train, y_train):
    # make sure the generated figure is saved to 'evaluation.png' in the current directory

    fold_num = 5
    max_clf_num = 20

    # TODO: implement the hyperparameter search here
    n_estimators_range = range(1, 21)  # 基分类器数量从1到20

    # 初始化AdaBoost和Random Forest分类器分数
    ada_auc_scores = []
    rf_auc_scores = []

    # 使用分层采样进行KFold划分
    kf = KFold(n_splits=fold_num, shuffle=True, random_state=42)

    # 遍历基分类器数量并计算AUC指标
    for n_estimators in n_estimators_range:
        ada_auc_kfold = []
        rf_auc_kfold = []

        for train_index, test_index in kf.split(X_train):
            X_train_kfold, X_test_kfold = X_train[train_index], X_train[test_index]
            y_train_kfold, y_test_kfold = y_train[train_index], y_train[test_index]

            ada = AdaBoostClassifier(T=n_estimators, max_depth=4)  # 假设使用决策树深度为4
            ada.fit(X_train_kfold, y_train_kfold)
            ada_proba = ada.predict_proba(X_test_kfold)
            ada_auc = roc_auc_score(y_test_kfold, ada_proba)
            ada_auc_kfold.append(ada_auc)

            rf = RandomForestClassifier(T=n_estimators, max_depth=4)  # 假设使用决策树深度为4
            rf.fit(X_train_kfold, y_train_kfold)
            rf_proba = rf.predict_proba(X_test_kfold)
            rf_auc = roc_auc_score(y_test_kfold, rf_proba)
            rf_auc_kfold.append(rf_auc)

        ada_auc_scores.append(np.mean(ada_auc_kfold))
        rf_auc_scores.append(np.mean(rf_auc_kfold))



    fig = plt.figure(figsize=(9, 6))

    # TODO: implement the plotting code here
    plt.plot(n_estimators_range, ada_auc_scores, label='AdaBoost AUC', marker='o')
    plt.plot(n_estimators_range, rf_auc_scores, label='Random Forest AUC', marker='x')
    plt.xlabel('Number of Base Classifiers')
    plt.ylabel('Average AUC Score')
    plt.title('AUC Score vs. Number of Base Classifiers')
    plt.legend()
    plt.grid(True)
    plt.savefig('evaluation.png')
    plt.show()


if __name__ == "__main__":

    X_train, y_train, X_test, y_test = load_dataset()


    rf_clf = RandomForestClassifier(T=10)
    result = rf_clf.evaluate(X_train, y_train, X_test, y_test)
    print(f"Random Forest AUC = {result:.3f}")

    ad_clf = AdaBoostClassifier(T=10)
    result = ad_clf.evaluate(X_train, y_train, X_test, y_test)
    print(f"AdaBoost AUC = {result:.3f}")

    # ==== Start of your plotting code ====

    make_plot(X_train, y_train)







