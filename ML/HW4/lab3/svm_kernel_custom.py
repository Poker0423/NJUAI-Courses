from sklearn import svm

def custom_kernel(X1, X2):
    '''
    :参数 X1: ndarray, 形状(m, d)
    :参数 X2: ndarray, 形状(n, d)
    :返回: 形状为(m, n)的Gram矩阵, 第(i,j)个元素为X1[i]和X2[j]之间的核函数值
    '''
    pass

clf = svm.SVC(kernel=custom_kernel)

