import os, datetime

from sklearn.metrics import accuracy_score
from sklearn.model_selection import StratifiedKFold

def evaluate_classifier(classifier_class, args, kwargs, fit_x, fit_y, predict_x, predict_y) -> float:
    classifier = classifier_class(*args, **kwargs)
    classifier.fit(fit_x, fit_y)
    predict_y_hat = classifier.predict(predict_x)
    acc = accuracy_score(predict_y, predict_y_hat)
    return acc

def distributed_evaluate_classifier(packed) -> float:
    task_id, classifier_class, args, kwargs, fit_x, fit_y, predict_x, predict_y = packed
    dt_str = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    print(f'[{dt_str}, {os.getpid()}] {task_id} <-')
    classifier = classifier_class(*args, **kwargs)
    classifier.fit(fit_x, fit_y)
    predict_y_hat = classifier.predict(predict_x)
    acc = accuracy_score(predict_y, predict_y_hat)
    dt_str = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    print(f'[{dt_str}, {os.getpid()}] {task_id} -> {acc}')
    return task_id, acc
    
def evaluate_5_fold_cv(classifier_class, args, kwargs, train_x, train_y) -> float:
    kf = StratifiedKFold(n_splits=5)
    accs = []
    for fold, (fit_index, predict_index) in enumerate(kf.split(train_x, train_y)):
        fit_x = train_x[fit_index]
        fit_y = train_y[fit_index]
        predict_x = train_x[predict_index]
        predict_y = train_y[predict_index]
        accs.append(evaluate_classifier(classifier_class, args, kwargs, fit_x, fit_y, predict_x, predict_y))
    return sum(accs) / len(accs)
