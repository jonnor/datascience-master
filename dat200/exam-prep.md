## Subspace analysis
PCA vs PLS, when would you use them? What do they maximize?

Dimensionality reduction
Especially useful when having many redundant/correlated features. Ex: spectral imaging
To make 

PCA, main principles of loadings and scores.

Difference between PCR and PLSR

Compression, why compress? (Why not?)
Linear Discriminant Analysis, main difference from PCA.

## Basic machine learning, classification

Perceptron, Adaline and Logistic Regression, main similarities and differences?

Look at cheat sheet DAT200-1 18V DAT200/Filer/V2018 lecture notes/V2018_03_ML_scikit_learn/otherDocs/cheatSheetPALR.pdf

Draw activation functions, write threshold functions based on z or ϕ(z)

Gradient descent and cost functions, sketch and explain.

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
Support vector machines, explain main principle.
	- kernels: why are they specially suited for SVM


K nearest neighbours, why are they memory intensive?
	- What would be the effect of varying density of observations in different regions of the feature space?

Decision trees, main parameters to tune, how are features splits chosen?
Impurities. 

Random forests, basic principles.

L1 and L2 regularization, what are they regularizing and how?

Which of these can shrink coefficients/weights to zero?


## Pre-processing
Missing data, main strategies to alleviate.

OneHotEncoder, what does it do? Why would one drop_first=True?


Training-test splitting, comment on large vs small training and test sets (split balance).


Some ML methods are not affected by feature scaling, which?

Decision trees / random forest
Naive Bayes



Sequential Backward Selection, explain the basics.

Greedy algorithm: what is it? Advantages, disadvantages?


Feature importance from random forests, which criterion is used?

## Kernels
The kernel trick, basics, why

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
    k= 3-10
    better estimate of the general performance of model

Learning and validation curves.
What is the difference and when do we use them?


Hyperparameters, what are they, how do we find "good" values?


Nested cross-validation, why/when do we use it?


Plot of ROC, what happens as you follow the curve from lower left to upper right?


micro vs macro in "one vs all" multiclass assessment?

## Ensemble learning

What variations of majority voting are there?

Bagging and boosting, main principles.

Broadly speaking, how are iterations weighted in AdaBoost?

## Exploratory data analysis

Why do we perform exploratory data analysis? And how?

RANSAC, why do we use it, and how does it work?

What does the beaver signify in data analysis?


Which tools do we use to search for un-modelled phenomena in our data?
What actions can be taken to improve on the shortcomings you find?

## Regression

Adjusting a parameter leads to an increase in R^2. What happens with MSE?

Describe the process of fitting a decision tree in regression (short by points).
Why can Random Forests be a more robust alternative?


## Cluster analysis
Hard and soft group memberships, what's the deal?

K-means clustering, sketch the algorithm.

What is "cluster inertia" and how can we exploit it?


K-means++ initialization, why do we need it and what does it do?


I'll give you two tiny clusters if you give me their silhouette values.
