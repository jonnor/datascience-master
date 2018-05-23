
# INF230

[NMBU info](https://www.nmbu.no/course/INF230)

## Topics
https://nmbu.instructure.com/courses/304/pages/pensumliste

    Introduction to data bases.
    Raw data and data processing.
    Analysis and methods
    Query and analysis of data
    Datalogging from external devices.
    Data and security.


### SQL

Book

    Chapter 1. Introduction
    Chapter 2. Queries to one table
    Chapter 3. Create and use tables
    Chapter 4. Queries to multiple tables
    Chapter 5. Advanced queries

Chapter 6. Relation model

    Mathematical underpinnings
 
Chapter 7. Data modelling with ER

    Entity Relationship
    1-1
    1-N
    N-N

Chapter 8. From model to database

    Normalization. Process
    1NF
    2NF
    3NF
    BCNF
    Denormalization

Chapter 12. Web applications

#### Mysql Workbench
?

#### Python and SQL

?

### Data Mining

Extracting structured data from semi/unstructured sources
Often from public resources
Most typically webpages

Lecture about Project Davis

* Davis weatherstations, hosted by users, logs to WeatherLink.com
* Python script miner. Downloads HTML data, parse with BeautifulSoup, extracts data, stores to .csv/DB 

Logging. Capturing historical data by periodically sampling/recording/checking datasource

### Data analysis

#### Exporative Data Analysis

Objectives

* Data understanding.
Typical values, range of values
* Data preparation.
Identifying anomalies.
Outliers, missing values, duplicate features, highly correlated features
* Data mining. Feature extraction
* Result interpretation.
Of prediction/classification/clustering results

Types of data

* Numeric,continious
* Categorical,nominal,ordinal.

Basic kinds of analysis

* Descriptive statistics
Center (mean,median,mode), spread (range,var,std), shape (symmetry,skew,kurtosis),
variable correlation,
* Data visualization
Single variable frequency (Histogram,boxwisker,distibution-chart)
Multiple variable frequency. Scatterplot, multi-scatter plot, scatter matrix.
Class-stratified, indicating different classes by point shape/color.
Bubble chart: Scatter with one variable as size of point.
Density chart: One dimensions shown as backgroun color
High-dimensional via projection.
Parallel chart: Projection to XY. Attributes along X, _all_ measures along Y. Needs normalization of values.
Deviation chart: Similar to parallell, but shows mean+stddev instead of individual measurements in Y
Andrews curves: Plots a Fourier series of the data as lines

Correlation is unit-less, scaled covariance. `[-1.0 0.0 1.0]`

#### Multivariate data analysis
Nature is multivariate
Most phenomenom consists of several factors

Often we have an indirect measurement, the metrics captured
are not directly the thing we want to study, but something influenced by it

Because one variable does not adequately describe the phenomenon,
we use multiple "non-selective" variables

Our obervations are a sum of the data-structure that we are interested in,
and noise (everything we are not interested in). Key is to supress the noise.
Mostly happens via the inter-variable correllation

Objectives

* Data description
* Discrimination and classification
* Regression and prediction 

Compress NNN-dimensional feature space into a lower dimensional one.
Easier to visualize, understand

Unsupervised: PCA.
Supervised: PLSR
Finds a low-dimensional hyper-plane that best summarizes variation in X,
using Ordinary Least Squares


Scores: New variables in the constructed PC space.
C components x N samples 
How different samples related to eachother

Scores plot.
Typically PC1 vs PC2, with explained var shown as labels
Note: have to ensure that there is a good amount of explained var. Otherwise cannot make strong interpretation
Close values -> similar, far -> dissimilar (in these components)
Groups/clustering -> suggests occurances of discrete classes 
Sample distribution. Evenly spread across plot, or tend to one of the sides?
 Spreading more and more -> asymmetric variation. Might want to do a transform (log etc)
 Are a few very different? Might be outliers

Loadings: Weights for each new variable, how it is constructed from original features.
Which features contribute 
K features x C components

Loadings plot
Shows importance of the different variables for components specified
Should preferably be used together with corresponding scores plot
! variables close to origo are poorly/not explained by the PCs

Line loadings plot.
Shows PC1,2,3 as colored lines, along one data axis. Typical for spectral imaging

Correlation loadings plot
Like loadings plot but a bit clearer.
Unit circle outer = 100% explained var, inner circle = 50% explained variance.

Influence plot
Q, F-residuals vs Leverage / Hotellinger T2.
Representing outliers
Samples with high residual variance (top of plot) are poorly described
Samples with high leverage (right of plot) are well described,
can be problematic if this is an outlier (large influence on model)
Worst outlier is those both high in variance and leverage

Explained variance
How much of X variance is explained by PC1,2,..,PCn
The part not explained is the residual, E
Can be plotted as the cumulative values. Useful for deciding where to cutoff



#### Davis weather stations analysis


## TODO

Exam prep

* Complete unfinished SQL queries in CA2
* Try run queries from book notes, ch.2
* Read up on Python and SQL
* Do 2 previous exam
* Do the book quiz, http://www.dbsys.info/Databasesystemer/quiz/index.html
* Do the assingments exercises
* Read up on, Davis weather stations analysis


