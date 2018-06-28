
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

// FIXME: actually include emtrees
//#include <emtrees.h>
typedef struct {} EmtreesModel;
int32_t
emtrees_predict(EmtreesModel *m, float *f, int32_t l) {
    return 0;
}
EmtreesModel *birddetect_model = NULL;

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


void
emaudio_sft(EmVector audio, EmVector bins) {

}

void
emaudio_melspec(EmVector audio, EmVector mels) {
    // FIXME: implement
}

void
emaudio_pcen(EmVector vector) {
    // FIXME: implement
}

// birddetector.h
typedef struct _BirdDetector {
    int n_frames;
    EmVector features;
    EmtreesModel *model;
} BirdDetector;

bool birddetector_classify_frame(BirdDetector *self, EmVector audio) {
    const int mels_length = 128;
    float mels_data[mels_length];
    EmVector mels = { mels_data, mels_length };

    // FIXME: need to consider SFT and the overlapping windows
    // for instance use 2 consecutive audio frames and use midpoint as center of window

    //emaudio_sft(audio, bins);
    //emaudio_melspec(bins, mels);
    emaudio_pcen(mels);

    // FIXME: calculate new features. Are they aggregated across frames?

    //emaudio_shift_features(features, frame_features);

    const int32_t cl = emtrees_predict(self->model, self->features.data, self->features.length);
    return cl == 1;
}


