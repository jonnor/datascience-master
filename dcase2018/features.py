
import os
import sys
import time
import zipfile
import tempfile
import math


import pandas
import numpy
import librosa 
import scipy.ndimage


def melspec(y, sr, n_fft=2048, hop_length=None, win_length=None, n_mels=128, fmin=0, fmax=None):
    import detectbirds

    if hop_length is None:
        hop_length = n_fft//2
    if win_length is None:
        win_length = n_fft
    if fmax is None:
        fmax = sr//2
        
    frames = librosa.util.frame(y, frame_length=n_fft, hop_length=hop_length)
    spec_frames = []
    for frame_no in range(frames.shape[1]):
        frame = frames[:,frame_no]
        assert frame.shape[0] == n_fft

        s = detectbirds.melspectrogram(frame, n_mels, fmin, fmax, n_fft, sr)                

        s = s.reshape(-1, 1)
        spec_frames.append(s)
        
    mels = numpy.hstack(spec_frames)
    assert mels.shape[1] == frames.shape[1], (mels.shape,frames.shape)
    return mels


def extract_from_zip(path, process_func, limit=None, offset=None):
    with zipfile.ZipFile(path) as archive:
        wavs = [ i for i in archive.infolist() if i.filename.endswith('.wav') ]

        if offset is not None:
            wavs = wavs[offset-1:]
        if limit is not None:
           wavs = wavs[:limit] 

        features = []
        names = []
        for n, info in enumerate(wavs):
            name = info.filename
            wavdata = archive.read(info)

            # librosa does not support reading from a buffer, create temporary file :(
            with tempfile.NamedTemporaryFile(suffix='.wav', delete=True) as temp:
                w = temp.write(wavdata)
                temp.flush()
                os.fsync(temp.fileno())

                f = process_func(temp.name, n, wavs)
                features.append(f)
                names.append(name)

        data = numpy.array(features)

        df = pandas.DataFrame(index=names, data=data)
        return df

def meansub(s):
    return s - (numpy.mean(s, axis=0) + 1e-8)

def minmaxscale(s):
    mins = numpy.min(s, axis=0) + 1e-8
    maxs = numpy.max(s, axis=0)
    return ( s - mins) / ( maxs - mins )

def melspec_maxp(mel):
    mel = meansub(mel)
    mel = minmaxscale(mel)
    filt = scipy.ndimage.median_filter(mel, (1, 3))

    features = numpy.concatenate([
        numpy.max(filt, axis=1),
    ])
    return features


def extract_melmax(wav, n, wavs):
    start = time.time()

    n_mels = 64
    features = numpy.empty(n_mels)
    features.fill(numpy.nan)
    try:
        y, sr = librosa.load(wav, offset=0, sr=None)
        assert sr == 44100
        mel = librosa.feature.melspectrogram(y=y, sr=sr, n_mels=n_mels, fmin=500, n_fft=2048, fmax=15000, htk=True)
        extracted = melspec_maxp(mel)
        assert extracted.shape == features.shape, (extracted.shape, features.shape)
        features = extracted
    except Exception as e:
        print('ERROR', e)
        # just leveave the NaNs

    end = time.time()
    t = end-start
    remaining = (len(wavs)-1-n) * t
    status = '{}/{}: {} sec. Remaining {} min'.format(n+1, len(wavs), t, math.ceil(remaining/60))
    print(status)

    return features

def main():
    inp = sys.argv[1]
    limit = int(sys.argv[2]) if len(sys.argv) > 2 else None
    offset = int(sys.argv[3]) if len(sys.argv) > 3 else None

    out = inp.replace('.zip', '.melmax.csv')
    

    print('opening', inp, out)
    features = extract_from_zip(inp, extract_melmax, limit=limit, offset=offset)
    features.to_csv(out, index_label='filename')

if __name__ == '__main__':
    main()
