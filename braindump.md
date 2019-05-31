## Ideas

Flowhub related

* From Jupyter to cloud-scale service using msgflo-python
* FBP/NoFlo execution for Jupyter. Kernel?. .fbp renderer, component/JavaScript evaluator
* Integrated data visualization for programming,
[dataviz](https://github.com/jonnor/projects/tree/master/introspectable-computing/dataviz)

Basic data science applications

* Energy usage at Bitraf/c-base, relative to weather. Anomaly detection, reporting/monitoring
* CNC usage at Bitraf. How many of the jobs/parts can be done on a 60x120 cm workarea machine.
Take gcode/dxfs from Dropbox, analyse.
* Predicting likelyhood of someone opening for guests upon ringing the doorbell.

Machine learning

* Assist in reverse engineering of protocols, for example for machine control (Shopbot,Redsail).
Record input, output pairs. Change input parameters, find corresponding change in output.


* Automation of CAM paths for maximizing material usage and waste management. Machine-vision
Automatic part layout of useful parts in remainder of cutsheet for CNC/laser.
Automatic creation of cutlines to discard pieces smaller than w,h.
Can a greedy algorithm perform well for part layout, ie does the problem have optimal substructure?

Electronics, EDA

* Component-based PCB autolayout & routing
Reusable modules with pre-laidout schematic/board snippets for a given functionality.
Autolayout by placing modules as black-box rectangles/polygons.
Using reduction in netlist size (implicit ignoring local connections) for better autorouting.
But this can be detected via strongly connected components of the graph?
Note, one can also use [Planarity_testing](https://en.wikipedia.org/wiki/Planarity_testing) to determine subgraphs
which can be laid out without 
Using contraints to express requirements, solving to autosuggest sub-circuit solutions.
http://www.electronicdesign.com/what-s-difference-between/what-s-difference-pcb-routing-then-and-now

Robotics



## Publishing

[Open Hardware Journal](https://openhardware.metajnl.com/about/#hardware-metapapers)

[ArXiv](https://arxiv.org). Pre-print / working paper publishing. Widely used open/free source of papers.
Interesting subs
Machin learning: `cs.LG`, `stat.ML`
Audio, speech processing: `eess.AS`
Computer vision: `cs.CV`, `eess.IV` 

[Hackaday Journal](https://journal.hackaday.io/submissions). Possiblity of presenting at the Hackaday Superconference.


Research relevant Journals

* [Journal listing search](https://newcatalog.library.cornell.edu/catalog?utf8=%E2%9C%93&f%5Bformat%5D%5B%5D=Journal%2FPeriodical&q=wireless+sensor+network&search_field=all_fields)

Sensor Networks

* MDIP Sensors journal. 15'000 NOK article processing fee.
* Wireless Communications and Mobile Computing.
* IEEE IoTJ.
* [International Journal of Sensors and Sensor Networks](http://www.sciencepublishinggroup.com/journal/index?journalid=130)
* [American Journal of Embedded Systems and Applications](http://www.sciencepublishinggroup.com/journal/index?journalid=236)
* [International Journal of Distributed Sensor Networks](http://journals.sagepub.com/home/dsn/)
* [IEEE IET Wireless Sensor Systems](https://ieeexplore.ieee.org/xpl/RecentIssue.jsp?punumber=5704589)
* [InderScience International Journal of Embedded Systems](http://www.inderscience.com/jhome.php?jcode=ijes#topics2).
Embedded machine learning, deep learning and artificial Intelligence. Bi-monthly.
* [EURASIP Journal on Embedded Systems](https://jes-eurasipjournals.springeropen.com/)

Sound / Acoustics

* ?


## Conferences

Lists

* [WikiCFP](http://www.wikicfp.com/cfp/call?conference=computer%20science). Loots

Sound / Acoustics

* International Conference on Acoustics, Speech, and Signal Processing. [ICASSP](https://2020.ieeeicassp.org/)

Sensor Networks / IoT + Machine Learning

* [iDSC 2019 : International Data Science Conference](http://wikicfp.com/cfp/servlet/event.showcfp?eventid=77574&copyownerid=90547).
Edge/Fog computing. Machine Learning.
* [WSOM+ 2019 : 13th International Workshop on Self-Organizing Maps and Learning Vector Quantization, Clustering and Data Visualization ](http://wikicfp.com/cfp/servlet/event.showcfp?eventid=81642&copyownerid=130748).
Unsupervised feature selection, extraction and data pre-processing. Software and hardware implementations.
Encourage scientific and application-oriented papers. Pattern recognition. Robotics and intelligent systems.
* [SmartSys 2019 : Smart Systems: bringing together computer vision, sensor networks and machine learning](http://wikicfp.com/cfp/servlet/event.showcfp?eventid=80513&copyownerid=127427).
Sensor networks, IoT - Internet of Things, Smart Cities. 
* [CAIP 2019 : Computer Analysis of Images and Patterns](http://wikicfp.com/cfp/servlet/event.showcfp?eventid=79113&copyownerid=102216).
Feature extraction. Machine learning for image and pattern analysis. Mobile multimedia. 



## Inbox

* [Hadley Wickham: Tidy data](http://vita.had.co.nz/papers/tidy-data.html).
This paper tackles a small, but important, component of data cleaning: data tidying.

Huge amount of Computer Science papers: https://github.com/papers-we-love/papers-we-love

## References

Books

* [The Elements of Statistical Learning](https://web.stanford.edu/~hastie/Papers/ESLII.pdf).
Recommended by Kristin T. regarding classification, regression methods.
* [The Art of Approximation in Science and Engineering](https://www.dropbox.com/s/bmqwzc8qqt5lv9p/9017.pdf?dl=1).
* [Street-Fighting Mathematics](https://mitpress.mit.edu/books/street-fighting-mathematics)

Lectures

* [Statistical Computing for Scientists and Engineers, U.Notre Dame](https://www.zabaras.com/statisticalcomputing).
Dense syllabus: from Bayesian Statistics, many Monte Carlo methods, and Uncertainty Quantification.

Big challenges

* [Eliezer Yudkowsky – AI Alignment: Why It's Hard, and Where to Start](https://www.youtube.com/watch?v=EUjc1WuyPT8).
Utility functions for intelligent agent behavior, challenges and ways to deal with.
Recent work in progress:
Utility indifference. Agent must respect an off/suspend switch. Paper: Corrigibility
Low impact: Agents that deliberately reduce their agency on the world. Paper: Reduced Impact Artificial Intelligence
Ambiguity indentification. Have the AI ask you about using new capabilities. Paper: The Value Learning Problem
Conservatism. Creating robust boundaries/space between desired and non-desired classifications,
such that new capabilities/stategries will fall on right side. Conservative white-listing instead of black-listing.
Specifying environmental goals using sensory data. What if AI is like modern machine learning. Paper: Formalizing Two Problems in Realistic World-Models. Being able to express environmental goals instead of just goals in terms of directly observable sensory input.
Inverse reinforcement learning. Watch another agent, induce what it wants. Paper: Learning the preference of Bounded Agents.
Act-based agent. Supervised learning by observing human behavior/strategies.
Mild optimization. Don't optimize your utility function so hard/narrow.
Recent completed work:
AXAI. How to create an AGI given unbounded computation. Paper: Universal Algorithmic Intelligence
Intelligent software agent cooperation. Program Equilibrium in the Prisoners Dilemma via Lobs Theorem.
Probabilitic game theory. Paper: Reflective oracles.

Robotics

* [Deep reinforcement for robotics](https://www.facebook.com/nipsfoundation/videos/1554594181298482)
Reinforcement learning is different from supervised methods. The agent observes its environment and performs actions on it.
It observes the outcome of its actions and compares this with desired outcome.
Current RL algorithms are fully generic (mathematically). They can get superhuman performance, but the learning efficiency is very low.
Can we make it more efficient by making use of particular information about the environment. Ie: obey our laws of physics
Can we meta-reinformcement learn? That let the agent learn to reinformcement learn?
Using Recurrent Neural Net as a generic compute achitecture, with both compute and storage ability. 
Evaluating on Multi-armed bandit problem, and known asymptomatically optimall algorithm.
Currently meta-learning works 2/3 of the time. Reasons for not working inlclude overfitting (or underfitting), and insufficient signal.
Model-Agnostic Meta-Learning.
Imitation learning. Many success stories in robotics. Human shows how to perform task, agent learns the policy.
Lifelong learning. Instead of only training/learning up-front, will learn continiously after deployment.
Simulation is very important. Huge advantages to training in real world.
Challenge is for the learnings in simulation to transfer over into real world.
One approach is randomized simulation domains. With enough variation - even when not high fidelity,
allows to train agent which performs well on real-life scenario without any real-life training data.
How to increase signal for reinformement learning?
Hindsight Experience Replay. Also learn from failures. Inject goals into old experiences
* [Amit's thoughts on pathfinding](http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html).
Detailed and well explained use of A* for pathfinding in games, including practical considerations.
Chosing heuristics function, its values. Tie breaking, data structures, making behavior interesting
* [Visual foresight](https://sites.google.com/view/visual-foresight).
Robots using real-time predictions of the visual/camera stimuly to learn how to perform tasks.

Computer vision

* [Bilateral_Filtering](http://homepages.inf.ed.ac.uk/rbf/CVonline/LOCAL_COPIES/MANDUCHI1/Bilateral_Filtering.html).
When performed in CIE-Lab gives very natural blurring, not introducing new colors. Also preserves edges and shadows well.
Can be applied iteratively, which effectively reduces the amount of colors present. Reducing/removing texture.
Could be used as a pre-processing step to color quantize an image? 

Efficiency

* [Optimizing fixed-point FIR filters](https://se.mathworks.com/help/dsp/examples/optimized-fixed-point-fir-filters.html),
by quantizing filter coefficients.  
* [dspguru FIR implementation](https://dspguru.com/dsp/faqs/fir/implementation/), some tricks in C
* [TIIR filters](https://ccrma.stanford.edu/~jos/tiirts/TIIR_Filters.html), truncated IIRs.
Using two IIRs to get the response of an FIR filter, but with fewer calculations.

Dealing with lack of (labeled) data

* Self learning. [Using Pseudo labeling for semi-supervised learning](https://towardsdatascience.com/simple-explanation-of-semi-supervised-learning-and-pseudo-labeling-c2218e8c769b).
After having trained model on labeled data, run it on the unlabeled data to get (pseudo) labels, then train it on the combined setup. Up to 25% pseudo labels in a batch. When method provides confidence score, take only the most confident samples into training set.
Also called .
* Semi-supervised learning can be done using a generative model, like Gaussian mixture, Naive Bayes, Hidden Markov.
Cluster-and-label: Use a clustering algorithm (unsupervised), take the labels of the majority of labeled data.
[Introduction to semi-supervised learning](http://pages.cs.wisc.edu/~jerryzhu/pub/sslicml07.pdf).
Can define a graph of similarities.
* Co-training. Semi-supervised learning. Each sample is encoded with two strong and different features, ie text and image.
Train one classifier per feature, then have the two classifiers teach eachother. Multiview 
* Active learning. Training phase done in batches, most important/pivotal candidates then labeled.
[Novak 2010](http://vhosts.eecs.umich.edu/ssp2012/nowak.pdf), active learning using binary search in low-rank embedding space.
* Generative Adverserial learning. Is/can it be used outside of GAN?
* Human/user-in-the-loop. Ask the user about the correct label
* Synthesising samples. Oversampling: duplicate some samples as-is.
Randomly sample attributes.
SMOTE, especially for balancing minority classes.
Example: [librosa sound augmentation](https://www.kaggle.com/huseinzol05/sound-augmentation-librosa)
* Programmatic supervision. Distant supervision. 
* Weak supervision. [Data Programming](http://dawn.cs.stanford.edu/pubs/snorkel-nips2016.pdf)
generates labels that are noisy and possibly conflicting, then learns the inaccuracies.

Data Augmentation

* [mixup: Beyond Empirical Risk Minimization](https://arxiv.org/abs/1710.09412). FB Research, 2017.
Data-agnostic data augmentation technique.
Improves generalization.
Very simple, done by mixing two sample files and their labels.
* Cutout / random erase
* [deepaugment](https://github.com/barisozmen/deepaugment). Learn augmentation strategies from dataset, using Bayesian Optimization

Deep learning

* [Andrej Karpathy: A Recipe for Training Neural Networks](https://karpathy.github.io/2019/04/25/recipe/)

Statistics

* [Cloudera: Common Probability Distributions: The Data Scientist’s Crib Sheet](https://blog.cloudera.com/blog/2015/12/common-probability-distributions-the-data-scientists-crib-sheet/).
Explains different probability distributions, their relationships and usages.

