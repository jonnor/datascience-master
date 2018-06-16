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

