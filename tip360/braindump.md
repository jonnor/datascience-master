
## Terms

* Wireless Sensor Network. WSN
* Wireless acoustic sensor networks. WASN
* Wireless multimedia sensor networks. WMSN

## Topics

* Energy source
* Processing power, memory requirements
* Network architecture.
* Data compression.
* Compressive sensing.
* On-edge machine learning.

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

### Interest organizations

European working group on noise.
Working Group Noise EUROCITIES. Since 2006.
https://workinggroupnoise.com/

EAA. European Acoustics Association.
Non-profit entity established in 1992.
EAA gathers 33 societies of acoustics and serves more than 9000 individual members.
https://euracoustics.org/

Norsk forening mot Stoy
http://stoyforeningen.no
1200 members, 1.7 employees 2017.
Over 1000 questions yearly about noise.
Members can borrow measurement device.
Or one can buy measurement and report. Costs from 4625 NOK for members. Upto 1.5 hours measurement.
Personal membership 300NOK/year.
Has open yearly reports, detailing noise conditions in Norway.
Has a yearly conference. Nasjonal støykonferanse.

### Events

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

Innenfor byområdene er kommunen ansvarlig for å sammenstille kartleggingen fra de ulike støykildene. Der byområdet består av flere kommuner er kommunen med flest innbyggere ansvarlig.
Utendørs støynivå skal beregnes med de metoder som er beskrevet i direktiv 2002/49/EF annex II, som endret ved direktiv (EU) 2015/996.


## Literature

### Noise classification

! noise measurements not always representative

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

### Wireless Sensor Networks
[The Evolution of Wireless Sensor Networks](). Silicon Labs. Whitepaper.
Shows how using a star/mesh network can decrease the transmission power per device, and total power.

[The Design Space of Wireless Sensor Networks](http://www.vs.inf.ethz.ch/publ/papers/wsn-designspace.pdf). Römer. 2004.

[Wireless sensor network survey](https://www.sciencedirect.com/science/article/pii/S1389128608001254). Yick, 2008. !!

### Energy efficiency in Wireless Sensor Networks

[Energy harvesting in wireless sensor networks: A comprehensive review](https://www.sciencedirect.com/science/article/pii/S1364032115012629). 2015. Comprehensive taxonomy of the various energy harvesting sources. Energy prediction models. Challenges.

[Energy conservation in wireless sensor networks: A survey](https://www.sciencedirect.com/science/article/pii/S1570870508000954). Giuseppe Anastasi, 2009. 

[Energy efficiency in wireless sensor networks: A top-down survey](https://www.sciencedirect.com/science/article/pii/S1389128614001418). TifennRault, 2014. Taxonomy of WSN applications. !!


### Wireless Acoustic Sensor Networks

[MEMS microphones for wireless applications](https://www.sciencedirect.com/science/article/pii/B9780081004494000087).

[Audio coding in wireless acoustic sensor networks](https://dl.acm.org/citation.cfm?id=2802336). Zahedi, 2015. ACM, Signal Processing. !!
Combining the measurement and received message at each node instead of forwarding the received messages and separate encoding.
Propose to use the measurement as side information and thereby form a distributed source coding (DSC) problem.

[Development of high performance wireless sensor node for Acoustic application](www.academia.edu/download/44284004/Development_of_high_.pdf). Arul Prabahar A, 2013. !!




## Misc

M2M Alliance.
Completely Wireless Realtime Sensor for Smart Factory Applications
https://www.slideshare.net/M2M_Alliance/completely-wireless-realtime-sensors-for-smart-factory-applications
Page 9. Table of requirements for Industrial applications. Latency,reliability,data rate,packet size,operating distance

IO Link. IEC standard for sensor communicaton. IO Link Wireless, based on Bluetooth.
Charge&Go wireless energy transmission. Sensor moves around deterministic path, passed by charging station periodically.
1 second charge, 200 seconds transmit.
EN300 330 standard, 125kHz. 45x45x4mm coil. Up to 5mm distance. Up to 15 watt.

Environmental Noise Monitoring. Most of the standards in use in the UK require you to use at least a Type 1 or Class 1 meter,
https://www.castlegroup.co.uk/guidance/noise-at-work-assessments/sound-meter-classes/

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

ESP32 power states. REFESP32 Series Datasheet

* Modem-sleep: 20-31mA @ 80Mhz, 30-68MHz @ 240Mhz
* Light-sleep: 0.8mA
* Deep-sleep: 10uA - 150uA (ULP co-processor on)

High-speed ADC is not available in deep-sleep.
It seems that I2S pheripheral is also not?
But low-speed ADC (RTC controller) can handle 200ksps.
12bit SAR.
! +-7LSB differential nonlinearity, +-12 integral nonlinearity.
! "±6% differences between chips"
After calibration, +=40mV for 1500mV range, approx 3%.

Cheapest I2S enabled ARM Cortex. EFM32 Zero Gecko.
I2S availability overview:
https://www.silabs.com/community/mcu/32-bit/knowledge-base.entry.html/2017/10/02/i2s_availabilityon-7Nox

https://www.silabs.com/products/mcu/32-bit/efm32-energy-modes
EM0: 180 µA/MHz run. EM1: 45 µA/MHz sleep mode (DMA+pheripherals). EM2. 0.9 µA/Mhz deep sleep. 2uS wakeup.
Deep sleep retains RAM, 32kHz RTC, and can still have pheripherals??


REF. Low Power Microphone Acquisition and Processing for Always-on Applications Based on Microcontrollers. Sensors2017. Luca Spelgatti

STM32. PDMtoPCM library in STM32Cube.
STM32L4 has hardware PDM filter support. DFSDM = Digital Filter for Sigma Delta Modulators
Ex. STM32L452. 5 USD. 160KB RAM. 256KB FLASH.
Supports PDM in sleep mode. Every 16ms the μC wakes up to process the audio
250uA sleep. 2mA run. With 'low power sound detector', average 360uA.
With voice deteciton, average 1.2mA.

STM32L431. 3 USD. 64KB RAM. 128KB FLASH.
STM32L451 and STM32L471 have more memory, up to 160KB/1024KB.

12bit SAR. 1Msampl. x64 oversampling, 83ksamples


Multimode PDM microphones can be clocked down. Standard compution 700uA. Low power 250uA.

### Microphone

Understanding Microphone Sensitivity
https://www.analog.com/en/analog-dialogue/articles/understanding-microphone-sensitivity.html


ST. Pre-amplifying the analog output 
! Figure 1, nice concise description of sense,noisefloor,SPL/pascal
Equation2. Gain max.
Equation4. Calculating equivalent whitenoise nV/Hz.
MP23AB02B with 64dB SNR has 56nV/Hz.
Noise sources sum as sqrtroot-sum-of-squares
Recommend opamp with 20nV/Hz or lower, 10nV/Hz ideal.
Note: resistors generate noise at 4*srqt(R_kohm) nV/Hz. Ex 100k = 40nV/Hz, 10k = 13nV/Hz
Minimum slew rate must be 0.19 V/us. Should be 1V/us

LMV321L has e_n=31nV/Hz, SR=0.6, Isupply=125uA.
MCP6001 basically same.
MCP603 higher slew rate, consumption.
TLV313 has 26nV/Hz, SR=0.45, 65uA

Reference level. 94dB
Analog microphone is specified in dbV (rms). V=1volv
Digital microphones in dBFS (peak). FS=full-scale, max digital value

Physical type. Module, MEMS PCB component.
Interface type. Analog, PDM, I2S.
Sensitivity.
MEMS range (-46dBFS, -18dBFS ).
Analog mic modules (-100dBA, -25dBA)

Noise floor. `>60dB SNR`, gives noise floor of 94-60=34dB.
Power draw. `<500uA`

Modules available directly with IP6x rating. https://no.mouser.com/Sensors/Audio-Sensors/Microphones/_/N-98yhe?P=1yzscmpZ1yzscms&Rl=98yheZer5eZ1yvtseyZ1yzxckmSGT&Ns=Current%20Rating|0

Vesper PMM-3738. MEMS bottom port. IP57. Piezo.
https://www.digikey.it/product-detail/en/pui-audio-inc/PMM-3738-VM1000-R/668-1577-1-ND/7062069

Analog

* CMC-9745-130T. Module.4-10mm dia. IP65. 500uA.  2 USD.
* Knowles modules available with 50uA rating. 10USD++
* SPM0687LR5H. 285 uA 

ST AN4598 Application note, Pre-amplifying the analog output of a MEMS microphone


Digital

https://no.mouser.com/Sensors/Audio-Sensors/MEMS-Microphones/_/N-98yda?P=1z0yqi5Z1y90qfa&Ns=Operating%20Supply%20Current|0


* PDM. MP45DT02. Used on STM32F4 Discovery. Top-port only! 0.6mA. 20Hz, -7dB, 10kHz, +3dB.
* I2S. ICS-43434. 490uA. Lowest I2S?






SPH0645

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

### Misc
Wireless Sensor Networks for Environmental Noise Monitoring.
Silvia Santini, Andrea Vitaletti, 2007.
! equations for L_eq and L_den
! reference for A weighting
! references for noise mapping measurements

for noise mapping near to buildings, the assessment points must be 4.0 ± 0.2 m above the ground and at the most exposed façade.
Other heights may be used but shall never be less than 1,5 m above ground, and corrected with an equivalent height of 4 m.


SoundCompass: A Distributed MEMS Microphone Array-Based Sensor for Sound Source Localization
Sensors 2014.
https://www.mdpi.com/1424-8220/14/2/1918
Current noise mapping techniques often fail to accurately identify noise pollution sources,
because they rely on the interpolation of a limited number of scattered sound sensors.
Aiming to produce accurate noise pollution maps, we developed the SoundCompass,
a low-cost sound sensor capable of measuring local noise levels and sound field directionality.
Our first prototype is composed of a sensor array of 52 Microelectromechanical systems (MEMS) microphones,
an inertial measuring unit and a low-power field-programmable gate array (FPGA).

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



Audio fingerprinting?

### Audio compression 

[A novel audio signal acquisition method for wireless sensor networks](https://ieeexplore.ieee.org/document/6199486). 2011. Han,Zheng.
Two signal acquisition methods based on compressive sensing.

[Random Sampling for Analog-to-Information Conversion of Wideband Signals](http://dept.math.lsa.umich.edu/~annacg/papers/DCAS2006.sparsogram.pdf).
Analog-to-information conversion. Sub-Nyquist acquisition and processing of wideband signals that are sparse in a local Fourier representation.
1. Random sampling system that can be implemented in practical hardware.
2. Information recovery algorithm to compute the spectrogram of the signal, which we dub the sparsogram.



[The undersampled wireless acoustic sensor network scenario: Some preliminary results and open research issues](https://ieeexplore.ieee.org/abstract/document/5291252/). Sommer, 2009. Sampling at under the Nyquist rate. Transparent Acoustic Communication (TAC).
Ad-hoc network of microphones, called Distributed Portable Acoustic Sensor (DPAS) network.

[An energy efficient audio compression scheme using wavelet with dynamic difference detection technique in wireless sensor network](https://dl.acm.org/citation.cfm?id=2345456). 2012.
Energy-saving audio data compression technique for WMSN combining wavelet lifting with a newly proposed difference detection technique.

[An energy saving audio compression scheme for wireless multimedia sensor networks using spatio-temporal partial discrete wavelet transform](https://www.sciencedirect.com/science/article/pii/S004579061500316X). Partial discrete wavelet transform (PDWT). Exploit both spatial and temporal correlation of data together. Tree-based routing.



[Avisoft Bioacoustics: Lossy Audio Data Compression Effects](https://www.avisoft.com/compression.htm). Shows some of the effects which can appear in spectrogram from common lossy audio encodings like MP3/AAC.
