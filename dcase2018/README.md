# DCASE2018 bird detection

DCASE2018 challegne: [Bird audio detection](http://dcase.community/challenge2018/task-bird-audio-detection)

## Goals

* Online classifier running in real-time on low-power ARM Cortex M4F,
with high enough classification rate to be useful as recording trigger
* Submit for DCASE18 challenge. Classification, code, technical paper. 
* Submit scientific paper for DCASE18. July 31

## TODO

First model

* Extract classic features for dataset(s). MFCC,?
* Review literature for promising tree/forest based approaches
* Setup basic sklearn pipeline/workflow
* Understand how GMMs work
* Try replicate iitMandi CASE17. GMM+SVM classifier

Hardware constraints

* Try to run MFCC feature calculation on M4F
* Try to run Random Forest classifier on M4F with (precalculated) MFCC features
* What does a GMM require?

## Background


### Feature representations

* MFCC. Spectrogram. Frames over time
* Chroma. 
* Harmonic-percussive-residual source separation. Especially for music.

### Blind source separation

* Subspace based approaches. Aims to partition the mixture space into source dominant spaces.
Learns the source specific filters/dictionaries/basis that span those spaces.
Examples.
Principal Component Analysis (PCA),
Independent Component Analysis (ICA),
Subspace analysis
* Decomposing and grouping approaches.
The mixture spectrogram is divided into small time-frequency bins
and individual sources are then recovered using a masking.
Masking is is learned using the acoustic properties of the sources.
Examples:
Adaptive Wiener filtering/rules.
Ideal Binary Masking (IBM),
Computational Auditory Scene Analysis (CASA)
* Model based approaches.
Models of the sources are built/learned.
Examples: Non Negative Matrix Factorization (NMF),
Non Negative Sparse Coding (NNSC)

Singular Value Decomposition (SVD),
Eigen Value Decomposition (EVD)
Spectral decomposition
Factorial HMM


### Temporal coherence

Speech has strong correlation (2nd order dependency) among adjacent Time-Frequency (T-F) slots in both time
and frequency. A T-F slot can be described as a pixel (or a set of adjacent pixels) in a power
spectrogram.

! Want to utilize this to classify, but many algorithms don't natively.

### Non Negative Matrix Factorization
Non-negativity constraint of NMF only allows additive combinations (not subtractive),
in contrast to ICA/PCA.
Leads to a parts-based representation.
Recommended to impose constraints like sparseness, orthogonality, or smoothness to get more interesting basis vectors.

Many factorization approaches. Gradient descent. Multiplicative update rules, easy to implement.
Semi-supervised method possible with Schmidt2007 "Wind Noise Reduction using Non-negative
Sparse Coding".


### Noise types
Biophony, geophony, and anthrophony

* Biophony refers to any sound produced by biological agents: in the forest major biophonies are birds, insects, frogs/toads, and mammals.
Because we are only interested in acoustic activity of birds, all other biological sounds are categorised as noise
* Geophony refers to all non-biological, natural sounds in the environment such as
wind and its effect on trees, rain, thunder, and running water.
* Anthrophony refers to all sound generated from human-made machines such as
aircraft, vehicles, wind turbines, and the recording device (microphone, recorder hum)

Characterises the noise according to its properties into:

* White noise has equal energy at all frequencies, meaning that the power spectrum is flat.
In practice, noise is only white over a limited range of frequencies.
While not all white noise is Gaussian, natural white noise can often be modelled as such.
* Coloured noise shows a non-uniform power spectrum, with the energy generally decreasing in proportion to the frequency f.
Common types of coloured noise include pink (power ∝1f) and brown (power ∝1f2).
* Impulsive noise refers to sudden click like sounds that last for a very short period of time (milliseconds), such as switching noise.
An ideal impulse generates a horizontal line in the power spectrum because these sharp pulses contain all frequencies equally.
* Narrow-band noise such as microphone hum shows a small range of frequencies.
* Transient noise is a burst of noise that occurs for some time, and then disappears.

### Noise reduction
Time domain
Frequency domain
Spectrogram domain

Spectral median filtering

## Ideas

Birdsong is quite melodic. Could melody-oriented features perform better than classic spectogram?

Typical recordings also have a lot of other sounds.
For instance rain,wind (random noise-like).



Birdsong denoising
Birdsong source separation
bioacoustic denoising 


[Bird Audio Detection: tips on building robust detectors](http://machine-listening.eecs.qmul.ac.uk/2016/11/bird-audio-detection-tips-on-building-robust-detectors/)
Filtering.
Noise reduction.
Data normalization. Amplitude normalized. Spectral whitening. Linear predictive coding filtering.
Representation. Default: Spectrogram, MFCC. Not getting good improvements by changing?
Data augmentation.
Self-adaptation.
Regularisation.
Combining models.


[Bird Audio Detection: baseline tests – and the problem of generalisation](http://machine-listening.eecs.qmul.ac.uk/2016/10/bird-audio-detection-baseline-generalisation/). First baseline of MFCCs and GMM method generalizes very badly to samples from unseen training sets.
Second baseline of spherical k-means feature learning, followed by a Random Forest classifier still managed 80% on unseen training sets.

[Automatic large-scale classification of bird sounds is strongly improved by unsupervised feature learning](https://peerj.com/articles/488/)
Inspired by techniques that have proven useful in other domains.
Compare twelve different feature representations derived from the Mel spectrum, using four large and diverse databases of bird vocalisations. Classified using a random forest classifier.
"in our classification tasks, MFCCs can often lead to worse performance than the raw Mel spectral data from which they are derived"
"unsupervised feature learning provides a substantial boost over MFCCs and Mel spectra without adding computational complexity after the model has been trained"

[Bird detection in audio: a survey and a challenge](https://arxiv.org/abs/1608.03417). D.Stockwell, 2016.
Usecases: Unattended monitoring, prefiltering step before other automatic analyses such as bird species classification.
Detection types:
Presence/absence in a given sound clip: a detector outputs a zero if none of the target species are detected, and a one otherwise.
Monotonic segmentation. Partition the time axis into positive and negative regions. Analogous to voice activity detection (VAD).
Methods:
Energy thresholding.
Spectrogram cross-correlation.
Hidden Markov Models.
Template matching with Dynamic Time Warping.
Open question whether the various different approaches (for single species detection)
can simply be aggregated under a meta-algorithm to produce species-agnostic output.
Sinousoidal tracks.

[A joint separation-classification model for sound event detection of weakly labelled data](https://arxiv.org/abs/1711.03037)


[An FPGA-Based WASN for Remote Real-Time Monitoring of Endangered Species: A Case Study on the Birdsong Recognition of Botaurus stellaris](http://www.mdpi.com/1424-8220/17/6/1331). Wireless Acoustic Sensor Networks (WASN).

[Design and Implementation of a Robust Acoustic Recognition System for Waterbird Species using TMS320C6713 DSK](https://www.igi-global.com/gateway/article/176715). A. Boulmaiz. International Journal of Ambient Computing and Intelligence (IJACI), 2017. 
Tonal region detector (TRD) using a sigmoid function.
Mel Frequency Cepstral Coefficients, Spectral Subtraction. Support Vector Machine.

[Robust acoustic bird recognition for habitat monitoring with wireless sensor networks](https://link.springer.com/article/10.1007%2Fs10772-016-9354-4). Amira Boulmaiz. International Journal of Speech Technology, September 2016.
Tonal region detector (TRD) using sigmoid function is proposed.
Once the tonal regions in the noisy bird sound are detected, the features gammatone teager energy cepstral coefficients (GTECC).
TRD–GTECC.
Quantile-based cepstral dynamics normalization (QCN) for noise reduction. Extending ideas from computationally inexpensive normalizations of
spectral subtraction (SS), cepstral mean and variance (CMVN), and recently introduced cepstral gain normalization (CGN).
Compares MFCC, perceptual-MVDR (PMVDR) and power-normalized cepstral coefficients (PNCC).
Using different feature normalizations; SS, CMVN, CGN, and QCN.
GTECC had the best recognition rate, while being slightly less computationally intensive than MFCC.

[librosa: Vocal separation](http://librosa.github.io/librosa/auto_examples/plot_vocal_separation.html#sphx-glr-auto-examples-plot-vocal-separation-py). Simple technique for separating vocals (and other sporadic foreground signals) from accompanying instrumentation.
Foreground/background separation.

[Vocal source separation using spectrograms and spikes, applied to speech and birdsong](https://www.research-collection.ethz.ch/handle/20.500.11850/175085). PhD thesis, ETH Zurich, 2017.
Audio source separation methods (ASS). Monaural source separation (MSS) special-case of ASS where only a single mixture is observed.
Spectral subtraction, Wiener filtering, and subspaces used in speech enhancement.
Ideal Binary Mask (IBM) used in auditory scene analysis (CASA).
Deep Neural Networks have been used to learn binary and soft masks, with state of art reslults.
This thesis presents novel linear and non-linear methods to address MSS in a supervised scenario

Three linear methods proposed in the thesis are:
1) Eigenmode analysis of covariance difference (EACD).
This method identifies spectro-temporal features associated with large
variance for one source and small variance for the other source.
2) Maximum likelihood demixing (MLD).
In this method, the mixture is modelled as the sum of two Gaussian signals
and maximum likelihood is used to identify the most likely sources.
3) Suppression-regression (SR).
Autoregressive models trained to reproduce one source but suppress the other.
4) A non-linear method called Multi-layered Random Forest (MLRF).
MLRF is an ensemble method that trains decision trees for each frequency band.
Given a mixture spectrogram, these trees classify individual T-F bin as belonging
to one of the speakers thus returning an estimate of the IBM.
An estimated IBM in a given layer is used to train a RF classifier in the next higher layer.
Outperforms a deep learning based method in terms of SNR of reconstructed audio.

[Birdsong Denoising Using Wavelets](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4728069/).
Using wavelets as alternative to bandpass. Not considering any source separation techniques.
Wavelet avoids the fundamental tradeoff between temporal and frequency resolution in Fourier spectrogram.
Nice background info on birdsong, including typical characteristics.

[Blind Source Separation With Non-stationary Mixing Using Wavelets](http://www.robots.ox.ac.uk/~sjrob/Pubs/addison_roberts.pdf)
ICA that uses wavelet representation. Uses a sliding-window ICA, assuming that mixing process changes slowly enough wrt window size.
"however seen that despite the best efforts of our proposed algorithm there are still difficulties with the permutation problem.
The choice of window size is also arbitrary". Proposes a Baysian framework as further work

[librosa: Harmonic-percussive source separation](https://librosa.github.io/librosa/auto_examples/plot_hprss.html?highlight=harmonic).
Including a margin-based approach which also separates out noise.

[librosa: enhanced Chroma](http://librosa.github.io/librosa/auto_examples/plot_chroma.html#sphx-glr-auto-examples-plot-chroma-py).
Using harmonic-percussive separation, non-local filtering and median-based filtering.


[muda: Python library for augmenting annotated audio data](https://github.com/bmcfee/muda)
