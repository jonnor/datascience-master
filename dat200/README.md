
# References

* [Feature Crossing](https://developers.google.com/machine-learning/crash-course/feature-crosses/crossing-one-hot-vectors)
Creating new (non-linear) features by combining existing features, in pairs or more. 
* [FeatureTools](https://docs.featuretools.com/index.html), automatically generating features from datasets. Python library.

# Ideas

## Distributed hyperparameter search

Existing work

* [Dask GridSearchCV](https://www.kdnuggets.com/2017/05/dask-searchcv-distributed-hyperparameter-optimization-scikit-learn.html)
* [Apache Spark GridSeachCV](https://databricks.com/blog/2016/02/08/auto-scaling-scikit-learn-with-apache-spark.html)
* Hard to do on AWS lambda, because sklearn is bigger than Lambda code limit of 50MB

Could do something similar as a Python module, for instance using Heroku API.

Job inputs:
- (git revision)
- Model hyperparameters
- test train/splits

Job outputs:
- inputs
- git revision
- training accurancy
- testing accuracy
- classification outputs (on compete)

Job generator
- can run locally

Job output saver
- can run locally

Autoscaler
- can run locally


## Machine learning on embedded/microcontroller

Implement inference/prediction part of an algorithm for microcontroller.
Using sklearn for the training, serialized and then deserialized again.
DecisionTreeClassifier?

### References

Existing work

* [Resource-efficient Machine Learning in 2 KB RAM for the Internet of Things](https://www.microsoft.com/en-us/research/wp-content/uploads/2017/06/kumar17.pdf). Describes Bonsai, a part of Microsoft Research Indias open-source [EdgeML](https://github.com/Microsoft/EdgeML).
Bonsay is tree-based algorithm. Relatively powerful nodes to enable short trees (reduce RAM usage).
Uses sparse trees, and the final prediction is a sum of all the nodes (path-based).
Optimization: `tanh(x) ≈ x if x < 1 and signum(x) otherwise`. Can run on Atmel AVR8
* [ProtoNN: Compressed and Accurate kNN for Resource-scarce Devices](http://manikvarma.org/pubs/gupta17.pdf).
k-Nearest Neighbor implementation. Can run on Atmel AVR8
* [Machine Learning for Embedded Systems: A Case Study](http://www.cs.cmu.edu/~khaigh/papers/2015-HaighTechReport-Embedded.pdf)
Support Vector Machines. Target system used for auto-tunic a mobile ad-hoc network (MANET) by
earns the relationships among configuration parameters. Running on ARMv7 and PPC, 128MB+ RAM.
Lots of detail about how they optimized an existing SVM implementation, in the end running 20x faster.

### On-edge processing cases

ML-learning tasks

* Classification
* regression
* predicion
* Outlier/novelty/anomaly detection

More valuabel when

* High bandwidth sensor input.
Audio, video, IMU
* Rare events
* Low bandwidth algorithm output
* Unreliable connection
* Low cost senor unit
* Low energy usage needed
* Low/predictable latency needed
* Local response needed
* Sending raw sensor data has privacy implications.
Audio, video

Example usecases

* Predictive maintenance, using audio/vibration data
* Activitity detection for people, using audio/accelerometer data

# Audio classification

* [Audio classification overview](http://www.nyu.edu/classes/bello/ACA_files/8-classification.pdf)
Criterias for good features,
PCA/LDA for dimensionality reduction. Sequential forward/backward selection
* [Environmental sound recognition: a survey](https://www.cambridge.org/core/services/aop-cambridge-core/content/view/S2048770314000122) (2014).
Mentiones MPEG-7 based features, efficient and perceptual.
* [Dolph-Chebyshev Window](http://practicalcryptography.com/miscellaneous/machine-learning/implementing-dolph-chebyshev-window/),
good window function for audio. C reference implementation.
* [Voice Activity Detection, tutorial](http://practicalcryptography.com/miscellaneous/machine-learning/voice-activity-detection-vad-tutorial/)
Using 5 simple features.

## Tools
* [pyAudioAnalysis](https://github.com/tyiannak/pyAudioAnalysis/wiki/3.-Feature-Extraction).
Chroma Vector, Mel Frequency Cepstral Coefficients, Zero Crossing Rate, Spectral Centroid...

## Datasets
* [Urbansound-8k](https://serv.cusp.nyu.edu/projects/urbansounddataset/urbansound8k.html).
8k samples, 10 classes. Compiled from freesound.org data
* [ESC-50: Dataset for Environmental Sound Classification](https://github.com/karoldvl/ESC-50).
2k samples, 40 classes in 5 major categories. Compiled from freesound.org data
* [NOIZEUS: A noisy speech corpus for evaluation of speech enhancement algorithms](http://ecs.utdallas.edu/loizou/speech/noizeus/)
30 sentences corrupted by 8 real-world noises. 

