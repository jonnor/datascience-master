
Machine hearing.
focus on audio event detection and a review methods applied on birdsong detection.

## Meta
### Goal
After reading this report,
a machine learning practitioner
without prior knowledge about sound or digital signal processing
shall be able to solve basic audio event detection problems.

### Scope
Focus on

* Acoustic Event Detection. Animals. Ecoacoustics/bioacoustics
* Robust methods, can be used in real-life noisy environments
* Efficient methods, possible to implement in embedded system

Only mentioned briefly

* Psycoacoustics
* Biological models of sound production

Prerequisite knowledge required

* Basics machine learning concepts
Supervised vs unsupervised learning.
Classification,clustering,regression.
* Familiarity with common methods
Support Vector Machine, Random Forests, Convolutional Neural Networks

Knowledge not required

* Audio, acoustics

Recommended

* Familiarity with Python
* Familiarity with scikit-learn
* Basic digital signal processing.
Linear-time-invariant systems, Causality, Fourier Transform.

### Format
* 15-25 pages, A4, 12pt, 1in margins
* Abstract
* Table of Contents, List of Figures
* Bibliography


## Introduction to sound

- Sound processing systems.
Aquisition. Storage. Processing. Output.
Online versus offline.

- Acoustics
- Digital recordings of sound
Discretization in amplitude
Discretization in time
File formats
Compression. Lossless, lossy
- audio mixtures

- Receiver characteristics.
Frequency response.
Noise.

- Environment characteristics
Noise. Stationary, quasi-stationary
Non-class sounds.
Distance to source(s). Changing level of target sound.
Reverberation.
Microphonics,vibrations.

- Source characteristics

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
- Multi-class
- Open ended
- Anomaly/novelity detection

## Feature representations
Criterias for good features
Keep relevant info, remove irrelevant.
Robust against variations


Normalization

### Low-level features
spectral center, spectral slope etc

### Time-frequency representations
STFT, windowing
filter-banks. Constant-Q. Fourier transform
mel-spectrogram
MFCC

delta, lag/lead frames
Summarizations
first-order, second-order statistics

### Biologically based
Coclear models
CARFAC

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


