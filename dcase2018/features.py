
import os
import sys
import time

import pandas
import numpy

import librosa 

def calculate_mel(inpath):
    y, sr = librosa.load(inpath, offset=0)
    mel = librosa.feature.melspectrogram(y=y, sr=sr, n_mels=128, fmax=8000)
    return mel

def extract_mel(inpath):
    out = inpath.replace('.wav', '.mel.csv')
    if os.path.exists(out):
        return None

    mel = calculate_mel(inpath)

    df = pandas.DataFrame(mel.T)
    df.to_csv(out, index=False)
    return mel

def extract_mfcc(inpath, mel):
    out = inpath.replace('.wav', '.mfcc.csv')
    if os.path.exists(out):
        return None

    if mel is None:
        mel = calculate_mel(inpath)
    mfcc = librosa.feature.mfcc(S=mel, n_fft=2048, hop_length=512, n_mfcc=20)

    df = pandas.DataFrame(mfcc.T)
    df.to_csv(out, index=False)
    return mfcc

def extract_features(wavpath):
    m = extract_mel(wavpath)
    f = extract_mfcc(wavpath, m)

def main():
    files = sys.argv[1:]
    last = len(files)-1
    for i, f in enumerate(files):
        before = time.time()
        print('{}/{}: {}'.format(i, last, f), end=' ')
        extract_features(f)
        after = time.time()
        print('{:.2f} seconds'.format(after-before))

if __name__ == '__main__':
    main()
