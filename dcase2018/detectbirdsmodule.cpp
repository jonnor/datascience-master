
#include <stdio.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

// TODO: speedup by precalculating coefficients: sine,cosine,
float goertzel(float* data, int n_samples, int frequency, int sr)
{
    const float scale = n_samples / 2.0;

    float samples = (float) n_samples;
    float k = (int) (0.5 + ((samples * frequency) / sr));
    float omega = (2.0 * M_PI * k) / samples;
    float sine = sin(omega);
    float cosine = cos(omega);

    float coeff = 2.0 * cosine;
    float q0=0;
    float q1=0;
    float q2=0;

    for(int i=0; i<n_samples; i++) {
        q0 = coeff * q1 - q2 + data[i];
        q2 = q1;
        q1 = q0;
    }
 
    const float real = (q1 - q2 * cosine) / scale;
    const float imag = (q2 * sine) / scale;

    float magnitude = sqrtf(real*real + imag*imag);
    return magnitude;
}

float goertzel_py(std::vector<float> samples, int frequency, int sr) {
    return goertzel(&samples[0], samples.size(), frequency, sr);
}

namespace py = pybind11;

PYBIND11_MODULE(detectbirds, m) {
    m.doc() = "Detect birdsong in audio";

    m.def("goertzel", goertzel_py);
}

