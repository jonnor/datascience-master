

import emnetc

import pytest
import sklearn
import numpy

import warnings
warnings.filterwarnings(action='ignore', category=sklearn.exceptions.ConvergenceWarning)

from sklearn.neural_network import MLPClassifier
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.preprocessing import StandardScaler

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

        print('l', layer_no, weights.shape, weights)    

        layer_weights.append(weights)

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
    #MLPClassifier(hidden_layer_sizes=(100,), max_iter=50),
    #MLPClassifier(hidden_layer_sizes=(50,50,10), max_iter=50),
    MLPClassifier(hidden_layer_sizes=(4), max_iter=50),
]


@pytest.mark.parametrize('model', MODELS)
def test_predict_equals_sklearn(model):

    for random in range(0, 5):
        # create dataset
        rng = numpy.random.RandomState(0)
        X, y = make_classification(n_features=2, n_redundant=0, n_informative=2,
                                   random_state=rng, n_clusters_per_class=1)
        X += 2 * rng.uniform(size=X.shape)
        X = StandardScaler().fit_transform(X)

        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=.2)
        with warnings.catch_warnings():
            warnings.simplefilter("ignore")
            model.fit(X_train, y_train)

            print('train', numpy.mean(cross_val_score(model, X_train, y_train, cv=5)))
            print('test', numpy.mean(cross_val_score(model, X_test, y_test, cv=5)))

            cmodel = convert(model)

            cpred = cmodel.predict(X_test)
            pred = model.predict(X_test)

        print(cpred)
        print(pred)
        assert list(cpred) == list(pred)

# TODO: test matrix multiplication against numpy

