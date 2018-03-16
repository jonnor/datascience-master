
import sklearn
import numpy
from sklearn import datasets
from sklearn import model_selection

import emtrees

def test_basic_binary_classification():
    X, Y = datasets.make_classification(n_classes=2)
    trees = emtrees.RandomForest(n_trees=5, max_depth=10)
    X = (X * 2**16).astype(int) # convert to integer
    scores = model_selection.cross_val_score(trees, X, Y, scoring='accuracy')
    print(scores)

    assert numpy.mean(scores) > 0.7, scores
