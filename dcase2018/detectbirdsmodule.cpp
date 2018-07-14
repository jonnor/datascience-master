
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

// FIXME: unhardcode
#define AUDIO_HOP_LENGTH 512
#define AUDIO_WINDOW_LENGTH 1024

class Processor {
private:
    BirdDetector detector;
    EmAudioBufferer bufferer;

    float record1[AUDIO_HOP_LENGTH];
    float record2[AUDIO_HOP_LENGTH];
    float input_data[AUDIO_WINDOW_LENGTH];
    float temp1_data[AUDIO_WINDOW_LENGTH];
    float temp2_data[AUDIO_WINDOW_LENGTH];

public:
    Processor(int n_mels, float fmin, float fmax, int n_fft, int samplerate) {

        bufferer = (EmAudioBufferer){ AUDIO_HOP_LENGTH, record1, record2, NULL, NULL, 0 };

        const EmAudioMel params = {
            n_mels: n_mels,
            fmin: fmin,
            fmax: fmax,
            n_fft:AUDIO_WINDOW_LENGTH,
            samplerate:samplerate,
        };

        const int features_length = params.n_mels; // only 1 feature per mel band right now
        float features_data[features_length];

        detector = {
            audio: (EmVector){ input_data, AUDIO_WINDOW_LENGTH },
            features: (EmVector){ features_data, features_length },
            temp1: (EmVector){ temp1_data, AUDIO_WINDOW_LENGTH },
            temp2: (EmVector){ temp2_data, AUDIO_WINDOW_LENGTH },
            mel_filter: params,
            model: birddetect_model,
        };

        reset();
    }

    void reset() {
        birddetector_reset(&detector);
        emaudio_bufferer_reset(&bufferer);
    }

    int add_samples(py::array_t<float, py::array::c_style | py::array::forcecast> in) {
        if (in.ndim() != 1) {
            throw std::runtime_error("process() input must have dimensions 1");
        }

        float *samples = (float *)in.data();
        int length = in.shape(0);

        int n_frames = 0;
        for (int i=0; i<length; i++) {
            const int16_t sample = samples[i] * INT16_MAX;
            emaudio_bufferer_add(&bufferer, sample);

            if (bufferer.read_buffer) {
                EmVector frame = { bufferer.read_buffer, bufferer.buffer_length };
                birddetector_push_frame(&detector, frame);
                bufferer.read_buffer = NULL; // done processing

                n_frames += 1;
            }

        }
        return n_frames;
    }

    py::array_t<float> get_features() {

        const int length = detector.features.length;
        auto ret = py::array_t<float>(length);
        EmVector out = { (float *)ret.data(), length };
        emvector_set(out, detector.features, 0);

        return ret;
    }

    bool predict() {
        return birddetector_predict(&detector);
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

    py::class_<Processor>(m, "Processor")
        .def(py::init< int, float, float, int, int >())
        .def("add_samples", &Processor::add_samples)
        .def("predict", &Processor::predict)
        .def("get_features", &Processor::get_features)
        .def("reset", &Processor::reset);


    m.def("rfft", rfft_py);
    m.def("melspectrogram", melspectrogram_py);
}

