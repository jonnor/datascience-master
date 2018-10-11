
# Machine Learning 2

## Questions

Keras

* Why is Dropout a layer? Seems more a parameter to a layer?
Looks like it is only used

## TODO

* emnet: Implement `convert()` for (simple) Keras models. Sequential
* emnet: Add support for 2d convolutional layers (Keras).
Supports N filters.
Can have activation function (or not).
Bias is optional, but defaults to on.
Supports strides.
Supports dilated convolution.
* Try to pre-seed convolution kernel parameters. Etc from spherical k-means, or random, or know (Gabor?).
Keras: layers can be frozen by setting `trainable=False`.
* DAT390: Implement a CNN model from DCASE2018 
* DAT390: Try a shallow convolutional frontend, using Concatenate with RandomForest (sparse) classifier?

## CNN

[Visualizing what ConvNets learn](http://cs231n.github.io/understanding-cnn/).
Visualizing feature map activations, weights, showing inputs that maximally activate a neuron,
t-SNE embedding to show similarity in learned model space, occluding patches of input to find which parts of input are critical

LocallyConnected is a convolution type layers where weights are not shared.
