# Particle tracking using machine learning

[Kaggle challenge](https://www.kaggle.com/c/trackml-particle-identification)


## TODO

* Setup feature transformation pipeline
* Attempt to learn a custom distance metric
* Use distance metric with DBSCAN
* Setup cross-validation

## Notes

Clustering?
- Each particle a cluster of hits
- [sklearn Clustering methods overview](http://scikit-learn.org/stable/modules/clustering.html#clustering)

Challenge: For any 2 hits there are an infinite number of helixes that can be constructed between them?

What is the probability that 2 hits come from the same track/particle?
Need to express similarity pair-wise.

Challenge: Data likely to be noisy

* DBSCAN. Has concept of noise, can eliminate outliers
* OPTIM: (deals better with difference in density)

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

- Angle phi
- Distance R
- Distance Z
- Position X,Y

Between two

- Distance between hits
- Angle phi between hits
- Angle of hits in Z
- Difference in angles

Between three

- Difference in XY angle (AB, BC). Expect small, as helix curve

