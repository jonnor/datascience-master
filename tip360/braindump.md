## Scope

Technical focus is primarily Passive Acoustic sensors,
where each sensor works indepdendently with one or a few microphones.
No active transducer.

Multichannel audio is within scope, but multi-sensor microphone fusion is out-of-scope. 
Acoustic data can be transmitted in fluids.


The application area focus is monitoring of domestic animals in farming,
and monitoring of wildlife.

Several aspects of the design may be transferrable to other medium-bandwidth sensor technologies,
such as vibration/accelerometer data or low-resolution imaging (visible,infrared).
This is generaly out-of-scope, but it may be relevant to comment briefly on this in the report.


## Terms

* Wireless Sensor Network. WSN
* Wireless acoustic sensor networks. WASN
* Wireless multimedia sensor networks. WMSN

## Topics

* Data compression.
* Compressive sensing.
* On-edge machine learning.
* Audio coding.
* Network topology. Mesh,Star. Routing, Flooding
* Processing power, memory requirements
* Energy source

## Extensions

- Noise modelling
- Traffic estimation
- Human presence detection. Footfall, voice activity
- Pollution estimation. From traffic est plus weather data.
- Domotic event detection. Make alarms be available online. Security, Smoke alarm / CO2 detector.

## Existing products
Indoor industrial

- https://soundear.com/soundear-3/
Easy visual representation of level. Instant-feedback
- Aretas dB Noise Monitor.
http://aretasworks.com/category/db-noise-monitor

Personal Noise dosimeters
Cirrus Research doseBadge® 5
https://www.cirrusresearch.co.uk/products/dosebadge5-noise-dosimeter/
measure to OSHA HCA, OSHA PEL, ACGIH & ISO

https://www.cirrusresearch.co.uk/blog/2018/11/noise-issues-in-uk-hospitals-need-more-than-a-band-aid-solution/
The World Health Organisation (WHO) advises that patients shouldn’t be exposed to noise louder than 35 decibels
Researchers from King’s College London say noise levels in intensive care
– where the most vulnerable patients are looked after – regularly exceed 100 decibels.

## Requirements for machine learning
Definition. Care about accurate detection/inference/prediciton
Raw data needed for evaluation/verification, and supervised learning. While developing.
Calibrate/adjust existing classifications. Report probabilities, not just thresholded decison/class?

Capturing other sensor modalities may also benefit. Picture,vibration

Application specific requirements.

How often to collect samples
How long samples to collect
Analysis window
Frame length
Maximum latency for analysis output
Transmission/upload period
How much raw data to persist
Type of audio detection problem. Event,scene classification. Event detection. Speaker/individual identification.
Precision of event in time
Source localization. Direction, distance
Acoustic challenges. Polyphony,reverberation
Features for machine learning.


### Data representations
Raw audio.
Features for machine learning.
Convolutional Neural Networks
melspectogram

Can mel-scaled spectrograms be used as 'raw' data format?
Requirements: 
- Learn-able. Can be used to train strong methods.
- Annotate-able. Can be labeled by humans to establish ground truth.
Transform back to audio for listening?
- Adaptable, can be used for other purposes than originally intended.
Ex. From birdsong presence detection to bird species classification
Can be used to develop stronger systems as state of art improves, or constraints are relaxed.
- General-purpose. Can be used across a wide range of problems.
Bioacoustics, ecoacoustics, industrial monitoring, security


What is a good compression scheme for specrograms?
Should they be recorded/transmitted raw, or after applying normalization?
Maybe store RMS and median/mean alongside?
What kind of lossy compressions can be tolerated, if any?

Log transform should compress the range a bit. Has also been shown to be beneficial
A COMPARISON OF AUDIO SIGNAL PREPROCESSING METHODS
FOR DEEP NEURAL NETWORKS ON MUSIC TAGGING

#### Image compression on spectograms

First tests in Compression.ipynb in jonnor/birddetect

    birdsong in noisy environment
    10 sec, 64 mels, 12ms frameshift (800 frames)
    8bit log melspec. 55k original

    with PNG
    30k, approx 50% of original
    8bit log melspec, with JPEG
    70% quality. => 8k, approx 15% of original.
    10% quality. => 2k, 4% of original.
    Visibly very degraded, but seems to have preserved the bird calls OK

Looks like 1/10th the size _might_ be realistic!

TODO: test classification with compressed spectograms
Both mismatched (train on originals, test on compressed)
and reduced (train+test on compressed)

TODO: consider other scaling methods. sqrt/cubic, 

"have tried running a JPEG encoder on ESP32, and got about 20 fps at 320×240 when compiling with -Os"
https://hackaday.com/2016/10/31/whats-new-esp-32-testing-the-arduino-esp32-library/#comment-3250015

OpenMV has an MIT licensed software JPEG encoder, optimized for microcontrollers.
Mostly integer math, using precomputed DCT etc.
https://github.com/openmv/openmv/blob/master/src/omv/img/jpeg.c

Ideas:
- 


#### References

Robust Features in Deep-Learning-Based Speech Recognition 
https://www.researchgate.net/publication/320732977_Robust_Features_in_Deep-Learning-Based_Speech_Recognition
Cepstral mean normalization, mean variance normalization

Comparing Time-Frequency Representations for
Directional Derivative Features
https://www.researchgate.net/publication/269097301_Comparing_Time-Frequency_Representations_for_Directional_Derivative_Features
Found cube-root compression to be good, both on Gammatone and Mels
Using Directional Derivative Features, from a Steerable Pyramid Filter-bank.
A generalization of delta-features for arbitrary angles.


### Data

Summary/presentation statistics:

- N/percentage days above threshold (per year,month)
- Histogram of noise values. Per day obervations
- Average/median noise over course of a day. Per-hour bins


### Energy source

Is charging periodically acceptable? Daily or weekly a no-go. Monthly or yearly though?
In industrial setting, may want to perform yearly checkup anyway? Calibration

In a consumer setting, responsibility would be on the consumer.
Some might charge it dilligently

Harvest from sun.
Harvest from existing powergrid. Streetlight.
Harvest from existing lights.

In best case, only need power for half of a day, or during power outtage cases.
In worst case, sun not strong enough for several days/weeks.

Want: Ability to monitor external power source. Minimum: battery level. Ideally: charge current.


Very little sun power in Norway during winter.
Can a battery last all the winter through?
At a cost,size where it is still advantageous

Battery temperature range
Self-discharge rate

Li-ion. Self-discharge rate 5%. Can be operated below 0, but not charged
https://electronics.stackexchange.com/questions/263036/why-charging-li-ion-batteries-in-cold-temperatures-would-harm-them
https://batteryuniversity.com/learn/article/elevating_self_discharge
https://en.wikipedia.org/wiki/Lithium-ion_battery#Uses

LiFePo4.
Safer, lower self-discharge rate.
3.2V nominal. Maximum charge 3.65, 2.5V minimum.
https://en.wikipedia.org/wiki/Lithium_iron_phosphate_battery

Ready-to-install solar power systems. Ex for pole mount
https://www.solarelectricsupply.com/remote-industrial-solar/mapps-pole-mount

Solar power chargers.
MPPT. Mean point

https://www.digikey.com/products/en/integrated-circuits-ics/pmic-battery-chargers/781?FV=ffe0030d&quantity=0&ColumnSort=1000011&page=1&k=solar&pageSize=25

Solar/MPPT pmICs
* SPV1040. Boost converter.
* LT3652

Voltage Proportional Charge Control (VPCC) pmICs:
* MCP73871. Also has battery temp protect over/under with 10k NTC.
Note: Linear. Needs solar powers with above 4.5V output voltage
https://www.digikey.com/product-detail/en/adafruit-industries-llc/390/1528-1400-ND/5638295
Adafruit design notes of charger board. https://learn.adafruit.com/usb-dc-and-solar-lipoly-charger/design-notes






## Measurement standards


    IEC 61252:1993 +AMD1:2000 Personal Sound Exposure Meters
    IEC 61252 Ed 1.1 (2002-03) Personal Sound Exposure Meters
    ANSI S1.25:1991 (R2017) Personal Noise Dosimeters
    IEC 61260-1:2014 Class 2 (Octave Bands from 63Hz to 8kHz)
    ANSI S1.11-2014 Class 2 (Octave Bands from 63Hz to 8kHz)

    Loudness (Zwicker Method- ISO 532 B).
    ITU-R 468. 

IEC 61672 – A Standard for Sound Level Meters Explained
https://www.cirrusresearch.co.uk/blog/2012/07/iec-61672-a-standard-for-sound-level-meters-in-three-parts/

* Part 1, details the performance characteristics that a Class 1 or Class 2 sound level meter should have.
* Part 2 is used by test laboratories, such as the PTB in Germany,
to test instruments to ensure that they do indeed meet the manufacturers claims. This is known as Type or Pattern Approval.
* Part 3 details test that can be carried during a periodic verification.

TA Lärm. German standard.

NEK IEC 61672-1:2013
https://www.standard.no/no/Nettbutikk/produktkatalogen/Produktpresentasjon/?ProductID=668154

Despite the measurement standard being normalized,
certifications are issued by national agencies.

    France: LNE (Laboratoire National de métrologie et d’Essais)
    Germany: PTB (Physikalisch-Technische Bundesanstalt)
    Switzerland:  METAS (Bundesamt für Metrologie)
    Portugal. Instituto Português da Qualidade, I.P.
    Spain: Centro Español de Metrologia (CEM).

### Implementing

A-weighting. Defined in IEC61672-1.
Can be performed in time-domain using FIR/IIR-filter.
https://dsp.stackexchange.com/questions/36077/design-of-a-digital-a-weighting-filter-with-arbitrary-sample-rate
6-tap IIR filter approximation.

Noise meters often report noise in. Octave bands or 1/3 octave bands.
Bandpass filters defined in IEC61260.

https://github.com/python-acoustics/python-acoustics
has dBa conversion, octave-band filters, and the time weighting methods.
Note bug: https://github.com/python-acoustics/python-acoustics/issues/210
http://siggigue.github.io/pyfilterbank/splweighting.html
has the dBa weightin-filter, using 2-order Butterworth


A common way for third-octave analysis is design the highest octave three filters,
and use them on progressively time-decimated versions of the input signal.
Davis S. Octave and fractional-octave band digital filtering based on the proposed ANSI standard; Proceedings of the 1986 IEEE International Conference on Acoustics, Speech and Signal Processing; Tokyo, Japan. 7–11 April 1986.

Antoni presents an alternative analysis method based on direct frequency weighting,
which yields a lower computational complexity as opposed to time filtering.
https://asa.scitation.org/doi/10.1121/1.3273888
Orthogonal-like fractional-octave-band filters








### Ref

An Efficient Audio Coding Scheme for Quantitative and Qualitative Large Scale Acoustic Monitoring Using the Sensor Grid Approach
https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5751573/
Bitrate is about 1.4 kbps
Shows that 1/3 octave filters (31 bands) can classify noises about as well as 20/40 band melspectrogram.


https://github.com/felixgontier/cense-coder
contains reference implementation of proposed approach. Python,MATLAB and STM32
STM32 code seems to use 32KHz samplerate.

### Interest organizations and events

European working group on noise.
Working Group Noise EUROCITIES. Since 2006.
https://workinggroupnoise.com/

EAA. European Acoustics Association.
Non-profit entity established in 1992.
EAA gathers 33 societies of acoustics and serves more than 9000 individual members.
https://euracoustics.org/

Euronoise is the European Conference and Exhibition on Noise Control
INTER-NOISE 2019 MADRID, the 48th International Congress and Exhibition on
Noise Control Engineering to be held on 16 – 19 June 2019 

26th International Congress on Sound and Vibration (ICSV26)
Montréal 7–11 July 201
http://www.icsv26.org/
31.th december. Abstract deadline.
Huge. Over 700 abstracts so far.

23rd International Congress on Acoustics, Sept. 09-13, 2019
Aachen
http://ica2019.org/eaa-euroregio-events/

Urban Sound Symposium
April 3-5, 2019 in Ghent, Belgium
https://urban-sound-symposium.org/

27th European Signal Processing Conference, EUSIPCO 2019
A Coruña, Spain, from September 2 to 6, 2019.
http://eusipco2019.org/

### Deployments


## SONYC
http://wp.nyu.edu/sonyc

1. Mydlarz C., Salamon J., Bello J. The implementation of low-cost urban acoustic monitoring devices. Appl. Acoust. 2017;117:207–218.
doi: 10.1016/j.apacoust.2016.06.010. 

## CENSE
http://cense.ifsttar.fr

Picaut J., Can A., Ardouin J., Crépeaux P., Dhorne T., Écotière D., Lagrange M. Characterization of urban sound environments using a comprehensive approach combining open data, measurements, and modeling. J. Acoust. Soc. Am. 2017;141:3808. doi: 10.1121/1.4988416. [CrossRef]

## Barcelona
??

http://www.sentilo.io/wordpress/urbiotica-sentilo-ready-noise-sensor-successfully-tested/

## Basel
Design of a Mobile Low-Cost Sensor Network Using Urban Buses for Real-Time Ubiquitous Noise Monitoring.
https://www.ncbi.nlm.nih.gov/pubmed/28036065/

## Ghent uni
https://www.scienceandtechnologyresearchnews.com/sensor-networks-monitor-noise-pollution-in-cities/
October 12, 2018 
Road traffic is the most important source of noise emission in urban environments, says Dick Botteldooren, a professor at Ghent University.
“In recent years, we’ve developed dynamic models for forecasting noise that combine traffic simulation with noise levels and propagation and diffusion models,”
“Trees are a natural way to control noise in cities since they contribute to reducing sound propagation,”
“Noise reduction through the planting of vegetation brings cities additional benefits,”

The researchers have already installed sound monitoring stations
Ghent, Antwerp, Brussels, Rotterdam, Paris.
“The idea is to monitor sound in those cities so it becomes possible to
reduce the levels of noise pollution and make the cities smarter in terms of controlling noise emissions,” 

### StadtLärm.
2016 – 2018.
https://www.imms.de/en/science/research-projects/stadtlaerm-2527.html

https://www.slideshare.net/M2M_Alliance/stadtlrm-a-distributed-urban-noise-monitoring-system
System architecture. Stakeholders. MQTT/Mosquitto. Grafana.
Raspberry PI Compute Module hardware.
Auto-encoder on edge, creates audio fingerprint.
Later, plan to move event/scene classification to device.
Plan: 25 sensors, Jena. March

An open platform for distributed urban noise monitoring
https://ieeexplore.ieee.org/document/8249339

### Oslo

Forskrift om begrensning av forurensning, del 2. Støy
https://lovdata.no/dokument/SF/forskrift/2004-06-01-931/KAPITTEL_2#KAPITTEL_2
"Når det gjennomsnittlige støynivået innendørs over døgnet overskrider 42 dB LpAeq,24h i eksisterende bygninger,
skal det gjennomføres tiltak etter § 5-9. Gjelder rom som er godkjent av bygningsmyndigheten til varig opphold."
Kartlegge støynivå ned til 35 dB LpAeq,24h. Kartleggingen skal oppdateres hvert femte år. 

Innenfor byområdene er kommunen ansvarlig for å sammenstille kartleggingen fra de ulike støykildene. Der byområdet består av flere kommuner er kommunen med flest innbyggere ansvarlig.
Utendørs støynivå skal beregnes med de metoder som er beskrevet i direktiv 2002/49/EF annex II, som endret ved direktiv (EU) 2015/996.

Attachments, defines the noise indicators, measuring setups and requirements for plans to remedy.

https://www.oslo.kommune.no/politikk-og-administrasjon/statistikk/miljostatus/trafikkstoy-og-stille-omrader/
14 designated quiet areas.
! is this being monitored? Seems only to be checked every 5 years.
"I midlertid viser støykartleggingen at 12 av 14 områder har fått noe redusert grad av stillhet i perioden fra 2006 til 2016.
Totalt har andelen av arealet som er stille i disse områdene sunket fra 64 til 57 prosent."
"Tilgjengelighet og støynivå skal kartlegges hvert femte år i de stille områdene. Neste kartlegging er planlagt i 2021."

Handlingsplan mot Støy 2018-2023, Oslo Kommune.
https://www.oslo.kommune.no/getfile.php/13300984/Innhold/Politikk%20og%20administrasjon/Milj%C3%B8%20og%20klima/Handlingsplaner%20og%20strategier/Handlingsplan%20mot%20st%C3%B8y%20i%20Oslo%20byomr%C3%A5de.pdf

- Oslo Sporveiene: Utviklet måleprogram for støyovervåking. Årlig siden 2007
- Som del av kommuneplan 2015 er det i Oslo vedtatt avvikssoner for støy. Dette åpner for boligbygging i støyutsatte områder. Rød støysone. 
- Mangler prognoser for trafikkøkning og forventet økning i antall støyutsatte, basert på dagens handlingsplan
- Inspill: For lave ambisjoner mhp. stille områder i Oslo.


Forskrift om begrensning av støy i Oslo kommune, Oslo
https://lovdata.no/dokument/OV/forskrift/1974-10-09-2
Last changed 2015.
Table 1: Allowed noise levels for construction work

Oslo Kommune 2013 report
- 754 skole- og barnehagebygg har støynivåer fra veitrafikk over anbefalt grense på 55 dB,
hvorav 173 slike bygninger har svært høye støynivåer (over 65 dB).
- 103 skole- og barnehagebygg har støy fra skinnegående trafikk over 55 dB,
og 24 bygg har over 65 dB.

Oslo Kommune statistics on noise. Wrt quiet areas, educadtional building
http://statistikkbanken.oslo.kommune.no/webview/index.jsp?headers=r&Omrdesubset=1+-+15&stubs=Omrde&measure=common&virtualslice=Andel_value&layers=virtual&study=http%3A%2F%2F192.168.101.44%3A80%2Fobj%2FfStudy%2FTL-stille-omrader-prosent-areal&mode=cube&v=2&virtualsubset=Andel_value&Omrdeslice=1&rsubset=2006+-+2016&measuretype=4&rslice=2016&cube=http%3A%2F%2F192.168.101.44%3A80%2Fobj%2FfCube%2FTL-stille-omrader-prosent-areal_C1&top=yes

Oslo Havn støy
https://www.oslohavn.no/no/miljo/miljo_i_havna/stoy/
Yearly noise reports. Made by Sweco.
2 sensor stations. Monthly/week plots available
! data ends in July 2018?
http://www.akustikk.info/bekkelagsskraningen/uke_kveld.htm
http://www.akustikk.info/ormoya/mnd_dag.htm

Norsk forening mot Stoy
http://stoyforeningen.no
1200 members, 1.7 employees 2017.
Over 1000 questions yearly about noise.
Members can borrow measurement device.
Or one can buy measurement and report. Costs from 4625 NOK for members. Upto 1.5 hours measurement.
Personal membership 300NOK/year.
Has open yearly reports, detailing noise conditions in Norway.
Has a yearly conference. Nasjonal støykonferanse.

Wireless Sensor Networks for Environmental Noise Monitoring.
Silvia Santini, Andrea Vitaletti, 2007.
! equations for L_eq and L_den
! reference for A weighting
! references for noise mapping measurements

for noise mapping near to buildings, the assessment points must be 4.0 ± 0.2 m above the ground and at the most exposed façade.
Other heights may be used but shall never be less than 1,5 m above ground, and corrected with an equivalent height of 4 m.

for noise pollution measurements sampling frequency may be reduced 32 kHz,
adult humans cannot perceive frequencies above 16 kHz.

Low-Cost Alternatives for Urban Noise Nuisance Monitoring Using Wireless Sensor Networks.
IEEE Sensors, 2014
https://www.researchgate.net/publication/265726706_Low-Cost_Alternatives_for_Urban_Noise_Nuisance_Monitoring_Using_Wireless_Sensor_Networks

Measuring the equivalent noise pressure level (called Leq) to acquite an accurate sound map using wireless networks with acoustic sensors. However, even with similar values of Leq, people can feel the noise differently according to its frequency characteristics.
Thus, indexes which can express people’s feelings by subjective measures are required.
In this paper we analyze the suitability of using the psycho-acoustic metrics given by the Zwicker’s model, instead of just only considering Leq. The goal is to evaluate the hardware limitations of a low-cost wireless acoustic sensor network that is used to measure the annoyance,
using two types of commercial and off-the shelf sensor nodes, Tmote-Invent nodes and Raspberry Pi platforms.
Model measures the Nuisance (N) based on other parameters which are:
Loudness (L), Sharpness (S), Roughness (R) and Fluctuation Strength (F).
Propose different simplifications to approximate these parameters
by taking into account the features of road traffic noise.
The nodes sample the noise, estimate N (measuring L, S, R and F) and finally send the results.
References to noise maps for New York [2], London [3], Munich [4], Beijing [5].
! references for subjective evaluations of road noise
! equations for noise parameters





SoundCompass: A Distributed MEMS Microphone Array-Based Sensor for Sound Source Localization
Sensors 2014.
https://www.mdpi.com/1424-8220/14/2/1918
Current noise mapping techniques often fail to accurately identify noise pollution sources,
because they rely on the interpolation of a limited number of scattered sound sensors.
Aiming to produce accurate noise pollution maps, we developed the SoundCompass,
a low-cost sound sensor capable of measuring local noise levels and sound field directionality.
Our first prototype is composed of a sensor array of 52 Microelectromechanical systems (MEMS) microphones,
an inertial measuring unit and a low-power field-programmable gate array (FPGA).

### Questions
How does Norwegian entities track noise today?

* Road, railroad, airport operators 
* Government. Municipality,fylke,state. Dedicated environmental agencies?



## Literature


### Wireless Sensor Networks
[The Evolution of Wireless Sensor Networks](). Silicon Labs. Whitepaper.
Shows how using a star/mesh network can decrease the transmission power per device, and total power.

[The Design Space of Wireless Sensor Networks](http://www.vs.inf.ethz.ch/publ/papers/wsn-designspace.pdf). Römer. 2004.

[Wireless sensor network survey](https://www.sciencedirect.com/science/article/pii/S1389128608001254). Yick, 2008. !!

### Energy efficiency in Wireless Sensor Networks

[Energy harvesting in wireless sensor networks: A comprehensive review](https://www.sciencedirect.com/science/article/pii/S1364032115012629). 2015. Comprehensive taxonomy of the various energy harvesting sources. Energy prediction models. Challenges.

[Energy conservation in wireless sensor networks: A survey](https://www.sciencedirect.com/science/article/pii/S1570870508000954). Giuseppe Anastasi, 2009. 

[Energy efficiency in wireless sensor networks: A top-down survey](https://www.sciencedirect.com/science/article/pii/S1389128614001418). TifennRault, 2014. Taxonomy of WSN applications. !!

[Survey of image compression algorithms in wireless sensor networks](https://ieeexplore.ieee.org/abstract/document/4631875/). 2008.
A review on eight popular image compression algorithms.
Found that Set-Partitioning in Hierarchical Trees (SPIHT) wavelet-based image compression best.
High compression efficiency and its simplicity in coding

### Wireless Acoustic Sensor Networks

[MEMS microphones for wireless applications](https://www.sciencedirect.com/science/article/pii/B9780081004494000087).

[Audio coding in wireless acoustic sensor networks](https://dl.acm.org/citation.cfm?id=2802336). Zahedi, 2015. ACM, Signal Processing. !!
Combining the measurement and received message at each node instead of forwarding the received messages and separate encoding.
Propose to use the measurement as side information and thereby form a distributed source coding (DSC) problem.

[Development of high performance wireless sensor node for Acoustic application](www.academia.edu/download/44284004/Development_of_high_.pdf). Arul Prabahar A, 2013. !!

## Applications

### Acoustic Emission monitoring
Using the emission of acoustic waves from materials under load/stress/failure.
Alternative to ultrasonic testing in some cases.

Structural health monitoring (SHM),
Quality control. Non-destructive testing
System feedback
Process monitoring

May require capture rates of 100-500kHz.

### Environmental monitoring of animals

[Compressive Sensing for Efficiently Collecting Wildlife Sounds with Wireless Sensor Networks](https://ieeexplore.ieee.org/abstract/document/6289298/). 2012. !!
Determine a sparse base that best represents the audio information used for identifying the target species. As a proof-of-concept, we focus on anuran (frogs and toads). 98% classification rate can be achieved by using as little as 10% of the original data.

[On the effect of compression on the complexity characteristics of wireless acoustic sensor network signals](https://www.sciencedirect.com/science/article/pii/S0165168414003752). Tatlas, 2015. Wireless acoustic sensor network for environmental monitoring is considered.

[Evaluation of MPEG-7-Based Audio Descriptors for Animal Voice Recognition over Wireless Acoustic Sensor Networks](http://www.mdpi.com/1424-8220/16/5/717/htm). Joaquín Luque. Use of generic descriptors based on an MPEG-7 standard. Demonstrate it to be suitable to be used in the recognition of different patterns

[Compressive sensing in wireless sensor network for poultry acoustic monitoring](http://www.ijabe.org/index.php/ijabe/article/view/2148). 2017.
Zigbee based network.

[Wireless sensor networks for environmental research: A survey on limitations and challenges](https://ieeexplore.ieee.org/abstract/document/6624996/). 2013.


### Poaching detection

[Optimization of sensor deployment for acoustic detection and localization in terrestrial environments](https://zslpublications.onlinelibrary.wiley.com/doi/full/10.1002/rse2.97).
We developed probabilistic algorithms for near‐optimal placement of sensors,
and for localization of the sound source as a function of spatial variation in sound pressure.
We employed a principled‐GIS tool for mapping soundscapes to test the methods on a tropical‐forest case study using gunshot sensors.
On hilly terrain, near‐optimal placement halved the required number of sensors compared to a square grid.
Using a Greedy heuristic for near‐optimal placement of detectors.

TMNR is a 25‐km2 area of mature tropical moist forest on undulating topography of 100–400 m elevation.
Detection frequently possible up to 500 m distance from a gun, but much rarer above 1000 m.
Predicted 79 devices within TMNR when applied to the soundscape from 829 gunshots on a 200‐m grid.
50 devices within TMNR (on a 750‐m grid) would achieve a residual detection‐failure probability of 0.237,
which is just bettered by near‐optimal placement of only 26 devices. 

onitoring in the Korup National Park in Cameroon using 12 passive acoustic devices
continuously recording for 2 years detected a high level of shooting within a 54‐km2 grid.

ew advances in radio communication promise the future capability for real‐time detection and localization of exploitation activity,
by linking networked devices to a base station. And are undergoing development for open‐source AudioMoth sensors (Hill et al. 2018)


## Misc

M2M Alliance.
Completely Wireless Realtime Sensor for Smart Factory Applications
https://www.slideshare.net/M2M_Alliance/completely-wireless-realtime-sensors-for-smart-factory-applications
Page 9. Table of requirements for Industrial applications. Latency,reliability,data rate,packet size,operating distance

IO Link. IEC standard for sensor communicaton. IO Link Wireless, based on Bluetooth.
Charge&Go wireless energy transmission. Sensor moves around deterministic path, passed by charging station periodically.
1 second charge, 200 seconds transmit.
EN300 330 standard, 125kHz. 45x45x4mm coil. Up to 5mm distance. Up to 15 watt.

## Hardware

### Microcontroller

NRF52832 only supports BLE5.0 with 1Mpbs.
NRF51 supports lower rates on Enhanced ShockBurst.
NRF52840 supports BLE5.0 long range at 125kbps. Up to 1km range.
[bt832x](http://www.fanstel.com/bt832x-bluetooth-5-module) NRF52832 board with 1km range.

215 EEMBC CoreMark® (3.36 CoreMark/MHz), 58 CoreMark®/mA (Flash)

NRF52 Thingy devkit.
https://www.digikey.no/product-detail/en/nordic-semiconductor-asa/NRF6936/1490-1061-ND/7175577

Has everything needed for prototyping, incl battery.
It is possible to measure the current flowing to nRF52832 by cutting the short on SB2 and placing an ampere
meter between the positive terminal and P1 and positive terminal and P2.

ESP32 power states.

* Modem-sleep: 20-31mA @ 80Mhz, 30-68MHz @ 240Mhz
* Light-sleep: 0.8mA
* Deep-sleep: 10uA - 150uA (ULP co-processor on)

High-speed ADC is not available in deep-sleep.
It seems that I2S pheripheral is also not?

### GPRS modem

GOOUUU TECG IOT-GA6 is not same as AI Thinkerer GA6, but can be reflashed
https://github.com/vshymanskyy/TinyGSM/issues/164
Might be better to go for SIM808 or SIM900A module in future.
Alternatively try to get one of the proper modules.
https://www.aliexpress.com/item/A6-Mini-GSM-GPRS-Development-Quad-band-Board-SMS-Audio-Board-5V-Replace-SIM800L/32756414108.html
https://www.aliexpress.com/item/A6-GPRS-GSM-Module-Adapter-Board-Plate-Quad-band-850-900-1800-1900MHZ-Antenna-F/32729084036.html

Note: TinyGSM says only some modules support TLS/HTTPS.
Test that this works with native TLS stack in ESP32/ESP8266, both for HTTPS and MQTTS.
Amazon IoT requires TLS1.2 with certificates
https://github.com/vshymanskyy/TinyGSM/issues/136
Ublox SARAU201 seems to have such support on device

Other alternative is to use modem in PPP mode. PPPoS = PPP over serial
Should be possible with ESP32 and esp-idk, https://github.com/loboris/ESP32-PPPOS-EXAMPLE

Typical supply voltage: 3.7V-4.2V
SIM800. Sleep-mode: 1.2mA
SIM800C. Sleep-mode: 0.88mA. 
SIM800H. Sleep-mode: 0.7mA
SIM900A. Sleep-mode: 1mA
SARA-G3. Standby: 0.9mA. Connected: `<250mA`

GSM is 1W or 2W max transmit, depending on class/band.
Datarate. 9.05kbps-85.6 kbps

### LTE

LTE category NB1:
Up to 31.25 kb/s UL
Up to 27.2 kb/s DL

SARA N2.
Note: 1.8V supply voltage.
Deep-sleep: 3uA, Active mode: 6mA. RX: 46mA, TX: 70-22mA


# Outdated


### Machine learning in WSNs

[Machine Learning in Wireless Sensor Networks: Algorithms, Strategies, and Applications](https://ieeexplore.ieee.org/abstract/document/6805162/). 2014. 120 citations. Likely many relevant for #embeddedml. !!
Extensive literature review over the period 2002-2013 machine learning methods that were used to address common issues in WSNs.
Provide a comparative guide to aid WSN designers in developing suitable machine learning solutions for their specific application challenges.

[Outlier Detection Techniques for Wireless Sensor Networks: A Survey]()

[Learning from data streams](https://link.springer.com/book/10.1007%2F3-540-73679-4). Book.

[Machine Learning Techniques Applied to Wireless Ad-Hoc Networks: Guide and Survey](https://ieeexplore.ieee.org/abstract/document/4496871/). 2007.

### Data compression

[Compressive sensing meets time–frequency: An overview of recent advances in time–frequency processing of sparse signals](https://www.sciencedirect.com/science/article/pii/S1051200417301665). 2018

[Energy-Aware Data Compression for Wireless Sensor Networks](https://ieeexplore.ieee.org/document/4217341/). Puthenpurayil, 2007.
Explores energy consumption tradeoffs associated with data compression, particularly lossless compression for acoustic signals.

[Data Compression in Wireless Sensor Network: A Survey](http://www.rroij.com/open-access/data-compression-in-wireless-sensornetwork-a-survey-.php?aid=47412). Chetna Bharat Mudgule. Mentions different approaches:

* Data aggregation (clustering,tree-based,chain,sector)
* Distributed Coding
* Predictive Coding. Linear Predictive coding.
* Transform-based Coding
DCT: Discrete Cosine Transform,
DWT: Discrete Wavelet Transform,
DKTL: Discrete Karhunen-Loeve Transform,
Distributed Wavelet Transform-based Lifting (DWT-lifting),
Distributed Wavelet Transform-based Harr (DWT-Harr),
* Compressed Sensing.

[](https://www.scribd.com/document/74166695/A-Survey-on-Data-Compression-in-Wireless-Sensor-Networks).
In terms of power consumption, operation of a wireless sensor node can be dividedinto three parts:
sensing, processing, and transmission.
Among those three operations, it is known that the most power consuming task is data transmission.
Approximately, 80% of power consumed in each sensor node is used for data transmission.
Tested standard lossless compression algorithms, showing gain. But not enough memory on WSN nodes.
bzip2 (BWT algorithm), compress (LZE algorithm), LZO (LZ77), PPMd(PPM), and zlib (LZ77).
Coding by Ordering. Pipelined In-Network Compression. Distributed Compression

[A survey on data compression in wireless sensor networks](https://ieeexplore.ieee.org/document/1425113/). Kimura, 2005.
Coding by ordering, pipelined in-network compression, low-complexity video compression, and distributed compression

[DATA COMPRESSION FOR INFERENCE TASKS IN WIRELESS SENSOR NETWORKS](http://www.ws.binghamton.edu/fowler/Fowler%20Personal%20Page/Publications_files/PhD_Dissertation_Mo_Chen.pdf). Mo Chen, 2006. PhD thesis. !!
"using data compression methods as a tool for accomplishing the optimal trade-off between rate, energy, and accuracy in a sensor network"
"a primary task of multi-sensor systems is to make statistical inferences based on the data collected and shared throughout the sensor system
in the viewpoint of rate, energy, and accuracy, it is important to design data compression methods that enable rapid and low-energy
consumption sharing while causing only minimal degradation of the quantity of these inferences"

[Practical data compression in wireless sensor networks: A survey](https://www.sciencedirect.com/science/article/pii/S1084804511000555). TossapornSrisooksai, 2011.

[Linear Prediction for data compression and recovery enhancement in Wireless Sensors Networks](https://ieeexplore.ieee.org/document/7577156/).
Zakia Jellali, 2016. Linear Prediction Coding (LPC) as a sparsifying transform. Orthogonal Matching Pursuit (OMP) CS algorithm is used for original data recovery.

### Compressed sensing
Aka compressive sensing.

[A Systematic Review of Compressive Sensing: Concepts, Implementations and Applications](). 2018, IEEE Access. MEENU RANI.
Accessible intro, good diagrams. Table over Number of Required Compressive Measurements with different random methods.
Including structured random and determenistic, which does not have to be sent along with signal.
Acquisition strategies: RANDOM DEMODULATOR, MODULATED WIDEBAND CONVERTER (MWC), RANDOM MODULATION PRE-INTEGRATOR (RMPI), RANDOM FILTERING,
COMPRESSIVE MULTIPLEXER, RANDOM EQUIVALENT SAMPLING (RES), RANDOM CONVOLUTION, QUADRATURE ANALOG-TO-INFORMATION
CONVERTER (QAIC), RANDOM TRIGGERING-BASED MODULATED WIDEBAND COMPRESSIVE SAMPLING (RT-MWCS).
! Random Filtering seems easy and applicable to streaming data.
Recovery methods.
Basis Pursuit, Basis Pursuit Denoising (BPDN), Dantzig Selector, Total Variation Denoising (TV).
Convex optimization: BP simplex, BP interior...
Greedy algorithms. Faster but requires knowledge of signal sparsity.
Matching Pursiot, Orthongonal Matching Pursuit.
Compressive sampling matching pursuit (CoSaMP) and subspace pursuit (SP).
Iterative hard thresholding (IHT), Iterative soft thresholding (IST), approximate message passing (AMP).
Fourier sampling, heavy hitters on steroids (HHS), chaining pursuits and sparse sequential matching pursuit. 

Applications in MRI, 3d-imaging, hyperspectral imaging, ultrasound imaging.
DiffuserCam, [Lensless single exposure 3d-imager](http://nuit-blanche.blogspot.com/2017/10/diffusercam-lensless-single-exposure-3d.html).
[3d-ultrasound with single sensor](http://nuit-blanche.blogspot.com/2017/12/compressive-3d-ultrasound-imaging-using.html)

[Introduction to Compressed Sensing](http://www.dfg-spp1324.de/download/preprints/preprint093.pdf). !!

[Compressed Sensing: The big picture](https://sites.google.com/site/igorcarron2/cs).
Acquiring and recovering a sparse signal in the most efficient way possible (subsampling) with the help of an incoherent projecting basis.
Buildling sensing hardware that can directly produced such compressed signals.
Sparse means signal of interest is compressible. Challenge: Need to know with which family of functions it is sparse.
Fourier,polynomials,wavelets.
Many approaches to finding sparse representations/sparse dictionaries. Page lists 11.
Donoho-Tanner phase transition diagram, tool for evaluating whether a signal is compressible with an L1 solver.
Lists a set of 10 different conditions needed to enable sparse recovery.
Lists some 40 different solvers, until 2013.

[Convolutional Dictionary Learning: A Comparative Review and New Algorithms](https://arxiv.org/abs/1709.02893). 2018.

[Single-sensor multispeaker listening with acoustic metamaterials](http://people.duke.edu/~yx35/reprints/Cocktail_party_listener_PNAS2015.pdf)
Hardware approach to multi-source separation. Using 3d-printed waveguides, single sensor.

[Compressive Sensing](https://link.springer.com/referenceworkentry/10.1007%2F978-0-387-92920-0_6). 2011.
Introduction and overview on both theoretical and numerical aspects of compressive sensing

[Compressive Sensing by Random Convolution](https://epubs.siam.org/doi/abs/10.1137/08072975X). 2009. !!
Demonstrates that convolution with random waveform followed by random time-domain subsampling is a universally efficient compressive sensing strategy. 

[Distributed Compressive Sensing](https://arxiv.org/abs/0901.3403). 2009.

[Sparse Representations, Compressive Sensing and dictionaries for pattern recognition](https://ieeexplore.ieee.org/abstract/document/6166711/).
2011, Vishal M. Patel. !!
Compressive Sensing (CS), Sparse Representation (SR) and Dictionary Learning (DL). 
Recent works in SR and CS have shown that if sparsity in the recognition problem is properly harnessed then the choice of features is less critical. What becomes critical, however, is the number of features and the sparsity of representation

Practical Compressed Sensing: modern data acquisition and signal processing. 2011. Becker.
One of the world’s first compressed sensing hardware devices, the random modulation pre-integrator (RMPI). The RMPI

### Spectrogram compression

[Very low bitrate spatial audio coding with dimensionality reduction](https://ieeexplore.ieee.org/document/7952254). 2017.
Using tensor compression based on randomization and partial observations.
A common strategy is to transmit only the downmix of the objects along some small information permitting reconstruction at the decoder. In practice, this is done by transmitting compressed versions of the objects spectrograms and separating the mix with Wiener filters.
Previous research used nonnegative tensor factorizations in this context, with bitrates as low as 1 kbps per object.
Building on recent advances on tensor compression, we show that the computation time for encoding can be extremely reduced. Then, we demonstrate how the mixture can be exploited at the decoder to avoid the transmission of many parameters, permitting bitrates as low as 0.1 kbps per object.

[Reduced dimension image compression and its applications](https://ieeexplore.ieee.org/document/537681).
Reduced dimension image compression (ReDIC) algorithm.
Discuss its application to sonar spectrograms for low-latency, low-cost transmission.
Compare original and reconstructed spectrograms derived from real data at a 52:1 compression ratio.

[Speech reconstruction for MFCC-based low bit-rate speech coding](https://ieeexplore.ieee.org/abstract/document/6890586). 2014.
Speech reconstruction is a key issue in speech coding.
(LSE-ISTFTM) speech reconstruction algorithm for MFCC-based low bit-rate speech coding.

Audio fingerprinting?

### Audio compression 

[A novel audio signal acquisition method for wireless sensor networks](https://ieeexplore.ieee.org/document/6199486). 2011. Han,Zheng.
Two signal acquisition methods based on compressive sensing.


[Random Sampling for Analog-to-Information Conversion of Wideband Signals](http://dept.math.lsa.umich.edu/~annacg/papers/DCAS2006.sparsogram.pdf).
Analog-to-information conversion. Sub-Nyquist acquisition and processing of wideband signals that are sparse in a local Fourier representation.
1. Random sampling system that can be implemented in practical hardware.
2. Information recovery algorithm to compute the spectrogram of the signal, which we dub the sparsogram.

[COMPRESSED SENSING OF AUDIO SIGNALS USING MULTIPLE SENSORS](https://www.researchgate.net/publication/257304755_Compressed_sensing_of_audio_signals_using_multiple_sensors). 2008. Anthony Griffin and Panagiotis Tsakalides.
Compares Signal Distortion Ratio (SDR) of Speech,Music,Birdcall,Impulsive type audio with DCT/DWT and basis/orthononal matching pursuit.
! Birdcall shows very high SDR, when using DCT. Good for denoising? 

[The undersampled wireless acoustic sensor network scenario: Some preliminary results and open research issues](https://ieeexplore.ieee.org/abstract/document/5291252/). Sommer, 2009. Sampling at under the Nyquist rate. Transparent Acoustic Communication (TAC).
Ad-hoc network of microphones, called Distributed Portable Acoustic Sensor (DPAS) network.

[An energy efficient audio compression scheme using wavelet with dynamic difference detection technique in wireless sensor network](https://dl.acm.org/citation.cfm?id=2345456). 2012.
Energy-saving audio data compression technique for WMSN combining wavelet lifting with a newly proposed difference detection technique.

[An energy saving audio compression scheme for wireless multimedia sensor networks using spatio-temporal partial discrete wavelet transform](https://www.sciencedirect.com/science/article/pii/S004579061500316X). Partial discrete wavelet transform (PDWT). Exploit both spatial and temporal correlation of data together. Tree-based routing.

[Effect of downsampling and compressive sensing on audio-based continuous cough monitoring](https://ieeexplore.ieee.org/abstract/document/7319816/). 2015. 98% at full rate. Undersampling to 400Hz 90%. Sampling with compressive sensing at 100Hz also 90%.

[Compressive Sensing in Acoustic Imaging](https://link.springer.com/chapter/10.1007/978-3-319-16042-9_6). Part of book Compressed Sensing and its Applications. Covers Nearfield acoustic holography (NAH), Active sonar, medical ultrasound imaging.

[A Comparative Study of Audio Compression Based on Compressed Sensing and Sparse Fast Fourier Transform (SFFT): Performance and Challenges](https://arxiv.org/abs/1403.3061).
References two other papers about compressed sensing in audio compression.
To obtain exact recovery, the rule of thumb is to apply incoherent sampling and taking measurements 4 times the sparsity level of the signal.
Orthogonal Matching Pursuit one algorithm for doing recovery.
Sparse Fast Fourier Transform can transform in sub-linear time.
Binning Fourier coefficients into a small number of buckets.
The recovery process reduces to extracting the location of the non-zero (index) elements in the matrix A and use them to order the sparse K signal, embed zeros in the other locations and perform inverse FFT.
Considerably simpler than the general compressed sensing case.
Propose an innovative way to embed the indices in the extracted largest frequency bins to relax the need for extra coded values.
! Only tested on a single, unspecified audio file, 15 seconds long.

[A compressive beamforming method](https://ieeexplore.ieee.org/abstract/document/4518185/). Direction of Arrival estimation.

[Avisoft Bioacoustics: Lossy Audio Data Compression Effects](https://www.avisoft.com/compression.htm). Shows some of the effects which can appear in spectrogram from common lossy audio encodings like MP3/AAC.
