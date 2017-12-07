
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

Flowhub related

* From Jupyter to cloud-scale service using msgflo-python
* FBP/NoFlo execution for Jupyter. Kernel?. .fbp renderer, component/JavaScript evaluator
* Integrated data visualization for programming, [dataviz](https://github.com/jonnor/projects/tree/master/introspectable-computing/dataviz)

Basic data science applications

* Energy usage at Bitraf/c-base, relative to weather. Anomaly detection, reporting/monitoring
* CNC usage at Bitraf. How many of the jobs/parts can be done on a 60x120 cm workarea machine. Take gcode/dxfs from Dropbox, analyse

Machine learning

* Modelling of guitar distortion (non-linear). Using neural-network?
* Assist in reverse engineering of protocols, for example for machine control (Shopbot,Redsail).
Record input, output pairs. Change input parameters, find corresponding change in output.

Bigger projects, potentially novel

* Machine-vision-assisted construction of . [smart-cad](https://github.com/jonnor/projects/tree/master/smart-cad)
* Automation of CAM paths for maximizing material usage and waste management. Machine-vision
Automatic part layout of useful parts in remainder of cutsheet for CNC/laser.
Automatic creation of cutlines to discard pieces smaller than w,h.
Can a greedy algorithm perform well for part layout, ie does the problem have optimal substructure?

* Component-based PCB autolayout & routing
Reusable modules with pre-laidout schematic/board snippets for a given functionality.
Autolayout by placing modules as black-box rectangles/polygons.
Using reduction in netlist size (implicit ignoring local connections) for better autorouting.
But this can be detected via strongly connected components of the graph?
Note, one can also use [Planarity_testing](https://en.wikipedia.org/wiki/Planarity_testing) to determine subgraphs
which can be laid out without 
Using contraints to express requirements, solving to autosuggest sub-circuit solutions.
http://www.electronicdesign.com/what-s-difference-between/what-s-difference-pcb-routing-then-and-now

## Publishing

[Open Hardware Journal](https://openhardware.metajnl.com/about/#hardware-metapapers)

Is TapeCore/Doverail/fabricatable-machines publishable in Open Hardware Journal?
Could I do the work as a 5-point self-organized topic (ie in robotics)?
Can/should I use NMBU as affiliation? Would they sponsor the publishing costs?
Would/should there be research uses at NMBU for testing practical application?

[Brage @ NMBU](https://www.nmbu.no/en/about-nmbu/library/publishing/brage). Open Access publishing for NMBU affiliates. 
Note: NMBU operates an internal publishing fund for Open Access publications, up to 15k NOK for publication.

[ArXiv](https://arxiv.org). Pre-print / working paper publishing. Widely used open/free source of papers.

[Hackaday Journal](https://journal.hackaday.io/submissions). Possiblity of presenting at the Hackaday Superconference.

## Conferences

* Fablab conference. FAB14 in France
* Open Source Hardware conference.
* FOSDEM
* Libre Graphics Meeting


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

## Interesting subproblems

Neural networks

* When used on images incredibly texture dependent. For instance cause vunerability to adverserial examples.
How to mitigate? Learning rate influences, higher rate, more noise.
* Seem that there is a lot of 'unecessary' complexity/information being encoded, that are irrelevant to the objective at hand.
How can one know how much complexity is needed to perform a particular function? How to estimate that it is well spent?
Are there information-theory approaches that can be applied?
