
#ifndef ARDUINO

#include <stdio.h>
#include <stdlib.h>

#include "pdf.h"
#include "embayes.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

class Classifier {
private:
    BayesSummary *summaries;
    BayesModel model;

public:
    Classifier(std::vector<float> data, int n_classes, int n_features)
        : summaries(nullptr)
    {
        // FIXME: check data is n_classes*n_features*2
        const int n_items = n_classes*n_features;
        summaries = (BayesSummary *)malloc(sizeof(BayesSummary)*n_items);

        model.n_features = n_features;
        model.n_classes = n_classes;
        model.summaries = summaries;

        for (int class_idx = 0; class_idx<n_classes; class_idx++) {
            for (int feature_idx = 0; feature_idx<n_features; feature_idx++) {
                const int32_t summary_idx = class_idx*n_features + feature_idx;
                BayesSummary summary;
                summary.mean = data[2*summary_idx + 0];
                summary.std = data[2*summary_idx + 1];
                model.summaries[summary_idx] = summary;
            }
        }
    }
    ~Classifier() {
        free(summaries);
    }

    int32_t predict(std::vector<float> values) {
        const int32_t p = embayes_predict(&model, &values[0], values.size());
        return p;
    }
};


PYBIND11_MODULE(embayesc, m) {
    m.doc() = "NaiveBayes classifiers for embedded devices";

    // using floating point
    m.def("pdf", pdf);
    m.def("pdf_fast", pdf_fast);
    m.def("pdf_linear4", pdf_linear4);

    // using fixed-point
    m.def("pdf_loglin4", pdf_loglin4_float);

    py::class_<Classifier>(m, "Classifier")
        .def(py::init<std::vector<float>, int, int>())
        .def("predict", &Classifier::predict);
}

#endif
