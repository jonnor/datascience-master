---
title: Audio Event Detection and applications to bioacoustics 
date: 'December 2018'
author: 'Jon Nordby <jonnord@nmbu.no>'
abstract: |
    TODO: write the abstract!
    Fo
    Fo
    Fo
    Bar
---



## Testing
This is a reference test (@pizza2000identification).

focus on audio event detection and a review methods applied on birdsong detection.

![This is the caption of the figure \label{mylabel}](./plot.png)

This is a referene to \ref{mylabel}.

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

### Sources of sound

Biotropy
Anthrophy


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

# Localization
Where in the FOV is the sound coming from.
Requires multiple microphones.
Spatial segmentation.

Where did the gunshot come from?
Detect poachers in a forest.

## Feature representations
Criterias for good features
Keep relevant info, remove irrelevant.
Robust against variations


Normalization

### Low-level features
spectral center, spectral slope etc

Standard low-level (SLL) signal parameters, includes: (1) root-mean-
square (RMS) level, (2) spectral centroid, (3) bandwidth, (4) zero-crossing rate, (5) spectral roll-off
frequency, (6) band energy ratio, (7) delta spectrum magnitude, (8) pitch, and (9) pitch strength

FEATURES FOR AUDIO CLASSIFICATION. Jeroen Breebaart. 2.1.1 Low-level signal parameters. 

Spectral flatness.
Spectral envelope. N-channel smooth approximation of spectrogram.

"Normalizing features across time avoids bias towards high-range features"

http://www.nyu.edu/classes/bello/MIR_files/timbre.pdf

Autocorrelation. Self-similarity

### Time-frequency representations
STFT, windowing
filter-banks. Constant-Q. Fourier transform
mel-spectrogram
MFCC

delta, lag/lead frames
Summarizations
first-order, second-order statistics
Texture windows
Bag-of-words. Ignores temporal order

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
* Scale Invariant Feature Transform (SIFT)
* Histogram of Oriented Gradients (HOG) 
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


# References

