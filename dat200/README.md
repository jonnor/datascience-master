
# Assignments

##Digits classification
[Jupyter notebook](./assignment1/Handwriting.ipynb)

##Basket shots prediction
[Jupyter notebook](./assignment2/Basketball.ipynb)

##Titanic survival prediction
[Jupyter notebook](./assignment3/Titanic.ipynb)

# TODO

Exam prep

* Write list of learning goals. Methods, key concepts
* Answer potential exam questions
* Skim the book
* Review all lecture notes

Maybe

* Implement linear/kernel SVM on microcontroller. `emsvm` 


# Book

## Ch 1. Intro
Supervised learning. Prediction. Classification, Regression
Reinforcement learning, interactive problems.
Unsupervised learning. Discovering structure. Clustering, dimensionality reduction.

## Ch 2. Classifiers principles
Artificial neurons
Perceptron learning
Adaptive linear neurons
Learning convergence
Gradient Descent
Stocastic Gradient Descent

## Ch 3. Classifiers tour
Perceptron
Logistic regression
Support Vector Machines
Kernel SVM
Decision-trees,Random Forest
K-nearest neighbours

## Ch 4. Data preprocessing, training sets
Missing data
Imputation
Categorical data
One-hot-encoding
Train-test splitting
Feature scaling
Feature selection
using L1 regularization
using sequential feature selection
Feature importance using Random Forests

## Ch 5. Dimensionality reduction
PCA
PLSR
LDA

## Ch 6. Model evaluation, hyperparameter tuning
sklearn Pipelines
k-fold cross-validation
Learning and validation curves
Grid search hyperparamters
Performance evaluation metrics

## Ch 7. Ensemble Learning
Majority vote
Weighted majority vote
Bagging
Boosting, Adaboost

## Ch 10. Regression
Ordinary Least Squares
RANSAC
Polynomial regression

## Ch 11. Clustering
k-means
Hierarchical tree clustering
DBSCAN



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


