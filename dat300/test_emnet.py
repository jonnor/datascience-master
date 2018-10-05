

import emnetc

import pytest
import sklearn
import numpy

from sklearn.neural_network import MLPClassifier

def convert_sklearn_mlp(model):

    if (model.n_outputs_ != 1):
        raise NotImplementedError("Only single-output models are supported")

    if (model.n_layers_ < 3):
        raise ValueError("Model must have at least one hidden layer")

    layer_weights = []
    for layer_no in range(0, model.n_layers_-1):
        #output_layer = input_layer + 1

        coefs = model.coefs_[layer_no]
        first = layer_no == 0
        if first:
            weights = coefs
        else:
            # add bias to weights
            bias = model.intercepts_[layer_no]
            weights = numpy.vstack([bias, coefs])

        print('l', layer_no, weights.shape)        

        layer_weights.append(weights)

    # layer_weights = [] # TEMP
    cmodel = emnetc.Classifier(model.activation, layer_weights)
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
        emnetc.Classifier("fake22", [[[]], [[]]])
    assert 'Unsupported activation' in str(ex.value)
    assert 'fake22' in str(ex.value)

MODELS = [
    MLPClassifier(hidden_layer_sizes=(8,), max_iter=1),
    MLPClassifier(hidden_layer_sizes=(4,4,4), max_iter=1),
]

@pytest.mark.parametrize('model', MODELS)
def test_predict_equals_sklearn(model):

    X = numpy.random.random(size=(2,3))
    Y = numpy.zeros(shape=(2,), dtype=numpy.bool)

    model.fit(X, Y)

    cmodel = convert(model)
    cmodel.predict(X)

# TODO: test matrix multiplication against numpy

