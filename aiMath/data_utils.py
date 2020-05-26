import numpy as np

import matplotlib.pyplot as plt
import sklearn
import sklearn.datasets
import sklearn.linear_model

def decision_boundary(model, X, Y, name=None):

    x_min, x_max = X[0, :].min() - 1, X[0, :].max() + 1
    y_min, y_max = X[1, :].min() - 1, X[1, :].max() + 1
    
    xx, yy = np.meshgrid(np.arange(x_min, x_max, 0.01), np.arange(y_min, y_max, 0.01))

    Z = model(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)
    
    plt.contourf(xx, yy, Z, cmap=plt.cm.RdBu)
    plt.xlabel('x0')
    plt.ylabel('x1')
    plt.scatter(X[0, :], X[1, :], s=20, c=Y.ravel(), cmap=plt.cm.RdBu)
    plt.title(name)
    plt.show()

# data를 만들어서 저장하고 있는 class
class dataloader:
    def __init__(self):
        # make dataset
        np.random.seed(1)
        N = 300
        X,Y = sklearn.datasets.make_blobs(n_samples=N, centers=2, n_features=2, cluster_std=2.0, center_box=(-5,5),random_state=3)
        self.Input = X.T
        self.Label = Y.reshape(1, -1)