
# Master of Data Science

At Norwegian University of Life Sciences.

[Programme](https://www.nmbu.no/en/studies/study-options/master/master-of-science-in-data-science)

[Programme structure](https://www.nmbu.no/en/studies/study-options/master/master-of-science-in-data-science/programme-structure)

## Courses

### [INF121](https://github.com/jonnor/bike-sharing-oslo)

### [INF200](https://bitbucket.org/jonnor/inf200_jonnordby)

### [INF221](./inf221)

### [INF250](./inf250)

## Interesting specializations

Construction

* [TBA210 Building Structures II](https://www.nmbu.no/course/TBA210).
!Requires [TBA190](https://www.nmbu.no/course/TBA190)
* [TBA331 Building Performance Simulation](https://www.nmbu.no/course/TBA331)
!Requires TBA210
* [TBM250 Finite Element Method](https://www.nmbu.no/emne/TBM250)
* [TBM200 Material Science](https://www.nmbu.no/emne/TBM200)

Renewable energy

* [FYS375 Energy Technology](https://www.nmbu.no/emne/FYS375)
* [FORN200 Renewable Energy](https://www.nmbu.no/emne/FORN200)
* [FORN330 Renewable Energy analysis](https://www.nmbu.no/emne/FORN330)

Robotics

* [TEL240 Control Engineering and Automation](https://www.nmbu.no/course/tel240)
* [TEL250 Robotics and automation](https://www.nmbu.no/emne/TEL250)
* [TMPP350C Prosessregulation](https://www.nmbu.no/emne/TMPP350C)

## Ideas

* Image Processing/analysis using imgflo/GEGL
* Image Processing, [smart-cad](https://github.com/jonnor/projects/tree/master/smart-cad) prototyping
* From Jupyter to cloud-scale service using msgflo-python
* FBP/NoFlo execution for Jupyter. Kernel?. .fbp renderer, component/JavaScript evaluator
* Energy usage at Bitraf/c-base, relative to weather. Anomaly detection, reporting/monitoring
* CNC usage at Bitraf. How many of the jobs/parts can be done on a 60x120 cm workarea machine. Take gcode/dxfs from Dropbox, analyse
* Integrated data visualization for programming, [dataviz](https://github.com/jonnor/projects/tree/master/introspectable-computing/dataviz)
* Modelling of guitar distortion (non-linear). Using neural-network? 
* Automatic part layout of useful parts in remainder of cutsheet for CNC/laser. Automatic creation of cutlines to discard pieces smaller than w,h.
* Using machine learning to (assist in) reverse engineering protocols for machine control. Record input, output pairs. Change

## Publishing

Is TapeCore/Doverail/fabricatable-machines publishable in Open Hardware Journal?
https://openhardware.metajnl.com/about/#hardware-metapapers
Could I do the work as a 5-point self-organized topic (ie in robotics)?
Can/should I use NMBU as affiliation? Would they sponsor the publishing costs?
Would/should there be research uses at NMBU for testing practical application?

## References

* [The Elements of Statistical Learning](https://web.stanford.edu/~hastie/Papers/ESLII.pdf).
Recommended by Kristin T. regarding classification, regression methods.
* [Relationship between Ridge regression and PCA regression](https://stats.stackexchange.com/questions/81395/relationship-between-ridge-regression-and-pca-regression)
* [Relationship between SVD and PCA. How to use SVD to perform PCA?](https://stats.stackexchange.com/questions/134282/relationship-between-svd-and-pca-how-to-use-svd-to-perform-pca)
* [How Are Principal Component Analysis and Singular Value Decomposition Related](https://intoli.com/blog/pca-and-svd/)
* [pandas](http://pandas.pydata.org/), Python package for analysing large amounts of data
* [Clever Machines Learn How to Be Curious](https://www.quantamagazine.org/clever-machines-learn-how-to-be-curious-20170919/).
Rewarding agents for curiosity, exploring their environment and preferring actions which they can least confidently predict.
In this way being able to learn to perform tasks without predefined goal and associated cost function.
* [Feature Visualization: How neural networks build up their understanding of images](https://distill.pub/2017/feature-visualization/).
Starting with feeding in noise, and then optimizing the response for some parameter (neuron, channel, logits.).
Discusses this approach versus finding representative examples in a dataset.
Using a 'diversity' term to optimization objective that pushes multiple examples to be different from eachother.
Optimizing for pairs of neurons, interpolating between them.
Discussed multiple existing approaches to regularization of the model to give representative results.
Broadly classified into: Frequency penalization, transformation robustness, learned priors.
Can also use preconditioning: transformations on the gradient. Can give good results in fewer steps, and reduces high-frequency impact
Paper presentation: Nice semi-interactive image galleries where one can adjust parameters and it gives results at that combo.


## Interesting subproblems

Neural networks

* When used on images incredibly texture dependent. For instance cause vunerability to adverserial examples.
How to mitigate? Learning rate influences, higher rate, more noise.
* Seem that there is a lot of 'unecessary' complexity/information being encoded, that are irrelevant to the objective at hand.
How can one know how much complexity is needed to perform a particular function? How to estimate that it is well spent?
Are there information-theory approaches that can be applied?
