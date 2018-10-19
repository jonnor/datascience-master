---
title: Machine Hearing
author: Jon Nordby <jonnord@nmbu.no>
date: November 16, 2018
---

# Goal
After reading this report

> a machine learning practitioner
> without prior knowledge about sound or digital signal processing
> shall be able to solve basic audio event detection problems.

# Format
30 minutes presentation. 15 minutes questions.

* One picture per slide
* 30 slides

# Outline
* Introduction: Examples of usecases/applications
* Introduction: Scope,focus. Out-of-scope
* Background: Sound
* Background: Problem formulations
* Feature representations
* Case study


# Usecases and Problem formulations

# Classification

## Audio Scene Classification
AUDIO.
What kind of place is this from?

## Musical genre classification
AUDIO. What genre is this?

## Open-ended classification
Classification problems often formulated as a closed-set. 
But in reality this might be too limiting.
Previously unseen birds may migrate into an area.
New musical genres are invented all the time.
Challenge: Creating a taxonomy, or consistent ontology

## Musical key classification
AUDIO. What key is this music in?
Quite hard, requires musical training.

## Heart auscultation
AUDIO. Is this a healthy heart?
Hard, requires very well trained doctor.
Serious, high consequences for wrong prediction.

AUDIO. Does this machine have a problem?

## Animal classification
AUDIO. What kind of animal is this?

Could be used for photo-trap triggering.
Take pictures / record video when lions are present, not when hyenas are.

## Bird detection

AUDIO. Is there a bird present in this recording? Binary

AUDIO. What species is this bird? Requires memorizing bird species and their sound, but not so hard.



# Event detection
AUDIO: Hold hand up when there is a bird, keep it low when no bird.

# Overlapping events
AUDIO: Raise your hand

## Tagging

# Speech Recognition
AUDIO. What is this person saying? Easy, we all have a very trained ear for speech.

## Diarization
Speaker diarization.
AUDIO. What do each of the persons here say?
In-order.

# Localization
Where in the FOV is the sound coming from.
Requires multiple microphones.
Spatial segmentation.

Where did the gunshot come from?
Detect poachers in a forest.

## Continious monitoring
All human hearing approaches requires a (trained) human to be present and alert.
 

# Digital sound
Microphones
Analog to digital conversion

# Loudness
Logarithmic

# Audio Mixtures
A sound never appears alone

# Framing
overlap, window function

# Low-level features

# Summarizations
equations 

# Spectrograms
Time-frequency
Short-time Fourier Transform (STFT)

# mel-spectrogram
mel-scale filters
Perceptually motivated
Reduces number of banks

# Mel-filter Cepstrum Coefficients (MFCC)
MFCC.
DCT
Speech

More compact representation.
Does not perform as well as mel-spectrograms

# Other filterbanks
Bark scale
Constant-Q

In practice does not make much difference compared to mel-spectrogram

# Wavelet filterbanks

# Scattering Transform

# Feature learning

# Case study: Detection of birdsong
