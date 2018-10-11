
import emnetc

def convert_sklearn_mlp(model):

    if (model.n_layers_ < 3):
        raise ValueError("Model must have at least one hidden layer")

    weights = model.coefs_
    biases = model.intercepts_
    activations = [model.activation]*(len(weights)-1) + [ model.out_activation_ ]

    cmodel = emnetc.Classifier(activations, weights, biases)
    return cmodel

def convert_keras_sequential(model):
    print('ll', model.layers)
    print('c', model.get_config()['layers'])
    print('w', model.get_weights())
    for l in model.layers:
        print('l', model.layers)

def convert(model, kind=None):
    if kind is None:
        kind = type(model).__name__ 

    if kind == 'MLPClassifier':
        return convert_sklearn_mlp(model)
    if kind == 'Sequential':
        return convert_keras_sequential(model)
    else:
        raise NotImplementedError("Unknown model type for " + str(model))
