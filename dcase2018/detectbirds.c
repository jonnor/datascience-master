
#include <stdio.h>

#include "detectbirds.h"

#include <assert.h>


#define ASSERT_EQUAL(a, b) if (a != b) { fprintf(stderr, "FAIL: %f != %f\n", a, b); assert(a == b); }

#define ASSERT_ALMOST_EQUAL(a, b) \
    const bool _a_cmp = fabs(a - b) < 0.0001; \
    if (!_a_cmp) { fprintf(stderr, "FAIL: %f != %f\n", a, b); assert(_a_cmp); }

#define ASSERT_NOERROR(x) if (x != 0) { fprintf(stderr, "ERROR: %d\n", x); } assert(x == 0);

void
test_emvector_nop() {
   float adata[4] = { 1.0, 2.0, 3.0, 4.0};
   EmVector a = { adata, 4 };
   ASSERT_NOERROR(emvector_shift(a, 0));
   ASSERT_EQUAL(a.data[0], 1.0);
   ASSERT_EQUAL(a.data[1], 2.0);
}

void
test_emvector_shift_down() {
   float adata[4] = { 1.0, 2.0, 3.0, 4.0};
   EmVector a = { adata, 4 };
   ASSERT_NOERROR(emvector_shift(a, -2));
   ASSERT_EQUAL(a.data[0], 3.0);
   ASSERT_EQUAL(a.data[1], 4.0); 
}

void
test_emvector_set_mid() {
   float adata[4] = { 1.0, 2.0, 3.0, 4.0};
   EmVector a = { adata, 4 };
   float bdata[2] = { 5.0, 6.0 };
   EmVector b = { bdata, 2 };

   ASSERT_NOERROR(emvector_set(a, b, 2));
   ASSERT_EQUAL(a.data[0], 1.0);
   ASSERT_EQUAL(a.data[1], 2.0);
   ASSERT_EQUAL(a.data[2], 5.0);
   ASSERT_EQUAL(a.data[3], 6.0); 
}

void
test_emaudio_mel_hz_roundtrip() {

    const float in = 133.0; 
    const float m = emaudio_mels_from_hz(in);
    const float out = emaudio_mels_to_hz(m);

    ASSERT_ALMOST_EQUAL(in, out);
}

void
test_emaudio_mel_bin() {
    const EmAudioMel params = { n_mels:32, fmin:0, fmax:10025, n_fft:1024, samplerate:20050 };

    const int low = mel_bin(params, 0);
    const int high = mel_bin(params, params.n_mels+1);

    ASSERT_EQUAL(low, 0);
    ASSERT_EQUAL(high, params.n_fft/2);
}

void
test_emaudio_mels() {
    const EmAudioMel params = { n_mels:32, fmin:0, fmax:20050/2, n_fft:1024, samplerate:20050 };
    float mels_data[params.n_mels];
    float spec_data[params.n_fft];

    EmVector spec = { spec_data, params.n_fft };
    EmVector mels = { mels_data, params.n_mels };

    ASSERT_NOERROR(emaudio_melspec(params, spec, mels));
}

void
test_emvector() {

    test_emvector_nop();
    test_emvector_shift_down();
    test_emvector_set_mid();
    printf("emvector: PASSED\n");
}

void
test_emaudio() {
    test_emaudio_mel_hz_roundtrip();
    test_emaudio_mel_bin();

    test_emaudio_mels();
    printf("emaudio: PASSED\n");
}

// main

#define AUDIO_FRAME_LENGTH 2048
float audio1[AUDIO_FRAME_LENGTH];
float audio2[AUDIO_FRAME_LENGTH];

const int N_FRAMES = 5;
const int FRAME_FEATURES = 2; // mean,std

EmAudioBufferer bufferer;

void adc_interrupt() {
    int sample = 13333;
    emaudio_bufferer_add(&bufferer, sample);
}

void main(void) {
    bufferer = (EmAudioBufferer){ AUDIO_FRAME_LENGTH, audio1, audio2, NULL, NULL, 0 };
    emaudio_bufferer_reset(&bufferer);

    test_emvector();
    test_emaudio();

    const int features_length = N_FRAMES*FRAME_FEATURES;
    float features_data[features_length];
    EmVector features = { features_data, features_length };
    BirdDetector detector = { N_FRAMES, features, birddetect_model };

    while (true) {

        if (bufferer.read_buffer) {
            EmVector frame = { bufferer.read_buffer, bufferer.buffer_length };
            const bool has_bird = birddetector_classify_frame(&detector, frame);
            bufferer.read_buffer = NULL; // done processing
        }
    }
}
