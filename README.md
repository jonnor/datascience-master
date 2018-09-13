
# Master of Data Science

Postgraduate studies in machine learning, data mining and applied statistics.
At Norwegian University of Life Sciences ([NMBU](https://nmbu.no)).

Interests

* Embedded Systems, microcontrollers, Internet of Things. Wireless Sensor Networks. 
* Digital fabrication. CAD/CAM. Electronics, EDA.
* Manufacturing. Low-scale automation. Cheap robotics and deployment.
* Model-based development. Simulations.
* Sustainability
* Circular economy. Recycling, waste-management
* Energy production. Renewable energy
* Agriculture, food-production

## Research projects

### [Machine Learning for Embedded Systems](./embeddedml)

### [Machine Hearing](./machinehearing)

## Competitions

### [DCASE2018](https://github.com/jonnor/birddetect-dcase2018) Bird Audio Detection

### [TrackML](./trackml) Particle tracking

## Courses

### [INF121](https://github.com/jonnor/bike-sharing-oslo)

### [INF200](https://bitbucket.org/jonnor/inf200_jonnordby)

### [INF221](./inf221)

### [INF250](./inf250)

### [DAT200](./dat200)

### [TEL240](./tel240)

### [INF230](./inf230)

### [DAT300](./dat300)

### [DAT390](./dat390)

### [TIP360](./tip360)

## Potential courses

! Still missing 5 sp in 3xx level!

Product development

* [TIP301 Idéutvikling og idéverifisering](https://www.nmbu.no/emne/TIP301). January, 5p. Manual signup. pass/no, project.
* [IND300 Eksperter i team](https://www.nmbu.no/emne/IND300). Janary, 5p. Project report. Limited slots.
* [INN355 Maskinlæring for optimalisering av forretningsprosesser](https://www.nmbu.no/emne/INN355). Spring. 5p with DAT200, else 10p. 2 projects, groups of 4.
* [INN350 Digitalisering og digitale forretningsmodeller](https://www.nmbu.no/emne/INN350). Autumn, 10p. 3 projects, groups of 4.


Distributed systems

* [UNIK4950 - Multiagent-systemer](http://www.uio.no/studier/emner/matnat/its/UNIK4950/index.html). Autumn, 10p
* [INF5040 - Åpen distribuert prosessering](http://www.uio.no/studier/emner/matnat/ifi/INF5040/index.html). Autumn, 10p

Computer vision

* [GMGI300 Geografiske databasesystemer](https://www.nmbu.no/emne/GMGI300). Autumn, 10p. 30% project, 60% exam.
* [UNIK4690 - Maskinsyn](http://www.uio.no/studier/emner/matnat/its/UNIK4690/index.html). Spring. 10p. Project-based evaluation
* [INF5860 - Maskinlæring for bildeanalyse](http://www.uio.no/studier/emner/matnat/ifi/INF5860/index.html). Spring. 10p.
* [UNIK4590 - Pattern Recognition](http://www.uio.no/studier/emner/matnat/its/UNIK4590/index-eng.html). Autumn, 10p

Renewable energy

* [FYS375 Energy Technology](https://www.nmbu.no/emne/FYS375), lab-oriented
* [UNIK4800 - Renewable Energy: science and technology](http://www.uio.no/studier/emner/matnat/its/UNIK4800/index.html). Autumn, 10p
* [UNIK4830 - Solenergisystemer](http://www.uio.no/studier/emner/matnat/its/UNIK4830/index.html). Spring, 10p
* [INF5870 - Energiinformatikk](http://www.uio.no/studier/emner/matnat/ifi/INF5870/index.html). Spring, 10p. Project and oral exam
* [UNIK4820 - Energisystemanalyse: Modellering, metoder og scenarioer](http://www.uio.no/studier/emner/matnat/its/UNIK4820/index.html). Spring,10p

Scientific

* [MNKOM4000 - Formidling og vitenskapsjournalistikk](http://www.uio.no/studier/emner/matnat/ibv/MNKOM4000/index.html). Pass/not, 10p, weekly tasks. Spring
* [UNIK4660 - Visualisering av vitenskapelige data](http://www.uio.no/studier/emner/matnat/its/UNIK4660/index.html)
* [IN5000 - Qualitative Research Methods](http://www.uio.no/studier/emner/matnat/ifi/IN5000/index.html)


## PhD

[Positions in Norway](https://www.finn.no/job/fulltime/search.html?occupation=0.13&q=data)


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

* Analyzing low-cost motion systems.
Using force-sensors on motors/actuator/effector and recording data at high speed
Perform tests on running different kind of jobs.
Measure: static/dynamic friction, coefficient.
Forces due to acceleration.
Forces working back on effector (CNC milling).
Slop. Backlash.
Compare with simulated data, detect anomalies.
Compare different technologies/techniques .
Use to guide development of ultra-low-cost, reprap-style, motion systems.
Note, friction coefficient very dependent on how tight bearings are.
Slop/precision also dependent on this. Especially for plain-bearings.
Should at least measure slop. For instance measure force needed to rotate N degrees?
Could try to tune slop to be same for doing comparative studies?
HEX711 IC commonly used only allows for 80 samples/second.
Would need. A load-cell is a Weathstone bridge, so an instrumentation amplifier is way to go.
ADC can be done in a fast microcontroller. STM32 etc.
Example circuit based on INA125, instrumentation amp with precision voltage reference included:
http://www.mechtechplace.net/mech-tech-electronics/building-a-low-cost-strain-gage-load-cell-amplifier/
INA125 has 4.5kHz bandwith @ 100x gain, should be good for 1k+ samples/second.

Detect failures modes in CNC machining though a model-based approach:
Generate from the CAM files the expected load conditions and compare it continiously, detect and flag anomalies. 
* [Tool breakage detection in CNC high-speed milling based in feed-motor current signals](https://link.springer.com/article/10.1007/s00170-010-2907-9). 
* [Prediction of Cutting Force in 3-Axis CNC Milling Machines Based on Voxelization Framework for Digital Manufacturing](https://ac.els-cdn.com/S2351978915010227/1-s2.0-S2351978915010227-main.pdf?_tid=abd03b3c-bcf8-419f-8e85-6b3b5870b1e8&acdnat=1521660091_5873ea8ff3d1ea396b558157776a4981)


## Publishing

[Open Hardware Journal](https://openhardware.metajnl.com/about/#hardware-metapapers)

[Brage @ NMBU](https://www.nmbu.no/en/about-nmbu/library/publishing/brage). Open Access publishing for NMBU affiliates. 
Note: NMBU operates an internal publishing fund for Open Access publications, up to 15k NOK for publication.

[ArXiv](https://arxiv.org). Pre-print / working paper publishing. Widely used open/free source of papers.

[Hackaday Journal](https://journal.hackaday.io/submissions). Possiblity of presenting at the Hackaday Superconference.

[Modelling, Identification and Control](http://www.mic-journal.no/), Nordic journal. Open Access.


Research relevant Journals

* [Journal listing search](https://newcatalog.library.cornell.edu/catalog?utf8=%E2%9C%93&f%5Bformat%5D%5B%5D=Journal%2FPeriodical&q=wireless+sensor+network&search_field=all_fields)
* MDIP Sensors journal. 15'000 NOK article processing fee.
[Algorithm and Distributed Computing for the Internet of Things](http://www.wikicfp.com/cfp/servlet/event.showcfp?eventid=74395&copyownerid=54155). Nov 30, 2018
[ Green, Energy-efficient and Sustainable Networks](http://www.wikicfp.com/cfp/servlet/event.showcfp?eventid=78650&copyownerid=24832). Jan 15, 2019.
* Wireless Communications and Mobile Computing.
[The Green Internet of Things (G-IoT)](http://www.wikicfp.com/cfp/servlet/event.showcfp?eventid=67602&copyownerid=5416).
2 November 2018.
* IEEE IoTJ.
* [International Journal of Sensors and Sensor Networks](http://www.sciencepublishinggroup.com/journal/index?journalid=130)
* [American Journal of Embedded Systems and Applications](http://www.sciencepublishinggroup.com/journal/index?journalid=236)
* [International Journal of Distributed Sensor Networks](http://journals.sagepub.com/home/dsn/)
* [IEEE IET Wireless Sensor Systems](https://ieeexplore.ieee.org/xpl/RecentIssue.jsp?punumber=5704589)
* [InderScience International Journal of Embedded Systems](http://www.inderscience.com/jhome.php?jcode=ijes#topics2).
Embedded machine learning, deep learning and artificial Intelligence. Bi-monthly.
* [EURASIP Journal on Embedded Systems](https://jes-eurasipjournals.springeropen.com/)

## Conferences

Lists

* [WikiCFP](http://www.wikicfp.com/cfp/call?conference=computer%20science). Loots

Research relevant

* [IEEE FRUCT 2018 : 23nd Conference of Open Innovations Association FRUCT](http://www.wikicfp.com/cfp/servlet/event.showcfp?eventid=74534&copyownerid=98795). Sep 14, 2018. Bologna, Italy
* [IEEE IRC 2019 : Third IEEE International Conference on Robotic Computing](http://www.wikicfp.com/cfp/servlet/event.showcfp?eventid=77145&copyownerid=66527). Oct 5, 2018. Naples, Italy
* [ISCSAI 2018 : 2018 International Symposium on Computer Science and Artificial Intelligence](http://www.wikicfp.com/cfp/servlet/event.showcfp?eventid=66819&copyownerid=55425). Nov 1, 2018. Hong Kong
* [ICUIA 2019 : International Conference on Urban Intelligence and Applications](http://www.wikicfp.com/cfp/servlet/event.showcfp?eventid=78038&copyownerid=121110). Nov 15, 2018. Wuhan, China
* [ICIAE 2019 : The 7th IIAE International Conference on Industrial Application Engineering 2019 ](http://www.wikicfp.com/cfp/servlet/event.showcfp?eventid=74231&copyownerid=58584). Nov 23. Kitakyushu, Japan
* [ICETI 2018 : 2018 3rd International Conference on Engineering and Technology Innovations](http://www.wikicfp.com/cfp/servlet/event.showcfp?eventid=66872&copyownerid=55425). Nov 5, 2018

Digital fabrication, Open source hardware

* Fablab conference. July. FAB14 in France, http://www.fab14.org/
* Open Source Hardware conference.

Open source software

* Open Source Summit Europe 2018. Oct 22-24, Edinbourgh.
[CFP until June 30](https://events.linuxfoundation.org/events/open-source-summit-europe-2018/program/cfp/)
* FOSDEM. February, Brussels

Python

* EuroPython.
* EuroSciPy. 2018. August 28 - September 1, Trento, Italy.

Embedded

* Embedded Linux Conference Europe. [CFP until June 30](https://events.linuxfoundation.org/events/elce-2018/program/cfp/)
* [ECDA 2018](https://euads.org/events/ecda-2018/). European Association for Data Science. Paderborn, Germany, 4th – 6th July, 2018.

Audio

* Linux Audio Conference.

Signal processing

* DAFX. 2018, September, Aveiro Portugal. [CFP March 29](https://www.mail-archive.com/sursound@music.vt.edu/msg09198.html)


## Inbox

* [Hadley Wickham: Tidy data](http://vita.had.co.nz/papers/tidy-data.html).
This paper tackles a small, but important, component of data cleaning: data tidying.

Huge amount of Computer Science papers: https://github.com/papers-we-love/papers-we-love

## References

Books

* [The Elements of Statistical Learning](https://web.stanford.edu/~hastie/Papers/ESLII.pdf).
Recommended by Kristin T. regarding classification, regression methods.

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

* Self learning. [Using Pseudo labeling for semi-supervised learning](https://towardsdatascience.com/simple-explanation-of-semi-supervised-learning-and-pseudo-labeling-c2218e8c769b). After having trained model on labeled data, run it on the unlabeled data to get (pseudo) labels, then train it on the combined setup. Up to 25% pseudo labels in a batch. When method provides confidence score, take only the most confident samples into training set.
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
* Data augmentation. Creating new samples based on peturbations of originals.
Example: [librosa sound augmentation](https://www.kaggle.com/huseinzol05/sound-augmentation-librosa)
* Programmatic supervision. Distant supervision. 
* Weak supervision. [Data Programming](http://dawn.cs.stanford.edu/pubs/snorkel-nips2016.pdf)
generates labels that are noisy and possibly conflicting, then learns the inaccuracies.


