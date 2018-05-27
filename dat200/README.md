
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
iterative, update weights individually for each training sample
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

Training: fit_transform() ... fit()
Test/use: transform() ... predict()

holdout cross-validation
single validation set
disadvantage: sensitive to just how this split was done

k-fold cross-validation
k-1 folds used for training,
1 fold for validation
repeat k times
averate performance metric
leave-one-out (LOO). k=n samples in set
Used when working with very small datasets

sklearn.cross_validation.cross_val_score(est, X, Y, cv=10)

Learning curve
evaluate variance/bias balance, over/underfit
x-axis: number of training samples
high variance: large distance between train/test-set
high bias: both train/set-set have low accuracy
good balance: distance between test/train set approaches 0, at high accuracy

validation curve
x-axis: value of hyperparameter
see influence of hyperparameter choice
choose optimal value, underfit/overfit balance

Grid search hyperparamters
used to find best hyperparameters using cross-validation

nested cross-validation
used to evaluate different models against eachother
2 levels of cross-validation

Performance evaluation metrics
confusion matrix
true positive   false negative
false positive  true negative

err=false/total
acc=1-err
True positive rate (recall)
Useful for imbalanced sets
tpr=TP/(FN+TP)
False positive rate
fpr=FP/(FP+TN)
Precision
pre=true_positive/(true_positive+false_positive)

F1 combines precision and recall

ROC curve
diagonal: random
left/top-side: perfect
AUC - area under curve. Perfect=1.0, random=0.5

multiclass metrics with One-vs-All
two averaging approaches
micro: average individual TP,TN,FP,FN
weight each instance equally
macro: average each system metric
overall performance wrt most frequent label
in sklearn, macro weigthed by number of instances in class

## Ch 7. Ensemble Learning
199-233

Combine multiple estimators into one meta-estimator with better perf
Assuming uncorrelated errors, and better-than-random invididual perf
different FP/FN mistakes can give better overall ROC AUC

Majority vote
multiclass: plurality voting, class with most votes win
Weighted majority vote
each classifier is weighted

Bagging
each classifier in ensemble trained on different bootstrapped samples
aka "bootstrap aggregation"
effective in reducing variance (overfit)
ineffective in reducing bias
used typically with high variance bases, ie unpruned decision trees

Boosting
weak learners=very simple, slightly better than random guess
ex: decision tree stump (one decision node)
focuses on misclassified results
simple form: add 50% of misclassified samples from last round into new training round

Adaboost, adaptive boosting
1. Start with uniform weights
for each of M boosting round
2. train a weak learner C, predict class labels
3. compute weighted error rate
4. calculate coefficient and update weights
5. re-normalize weights
6. compute

## Ch 10. Regression
277-311

Supervised learning of continious response

EDA
scatterplot matrix
correlation matrix, linear correlation between variables
numpy.corrcoeff

Ordinary Least Squares
minimize SSE
in principle can be done with Gradient Decent (on standardized data)
sklearn solver LIBLINEAR converges better on nonstandardized data
is impacted a lot by outliers

RANSAC
linear regression against (estimated) inliers
1. selects random samples as inliers, fit model
2. tests all other data with this model, add samples within tolerances as inliners
3. efit on all inliers, estimate error difference
4. terminate if redisuals below threshold or max iterations
challenge: setting inlier threshold
sklearn: Median Absolute Deviation

Residual plots
Plots the residuals of (multidimensional) model
Expect errors randomly distributed around 0
Patterns means there are non-linearities we cannot explain

MSE, average of SSE
R2, standardized version of MSE. Fraction of captured response variance 
R2=1-(SSE/SST)
SST= total sum of squares

Regression can overfit.
Evaluate like normally, perf of testset versus training set

Regularization to avoid
RIDGE. L2 regularization. adds squared sum of weights to cost function
LASSO. L1 penality. Drives some weights to 0
ElasticNet. combined L2,L1


Polynomial regression
Models a non-linear relationship
Still considered a linear model, because of linear weights
Select degree of polynomial, eg d=3

Alt for non-linear relationshop, transform features/targets
Ex: log, squareroot

Random forest regression
split criterion: MSE/within-node variance/variance-reduction
Downside: not continious decision boundary, prone to overfitting

## Ch 11. Clustering
311-340

Unsupervised learning
find groups of similar objects

k-means
prototype-based clustering
have to decide k upfront
good at finding spherical clusters
1. start with randomly selected centroids
2. assign each sample to closest centroid
3. move centroid to center of samples assigned
4. continue until less than M samples change, or max iterations

random start can result in bad clustering or slow convergence
running multiple times with different random state,
chosing best model based on SSE


k-means++
the default algorithm in sklearn
different initialization
1. randomly chose one of input samples as first centroid
2. for each sample not a centroid, calculate distance to nearest chosen center
3. chose a new datapoint as center randomly, using weighted probability x**2
4. repeat 2-3 until k centers are chosen
then performs k-means normally

hard clustering, sample belongs to one cluster only
soft/fuzzy clustering, sample can be in one or more clusters

fuzzy C-means. FCM
aka soft/fuzzy k-means
similar to k-means, different loss function
cluster membership probability
fuzziness coefficient m=1,2,3


elbow method
to find optimal number of clusters (k)
within-cluster SSE = distortion = inertia
if k increases, distortion decreases
plot distortion versus k,
chose k to where distortion decrease drops off

siluette plots
measure of how tightly grouped samples in clusters are
siluette coefficient, `[-1.0 1.0]`
ideal = 1.0
siluettes should have roughly same length

a. cohesion = average distance between sample and all other points in cluster
b. separation = from next closest cluster, average distance between sample and all samples in nearest cluster
siluette = s = (b-a)/max(a,b)


Hierarchical tree clustering

agglomerative: start with each sample in cluster, combine
divisive: start with one cluster, split

agglomorative most common. Different linkages to decide which clusters to merge 

single linkage: compute distance between most similar members, merge the closest
complete linkage: "" most dissimilar, merge closest
average linkage: minimum average distance
Ward: minimum increase of total within-cluster SSE

dendrograms, visualization of binary hierachical clustring
heat map, show values associated


DBSCAN
density-based clustering
number of points within specified radius E

core point: if at least MinPts of neighbouring points are in radius E
border point: fewer neighbours within E, but lies within E of core point
noise point: neither core nor border

1. form a cluster per core point or connected group of core points (if closer than E)
2. assign each border point to the cluster of its core point

does not assume clusters are spherical
can remove noise

challenging to chose E,minpts with varying density in dataset

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


