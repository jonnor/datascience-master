
#include "detectbirds.h"

#include <assert.h>
#include <stdio.h>

#define ASSERT_EQUAL(a, b) if (a != b) { fprintf(stderr, "FAIL: %f != %f\n", a, b); assert(a == b); }

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
test_emvector() {

    test_emvector_nop();
    test_emvector_shift_down();
    test_emvector_set_mid();
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
