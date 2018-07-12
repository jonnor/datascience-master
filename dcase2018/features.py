
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

def melspec_maxp(mel):
    mel = meansub(mel)
    filt = scipy.ndimage.median_filter(mel, (1, 1))

    features = numpy.concatenate([
        numpy.max(filt, axis=1),
    ])
    return features


def extract_melmax(wav, n, wavs):
    start = time.time()

    y, sr = librosa.load(wav, offset=0, sr=None)
    mel = librosa.feature.melspectrogram(y=y, sr=sr, n_mels=64, fmin=500, fmax=8000)
    features = melspec_maxp(mel)

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
