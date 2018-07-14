
import numpy
import numpy.fft
import librosa

import pytest
import numpy.testing

import features
import detectbirds

def test_rfft_simple():
    ss = numpy.arange(0, 1024)
    ref = numpy.fft.fft(ss, n=1024).real
    out = detectbirds.rfft(ss)

    numpy.testing.assert_allclose(out, ref, rtol=1e-5)

def test_rfft_not_power2_length():
    with pytest.raises(Exception) as e:
        detectbirds.rfft(numpy.array([1,3,4,5]))

@pytest.mark.skip('wrong scaling?')
def test_melspectrogram():

    y, sr = librosa.load('data/ff1010bird/{}.wav'.format(19037), offset=0)

    ref = librosa.feature.melspectrogram(y, sr, fmin=0, fmax=None, n_fft=1024, n_mels=64, norm=None, htk=True)
    out = features.melspec(y, sr, n_fft=1024, fmin=0, fmax=None, n_mels=64)
    ref = ref[:,1:-1]

    print(numpy.mean(ref))
    print(numpy.mean(out))

    ref = features.melspec_maxp(ref)
    out = features.melspec_maxp(out)

    print(numpy.mean(ref))
    print(numpy.mean(out))

    print(out-ref)
    numpy.testing.assert_allclose(out, ref, rtol=1e-6);

def test_process():

    y, sr = librosa.load('data/ff1010bird/{}.wav'.format(19037), offset=0)
    print('max', numpy.max(y), numpy.min(y))

    n_mels = 64
    p = detectbirds.Processor(n_mels, 0.0, 8000.0, 1024, sr)
    n_frames = p.add_samples(y)
    assert n_frames == 430

    f = p.get_features()
    assert f.shape[0] == n_mels
    print(f)
