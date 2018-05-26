
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
Supervised learning. Prediction. Classification, Regression. Labeled data
Reinforcement learning. Interactive problems. Reward function.
Unsupervised learning. Discovering structure. Clustering, dimensionality reduction.

Samples. Instances, observations, 
Features. Attributes, measurements, dimensions
Class labels. Target

## Ch 2. Classifiers principles
Artificial neurons

Activation functions. phi(z) φ(z)

Continuously differentiable – This property is desirable for enabling gradient-based optimization methods
non-linear: with activation function is non-linear, then a two-layer neural network can be proven to be a universal function approximator.
Monotonic: When the activation function is monotonic, the error surface associated with a single-layer model is guaranteed to be convex
Approximates identity near the origin – lets the neural network will learn efficiently when its weights are initialized with small random values. 

Identity. Binary step. Linear
Logistic (sigmoid)
TanH
arctan
softsign

Perceptron learning

Threshold often stored as first weight: -w_0
z = w^T*x
φ(z) = { 1 if > w_0 else -1 } # binary step 

New weights: w_j := w_j + ∆w_j
∆w_j = η(y - yhat) x_j
η is learning rate, 0.0-1.0
y is true class
yhat is predicted class
Weights updated one-at-a-time

Perceptron convergence only guaranteed for linearly separable classes,
and low enough learning rate


Adaline. Adaptive linear neurons
Identity activation function.
Learning on the linear relationship: w^T*x,
A quantizier used to get class labels
Cost function: SSE, sum squared errors.
Cost function is differentiable and convex
Optimized using Gradient Descent
∆w = -η∆J(w)
-∆J(w): negative gradient
All weights updated simultaniously (batch gradient descent)

Can still fail to converge with large learning rates

Stocastic Gradient Descent
iterative , update weights individually for each training sample
Typically converges faster.
Error surface noisier, can allow to escape local minima
Input data must not have order, random shuffle each epoch
Can be used for online learning

Often use an adaptive learning rate, decreasing over time

Mini-batch gradient descent. NN-NNN samples. Vectorized

## Ch 3. Classifiers tour

Logistic regression
Modelling class probabilities

logit = log(p/(1-p)) # log-odds
sigmoid φ(z) = log(1/(1+e^-z))
0.0 - 1.0, 0.5 at z=0 
principle: maximize likelyhood function
practice: minimizing negative log-likelihood function
wrong predictions penelized a lot, error goes towards infinity
minimizes misclassifications

L2 regularization. In sklearn, C=1/lambda. C="complexity", low value -> lots of regularization

Support Vector Machines
Maximising margin classification
large margins tend to have a lower generalization error
find hyperplane between support vectors.
In middle of planes from negative and positive support vectors
principle: maximize 2/||w||
practice: minimize 1/2*||w^2||
via quadratic programming

soft-margin
using slack variable
C as constant to adjust. "complexity".
Similar to regularization

Kernel SVM
non-linear problems
principle: move input into new space using a non-linear transformation, do (linear) separation there
practice: kernel trick, only the inner product 

Radial Basis function (RBF) kernel
rbf = exp(-γ * ||x_i - x_j||^2)
similarity function. 1.0 = identical, 0.0 = very dissimilar
where gamma is a cutoff for the Gaussian sphere
higher gamma, more detailed decision boundary

Decision-trees
Good for interpretability
Classifies based on a series of yes-no questions
Learns by attempting splits on features
in order to maximize Information Gain
impurity measures.
Entropy. 0.0 if all are same class, 1.0 if classes are evenly distributed. Maximize mutual information
Gini coefficient. Minimize probability of misclassification
Classification error
Axis-parallel, rectangular decision boundaries
Vunerable to overfitting without depth limit or pruning

Random Forest
combines many weak learners to a strong learner

1. draw bootstrap sample
2. grow a decision tree: at each node, randomly select d features without replacement, select best split
3. repeat 1-2 k times
4. aggregate the trees by majority voting

more robust results, less prone to overfitting, easier to select hyperparameters

K-nearest neighbours
lazy learning algorithm
memorizes the training data
"nonparametric", instance-based learning

0. chose K and a distance metric
1. find the k nearest neighbours of input sample
2. assign class label by majority vote on these neighbours
tie break (in sklearn): closest sample

challenge: storage space grows without bounds
k is a critical hyperparameter to avoid overfitting
especially for high-dimensional space. curse of dimensionality


## Ch 4. Data preprocessing, training sets
Missing data
drop: sample, row
Imputate: mean, median, mode/most_frequent
`Imputer(missing_values='NaN', strategy='mean', axis=0)`

Categorical data
ordinal: with order, sortable. LabelEncoder
nominal: no order. OneHotEncoder. df.get_dummies()
One-hot-encoding
Dummy feature per unique value

Train-test splitting
X_train, X_test, y_train, y_test = \
  train_test_split(X, y, test_size=0.3, random_state=0)

Feature scaling
MinMaxScaler
StandardScaler

Feature selection
using L1 regularization
drives some feature weights to 0 -> can be eliminated

Regularization path plot
Shows feature weights per feature, versus regularization C

using sequential feature selection
greedy search, makes local optimal choice
Sequential Backward Selection (SBS)
while `k>d` try to remove features, check performance
remove the one that reduced performance the least

Feature importance using Random Forests
measure feature importance as the averaged impurity decrease
gotcha: if features are correlated/redundant, RF will pick one, other will show as not-important

## Ch 5. Dimensionality reduction
99-127

PCA: Principal Component Analysis
Unsupervised linear transformation to subspace
Highly sensitive to scaling, need standardization 
Decomposes covariance matrix to eigenvector/values
Selects k eigenvectors with highest eigenvalues 
Variance explained

LDA: Linear Discriminant Analysis
Supervised data compression
Optimize class separability
Assumes normaly distributed data,
classes with identical covariances,
and statistically independent features.
But works OK with slight violations

Can output discriminiability for each discriminant (component)

kernel principal component analysis
Uses the kernel trick with PCA
kernel computes similarity as dot product between two vectors
polynomial kernel
sigmoid kernel
RGF kernel

## Ch 6. Model evaluation, hyperparameter tuning
127-167

sklearn Pipelines
k-fold cross-validation
Learning and validation curves
Grid search hyperparamters
Performance evaluation metrics

## Ch 7. Ensemble Learning
199-233

Majority vote
Weighted majority vote
Bagging
Boosting, Adaboost

## Ch 10. Regression
277-311

Ordinary Least Squares
RANSAC
Polynomial regression

## Ch 11. Clustering
311-340

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


