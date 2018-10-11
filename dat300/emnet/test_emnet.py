
import emnet

import pytest
import sklearn
import numpy
from numpy.testing import assert_equal, assert_almost_equal

import sys
import warnings
warnings.filterwarnings(action='ignore', category=sklearn.exceptions.ConvergenceWarning)

from sklearn.neural_network import MLPClassifier
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.preprocessing import StandardScaler



def test_unsupported_activation():
    with warnings.catch_warnings():
        warnings.simplefilter("ignore")
        model = MLPClassifier(hidden_layer_sizes=(2,), max_iter=10)
        model.fit([[1.0]], [True])
    with pytest.raises(Exception) as ex:
        model.activation = 'fake22'
        emnet.convert(model)
    assert 'Unsupported activation' in str(ex.value)
    assert 'fake22' in str(ex.value)


def test_inference_simple():
    features = 2
    rng = numpy.random.RandomState(0)
    X, y = make_classification(n_features=features, n_classes=3,
                               n_redundant=0, n_informative=features,
                               random_state=rng, n_clusters_per_class=1)
    X += 2 * rng.uniform(size=X.shape)
    X = StandardScaler().fit_transform(X)

    with warnings.catch_warnings():
        warnings.simplefilter("ignore")

        model = MLPClassifier(hidden_layer_sizes=(3,), max_iter=10, random_state=rng)
        model.fit(X, y)
        cmodel = emnet.convert(model)
    
        X_test = X[:1]
        cpred = cmodel.predict_proba(X_test)
        pred = model.predict_proba(X_test)

    assert_almost_equal(cpred, pred, decimal=5)


PARAMS = [
    ( dict(hidden_layer_sizes=(4,), activation='relu'), {'classes': 3, 'features': 2}),
    ( dict(hidden_layer_sizes=(4,), activation='tanh'), {'classes': 2, 'features': 3}),
    ( dict(hidden_layer_sizes=(4,5,3)), {'classes': 5, 'features': 5}),
]

@pytest.mark.parametrize('modelparams,params', PARAMS)
def test_predict_equals_sklearn(modelparams,params):

    model = MLPClassifier(**modelparams, max_iter=20)

    for random in range(0, 3):
        # create dataset
        rng = numpy.random.RandomState(0)
        X, y = make_classification(n_features=params['features'], n_classes=params['classes'],
                                   n_redundant=0, n_informative=params['features'],
                                   random_state=rng, n_clusters_per_class=1, n_samples=50)
        X += 2 * rng.uniform(size=X.shape)
        X = StandardScaler().fit_transform(X)

        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=.2)
        with warnings.catch_warnings():
            warnings.simplefilter("ignore")
            model.fit(X_train, y_train)

            cmodel = emnet.convert(model)

            X_test = X_test[:3]
            cproba = cmodel.predict_proba(X_test)
            proba = model.predict_proba(X_test)
            cpred = cmodel.predict(X_test)
            pred = model.predict(X_test)

        assert_almost_equal(proba, cproba)
        assert_equal(pred, cpred)

# TODO: test matrix multiplication against numpy

import keras
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Dropout
from keras.optimizers import RMSprop

# TODO: avoid all the repetition with above tests
def test_keras_mlp():
    n_features = 3
    n_classes = 3
    
    for random_seed in range(0, 3):
        # Dataset
        rng = numpy.random.RandomState(random_seed)
        X, y = make_classification(n_features=n_features, n_classes=n_classes,
                                   n_redundant=0, n_informative=n_features,
                                   random_state=rng, n_clusters_per_class=1, n_samples=50)
        X += 2 * rng.uniform(size=X.shape)
        x_train, x_test, y_train, y_test = train_test_split(X, y, test_size=.2)

        # Model
        batch_size = 10
        epochs = 3

        # convert class vectors to binary class matrices
        y_train = keras.utils.to_categorical(y_train, n_classes)
        y_test = keras.utils.to_categorical(y_test, n_classes)

        model = Sequential()
        model.add(Dense(10, activation='relu', input_shape=(n_features,)))
        model.add(Dense(10, activation='relu'))
        model.add(Dense(n_classes, activation='softmax'))

        model.summary()

        model.compile(loss='categorical_crossentropy',
                      optimizer=RMSprop(),
                      metrics=['accuracy'])

        history = model.fit(x_train, y_train,
                            batch_size=batch_size,
                            epochs=epochs,
                            verbose=1,
                            validation_data=(x_test, y_test))
        score = model.evaluate(x_test, y_test, verbose=0)
        print('Test loss:', score[0])
        print('Test accuracy:', score[1])

        cmodel = emnet.convert(model)

        assert False
