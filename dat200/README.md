
# References

* [Feature Crossing](https://developers.google.com/machine-learning/crash-course/feature-crosses/crossing-one-hot-vectors)
Creating new (non-linear) features by combining existing features, in pairs or more. 
* [FeatureTools](https://docs.featuretools.com/index.html), automatically generating features from datasets. Python library.
* [Feature engineering Guide](http://adataanalyst.com/machine-learning/comprehensive-guide-feature-engineering/).
Lots of relevant things, well explained

CA02

* http://adataanalyst.com/kaggle/kaggle-tutorial-kobe-bryant/, good plots for showing, some cleaning steps
* http://adataanalyst.com/kaggle/kaggle-tutorial-using-kobe-bryant-dataset-part-3/
good pairplots, shows non-linear effects in loc_y/x
using timeRemaining instead of timeplayed - same?
195 has a more accurate shot_distance calculation
* http://adataanalyst.com/kaggle/kaggle-tutorial-using-kobe-bryant-dataset-part-4/
lots of attempts at shots last seconds, with much worse accuracy

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

Implement at least inference/prediction part of an algorithm for microcontroller.
Training phase would then run on a standard computer, using existing tools as much as possible.

### Online learning

It is also desirable to learn on-the-fly.
First level is hybrid systems where new samples is used to tune/improve a pre-trained model.
More advanced is on-line training which can automatically detect new classes.
Get closer to typical Artificial Intelligence field, since now have an intelligent agent able to learn on its own.

Hybrid learning, adaptive machine learning, progressive learning, semi-supervised learning.

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
* [Embedded Learning Library](https://github.com/Microsoft/ELL) by Microsoft.
Set of C++ libraries for machine learning on embedded platforms. Includes code for kNN, RandomForest etc.
Also has some node-based dataflow system in place it seems. JavaScript and Python bindings.

Books

* [Learning in Embedded Systems](https://mitpress.mit.edu/books/learning-embedded-systems), May 1993.

### On-edge processing cases

ML-learning tasks

* Classification
* regression
* predicion
* Outlier/novelty/anomaly detection

More valuabel when

* Local response needed
* Adaptable response needed. Over time, in context
* Low/predictable latency needed
* Sending raw sensor data has privacy implications.
Audio, video
* Unreliable connection
* High bandwidth sensor input.
Audio, video, IMU
* Low bandwidth algorithm output
* Events of interest are rare
* Low energy usage needed
* Full/raw sensor data is not valuable to store
* Low cost sensor unit

Keywords

* Wireless Sensor networks

Example usecases

* Predictive maintenance, using audio/vibration data
* Activitity detection for people, using audio/accelerometer data. Assistive tech, medical
* Appliance disaggregation, using aggregated power consumption data. "Non-Intrusive Load Monitoring" (NILM)
* Anomaly/change detection for predictive maintenance, using audio/vibration data, or electrical data
* Gesture recognition as human input device, using accelerometer/gyro data.
* Speech/command recognition as human input device, using microphone. Keyword detection
* ? Estimating battery lifetime of sensor
* ? Battery saving by normally sending day/week aggregates, and on event detection send data directly
* ? Quality monitoring in production line, using ?? data
* Health status of animals via activity detected using accelerometer
* Monitoring eating activity using accelerometer [1](https://www.sciencedirect.com/science/article/pii/S0010482515000086)
* Environmental monitoring, using microphone to detect unwanted activity like cutting down trees
* Adaptive signalling and routing for wireless transmission

Techniques

* Decision trees, random forests
* Naive Bayes
* Binary Neural networks
* SVM. Linear/kernel
* kNN. Challenge: Storage/memory use
* k-means clustering.
* PCA.
* Model-based approaches
* Q-learning (reinforcement learning)

#### References
* [Machine Learning in Wireless Sensor Networks: Algorithms, Strategies, and Applications](https://arxiv.org/pdf/1405.4463.pdf). 2013.
Review and summary of many papers. Discusses dynamic routing, local data aggregation, collaborative/distributed data processing, event detection, positioning. PCA for data compression, plus Compressive sensing, Expectation-Maximimization.
"80 percent of nodes energy consumed when sending data".

#### Hardware

* Microcontroller with connectivity. Ex: ESP8266/ESP32 with WiFi/BLE. Or some ARM Cortex M
* Microphone. [Analog](https://www.digikey.co.uk/products/en/audio-products/microphones/158?k=microphone&k=&pkeyword=microphone&FV=ffe0009e%2Ca40062&quantity=0&ColumnSort=1000011&page=1&stock=1&nstock=1&datasheet=1&pageSize=25) [I2S](https://www.digikey.co.uk/products/en/audio-products/microphones/158?FV=ffe0009e%2Ca4027e&quantity=&ColumnSort=1000011&page=1&k=microphone&pageSize=25&pkeyword=microphone)
* IMU
* Piezo vibration sensor?
* SPI ADC, [MCP3002](https://www.digikey.no/product-detail/en/microchip-technology/MCP3002T-I-SN/MCP3002T-I-SN-ND/319415)

#### Random Forests
Some work in [emtrees](https://github.com/jonnor/emtrees)

#### Extra trees

Like random forest (of decision trees) but even simpler.
Often performing just as good or even slightly better on classification tasks.

Resources

* [libextratrees](https://github.com/paolo-losi/libextratrees/), C implementation. Clean code.
Uses dynamic allocation and floats.
* Standalone example of Random Forest implementation in Python, with results.
[1](https://machinelearningmastery.com/implement-random-forest-scratch-python/), shows the principles well.
* [How are feature_importances in RandomForestClassifier determined?](https://stackoverflow.com/a/15820105)
* [Current peak based device classification in NILM on a low-cost embedded platform using extra-trees](http://ieeexplore.ieee.org/document/8284200/). Published November 2017. Ran on a Rasperry PI 3, classification of an event was done in 400ms. Events were detected based on a current draw profile of 1 second / 60 current peaks. No details on the code used, probably a standard toolset like Python/sklearn.
Possibly a testcase.

#### Naive Bayes

Simple and very effective at some classification problems.

Coefficients to store. For Gaussian 2xNxM: 2=mean,stddev. N classes and M 
Prediction: multiply probabilities together.
Probably need to do log trick to avoid underflow issues.
Fixed point representation should have domain [0 1.0].

Naive Bayes classifier implementations
 
* Python. Discrete Naive Bayes. [AppliedMachineLearning](https://appliedmachinelearning.wordpress.com/2017/05/23/understanding-naive-bayes-classifier-from-scratch-python-code/)
* Gaussian Naive Bayes in Python. 
[MachineLearningMastery](https://machinelearningmastery.com/naive-bayes-classifier-scratch-python/)
* Discrete Naive Bayes in C++ [codeforge](http://www.codeforge.com/read/387365/BayesianClassifier.cpp__html)
* Discrete,Gaussian,Multinomial,etc in Python [scikit-learn](https://github.com/scikit-learn/scikit-learn/blob/master/sklearn/naive_bayes.py)

#### Binarized Neural Networks

Bitwise arithmetic packed into integer representations.
Decreases weights storage drastically.
Implementable efficiently on constrained hardware (only fixed-point units).
Also called BNN, Binary Neutral Network, and XNOR neural network. 

* [Introduction](https://software.intel.com/en-us/articles/accelerating-neural-networks-with-binary-arithmetic)
* Paper: [Binarized Neural Networks: raining Neural Networks with Weights and Activations Constrained to +1 or −1](https://ai.intel.com/wp-content/uploads/sites/53/2017/06/1602.02830v3.pdf)
* eBNN. Paper: [Embedded Binarized Neural Networks](http://www.eecs.harvard.edu/~htk/publication/2017-ewsn-mcdanel-teerapittayanon-kung.pdf).
Runs MINST with 95% accuracy in under 50ms on Intel Curie. 32bit, 16KB RAM, 32MHz.
Reorders computation compared to BNN to only need a single floating point intermediate value, instead of one per layer.
[Code](https://gitlab.com/kunglab/ddnn). Python module which generates a C header, plus C library.
* [Deep Learning Binary Neural Network on an FPG](https://web.wpi.edu/Pubs/ETD/Available/etd-042717-145953/unrestricted/sredkar.pdf).
332,164 images per second with 85% accuracy on CIFAR-10.
* [Accelerating Binarized Neural Networks: Comparison of FPGA, CPU, GPU, and ASIC](http://jaewoong.org/pubs/fpt16-accelerating-bnn.pdf)

#### Audio

Existing work
* [ML-KWS-for-MCU](https://github.com/ARM-software/ML-KWS-for-MCU/tree/master/Deployment).
Speech recognition on microcontroller.
Neural network trained with TensorFlow, then deployed on Cortex-M7, with FPU.
Using CMSIS NN and DSP modules.
* [CASE2012](http://elaf1.fi.mdp.edu.ar/electronica/grupos/lac/pdf/lizondo_CASE2012.pdf).
Implemented speech recognition using MFCC on 16-bit dsPIC with 40 MIPS and 16kB RAM.
A Cortex-M3 at 80 MHz should have 100+MIPS.


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
* [Machine Learning for Audio, Image and Video Analysis](http://www.dcs.gla.ac.uk/~vincia/textbook.pdf).

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
* [Speech Commands Data Set](https://www.kaggle.com/c/tensorflow-speech-recognition-challenge/data).
Kaggle competition required submissions to run in below 200ms on a Raspberry PI3.

# Vibration analysis
Often used for 'machine condition' analysis, especially for rotating machines.

* [Fundamentals of Vibration Measurement and Analysis Explained](http://www.lifetime-reliability.com/free-articles/maintenance-management/Fundamentals_of_Vibration_Measurement_and_Analysis_Explained.pdf), explains how to capture data, process it to commonly used features etc
* [Beginning Vibration Analysis](http://www.vibranalysis.co.za/ctc/pdf/pubTechPapers/01-Beginning%20Vibration%20Analysis.pdf),
page 82+ shows data for some problematic cases

# Noise removal

* Denoising autoencoders. sDSA, stacked... [Theano tutorial](http://deeplearning.net/tutorial/SdA.html)
* mSDA, fast denoising autoencoder. [Applied to robot arm](http://fastml.com/very-fast-denoising-autoencoder-with-a-robot-arm/)

# Change detection
Novelity detection.
Anomaly detection.
Change point detection (mostly in time series).

* [Change point detection in time series data with random forests](https://www.sciencedirect.com/science/article/pii/S0967066110001073)
* [Two approaches for novelty detection using random forest](https://www.sciencedirect.com/science/article/pii/S0957417414008070)
