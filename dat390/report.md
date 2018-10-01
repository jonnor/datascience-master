
Machine hearing.
focus on audio event detection and a case study in

## Introduction to sound

- Acoustics
- Digital recordings of sound
Quantization amplitude
File formats
Compression. Lossless, lossy
- audio mixtures

### Psychoacoustics
(Brief)
Non-linearities.
Log-ish frequency. notes. mel scale, gammatone
False pitch
Shepherds tone. Octave repetition
Missing fundamental
Reflection pitch

Log-ish power. desibel. 
Loudness. Stevens power law.
sones.
phones, equal loudness contours

Critical bandwidth. Loudness in mixes dependent on distances in frequency
Masking. One sound can hide another.
Simultaneous masking. Loud High tone can mask low tone.
forward masking. tensof ms

Temporal compression

Binaural hearing.

Function of sound.
Speech. "point the eyes"
Audio event. what,where

Cocktail party problem. Source separation, multi-source attention

### Models of sound production
- Biological models sound production in animals.
Formants
- (Acoustic models of instruments)

## Applications
of machine learning on sound

- **Speech Recognition**
- **Music information retrieval**

* Ecoacoustics/bioacoustics. Population estimation. Health monitoring.
* Predictive maintenance. Anomaly detection.
* Process control. Do something once audible event happens. Coffe
* Smart home / home automation.  Children crying, smokealarm
* Security. Intrusion detection. Aggression detection.
* Surveillance. Event detection for. Voice

Connected problems and fields:

- vibration data
- time-series


## Problems formulations

- Classification
- Detection, precise time
- Segmentation
- Source/individual identification
- Diarization 
- Monophonic vs polyphonic
- Multi-label

## Feature representations
Criterias for good features

### Low-level features
spectral center, spectral slope etc

### Time-frequency representations
STFT, windowing
filter-banks. Constant-Q. Fourier transform
mel-spectrogram
MFCC

delta, lag/lead frames
Summarizations on spectrograms

### Biologically based
Coclear models

### Wavelet based
* Wavelet filterbanks
* Scattering transform

### Representation learning
Convolutional kernels

## Models

- Linear
- Tree-based
- CNN
- Gaussian Mixtures, Hidden Markov Model

## Pre-processing
- Noise reduction
- Source separation

## Data augmentations
Respects invariants/properties of features. Modelling particular challenges.

- noise addition
- volume change
- frequency response change

## Comparative study
On DCASE2018 bird-detection challenge.

Features

* low-level
* MFCC
* melspectrogram (log?)
* add delta frames
* learned convolution kernels
* combinations

Classifiers

* Linear. SVC?
* RandomForest
* CNN

Evaluation

* accuracy
* training time
* prediction time (incl feature extration)

## Summary
What can be done using state-of-the-art?
Open problems, areas of research.
Summary of current situation.


