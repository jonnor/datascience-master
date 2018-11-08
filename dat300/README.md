
# Machine Learning 2

## Questions

Keras

* Why is Dropout a layer? Seems more a parameter to a layer?
Looks like it is only used

## TODO

* emlearn: Implement convolutions
* emlearn: Support Keras CNN models

## CNN

[Visualizing what ConvNets learn](http://cs231n.github.io/understanding-cnn/).
Visualizing feature map activations, weights, showing inputs that maximally activate a neuron,
t-SNE embedding to show similarity in learned model space, occluding patches of input to find which parts of input are critical

LocallyConnected is a convolution type layers where weights are not shared.

[CNN models for human activity recognition](https://machinelearningmastery.com/cnn-models-for-human-activity-recognition-time-series-classification/).
Example code in Keras for 1D CNN on accerelerometer data.
Also explores standarization, number of filters, kernel sizes.
Also shows multi-headed CNN, using 3 parallel branches with different kernel sizes, concatenated into one.
Almost all models perform a little bit better than 90% accuracy (6 classes).

Tied versus untied biases.
tied biases: one bias per convolutional filter/kernel
untied biases: one bias per kernel and output location

Tied is more common.

## NN

Dropout is used to regularize. Only active during training.
Ignores a random set of activations, and avoids updating these weights.
Encourages redundant data representations in the network.

## Keras
Sparse input matrices. Can either densify in `fit_generator()`, or use `Input(..., sparse=True)` layer

https://www.kaggle.com/luisgarcia/keras-nn-with-parallelized-batch-training

