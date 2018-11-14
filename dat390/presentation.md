---
title: Audio Classification using Machine Learning
author: Jon Nordby <jonnord@nmbu.no>
date: November 15, 2018
---

# Introduction

1 minute

## Goal

> a machine learning practitioner
> 
> without prior knowledge about sound processing
> 
> can solve basic Audio Classification problems

## Assumed knowledge

* Machine learning fundamentals
** Supervised vs unsupervised. Common methods
* Basic signal processing
** Sampling, Frequency Response, Fourier Transform

## Study material

* "Computational Analysis of Sound Scenes and Events". Virtanen,Plumbley,Ellis, 2018
* "Human and Machine Hearing - Extracting Meaning from Sound". Richard F. Lyon, 2018 (rev2)
* DCASE2018 Bird Audio Detection challenge
* 50+ papers on Audio Event Detection etc.

# Machine Hearing

5 minutes

## Examples

Various usecases and tasks that Machine Hearing can be applied to.

## Speech Recognition
What is this person saying?

<audio controls src="woodpecker2.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

::: notes

Easy, most people have a very trained ear for speech.

:::

## Musical key classification
What key is this music in?

<audio controls src="woodpecker2.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

::: notes
Quite hard, requires musical training.

Piano Chord Progression (F - 120 BPM).wav
https://freesound.org/people/Xinematix/sounds/261324/

:::

## Audio Scene
What kind of place is this from?

<audio controls src="woodpecker2.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

::: notes

Playground outdoors
https://freesound.org/people/miksmusic/sounds/169043/

Restaurant
https://freesound.org/people/soundtracvkradio/sounds/394678/

Context-aware smart devices. In the home, smartphones.

:::

## Medical diagnostics
Is this a healthy heart?

<audio controls src="woodpecker2.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

::: notes

Hard, requires very well trained doctor.
Serious, high consequences for wrong prediction.

Many examples of various innocent and unhealthy heart sounds, explained.
https://www.easyauscultation.com/heart-sounds-audio

Heart Sounds and Heart Murmurs, Animation.
https://www.youtube.com/watch?v=dBwr2GZCmQM
Very clear explanation of normal and various abnormal heart sounds.

Heart classification challenge.
http://www.peterjbentley.com/heartchallenge/

:::

## Industrial monitoring
Is this machine operating normally?

<audio controls src="woodpecker2.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

::: notes

wornoutballbearing.wav
https://freesound.org/people/vumseplutten1709/sounds/211087/

:::

## Ecoacoustics
What kind of animal is this?

<audio controls src="woodpecker2.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

::: notes

https://freesound.org/people/Benboncan/sounds/67261/
Ecoacoustics. Measuring biodiversity.

:::

## Established subfields

- Speech Recognition
- Music Information Retrieval
- **Sound Scenes and Events**


# Brief primer on sound

5 minutes

## Acoustic model
Sources. Channel. Receiver.

## Audio Mixtures
A sound seldom appears alone.
Sometimes separable in time-frequency.
Many sounds have patterns in frequency. Eg voice formants

## Channel effects
Noise
Frequency response
Reverberation

## Human hearing

Approx 20Hz - 20kHz.
Binaural

A non-linear system

* Loudness is not linear with sound pressure
* Loudness is frequency dependent 
* Compression. Sensitivity lowered when loud
* Masking. Close sounds can hide eachother

## Digitizing sound

Microphones
Analog to digital conversion

## Time-domain
Linear, logarithmic. Amplitude versus power.

## Frequency-domain
Fourier Transform.

## Spectrograms
Time-frequency domain.

Tradeoff. Time vs frequency resolution



# A practical example: Birdsong


AUDIO. Is there a bird present in this recording?
Binary.

AUDIO. What species is this bird?
Requires trained expert. Memorizing bird species and their sound.


# Problem formulations

5 minutes

## Classification

* Binary. Bird? yes/no
* n-way. Which species is this?

## Event detection
Return time something occurred.

* "Bird singing started", "Bird singing stopped"
* Classification-as-detection. Classifier on short time-frames
* Monophonic: Returns most prominent event

::: notes

Great summary of Sound Event Detection progress, 2010-2017.
f1 score 8.4% -> 70%. MFCC+HMM+Viterbi -> MFCC+HMM+NMF -> mel+DNN -> mel+CRNN 
http://www.cs.tut.fi/~heittolt/research-sound-event-detection0

:::

## Audio segmentation

Return sections of audio that contain desired class of audio.

* Ex: based on Event Detection time-stamps
* Pre-processing to specialized classifiers

## Source separation

Return only the birdsong from the input audio.

* Blind-source separation
* Model-based separation

## Overlapping events

* Bird singing yes/no, Human talking yes/no
* Bird A singing y/n, Bird B singing y/n

Multi-label classification, or separate classifiers.

## Tagging
Multi-label classification problem

## Our case

Data from DCASE2018 Bird Audio Detection challenge.

* 10 second clips
* Has bird? yes/no (binary)
*  (weakly annotated)

::: notes

How much or where in clip bird occurs = unknown.
Weakly annotated.

:::

# Feature extraction

## Example

::: notes

10 second clip
Audio                Features            bird yes/no
-> [Feature Extraction] -> [Classifier] -> 

:::

## Desirable traits
What is needed for good audio classification?

* Volume independent
* Robust against mixtures of other sounds
* Handles (small) variations in frequency
* Can exploit frequency modulation
* Can exploit temporal patterns
* Compact. Little redundancy

::: notes

Exact traits wanted is somewhat problem/sound dependent.

:::

## Time domain

Hard to discriminate sounds in realistic settings:

* Samples are highly correlated
* Frequency information mixed with temporal
* Sensitive to noise

Actively researched using very strong models and large datasets.

::: notes
IMAGE. Waveform

:::

## Low-level features

Calculated from time-domain data.

## Framing
overlap, window function

## Summarizations

* min,max
* mean,std
* Kurtosis,skew

equations

## Texture windows


## mel-spectrogram
mel-scale filters
Perceptually motivated
Reduces number of banks

## Mel-filter Cepstrum Coefficients (MFCC)
MFCC.
DCT
Speech

More compact representation.
De-correlated, important for non-linear methods.
With strong classifiers, not not as good as mel-spectrograms.

## Feature learning

## Advanced features

* Wavelet filterbanks
* Scattering Transform


# Classifiers

## General purpose

* Linear methods. SVM, Logistic Regression
* Non-linear. Kernel SVM. RandomForest

## Un-usual methods

* Gaussian Mixture Models (GMM)
* Hidden Markov Model (HMM)
* Non-negative Matrix Factorization (NMF)

## Deep learning



# Results

## Own results 

Preliminary

## DCASE2018 challenge

# Summary

If you have an Audio Classification problem.

## Problem formulation

## Feature representation

Try first **log mel-spectrogram**. MFCC as fallback

## Classifier

Try Convolutional Neural Networks (or RCNN) first.

1) Alternative: Shallow convolutions + RandomForest
1) Last resort: GMM+HMM+SVM, on MFCC summarizations


# Questions?



# Bonus

Anything that did not fit...


## Preprocessing/normalization

## Little data?

Use Transfer Learning or Unsupervised Kernel Learning.
Use Data Augmentation.
