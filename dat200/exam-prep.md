## Subspace analysis
Compression, why compress? (Why not?)

    Dimensionality reduction
    Especially useful when having many redundant/correlated features. Ex: spectral imaging
    Can help make model more explainable 

    Most methods are linear, not useful with non-linear phenomenon

PCA, main principles of loadings and scores.

    scores: Samples in the constructed PC space.
    Can evaluate their similarity etc
    
    loadings: Weights for each new variable, how PC components relate to original features
    Similar:=correlated
    Opposite:=inversely correlated
    in center, not explained

PCA vs PLS(R), when would you use them? What do they maximize?

    PCA maximizes explained variance for each principal component
    Use for data exploration
    When Y data is not available

    PLSR maximizes
    direction in the X space that explains the maximum variance direction in the Y space
    PLSR good when number of features > number of observations

Difference between PCR and PLSR

    PCR: PCA on X, regression with ODS unaltered Y, transform back PCA
    PLSR: both X and Y are transformed to new space. Latent variable

Linear Discriminant Analysis, main difference from PCA.

    LDA is supervised
    attempts to model the difference between the classes of data.
    Can be used as a classifier, or as dimensinality reduction

## Basic machine learning, classification

Perceptron, Adaline and Logistic Regression, main similarities and differences?

    all have a linear set of weights
    different activation functions
     
    perceptron: step function, discrete errors, feedback to update weights
    adaline: identify function, continious errors, SSE cost, gradient descent
    logistic regression: sigmoid function

    ! Look at cheat sheet
    DAT200-1 18V DAT200/Filer/V2018 lecture notes/V2018_03_ML_scikit_learn/otherDocs/cheatSheetPALR.pdf

Draw activation functions, write threshold functions based on z or ϕ(z)

    !
    linear/identity
    logit
    sigmoid

Gradient descent and cost functions, sketch and explain.

    Convex optimization
    Estimate slope
    Learning rate
    Convergence

Principles behind extending binary classifiers into multi-class classifiers 

    One-vs-All/One-vs-Rest.
    One classifier per class.
    Assign label as the classifier with highest confidence

    One-vs-one
    K(K−1)/2 binary classifiers for a K-way multiclass
    each get samples of a pair of classes from training set, must learn to distinguish these two classes
    For prediction, voting is applied. All classifiers are ran on unseen sample, class that gets most "+1" wins

    Multilayer perceptron: one output node in last layer per class
    k-NN. Considers distance of input to k closest neighbour from training. Majority voting
    Naive Bayes. Each class has own conditional probabilty. Highest win
    Decision trees. Feature splits are done, at the leaves are class labels.


## ML classifiers in scikit-learn

Logistic regression, what does it do?

    linear classifier based on class probabilities
    
    principle: maximize likelyhood function
    practice: minimizing negative log-likelihood function
    wrong predictions penalized a lot, error goes towards infinity
    minimizes misclassifications

Support vector machines, explain main principle.

    maximal margin hyperplane
    construct neg/pos hyperplanes using support vectors, boundary in middle
    needs to be optimized using quadratic programming
    linear or kernel

Kernels: why are they specially suited for SVM

    Only have to calculate inner product
    Only calculate wrt to support vectors, relatively few

K nearest neighbours, why are they memory intensive?

    Remembers each sample

What would be the effect of varying density of observations in different regions of the feature space?

    ? context

Decision trees, main parameters to tune, how are features splits chosen? Impurities. 

    tree depth
    feature splits chosen to minimize impurity
    impurity measures: entropy, Gini

Random forests, basic principles.

    Ensemble of desicion trees
    Each trained on random subset of features (bootstrapping)

L1 and L2 regularization, what are they regularizing and how?

    Regularizes weights of linear classifiers.
    By adding a punishment term to cost function
    Pushes values towards 0
    L1:
    L2: 

Which of these can shrink coefficients/weights to zero?

    L1 can make weights become 0. Sparse weights. Can be used for feature selection

## Pre-processing
Missing data, main strategies to alleviate.

OneHotEncoder, what does it do? Why would one drop_first=True?

    Encode categorical variables as dummy variables
    Each unique value gets a feature column
    drop_first removes redundancy

Training-test splitting, comment on large vs small training and test sets (split balance).

    must ensure enough samples in testset to give good generalized estimate
    but more training data good, so with bigger sets allow bigger proportions
    60/40, 70/30 small sets
    90/10, 95/5, 99/1 big dataset

Some ML methods are not affected by feature scaling, which?

    Decision trees / random forest
    Naive Bayes

Sequential Backward Selection, explain the basics.

Greedy algorithm: what is it? Advantages, disadvantages?

    Locally optimal choice
    Fast, does not consider all options
    Not guaranteed to give optimal solution

Feature importance from random forests, which criterion is used?

    feature importance as the averaged impurity decrease
    typ entropy,Gini coefficient

## Kernels
The kernel trick, basics, why

    implicit feature space
    computes similarity of two vectors directly (in this feature space)
    without having to transform each and every sample
    high-dimensional spaces, even infinite. e^||a-b||

## Cross-validation and parameter optimisation
My pipeline is filled with ... what?
In a general data analysis problem, what would be typical elements in a pipeline?

    Feature extraction.
    Normalization
    Feature selection. Data compression
    Classification/regression/clustering

Outside the pipeline

    Reading data
    Test/train splits. Dataset subsampling
    Cross-validation, Gridsearch
    Storing/displaying results

Training, validation and test set, why three parts, what are their roles?

    Training Dataset: Sample of data used to fit the model.
    Validation Dataset: Sample of data used for unbiased evaluation of model while tuning model hyperparameters.
      The evaluation becomes more biased as skill on the validation dataset is incorporated into the model configuration.
    Test Dataset: Sample of data used to provide an unbiased evaluation of a final model fit on the training dataset.


Alternative to single training-validation split?

    k-fold cross-validation
    k typ 3-10
    better estimate of the general performance of model

Learning and validation curves.
What is the difference and when do we use them?

    learning curve
    evaluate variance/bias balance, over/underfit
    x-axis: number of training samples
    high variance: large distance between train/test-set
    high bias: both train/set-set have low accuracy
    good balance: distance between test/train set approaches 0, at high accuracy

    validation curve
    x-axis: value of hyperparameter
    see influence of hyperparameter choice
    choose optimal value, underfit/overfit balance

Hyperparameters, what are they, how do we find "good" values?

    Parameters not learned by model, but have to be chosen
    Gridsearch or random search across hyperparamters space,
    evaluated by k-fold cross-validation
    Good values are those that maximize our metric on validation/test set

Nested cross-validation, why/when do we use it?

    Evaluate different models against eachother
    To tune each individual model, but then get a generalized view of final performance (not just single test)

Plot of ROC, what happens as you follow the curve from lower left to upper right?


micro vs macro in "one vs all" multiclass assessment?

    how overall metrics are calculated

## Ensemble learning

What variations of majority voting are there?

    Plain majority/plurality
    Weighted

Bagging and boosting, main principles.

Broadly speaking, how are iterations weighted in AdaBoost?

    e = weighted error rate
    coeff = 0.5*log((1-e)/e)
    w *= exp(-coeff * y * yhat)
    

## Exploratory data analysis

Why do we perform exploratory data analysis? And how?

    boxplot variables
    scatterplot matrix
    stratified scatterplot
    maybe PCA, look at correlated-loadings plot

What does the beaver signify in data analysis?

    Overfitting

Which tools do we use to search for un-modelled phenomena in our data?
What actions can be taken to improve on the shortcomings you find?

    If doing linear regression can use Residual plots
    try feature-transformation, eliminating outliers, non-linear model
    ?

## Regression

Adjusting a parameter leads to an increase in R^2. What happens with MSE?

    MSE goes down proportionally

Describe the process of fitting a decision tree in regression (short by points).
Why can Random Forests be a more robust alternative?

    Smoother desiciond boundary. Majority voting averages out

RANSAC, why do we use it, and how does it work?

    Regression on noisy data
    Eliminate influence of outliers

## Cluster analysis
Hard and soft group memberships, what's the deal?

    Hard: sample belongs to one cluster only
    Soft: sample may belong to multiple clusters. Typically expressed as probability
    
K-means clustering, sketch the algorithm.

    1. start with randomly selected centroids
    2. assign each sample to closest centroid
    3. move centroid to center of samples assigned
    4. continue until less than M samples change, or max iterations

K-means++ initialization, why do we need it and what does it do?

    spreads out the clusters across the area spanned by features 
    because original k-means can give arbitrarily bad results, and converge slowly
    
    1. randomly chose one of input samples as first centroid
    2. for each sample not a centroid, calculate distance to nearest chosen center
    3. chose a new datapoint as center randomly, using weighted probability x**2
    4. repeat 2-3 until k centers are chosen


What is "cluster inertia" and how can we exploit it?

    same as "distortion"
    within-cluster SSE 
    use to evaluate how good our clustering is
    using elbow method, decrease in distortion as k increases


I'll give you two tiny clusters if you give me their silhouette values.
