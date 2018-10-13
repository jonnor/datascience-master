
## Return bitrates (bits/second) for different data/feature representations
def audio_size(samplerate, bits=4):
    return samplerate * bits

def melspec_size(frame_shift, n_mels, bits=4):
    n_frames = 1.0/frame_shift
    return n_frames * n_mels * bits

def mfcc_size(frame_shift, n_mfcc, bits=4):
    n_frames = 1.0/frame_shift
    return n_frames * n_mfcc * bits

def summaries_size(window_length, n_features, bits=4):
    n_summaries = 1.0/window_length
    return n_summaries * n_features * bits


def main():
    frame_shift = 512/44100

    print('len', (44100*10) / 512)

    audio = audio_size(44100, bits=16)
    mels = melspec_size(frame_shift, 64, bits=8)
    mfccs = mfcc_size(frame_shift, 20, bits=32)
    summ = summaries_size(10, 64*2*2, bits=32)

    print((mels/8 * 10)/1000)

    print(locals())

if __name__ == '__main__':
    main()
