
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

## Recurrent Neural Networks

* [The Unreasonable Effectiveness of Recurrent Neural Networks](http://karpathy.github.io/2015/05/21/rnn-effectiveness/).
"even if your data is not in form of sequences, you can still formulate and train powerful models that learn to process it sequentially.
You’re learning stateful programs that process your fixed-sized data"
* [Understanding-LSTMs](http://colah.github.io/posts/2015-08-Understanding-LSTMs/)
* 

## NN

Dropout is used to regularize. Only active during training.
Ignores a random set of activations, and avoids updating these weights.
Encourages redundant data representations in the network.

* [Neural Networks, Manifolds, and Topology](http://colah.github.io/posts/2014-03-NN-Manifolds-Topology/)
Shows how Neural Networks can create non-linear decision boundaries, by manipulating the space that the input data exists in.
Particularly how the `tanh` layer performs a linear transformation, translated by the bias, and applies the non-linear activation function.
Using animations which play the transformations after eachother in time.
"Each layer stretches and squishes space, but it never cuts, breaks, or folds it.
Intuitively, we can see that it preserves topological properties.
For example, a set will be connected afterwards if it was before (and vice versa)."
=> homeomorphisms, bijections that are continuous functions both ways.
"The manifold hypothesis is that natural data forms lower-dimensional manifolds in its embedding space."


## Keras
Sparse input matrices. Can either densify in `fit_generator()`, or use `Input(..., sparse=True)` layer

https://www.kaggle.com/luisgarcia/keras-nn-with-parallelized-batch-training

