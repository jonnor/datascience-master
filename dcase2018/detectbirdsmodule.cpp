
#include <stdio.h>

#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

typedef struct _EmGoertzel {
    float sine;
    float cosine;
} EmGoertzel;

EmGoertzel
emgoertzel_coefficients(int frequency, int n_samples, int sr)
{
    const float samples = (float)n_samples;
    const float k = (int)(0.5 + ((samples * frequency) / sr));
    const float omega = (2.0 * M_PI * k) / samples;
    const EmGoertzel c  = { sin(omega), cos(omega) }; 
    return c;
}


float
emgoertzel_run(EmGoertzel c, float* data, int n_samples)
{
    const float coeff = 2.0 * c.cosine;
    float q0=0;
    float q1=0;
    float q2=0;

    for(int i=0; i<n_samples; i++) {
        q0 = coeff * q1 - q2 + data[i];
        q2 = q1;
        q1 = q0;
    }
 
    const float scale = n_samples / 2.0;
    const float real = (q1 - q2 * c.cosine) / scale;
    const float imag = (q2 * c.sine) / scale;

    const float magnitude = sqrtf(real*real + imag*imag);
    return magnitude;
}



// TODO: implement numpy in/out
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
            printf("c %d %f %f %f\n", i, freqs[i], coefficients[i].sine, coefficients[i].cosine);
        }
    }

    std::vector<float> process(std::vector<float> samples) {

        if ((int)samples.size() != n_samples) {
            throw std::runtime_error("Wrong number of samples");
        }

        std::vector<float> results(coefficients.size());

        for (unsigned int i=0; i<coefficients.size(); i++) {
            const float r = emgoertzel_run(coefficients[i], &samples[0], samples.size());
            results[i] = r;
        }
     
        return results;   
    }
};

namespace py = pybind11;

PYBIND11_MODULE(detectbirds, m) {
    m.doc() = "Detect birdsong in audio";

    py::class_<GoertzelBank>(m, "GoertzelBank")
        .def(py::init< std::vector<float>, int, float>())
        .def("process", &GoertzelBank::process);

   // m.def("goertzel", goertzel_py);
}

