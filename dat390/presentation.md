---
title: Audio Event Detection using Machine Learning
author: Jon Nordby <jonnord@nmbu.no>
date: November 15, 2018
---

# Introduction

## Goal

> a machine learning practitioner
> 
> without prior knowledge about sound processing
> 
> can solve basic Audio Event Detection problems

## Machine Hearing subfields

- Speech Recognition
- Music Information Retrieval
- **Sound Scenes and Events**

# Examples of Machine Hearing tasks

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

# What is sound?

## Acoustic waves
 
## Digitizing sound
Microphones
Analog to digital conversion

## Waveform

## Loudness
Logarithmic

## Spectrograms
Time-frequency domain


## Audio Mixtures
A sound never appears alone

## Channel effects
Frequency reponse
Reverberation


# Feature representations

## Time domain

Interesting signals very sparse in this domain.
Lots of noise.
All mixtures are 'on top of eachother'.

Open research problem.
1D Recurrent Neural Networks.

## Framing
overlap, window function

## Low-level features

## Summarizations
equations 

## Spectrograms
Time-frequency
Short-time Fourier Transform (STFT)

## mel-spectrogram
mel-scale filters
Perceptually motivated
Reduces number of banks

## Mel-filter Cepstrum Coefficients (MFCC)
MFCC.
DCT
Speech

More compact representation.
Does not perform as well as mel-spectrograms

## Other filterbanks
Bark scale
Constant-Q

In practice does not make much difference compared to mel-spectrogram

## Wavelet filterbanks

## Scattering Transform

## Feature learning



# A practical example: Bird Detection


# Bird detection

AUDIO. Is there a bird present in this recording?
Binary.

AUDIO. What species is this bird?
Requires trained expert. Memorizing bird species and their sound.


# Problem formulations

## Classification

Weakly annotated. Don't know where in image

## Open-ended classification
Classification problems often formulated as a closed-set. 
But in reality this might be too limiting.
Previously unseen birds may migrate into an area.
New musical genres are invented all the time.
Challenge: Creating a taxonomy, or consistent ontology

## Event detection

## Overlapping events

## Audio segmentation

## Tagging
Multi-label classification problem

## Audio Source Separation

# Data augmentations

## Examples

Respects invariants/properties of features.
Modelling particular challenges.

- noise addition
- volume change
- frequency response change



