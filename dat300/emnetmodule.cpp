
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
        char *func_str = emnet_activation_function_strs[i];
        if (strcmp(str, func_str) == 0) {
            ret = (int32_t)i;
        }
    }

    return ret;
}

class EmNetClassifier {
private:
    std::vector<int32_t> roots;
    std::vector<EmNetLayer> *layers;
    std::vector<float> weights;
    EmNet model;

public:
    EmNetClassifier(std::string activation)
    {

        const int32_t a = emnet_activation_func(activation.c_str());
        if (a < 0) {
            throw std::runtime_error("Unsupported activation function: " + activation);
        }
        EmNetActivationFunction activation_func = (EmNetActivationFunction)a;

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
                throw std::runtime_error("Error code: " + std::to_string(-p));
            }
            r(i) = p;
        }

        return classes;
    }

};

PYBIND11_MODULE(emnetc, m) {
    m.doc() = "Neural networks for embedded devices";

    py::class_<EmNetClassifier>(m, "Classifier")
        .def(py::init<std::string>())
        .def("predict", &EmNetClassifier::predict);
}

