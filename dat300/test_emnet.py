

# TODO: test MPL against sklearn
# TODO: test matrix multiplication against numpy

import emnetc

import pytest
import sklearn
import numpy

from sklearn.neural_network import MLPClassifier

def convert_sklearn_mlp(model):

    print(len(model.coefs_))
    print(model.coefs_[0].shape)

    print(len(model.intercepts_))
    print(model.intercepts_[0].shape)

    if (model.n_outputs_ != 1):
        raise NotImplementedError("Only single-output models are supported")

    weights = []
    for layer_no in range(model.n_layers_):
        weights.append([])

    cmodel = emnetc.Classifier(model.activation)
    return cmodel


def convert(model, kind=None):
    if kind is None:
        kind = type(model).__name__ 

    print(kind)
    if kind == 'MLPClassifier':
        return convert_sklearn_mlp(model)
    else:
        raise NotImplementedError("Unknown model type for " + model)

def test_unsupported_activation():
    with pytest.raises(Exception) as ex:
        emnetc.Classifier("fake22")
    assert 'Unsupported activation' in str(ex.value)
    assert 'fake22' in str(ex.value)

def test_mpl():
    model = MLPClassifier(hidden_layer_sizes=(8,8,8), max_iter=1)

    X = numpy.random.random(size=(2,4))
    Y = numpy.zeros(shape=(2,), dtype=numpy.bool)

    model.fit(X, Y)

    cmodel = convert(model)

    cmodel.predict(X)

