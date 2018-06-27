
// emaudio.h
struct EmVector {
    float *data;
    size_t length;
};

// Double buffering
struct EmAudioBufferer {
    const int buffer_length;
    float *buffer1;
    float *buffer2;

    float *write_buffer;
    float *read_buffer;
    int write_offset;
}

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

void
emaudio_shift_features(EmVector features, EmVector frame)
{
    // FIXME: implement
    // drop oldest frame by move existing features down
    // add new frame
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
struct BirdDetector {
    int n_frames;
    EmVector features;
    EmtreesModel *model;
};

bool birddetector_classify_frame(BirdDetector *self, EmVector audio) {
    const int mels_length = 128;
    float mels_data[mels_length];
    EmVector mels = { mels_data, mels_length };

    emaudio_melspec(audio, mels);
    emaudio_pcen(mels);

    // features is from multiple frames, probably summarized?
    // TODO: calculate features for this frame

    emaudio_shift_features(features, frame_features);

    const int32_t cl = emtrees_predict(model, features.data, features.length);
    return cl == 1;
}

// main

const int AUDIO_FRAME_LENGTH = 2048;
float audio1[AUDIO_FRAME_LENGTH];
float audio2[AUDIO_FRAME_LENGTH];

const int N_FRAMES = 5;
const int FRAME_FEATURES = 2; // mean,std

EmAudioBufferer bufferer;


void adc_interrupt() {
    emaudio_bufferer_add(bufferer, sample);
}

void main(void) {
    bufferer = { AUDIO_FRAME_LENGTH, audio1, audio2, NULL, NULL, 0 };
    emaudio_bufferer_reset(&bufferer);

    const int features_length = N_FRAMES*FRAME_FEATURES;
    float features_data[features_length];
    EmVector features = { features_data, features_length };
    BirdDetector detector = { N_FRAMES, features, birddetect_model };

    for (;;;) {

        if (bufferer->read_buffer) {
            EmVector frame = { ready_audio, AUDIO_SIZE };
            const bool has_bird = classify_frame(features, frame)
            bufferer->read_buffer = NULL; // done processing
        }
    }
}
