
#include <stdio.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

float goertzel(int numSamples,int TARGET_FREQUENCY,int SAMPLING_RATE, float* data)
{
    int     k,i;
    float   floatnumSamples;
    float   omega,sine,cosine,coeff,q0,q1,q2,result,real,imag;

    floatnumSamples = (float) numSamples;
    k = (int) (0.5 + ((floatnumSamples * TARGET_FREQUENCY) / SAMPLING_RATE));
    omega = (2.0 * M_PI * k) / floatnumSamples;
    sine = sin(omega);
    cosine = cos(omega);
    coeff = 2.0 * cosine;
    q0=0;
    q1=0;
    q2=0;

    for(i=0; i<numSamples; i++)
    {
        q0 = coeff * q1 - q2 + data[i];
        q2 = q1;
        q1 = q0;
    }
    real = (q1 - q2 * cosine);
    imag = (q2 * sine);
    result = sqrtf(real*real + imag*imag);
    return result;
}

namespace py = pybind11;

PYBIND11_MODULE(emtreesc, m) {
    m.doc() = "Detect birdsong in audio";

    m.def("goertzel", goertzel);
}

