
#ifndef DETECTBIRDS_H
#define DETECTBIRDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "fft.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// FIXME: actually include emtrees
//#include <emtrees.h>
typedef struct {} EmtreesModel;
int32_t
emtrees_predict(EmtreesModel *m, float *f, int32_t l) {
    return 0;
}
EmtreesModel *birddetect_model = NULL;


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
emgoertzel_run(EmGoertzel c, const float* data, int n_samples)
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

// emaudio.h
typedef struct {
    float *data;
    size_t length;
} EmVector;

// Double buffering
typedef struct _EmAudioBufferer {
    int buffer_length;
    float *buffer1;
    float *buffer2;

    float *write_buffer;
    float *read_buffer;
    int write_offset;
} EmAudioBufferer;

void
emaudio_bufferer_reset(EmAudioBufferer *self) {
    self->write_buffer = self->buffer1;
    self->read_buffer = NULL;
    self->write_offset = 0;
}

int
emaudio_bufferer_add(EmAudioBufferer *self, int16_t s) {

    self->write_buffer[self->write_offset++] = (float)s/INT16_MAX; 

    if (self->write_offset == self->buffer_length) {
        // FIXME: error if read_buffer has not been cleared
        self->write_offset = 0;
        self->read_buffer = self->write_buffer;
        self->write_buffer = (self->read_buffer == self->buffer1) ? self->buffer2 : self->buffer1;
        return 1;
    } else {
        return 0;
    }
}

int
emvector_shift(EmVector a, int amount)
{
    if (abs(amount) >= a.length) {
        return -2; // non-sensical
    }

    if (amount == 0) {
        return 0;
    } else if (amount > 0) {
        return -1; // TODO: implement
    } else {
        for (int i=a.length+amount; i<a.length; i++) {  
            a.data[i+amount] = a.data[i];
        }
        return 0;
    }
}

int
emvector_set(EmVector dest, EmVector source, int location) {
    const int final_dest = source.length+location;
    if (final_dest > dest.length) {
        return -1;
    }
    if (location < 0) {
        return -2;
    }

    for (int i=location; i<final_dest; i++) {
        dest.data[i] = source.data[i-location]; 
    }
    return 0;
}


#define EMAUDIO_FFT_LENGTH 1024
#define FFT_TABLE_SIZE EMAUDIO_FFT_LENGTH/2

int
emaudio_rfft(EmVector audio, EmVector bins) {  

    // FIXME: change to floats
    double real[EMAUDIO_FFT_LENGTH];
    double imag[EMAUDIO_FFT_LENGTH];

    // FIXME: change to floats, pass in from outside
	double fft_cos[FFT_TABLE_SIZE];
	double fft_sin[FFT_TABLE_SIZE];
    FFTTable fft = { FFT_TABLE_SIZE, fft_cos, fft_sin };
    fft_table_fill(fft, EMAUDIO_FFT_LENGTH);

    if (audio.length != EMAUDIO_FFT_LENGTH) {
        return -1;
    }
    if (bins.length != EMAUDIO_FFT_LENGTH) {
        return -2;
    }

    for (int i=0; i<EMAUDIO_FFT_LENGTH; i++) {
        real[i] = audio.data[i];
        imag[i] = 0.0;
    }

    fft_table_transform(fft, real, imag, EMAUDIO_FFT_LENGTH);

    for (int i=0; i<EMAUDIO_FFT_LENGTH; i++) {
        bins.data[i] = real[i];
    }

    return 0;
}

// Power spectrogram
int
emaudio_power_spectrogram(EmVector rfft, EmVector out, int n_fft) {
    const int spec_length = 1+n_fft/2;

    if (rfft.length < spec_length) {
        return -1;
    }
    if (out.length != spec_length) {
        return -2;
    }

    const float scale = 1.0f/n_fft;
    for (int i=0; i<spec_length; i++) {
        const float a = fabs(rfft.data[i]);
        out.data[i] = scale * powf(a, 2);
    }
    return 0;
}

// Simple formula, from Hidden Markov Toolkit
// in librosa have to use htk=True to match
float
emaudio_mels_from_hz(float hz) {
    return 2595.0 * log10(1.0 + (hz / 700.0));
}
float
emaudio_mels_to_hz(float mels) {
    return 700.0 * (powf(10.0, mels/2595.0) - 1.0);
}


typedef struct _EmAudioMel {
    int n_mels;
    float fmin;
    float fmax;
    int n_fft;
    int samplerate;
} EmAudioMel;


static int
mel_bin(EmAudioMel params, int n) {

    // Filters are spaced evenly in mel space
    const float melmin = emaudio_mels_from_hz(params.fmin);
    const float melmax = emaudio_mels_from_hz(params.fmax);
    const float melstep = (melmax-melmin)/(params.n_mels+1);

    const float mel = melmin + (n * melstep);
    const float hz = emaudio_mels_to_hz(mel);
    const int bin = floor((params.n_fft+1)*(hz/params.samplerate));
    return bin;
}


// https://haythamfayek.com/2016/04/21/speech-processing-for-machine-learning.html
int
emaudio_melspec(EmAudioMel mel, EmVector spec, EmVector mels) {

    const int max_bin = 1+mel.n_fft/2;
    if (max_bin > spec.length) {
        return -1;
    }
    if (mel.n_mels != mels.length) {
        return -2;
    }

    // Note: no normalization

    for (int m=1; m<mel.n_mels+1; m++) {
        const int left = mel_bin(mel, m-1);
        const int center = mel_bin(mel, m);
        const int right = mel_bin(mel, m+1);
    
        if (left < 0) {
            return -3;
        }
        if (right > max_bin) {
            return -4;
        } 

        float val = 0.0f;
        for (int k=left; k<center; k++) {
            const float weight = (float)(k - left)/(center - left);
            val += spec.data[k] * weight;
        }
        for (int k=center; k<right; k++) {
            const float weight = (float)(right - k)/(right - center);
            val += spec.data[k] * weight;
        }

        mels.data[m-1] = val;
    }

    return 0;
}

int
emaudio_hann_apply(EmVector out) {

    const long len = out.length;
    for (int i=0; i<len; i++) {
        float m = 0.5 * (1 - cos(2*M_PI*i/(len-1)));
        out.data[i] = m * out.data[i];
    }
    return 0;
}

#define EM_MAX(a, b) (a > b) ? a : b

int
emvector_max_into(EmVector a, EmVector b) {
    if (a.length != b.length) {
        return -1;
    }

    for (size_t i=0; i<a.length; i++) {
        a.data[i] = EM_MAX(a.data[i], b.data[i]);
    }
    return -1;
}

int
emvector_set_value(EmVector a, float val) {
    for (size_t i=0; i<a.length; i++) {
        a.data[i] = val;
    }
    return 0;
}

// birddetector.h
typedef struct _BirdDetector {
    EmVector audio;
    EmVector features;
    EmVector temp1;
    EmVector temp2;
    EmAudioMel mel_filter;
    EmtreesModel *model;
} BirdDetector;

int
process_frame(EmVector in, EmVector temp) {

    EmVector input = { };
    EmVector windowed = { };
    EmVector rfft = { };
    EmVector spec = { };
    EmVector mels = { };

    //emaudio_hann_apply

    // FIXME: implement

    //emaudio_rfft(audio, bins);
    //emaudio_spectrogram():
    //emaudio_melspec(bins, mels);

    //

}

void
birddetector_reset(BirdDetector *self) {

    emvector_set_value(self->audio, 0.0f);
    emvector_set_value(self->features, 0.0f);
}

void
birddetector_push_frame(BirdDetector *self, EmVector frame) {

    // XXX: each frame is hop_length sized

    // insert new frame into our buffer
    emvector_shift(self->audio, -frame.length);
    emvector_set(self->audio, frame, self->audio.length-frame.length);

    // process window
    emvector_set(self->temp1, self->audio, 0);

    process_frame(self->temp1, self->temp2);

    // Feature summarization
    emvector_max_into(self->features, self->temp2);
}

bool
birddetector_predict(BirdDetector *self) {

    const int32_t cl = emtrees_predict(self->model, self->features.data, self->features.length);
    return cl == 1;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // DETECTBIRDS_H

