
\newpage
# Introduction

## Definitions

### Environmental noise

Noise is unwanted sound. Environmental noise is the summary of noise pollution from outside,
caused by transport, industrial and recreational activities.

Road traffic is the most widespread source of environmental noise.
Noise from railways, air traffic and industry are also important sources of noise.

### Sound level

Sound level is measured in decibel (dB).
0dB is the threshold of hearing, at $20\e{-6} Pascal$ relative sound pressure. 
The level is normally A-weighted, which simulates the frequency response of human hearing.

![Descibel scale with common noise sources](./images/decibel-scale.jpg)

### Equivalent Continious Sound Level

The sound level is constantly changing.
To get a single number representation, the sound level is averaged over a time period **T**.

![Equivalent continious sound level](./images/equivalent-continious-level.jpg)


## Background

### Regulations

Environmental noise is regulated in the EU by the Environmental Noise Directive (2002/49/EC)[@EuNoiseDirective].
The purpose of the directive is to:

* determine peoples exposure to environmental noise
* ensuring that information on environmental noise and its effects is available to the public
* preventing and reducing environmental noise where necessary
* preserving environmental noise quality where it is good

The Directive requires Member States to prepare and publish noise maps and noise management action plans every 5 years for:

* agglomerations with more than 100,000 inhabitants
* major roads (more than 3 million vehicles a year)
* major railways (more than 30.000 trains a year)
* major airports (more than 50.000 movements a year, including small aircrafts and helicopters)

The Directive does not set limit or target values, nor does it prescribe the measures to be included in the action plans.
This is up to authorities of each individual Member State.

However, Environmental Noise Directive defines *indicators* for noise pollution:

$L_{den}$: Designed to assess overall annoyance.
It refers to an annual average day, evening and night period of exposure.
Evening are weighted 5 dB(A) and a night weighting of 10 dB(A).
Indicator level: 55dB(A).

$L_{night}$: Designed to assess sleep disturbance.
It refers to an annual average night period of exposure.
Indicator level: 50dB(A).

In Norway, the coverning legislation for noise pollution is [@Forurensningsloven],
which implements the EU directive.

### Health impact

According to European Commission introduction on the Health effects of Noise [@EuNoiseHealthEffects],
Noise pollution the second environmental cause of health problems in Europe, after air pollution.

Sleepers that are exposed to night noise levels above 40dB on average throughout
the year can suffer health effects like sleep disturbance and awakenings.
Above 55dB long-term average exposure, noise can trigger elevated blood pressure and lead to ischaemic heart disease.
The WHO has set a Night Noise Guideline level for Europe at 40 dB $L_{night}$.

According to a report done on behalf of the European Commision[@RVIMTransportationNoise]

"The exposure to transportation noise in Europe led in 2011 to about
900 thousand cases of hypertension and 40 thousand hospital admissions due to cardiovascular disease and stroke"
and "the number of cases of premature mortality due to these diseases as a result of noise exposure is about 10 thousand per year.",
and "An estimated 8 million people experience sleep disturbance due to transportation noise and about 4 million perceive this as severe".


### Noise measurements

Periodic noise measurements can be done with hand-held Sound Level meters.
Their specifications are standardized in IEC 61672-1 Sound Level Meters[@IECSoundLevelMeters].
Use of a handheld device requires an operator to be present, which limits how often
and at how many locations measurements are made.

![Norsonic Nor140 handheld acoustic measurement unit](./images/nor140.jpg)

Specifically for workplace monitoring, and evaluating risk of hearing impairment
noise dosimeters are also used. They are standardized in IEC 61252 Personal Sound Exposure Meters[@IECPersonalSoundExposureMeters].
These are not used for evaluating environmental noise.

![Cirrus Research DoseBadge5 noise dosimeter](./images/dosebadge5.jpg)

With a continous noise monitoring station, measurement are be done automatically,
giving very good coverage over time.
Many such stations can be deployed to also give good spatial coverage,
operating together in a Wireless Sensor Network.

![CESVA TA120 noise monitoring station](./images/cesva-ta120.png)

### Who may want to track noise

The noise pollutants,
to ensure compliance with noise regulations and protect against false accusations.

* Operators of road, railroad, airports and ports
* Construction and industry companies
* Hotel and apartment managers. Ensure guests dont cause too much noise.
* Restaurants, bar and club managers

Those affected by noise pollution.

* House owners
* Workers
* Pedestrians and bicyclists

Service operator where noise pollution can be an issue for users of service.

* Hospitals
* Schools, kindergarden
* Municipalities
* Departments for roads and infrastructure


### Existing solutions

There are a number of commercially available products for continious noise monitoring.
For outdoor monitoring for industrial and smart-city usage [@CesvaTa120], [@NorsonicNor1531], [@UrbioticaUSound],
[@ScantekScanmonitor], [@RionNa37a] and [@SoundEar320x].
Of these only the SoundEar3-320X has pricing available,
stating that it is the "most affordable external noise monitoring with system prices starting from €2,000".

Fewer products seem to be dediated for continiously indoor noise monitoring alone,
however some "weather station" devices also support sound level (in addition to temperature, humidity and air quality). 
Examples include Netatmo Homecoach [@NetatmoHomecoach] and Archos WeatherStation [@ArchosWeatherStation].

One of the few noise sensor companies that explicitly target consumers is NoiseAware [@NoiseAware].
They provide an indoor sensor which plugs into a mains power socket and communicates over over WiFi,
and an outdoor unit, which is battery powered and communicates via the indoor unit.
As of this time, their units are available for preorder in USA, with international launch "planned for 2019".
The indoor sensors costs 199USD per unit, and the outdoor unit an additional 99USD.
To utilize the sensor, one must also have a subscription at 99USD/year.

In addition to commercial products, a number of research projects have deployed sensor networks for acoustic noise.
This includes SONYC[@Sonyc] in New York City, and the Sentilo[@Sentilo] project in Barcelona.

\newpage
## Problem statement

To enable a more widespread deployment of continious monitoring systems:

Design a sensor node for environmental noise monitoring,
that is substantially cheaper than existing offerings.

The device must be able to measure sound level continiously
and log the measurements to a centralized system.
The system should allow alerting when sound level exceeds define threshold.

Additionally, it is desirable to be able to indicate the sources of noise pollution.

\newpage
# Specifications

## Requirements

Legal

* Designed-for-privacy. Unable to record peoples conversations.

Costs

* Unit production costs `<1000 NOK`
* Installation. `<1000 NOK`
* Running costs. `<1000 NOK/year`

Sound Level Measurements

* Must transmit: Continuous sound level weighting A (LAeqT) in dB(A)
* Frequency weighting: Frequency weighting A, according to 61672-1
* Integration time. Min 1 second - max 1 minute
* Tolerance. From 10Hz to 20kHz, maximum allowed variance LAeq±2dB(A) and/or compliance to
Class 2 limits according to IEC 61672-1.
* Measurement range. Minimum from 40 to 90 dB(A)

Environmental protection

* Weatherproofing grade. IP55+ (IEC 60529)
* Temperature tolerance. Operational: -10C to +40C
* Microphone protection. Windscreen, wind/rain, birds

Physical characteristics

* Mountable on flat surface, such as a wall.
* Size. Under 100x100x30 mm
* Weight. Under 500gram.
* Aestethics. Designed such that homeowners are willing to have it on their wall

Reporting latency

* Measurements updated at least daily.
* Alerts must be given within the hour.

Several of the requirements in sections Sound Level Measurements and Environmental protection are imported from
the specifications for noise sensor in Barcelona[@BarcelonaSoundSensorSpecification].


\newpage
# Design

## Electronics

![Hardware architecture](./images/hw-blocks.png) 

The microphone requires 0.5mA, the microcontroller typically 0.25 mA in always-listening mode.
Amplifier and other is estimated to 0.10mA.
This leaves 0.15mA average as the energy budget for data transmission.

![Bill of Materials](./images/bom.png)

Total component cost is 84 USD, ~750 NOK.
This is below the 1000 NOK target with some margin.

## Power source

With a 1mA energy budget and minimum 1 year lifetime,
the power source needs to supply 1mA@365 days = 8760 mAh.

4x standard 18650 Li-ion have 4*3200 mAh = 12800 mAh capacity.
After accounting for a 2.5% self-discharge per month this should be enough.

![4x 16850 Li-ion cells](./images/4x18650.jpg)

By integrating a charging circuit, the device can be charged
with common phone charger with Micro USB Type-B connector.
Charging time is estimated to be 24 hours at 500mA.

To optionally allow for a continious deployment without needing recharging,
the device also has an external 12-24V power input.
This could be a solar panel energy harvesting system,
mains power or low-voltage from other sensor systems deployed together. 
The batteries would then act like a buffer
and backup for disruptions in the primary energy supply.


## Connectivity
To let the sensor node send its measurements.

To minimize the install costs, the proposed design uses the standard cellular network,
and no custom gateway devices. The network can be 2G with GPRS data connectivity,
or 4G with NB-IoT connectivity.

![SARA cellular module. 2G/3G/4G](./images/sara-module.jpg)

Using 2G/GPRS with COM4.no, monthly fees are 12 NOK.

| Type  | Data/day | Cost/month | Current draw |
| ------- |:-------:|-----:|-----:|
| Leq minute | 1.5 kB | 13 NOK | |
| Leq sec/8 | 691.2 kB |  51 NOK  | |

`TODO: define power utilization`

An alternative to 2G would be 4G/NB-IoT.
1.5 kB over 365 days is 500 kB. Telenor offers NB-IoT with 5 MB/year for 99 NOK.


## Data processing

![Audio processing pipeline for sensor firmware](./images/processing-blocks.png)

The firmware needs to capture microphone input continiously,
and from this compute the `Leq` sound level.
This processing is specified by IEC Sound Level meter standard[@IECSoundLevelMeters].
For the STM32 platform, the provided Sound Meter Library[@STM32SoundMeterLibrary] can be used.

### Noise source identification using machine learning

When the sound level exceeds a configured threshold,
the sensor will collect more detailed information that can be
used to automatically identify the noise source.

The noise profile data is based on the 1/3 octave band, following the standard IEC 61260-1:2014[@IECOctaveBands].
It has been shown that this can be used by a machine learning system to distinguish different noise sources[@AudioCodingSensorGrid].
The paper also demonstrates that when frequency spectrum samples are performed 10 times per second or more seldom,
it is not possible to understand conversations. This preserves the privacy requirement.

To avoid using too much energy, the noise identification trigger has an upper limit
on how often it will record noise profiles.

## Microphone

![CMC-9745-130T microphone capsule](./images/CMC-9745-130T.jpg)

The microphone is the most critical component to ensure high quality acoustic measurements.
Additionally the microphone is the most sensitive component with respect to environmental protection,
as it needs to be protected against water and dust without impacting acoustic performance.
For that reason an IP55 rated microphone was selected, the CMC-9745-130T.

![Microphone frequency response (blue) within tolerance requirements for Class2 (green)](./images/mic-response.png)

While the microphone looks to be within the Class2 standard for frequency tolerance,
it remains to be tested that the entire system can meet the standard.

## Physical

To make a sensor unit that could fit into an office or home, a custom enclosure was designed and prototyped.
In small scale this can be CNC machined, and at larger scales it can be injection molded.

![Prototype viewed from front. Custom enclosure CNC machined from acrylic plastic](./images/proto1-front.jpg)

The overall dimensions required for fitting the 4x 18650 batteries is 100x100x25 mm.
The prototype shown only has height=20mm.

## Installation

The designed enclosure can be attached to any flat surface of more than 100mm using 2 screws.
For medium-term indoor uses it can also be attached using double-sided tape.

![Prototype installed in manufacturing and office space](./images/proto1-installed.jpg)

Example deployments scenarios inside

* In ceiling in office, mic down.
* On wall in industrial space, mic sideways

Example deployment scenarios outside

* Hanging from streetlamp, mics down
* Placed on streetlight pole, mics sideways
* On a moving vechicle used for noise mapping. Bus

To enable the sensor, installer only needs to switch the on button.
Immediately on power-on the sensor will transmit, allowing to verify data transmitted to sensor hub.
The installer can then update the location of the sensor on the map, and add documentation
about its exact placement.
This process should be easy enough that consumers can perform installation themselves.

## Data management platform

The sensor node periodically communicates measurements to the central system over HTTP(S) or MQTT(S).
This system creates aggregate statistics over longer time-periods and from multiple sensors.
A graphical user interface allows users to query these statistics, and see status of the sensor devices.

Pre-made platforms for noise data exist, including Sentilo[@Sentilo],
an open-source[@SentiloGithub] platform developed and used by city of Barcelona since 2013.

![Map showing noise sensors in Barcelona using the Sentilo platform](./images/sentilo-map.png)

# Discussion

* Need very big batteries for always-on measurements
* Unable to provide *Short Leq* (8 per second) measurements
* Microphone consumes majority of energy!
Can one do periodic sampling? As a mode?

# Conclusion

This preliminary design indicates that it is possible to implement a
acoustic noise sensor node with production, installation and running cost under 1000 NOK.
The installation costs are keep low by allowing battery-only operation
and using a mobile network for connectivity.
Existing research indicates that identification of noise sources is
possible using 1/3 octave acoustic measurements.

\newpage
# References
