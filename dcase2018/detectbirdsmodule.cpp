
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

    EmVector inv = { samples, EMAUDIO_FFT_LENGTH };
    EmVector out = { retdata, EMAUDIO_FFT_LENGTH };

    const int status = emaudio_rfft(inv, out);
 
    if (status != 0) {
        throw std::runtime_error("SFT returned error");
    }

    return ret;
}

py::array_t<float>
spectrogram_py(py::array_t<float, py::array::c_style | py::array::forcecast> in) {
    if (in.ndim() != 1) {
        throw std::runtime_error("SFT input must have dimensions 1");
    }

    const int n_fft = in.shape(0);
    if (n_fft != EMAUDIO_FFT_LENGTH) {
        throw std::runtime_error("SFT must have length EMAUDIO_FFT_LENGTH");
    }

    const int length = 1+n_fft/2;
    auto ret = py::array_t<float>(length);

    EmVector inv = { (float *)in.data(), EMAUDIO_FFT_LENGTH };
    EmVector out = { (float *)ret.data(), length };

    const int status = emaudio_power_spectrogram(inv, out, n_fft);
 
    if (status != 0) {
        throw std::runtime_error("SFT returned error");
    }

    return ret;
}

py::array_t<float>
spectrogram_frame(py::array_t<float, py::array::c_style | py::array::forcecast> in) {
    if (in.ndim() != 1) {
        throw std::runtime_error("spectrogram input must have dimensions 1");
    }

    const int n_fft = in.shape(0);
    if (n_fft != EMAUDIO_FFT_LENGTH) {
        throw std::runtime_error("spectrogram must have length EMAUDIO_FFT_LENGTH");
    }

    EmVector frame = { (float *)in.data(), EMAUDIO_FFT_LENGTH };
    emaudio_hann_apply(frame); // XXX: modifies input

    auto temp_py = py::array_t<float>(EMAUDIO_FFT_LENGTH);
    EmVector fft_out = { (float *)temp_py.data(), EMAUDIO_FFT_LENGTH };
    const int rftt_status = emaudio_rfft(frame, fft_out);

    if (rftt_status != 0) {
        throw std::runtime_error("FFT returned error");
    }

    //emvector_set(frame, fft_out, 0);

    const int spec_length = 1+n_fft/2;
    auto ret = py::array_t<float>(spec_length);
    EmVector spec = { (float *)ret.data(), spec_length };

    const int spec_status = emaudio_power_spectrogram(fft_out, spec, n_fft);

    if (spec_status != 0) {
        throw std::runtime_error("spectrum returned error");
    }

    return ret;
}

py::array_t<float>
mel_py(py::array_t<float, py::array::c_style | py::array::forcecast> in,
    int n_mels, float fmin, float fmax, int n_fft, int samplerate
)

{
    if (in.ndim() != 1) {
        throw std::runtime_error("spectrogram input must have dimensions 1");
    }

    const int length = in.shape(0);
    EmVector spec = { (float *)in.data(), length };

    const EmAudioMel params = { n_mels, fmin, fmax, n_fft, samplerate };
    auto ret = py::array_t<float>(params.n_mels);

    EmVector mels = { (float *)ret.data(), params.n_mels };
    const int status = emaudio_melspec(params, spec, mels);

    if (status != 0) {
        throw std::runtime_error("mels returned error: " + std::to_string(status));
    }

    return ret;
}




PYBIND11_MODULE(detectbirds, m) {
    m.doc() = "Detect birdsong in audio";

    py::class_<GoertzelBank>(m, "GoertzelBank")
        .def(py::init< std::vector<float>, int, float>())
        .def("process", &GoertzelBank::process);

    m.def("rfft", rfft_py);
    m.def("spectrogram", spectrogram_py);
    m.def("spectrogram_frame", spectrogram_frame);
    m.def("melfilter", mel_py);
}

