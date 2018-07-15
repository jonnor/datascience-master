
import os
import sys
import time
import zipfile
import tempfile
import math
import os.path


import pandas
import numpy
import librosa 
import scipy.ndimage

def extract_samples(path, outdir, limit=100, seed=0):
    numpy.random.seed(seed)

    with zipfile.ZipFile(path) as archive:
        wavs = [ i for i in archive.infolist() if i.filename.endswith('.wav') ]

        wavs = numpy.array(wavs)
        wavs = numpy.random.choice(wavs, size=limit, replace=False)
        for info in wavs:
            archive.extract(info, outdir)

        df = pandas.DataFrame({'filenames': [ f.filename for f in wavs ]})
        return df

def main():
    inpath, outpath, limit = sys.argv[1:4]
    limit = int(limit)
    df = extract_samples(inpath, outpath, limit)
    b = os.path.basename(inpath)
    df.to_csv(os.path.join(outpath, b+'.files.csv'))

if __name__ == '__main__':
    main()
