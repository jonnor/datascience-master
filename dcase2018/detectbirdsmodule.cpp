
#include <stdio.h>

#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include "detectbirds.h"

namespace py = pybind11;

class GoertzelBank {
    float sample_rate;
    int n_samples;
    std::vector<EmGoertzel> coefficients;

public:
    GoertzelBank(std::vector<float> freqs, int _n_samples, float _sample_rate)
        : sample_rate(_sample_rate)
        , n_samples(_n_samples)
        , coefficients(freqs.size())
    {
        for (unsigned int i=0; i<coefficients.size(); i++) {
            coefficients[i] = emgoertzel_coefficients(freqs[i], n_samples, sample_rate);
        }
    }

    py::array_t<float>
    process(py::array_t<float, py::array::c_style | py::array::forcecast> in) {
        if (in.ndim() != 1) {
            throw std::runtime_error("process input must have dimensions 1");
        }

        const int in_samples_n = in.shape()[0];
        if (in_samples_n != n_samples) {
            throw std::runtime_error("Wrong number of samples");
        }

        const float *samples = in.data();

        auto ret = py::array_t<float>(coefficients.size());
        auto r = ret.mutable_unchecked<1>();

        for (unsigned int i=0; i<coefficients.size(); i++) {
            const float s = emgoertzel_run(coefficients[i], samples, in_samples_n);
            r(i) = s;
        }
     
        return ret;
    }

};


py::array_t<float>
rfft_py(py::array_t<float, py::array::c_style | py::array::forcecast> in) {
    if (in.ndim() != 1) {
        throw std::runtime_error("SFT input must have dimensions 1");
    }

    if (in.shape(0) != EMAUDIO_FFT_LENGTH) {
        throw std::runtime_error("SFT must have length EMAUDIO_FFT_LENGTH");
    }

    auto ret = py::array_t<float>(in.shape(0));

    float *samples = (float *)in.data();
    float *retdata = (float *)ret.data();

    float imag_data[EMAUDIO_FFT_LENGTH];
    EmVector real = { samples, EMAUDIO_FFT_LENGTH };
    EmVector imag = { imag_data, EMAUDIO_FFT_LENGTH };
    emvector_set_value(imag, 0.0f);

    const int status = emaudio_fft(real, imag);
 
    emvector_set((EmVector){retdata,EMAUDIO_FFT_LENGTH}, real, 0);

    if (status != 0) {
        throw std::runtime_error("SFT returned error");
    }

    return ret;
}


py::array_t<float>
melspectrogram_py(py::array_t<float, py::array::c_style | py::array::forcecast> in,
    int n_mels, float fmin, float fmax, int n_fft, int samplerate
)

{
    if (in.ndim() != 1) {
        throw std::runtime_error("spectrogram input must have dimensions 1");
    }

    const EmAudioMel params = { n_mels, fmin, fmax, n_fft, samplerate };

    // Copy input to avoid modifying
    const int length = in.shape(0);
    float inout_data[length];
    float temp_data[length];
    EmVector inout = { inout_data, length };
    EmVector temp = { temp_data, length };
    emvector_set(inout, (EmVector){(float *)in.data(), length}, 0);

    const int status = emaudio_melspectrogram(params, inout, temp);

    if (status != 0) {
        throw std::runtime_error("melspectrogram returned error: " + std::to_string(status));
    }

    auto ret = py::array_t<float>(params.n_mels);
    EmVector out = { (float *)ret.data(), params.n_mels };
    emvector_set(out, emvector_view(inout, 0, params.n_mels), 0);

    return ret;
}

PYBIND11_MODULE(detectbirds, m) {
    m.doc() = "Detect birdsong in audio";

    py::class_<GoertzelBank>(m, "GoertzelBank")
        .def(py::init< std::vector<float>, int, float>())
        .def("process", &GoertzelBank::process);

    m.def("rfft", rfft_py);
    m.def("melspectrogram", melspectrogram_py);
}

