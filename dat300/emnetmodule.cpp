
#include <stdio.h>

#include "emnet.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

// Returns an EmNetActivationFunction or -EmNetError
int32_t
emnet_activation_func(const char *str)
{
    int32_t ret = -EmNetUnsupported;

    for (int i=0; i<EmNetActivationFunctions; i++) {
        const char *func_str = emnet_activation_function_strs[i];
        if (strcmp(str, func_str) == 0) {
            ret = (int32_t)i;
        }
    }

    return ret;
}

typedef py::array_t<float, py::array::c_style | py::array::forcecast> FloatArray;

class EmNetClassifier {
private:
    std::vector<int32_t> roots;
    std::vector<EmNetLayer> layers;
    std::vector<FloatArray> weights;
    std::vector<FloatArray> biases;
    std::vector<float> activations_buffer_1;
    std::vector<float> activations_buffer_2;
    EmNet model = {0,};

public:
    EmNetClassifier(std::vector<std::string> activations,
                std::vector<FloatArray> _weights,
                std::vector<FloatArray> _biases)

    {
        // store reference
        weights = _weights;
        biases = _biases;

        // Layers
        if (weights.size() < 2) {
            throw std::runtime_error("Must have weights between 3 layers");
        }

        model.n_layers = weights.size();
        layers = std::vector<EmNetLayer>(model.n_layers);
        model.layers = layers.data();

        for (int i=0; i<model.n_layers; i++) {
            const int32_t a = emnet_activation_func(activations[i].c_str());
            if (a < 0) {
                throw std::runtime_error("Unsupported activation function: " + activations[i]);
            }

            layers[i].n_inputs = weights[i].shape(0); 
            layers[i].n_outputs = weights[i].shape(1);
            layers[i].activation = (EmNetActivationFunction)a;
            layers[i].weights = (float *)weights[i].data();
            layers[i].biases = (float *)biases[i].data();
        }

        // Buffers for activations
        const int32_t act_max = emnet_find_largest_layer(&model);
        activations_buffer_1 = std::vector<float>(act_max);
        activations_buffer_2 = std::vector<float>(act_max);
        model.activations1 = activations_buffer_1.data();
        model.activations2 = activations_buffer_2.data();
        model.activations_length = act_max;
    }

    ~EmNetClassifier() {

    }

    py::array_t<int32_t>
    predict(py::array_t<float, py::array::c_style | py::array::forcecast> in) {
        if (in.ndim() != 2) {
            throw std::runtime_error("predict input must have dimensions 2");
        }

        const int64_t n_samples = in.shape()[0];
        const int32_t n_features = in.shape()[1];

        auto classes = py::array_t<int32_t>(n_samples);
        //auto s = in.unchecked();
        auto r = classes.mutable_unchecked<1>(); 
        for (int i=0; i<n_samples; i++) {
            const float *v = in.data(i);
            const int32_t p = emnet_predict(&model, v, n_features);
            if (p < 0) {
                const std::string err = emnet_strerr((EmNetError)-p);
                throw std::runtime_error("Prediction error: " + err);
            }
            r(i) = p;
        }

        return classes;
    }

};

PYBIND11_MODULE(emnetc, m) {
    m.doc() = "Neural networks for embedded devices";

    py::class_<EmNetClassifier>(m, "Classifier")
        .def(py::init< std::vector<std::string>, std::vector<FloatArray>, std::vector<FloatArray> >())
        .def("predict", &EmNetClassifier::predict);
}

