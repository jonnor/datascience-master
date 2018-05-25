# Particle tracking using machine learning

[Kaggle challenge](https://www.kaggle.com/c/trackml-particle-identification)

## Done

* TrackML Python library: [Fixing reading of some files](https://github.com/LAL/trackml-library/pull/9)

## TODO

* Calculate distance from RandomForest probability 
* Plug distance metric into H/DBSCAN clustering
* Update RandomForest to use RFD feature formulation
* Add RFD position vector also
* Add more/different features
* Change code into a proper pipeline/estimators
* Build training/testset sampled across a larger set of events

## Notes

Clustering?
- Each particle a cluster of hits
- [sklearn Clustering methods overview](http://scikit-learn.org/stable/modules/clustering.html#clustering)

Challenge: For any 2 hits there are an infinite number of helixes that can be constructed between them?

What is the probability that 2 hits come from the same track/particle?
Need to express similarity pair-wise.

Challenge: Data likely to be noisy

* DBSCAN. Has concept of noise, can eliminate outliers
* OPTICS: (deals better with difference in density)
* HDBSCAN: refinement on DBSCAN
With custom projection (unrolled helix, partitioned), has gotten 0.4x score (top3 as of May 22),
https://www.kaggle.com/c/trackml-particle-identification/discussion/57180

Hierarchical clustering

* How to specify/find right number of clusters?
* Use a custom linkage function, which checks to which degree cluster is a good track?

Learn a distance/similarity metric?

* Global versus local. 
* [Distance metric learning, with application to clustering with side-information](https://ai.stanford.edu/%7Eang/papers/nips02-metric.pdf).
Probabilistic Global Distance Metric Learning / PGDM / MMC. Eric P. Xing, Andrew Y. Ng, Michael I. Jordan and Stuart Russell.
* [Supervised distance metric learning through maximization of the Jeffrey divergence](https://www.sciencedirect.com/science/article/pii/S0031320316303600)
* [Distance metric learning in R](https://github.com/terrytangyuan/dml), huge list of methods implemented. 
* [metric-learn](https://github.com/metric-learn/metric-learn), Python library implementing many metric learning methods. sklearn-like API
* [Local Discriminative Distance Metrics Ensemble Learning](https://www.cs.umb.edu/~ding/papers/pr2013.pdf). 2013.
Learns an ensemble of local distance metrics, to deal with non-uniform distances in the sample space.
* [Distance Metric Learning: A Comprehensive Survey](https://www.cs.cmu.edu/~liuy/frame_survey_v2.pdf). 2006
* LDA or PLSR as transformation. Limitation: linear only? Alt: Kernel SVM, Random Forests
* [A Survey on Metric Learning for Feature Vectors and Structured Data](https://arxiv.org/abs/1306.6709).
From 2014. Very comprehensive, 50 approaches, 60 pages.
* Random Forest Distance (Xiong et al., 2012). Using a pairwise classification approach, |a-b|, 0.5(a+b).
[Paper](https://arxiv.org/pdf/1201.0610.pdf). States that the pseudometric not respecting triangle equality not a problem in practice.
* C-DBSCAN, Density-Based Clustering with Constraints. [](https://link.springer.com/chapter/10.1007%2F978-3-540-72530-5_25)
* [umap](https://github.com/lmcinnes/umap) suggested by HDBSCAN author to do dimensionality reduction of custom metric to use Euclidian from custom distance metric.
* [Tutorial on Metric Learning](http://researchers.lille.inria.fr/abellet/talks/metric_learning_tutorial_CIL.pdf), Aurélien Bellet, USC. 122 pages/slides.

Metric learning, single hit with triple loss.
https://www.kaggle.com/c/trackml-particle-identification/discussion/57354
Contrastive loss, center loss, magnet loss.

Custom loss function for Gradient Descent in Python with autograd
http://willwolf.io/2015/11/18/so-you-want-to-implement-a-custom-loss-function/

Challenge: Comparing pairwise distances has complexity N**2

* Can we partition. Ex. Hits in positive Z are probably rarely in same track as hits in negative Z?
* Can we eliminate hits by finding the easy tracks (linear or near linear)?
* How can we eliminate the noise hits (particle_id=0)?
* How to split the learning into batches? Bagging ensemble with trees?
https://stackoverflow.com/questions/42920148/using-sklearn-voting-ensemble-with-partial-fit
Stocastic Gradient Descent, with criterion SVM/logic?
http://scikit-learn.org/stable/modules/generated/sklearn.linear_model.SGDClassifier.html

Supervised clustering

* [Supervised Clustering with Support Vector Machines](https://www.cs.cornell.edu/people/tj/publications/finley_joachims_05a.pdf).
"One approach is to use a binary classifier.
Take all pairs of items in all training sets,
describe each pair in terms of a feature vector.
Let positive examples be those pairs in the same cluster,
and negative examples be those pairs in different cluster.
We discuss three problems with this approach".
Could be useful for feature extraction? Checking whether given features can classify correctly.
"For our clustering method, we use correlation clustering, maximizing sum of similarities.
Any clustering method with an objective function expressible as a linear product of `w` is acceptable."
"We used SVM struct from SVM lite"
* [Supervised Clustering – Algorithms and Benefits](http://www2.cs.uh.edu/~ceick/kdd/EZZ04.pdf)

Constrained clustering

- [Constrained Clustering Algorithms: Practical Issues and Applications](http://www.dc.fi.udc.es/~edu/pubs/meares-phd.pdf). 2013, 170 pages.
must-link constraints, cannot-link constraints.
constraint-based vs distance-based.
- [Constrained Clustering: Advances in Algorithms, Theory, and Applications](https://dl.acm.org/citation.cfm?id=1404506). Book, 2008.
- [Agglomerative Hierarchical Clustering with Constraints: Theoretical and Empirical Results](http://www.cs.albany.edu/~davidson/Publications/hierCameraReady.pdf). 200+ citations.

Sequence labling
- 

Helixal path
High momentum: More straight

Cylindrical coordinate transformation
A circle in XY
Almost a straight line in RZ

Almost always moving faster/more in Z?
Sort-by-Z as ordering of hits

Conventional:
- Consider all 3-sets of points relatively near eachother.
If , make it a tracklet. Attempt to join tracklets to form tracks
Kalman filter often starts from outside going in towards center.

### Features
Hits that from the same particle should lie on a helical track

In momentum space tracks are typically arcs
https://www.kaggle.com/c/trackml-particle-identification/discussion/56668

#### Specials

about 32% of the tracks are almost perfectly straight and they make up about 0.368 of the total metric score.
about 43% of the track are quite straight, makeup 0.52 of metric score.
https://www.kaggle.com/c/trackml-particle-identification/discussion/56580

2.5 times higher probability that particle_id /track_id is equal 0
https://www.kaggle.com/c/trackml-particle-identification/discussion/57004


#### Per hit

- Angle phi (in XY)
- Angle theta (in Z). Absolute value may say something about momentum?
- Distance R (in XY)
- Distance Z (absolute)
- Position X,Y. (redundant with phi,R)

[Coordinate transformation ex](https://www.kaggle.com/mikhailhushchyn/dbscan-benchmark)

#### Between two hits

- Distance between hits
- Angle phi between hits
- Angle of hits in Z
- Difference in angles

Distances should maybe be normalized to compensate for different density/sparseness.
Divide by r*r in XY plane and z in Z plane?

#### Between three hits

- Difference in XY angle (AB, BC). Expect small, as helix curve

