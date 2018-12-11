

# Introduction

Sound, and machine learning on sound, is a wide topic.
Some areas have enough interest to be considered their own fields.
This especially includes machine understanding of human speech (*Speech Recognition*) and
the computational analysis of music (*Music Information Retrieval*).

This paper instead focuses on detection and classification of *Acoustic Events*.
Such events can be any kind of sound, and in contrast to speech and music,
are often not produced with an intent to communicate.
Many of the techniques utilized for Acoustic Events can also be
used within speech and music, and many methods were in fact adopted from these fields.

While not as popular as computer vision or natural language processing,
the application of machine learning to acoustic events can be
found across many fields of scientific study and in many industries.

`TODO: add references`

In predictive maintenance, ...


In natural disaster management, early warning systems for landslides uses acoustic sensors

In ecoacoustics, ...

In security, detection of acoustic events are used to alert security camera operators to potential

In structural analysis, acoustic emissions is used to detect delamination of concrete on bridges

In domestic animal care, ...

In the smart home, acoustic sensors can detect and alert about baby crying or smoke alarm.


In most application scenarios, sound is transmitted via the air.
However there are fluid-borne sound (hydrophony) and structure-borne sounds and vibrations. 
Some sounds are below the audible frequency range for humans (infrasound) and some above (ultrasound).
The techniques presented here should apply in general across these modalities.


\newpage

While a basic understanding of the human auditory system can be beneficial when developing machine hearing,
Psychoacoustics will not be covered here. Those interested in a detailed treatise on this subject can read [@HumanMachineHearing].

The paper assumes some prerequisite knowledge on machine learning.
In particular it is assumed that the reader:
knows the difference between supervised and unsupervised learning;
knows task formulations like Classification, Clustering and Regression;
basic familiarity with common methods like Support Vector Machines, Random Forests and Convolutional Neural Networks.
A good primer is [@PythonMachineLearning].

Basic familiarity with Digital Signal Processing is assumed.
In particular knowledge of the Fourier Transform, digital filters and convolutions.

When it comes to sound, a brief background is provided.
We will then cover the main aspects of Machine Learning for Acoustic Event Detection and Classification. 
And at the end, we use the task of detecting the presence of birds as a practical example.

In summary, the goal is that after reading this report:
a machine learning practitioner,
without prior knowledge about sound and digital audio processing,
is be able to solve basic Acoustic Event Detection problems.


\newpage
# Theory

## Background 


### Digital sound representations

Physically, sound is a variation in pressure over time.
For machine learning, it must be exist in a digital representation.

![From acoustical sound to digital and back. Source: [@ProcessingTutorial]](./images/digital-sound-processing.png).

The acoustic data is converted to analog electric signals by a microphone and
then digitized using an Analog-to-Digital-Converter (ADC).

In the digitization process, the signal is quantized in time at a certain sampling frequency,
and the amplitude quantized at a certain bitdepth.
A typical sampling frequency is 44100 Hz, and bitdepth 16 bit. With these parameters,
the acoustic sound can be reconstructed without perceivable differences by humans.

Recordings can be multi-channel but for acoustic events
single-channel (mono) data is still the most common.

Digital sound can be stored uncompressed (PCM .wav), using lossless compression (.flac)
or using lossy compression (.mp3). Lossy compression removes information and may add artifacts,
and is best avoided for machine learning tasks.


#### Time domain

In the time domain an audio signal is seen as a continiously varying
signal corresponding to the pressure variation of the acoustic signal.

![Waveform (time domain) of a frog croaking repeatedly. Overall changes in signal intensity over time is visible, but what pitches are present (if any) is not.](./images/frog_waveform.png)

#### Frequency domain
Using the Fourier Transform, the audio can be losslessly converted to the frequency domain.

![Spectrum (frequency domain) of same frog sample. The frequency content can be seen, but temporal patterns are gone](./images/frog_spectrum.png)

#### Time-Frequency domain
Using Short-Time-Fourier-Transform (STFT), the audio can be mapped to the Time-Frequency domain.

![STFT spectrogram of same frog sample. Both temporal pattern and frequency patterns can be seen.](./images/frog_spectrogram.png)

The STFT has a tradeoff in time/frequency resolution.
Multi-resolution STFT can be used if high resolution in both time and frequency is needed.


\newpage
## Problem formulations

### Classification

In classification the goal is to determine the which acoustic event appears in an audio sample.
Samples can be short relative to the acoustic event length, or long, possibly having many instances of an event.
The number of events and their time is not returned in classification.

![Classification task with one class label per audio sample. Source: [@ComputationalAnalysisSound, fig 6.1]](./images/classification.png)

The classification can be binary (is this birdsong?), or multi-class (which species is this?).
Classification is often limited to a single label.

When the classification is done on long samples consisting of many different events
it is called Acoustic Scene Classification. Examples of a 'scene' in urban environments
could be 'restaurant', 'park', 'office', each having a different
composition of typical acoustic events.

### Event Detection

In event detection (also known as onset detection) the goal is to find the time spans where a given acoustic event occurs.
If the acoustic event is "frog croaking", then for each instance of a frog croak
the start time and end time of this event should be marked.

![Event detection, with labels at precise start and end locations in time. Source: [@ComputationalAnalysisSound, fig 6.3] ](./images/eventdetection.png)

In monophonic event detection, only the most prominent event is returned.
A classifier ran on short samples relative to the length of the acoustic event
can be used a detector.

In polyphonic event detection, multiple events are allowed at the same time.
This can be approached using separate classifiers per event type,
or using a multi-label classifier as a joint model.



### Weak labeling

Many acoustic events are short in duration, for instance a door slamming.
Other acoustic events only happen intermittently, like the the frog vocalizations in previous example.

Under supervised learning, ideally each and every of the acoustic events instances in the training data
would be labeled with their start and end time. This is called 'strong labels'.
However aquiring strong labels requires careful attention to detail by the annotator and is costly.

Therefore, often per-event time-based labels are not available.
Instead fixed-length audio clips are only marked whether an event occurs at least once, or not at all.
This is called a 'weak label' or 'weakly annotated' data.

When performing event detection, with small time windows (compared to annotated audio clips) as input,
the missing time information means there is not a direct label for this input.
This is known as a Multiple Instance Learning (MIL) problem.
Under MIL input instances are grouped into a 'bag', and the label exists on the bag
instead of the individual instances.
MIL formulations exist for many common machine learning algorithms.


\newpage
# Feature representations

In a typical machine learning pipeline, raw data is transformed into features
for the machine learning model via feature extraction.
The typical feature extraction process and feature representation is discussed here.

## Frames

To process and analyze the audio data it is often represented as *frames*, small groups of samples across time.
Frames can be produced in real-time, by collecting N samples at a time,
or by splitting up audio files after they have been recorded.

In a frame based approach, a frame is the smallest unit of time processed by the machine learning algorithm.
Therefore the frame length must be set long enough to contain enough relevant information,
but not so long that temporal variations disappear. For speech, a typical choice of frame length is 25ms.
Similar frame lengths are often adopted for acoustic events, unless there are specific concerns.

![Computing frames from an audio signal, using windows functions. Based on image by [@AudioFraming]](./images/frames.png)

Frames often use overlapping samples at the start and end.
Without overlap, acoustic event that happens partially in one frame results in different signals than when appearing in the middle.
The overlap can be specified as percentage of the frame length (overlap percentage).
or as a number of samples (hop length). Overlap can for instance be 50%.
A window function is applied to ensure that the signal level stays constant also in overlapping sections.


## Low-level features

From the samples in each frame, features can be calculated.

[@Breebaart2004, Ch 2.1.1] defined a Low-Level feature set for audio classification as:

1. root-mean-square (RMS) level
2. spectral centroid
3. spectral bandwidth
4. zero-crossing rate
5. spectral roll-off frequency,
6. band energy ratio,
7. delta spectrum magnitude,
8. pitch and (9) pitch strength

![Low-level features of birdsong. There are distinct peaks in the signals, but how well they correspond to birdsong events is not immediately clear.](./images/bird_clear_lowlevel.png)

Of these, root-mean-square (RMS) and zero-crossing rate (ZCR)
are calculated directly on the samples in the time-domain.

The spectral features are computed using the Fourier Transform on a frame,
and then summarizing with standard statistics. See [@DonggeLi2001] for the definitions.

Low-level spectral features, being univariate statistics on the spectrogram,
removes a lot of the information present.

## Spectrograms

A raw Short Time Fourier Transform can contain 1024 or more bins, often with strong correlation across multiple bins.
To reduce dimensionality, the STFT spectrogram is often processed with a filter-bank of 40-128 frequency bands.
Some filter-bank alternatives are 1/3 octave bands, the Bark scale, Constant-Q transform and the Mel scale.
All these have filters spacing that increase with frequency, mimicking the human auditory system.

## Mel-spectrogram

The most popular filter-bank uses triangular filters evenly spaced on the Mel scale.
A spectrogram processed with such a filterbank is called a Mel-spectrogram. 

`TODO: add ref for popularity`
`REF: log mel-spectrogram highest performing and most popular DCASE2018 results`


![Mel-spaced filterbank. Filters are normalize to be unity-area. Source: [@LowlevelFeaturesTimbre, p.20]](./images/mel-filterbanks.png)

Mel-filters using unit-area filters also exist.

![Mel-spectrogram of birdsong. The birdsong is clearly visible as up and down chirps at 3kHz and higher](./images/bird_clear_melspec.png)

A mel-spectrogram can still have significant correlation between bands.

## MFCC

To reduce correlation one can compute the Discrete Cosine Transform (DCT-2) on the mel-spectrogram.
The result is known as the Mel Filter Cepstrum Coefficients (MFCC).

![MFCC of birdsong](./images/bird_clear_mfcc.png)

Another advantage of the DCT is that important information in the signal tends to end up in the lower coefficients.
Therefore it can be compressed efficiently (but lossily) by dropping the higher coefficients. 13-20 coefficients is common.

The band in the cepstrum are the coefficient of cosines that when summed together reconstruct the input (using the inverse DCT).
This means that events that are close in frequency domain are no longer next to each other in a MFCC matrix,
making local pattern-matching algorithms less effective. 
Therefore they are not so popular for use with Convolutional Neural Networks,
but mostly used with linear models such as Gaussian Mixture Models (GMM) and Hidden Markov Models (HMM.


## Summarizing features

When classifying longer segments of labeled audio it can be desirable to
come up with a summary that represents the entire clip.
This can be done by computing statistics across the per-frame features for all frames in the clip.

![Clip summarizations of frames. Source: [@LowlevelFeaturesTimbre, p.27]](./images/summarizing-frames.png)

Any statistical aggregate functions can be used, such as `min`,`max`,`median`,`mean`,`skew`, `Kurtosis`.
In a summary the order of frames is ignored, and we have a Bag-of-Frames feature model.

## Convolution

`TODO: examples of non-learned convolutional kernel, applied to spectrogram`
Standard: Vertical edge detector. Median filter. 
Customized: detect cascade up or down 

In this way, a convolutional kernel can be seen as parametric local feature detector.

![](./images/convolution.png)
https://i1.wp.com/timdettmers.com/wp-content/uploads/2015/03/convolution.png?resize=500%2C193

Often a set of convolution kernels are used, and in combination they can detect many pattern variations.


## Feature learning

To avoid having to manually design or choose convolution kernels, they can be learned from data.
One approach is to randomly select small N,M sized patches from the spectogram and to reduce this
into a a representative codebook using vector quantization.
In [@BirdFeatureLearning], this was done for detection of birdsong using *spherical k-means* clustering,
a variation of k-means using the cosine (dis)similarity as the distance metric.
In  [@FeatureLearningMatrixFactorization], Sparse Non-negative Matrix Factorization was used for
Acoustic Scene Classification.

Other unsupervised methods include and Convolutional AutoEncoders (CAE).
In [@FeatureLearningAutoEncoder], CAEs were stacked to obtain a 'deep' model of hierarchical features.

If large amount of labeled data are available, a Convolutional Neural Network (CNN)
can be used for supervised learning of deep network of convolution operators.

CNN-based models are currently among the best performing models both in 
in audio classification. 
`TODO: ref for best perf`

## Learning on raw audio waveform

Deep neural networks can also the raw audio waveform as input features,
skipping the spectrogram computation step.
This learning a model without dedicated feature extraction, is sometimes called 'end 2 end' learning.

[@RawWaveformCNN] was able to train a Convolutional Neural Network on raw waveform data
to match log-mel spectrogram features in an audio classification task.
The network also needed to jointly learn bandpass filters in the first layers to
replace the transformation normally performed by the spectrogram.

Such models can also be used in fusion with spectrogram model, as in [@RawWaveformMelSpectrogramFusion]. 

## Other feature representations
A large amount of alternative feature representations have been proposed.
Some have explored wavelet filterbanks and the Scattering transform [@ScatteringUrbanSound].

Prior to efficient convolutional neural networks, image-based features like
Scale Invariant Feature Transform (SIFT) and Histogram of Oriented Gradients (HOG) 
have also been applied to spectrograms [@SIFTMusicStyle], [@HOGSpeechRecognition].

Feature extraction models that more closely mimics the human hearing system
include Cascade of Asymmetric Resonators with Fast-Acting Compression (CARFAC) [@CARFACMachineHearing].



\newpage
# Case study

To apply the above theory, we look at the Bird Audio Detection task from the
DCASE2018 machine-learning challenge.

Some code will be provided inline for illustration, while the
full code is available at https://github.com/jonnor/birddetect as executable Jupyter Notebooks.

## Bird vocalization detection

The problem formulation is binary classification:
the system should output whether audio sample has bird(s) or not.

* 10 second audio clips
* One label for the clip (weakly annotated)
* 3 training sets, 3 test sets
* Total 48'000 samples

The 2018 edition of this challenge is focused on generalizable performance.
Therefore 2 of the test sets are recorded at different locations with different equipment
than the training samples (mismatched conditions).


## Feature representation

As a basis for feature representations, the log-transformed mel-spectrogram is used.
The mel-spectrogram is calculated with 64 mel-filter bands, from 500Hz to 15000 Hz.
Exploration of the dataset showed that many recordings had a lot of static white-noise below approximately 1000Hz,
and not all recordings had data above approximately 16KHz.
Especially those from the remote monitoring scenarios (`PolandNFC`, `Chernobyl`) were affected.
The implicit assumption is that most or all of the bird vocalization is inside the preserved range.

The spectrogram is then preprocessed by removing the median per frequency band,
and finally it is min-max scaled to a range of 0-255, and converted to an 8 bit-unsigned integer.
This hopefully reduces variation between the different recording characteristics of the different datasets. 

`TODO: spectrogram image. Before+after 8-bit quantization?`

```python
def read_audio(url):
    f = urllib.request.urlopen(url)
    data = io.BytesIO(f.read())
    samplerate, samples  = scipy.io.wavfile.read(data)
    assert samplerate == 44100, samplerate
    data = samples.astype('float')/32768
    return samplerate, data

def melspec(data, sr, subtract='median', n_mels=64, fmin=500, fmax=15000, htk=True,):
    from librosa.feature import melspectrogram
    
    mel = melspectrogram(y=data, sr=sr,
                         n_mels=n_mels, fmin=fmin, fmax=fmax, htk=True)
    mel = librosa.core.amplitude_to_db(mel, ref=1.0)
    if subtract == 'median':
        mel = mel - (numpy.median(mel, axis=1, keepdims=True) + 1e-8)

    return mel

def quantize_8bit(s):
    out_min,out_max  = 0, 255
    in_min, in_max = s.min(), s.max()
    std = (s - in_min) / (in_max - in_min)
    scaled = std * (out_max - out_min) + out_min
    return scaled.astype(numpy.uint8)
```

For each file, the features are computed using these functions:

```python
sr, data = read_audio(wav_url)
mel = melspec(data, sr, n_mels=64)
mel = quantize_8bit(mel)
```

Using 8-bit unsigned integer allows to store the features compressed using standard image formats.
For lossless storage, the PNG format is used.

`TODO: say something about compression rate`

The features are pre-calculated for each of the 48'000 files and stored in Google Cloud Storage, as a public dataset.
`TODO: link to dataset`

A small Python module `dcase2018bird.py` was developed to have convenient access to the dataset.

`TODO: code example snippet`


## Compared methods

A couple of different machine learning pipelines was developed.
All use the same mel-spectrogram input. 

* `melspec-maxp-rf`: Max-summarization, RandomForestClassifier.
* `melspec-cnn-logreg`: Pretrained CNN, LogisticRegression classifier


No data augmentation was performed.


`TODO: write a bit about each model`
`TODO: import code for each model`

## Results

Evaluation method

`TODO: accuracy for each model`

`TODO: say something about training time?`

## Discussion


## Conclusion



# Where to go from here
???

? Data augmentation
? More problem formulations


# References

