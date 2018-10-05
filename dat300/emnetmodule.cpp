
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

typedef py::array_t<float, py::array::c_style | py::array::forcecast> LayerWeights;

class EmNetClassifier {
private:
    std::vector<int32_t> roots;
    std::vector<EmNetLayer> layers;
    std::vector<LayerWeights> layer_weights;
    std::vector<float> activations_buffer_1;
    std::vector<float> activations_buffer_2;
    EmNet model = {0,};

public:
    EmNetClassifier(std::string activation, std::vector<LayerWeights> _layer_weights
    )

    {
        // Activation function
        const int32_t a = emnet_activation_func(activation.c_str());
        if (a < 0) {
            throw std::runtime_error("Unsupported activation function: " + activation);
        }
        const EmNetActivationFunction activation_func = (EmNetActivationFunction)a;

        // Layers and weights
        if (_layer_weights.size() < 2) {
            throw std::runtime_error("Must have weights between 3 layers");
        }

        layer_weights = _layer_weights; // store reference
        model.n_layers = layer_weights.size();
        layers = std::vector<EmNetLayer>(model.n_layers);
        model.layers = layers.data();
        
        for (int i=0; i<model.n_layers; i++) {
            auto weights = layer_weights[i];
            fprintf(stderr, "weight shape %d (%d, %d)\n", weights.ndim(), weights.shape(0), weights.shape(1));
            layers[i].n_inputs = weights.shape(0); 
            layers[i].n_outputs = weights.shape(1);
            layers[i].activation = activation_func;
            layers[i].weights = (float *)weights.data();
        }

        // Buffers for activations
        const int32_t act_max = emnet_find_largest_layer(&model);
        activations_buffer_1 = std::vector<float>(act_max);
        activations_buffer_2 = std::vector<float>(act_max);
        model.activations1 = activations_buffer_1.data();
        model.activations2 = activations_buffer_2.data();
        fprintf(stderr, "act=%d a1,a2 = %p,%p\n", act_max, model.activations1, model.activations2);
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
        .def(py::init< std::string, std::vector<LayerWeights> >())
        .def("predict", &EmNetClassifier::predict);
}

