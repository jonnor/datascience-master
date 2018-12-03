
\newpage
# Introduction

## Background

### Environmental noise

EU directive 2002/49/EC.
http://ec.europa.eu/environment/noise/directive_en.htm

* the determination of exposure to environmental noise
* ensuring that information on environmental noise and its effects is made available to the public
* preventing and reducing environmental noise where necessary
and preserving environmental noise quality where it is good

The Directive requires Member States to prepare and publish, every 5 years, noise maps and noise management action plans for:

* agglomerations with more than 100,000 inhabitants
* major roads (more than 3 million vehicles a year)
* major railways (more than 30.000 trains a year)
* major airports (more than 50.000 movements a year, including small aircrafts and helicopters)

When developing noise management action plans, Member States' authorities are required to consult the concerned public.

It is important to note, however, that the Directive does not set limit or target values, nor does it prescribe the measures to be included in the action plans, thus leaving those issues at the discretion of the competent Member State authorities.

http://noise.eea.europa.eu/
Interactive maps. Road,rail,airport,industry

EU indicators for noise pollution
Lden: day-evening-night, 55dB
Lnight: night, 50dB

http://ec.europa.eu/environment/noise/sources_en.htm
The various directives for common noise sources:
Road traffic noise, Aircraft noise, Railway noise, Noise from Equipment for Use Outdoors


Population exposure to environmental noise
https://www.eea.europa.eu/data-and-maps/indicators/exposure-to-and-annoyance-by-2/assessment-2
Published 19 Jul 2018.
Based on country submissions and redeliveries of the 2012 round of reporting,
eceived by the EEA at the end of March 2017.

* Noise pollution is a major environmental health problem in Europe.
* Road traffic is the most widespread source of environmental noise,
with more than 100 million people affected by harmful levels in the EEA-33 member countries.
Noise from railways, air traffic and industry are also important sources of noise.
* The European Union's Seventh Environment Action Programme (7th EAP) sets the objective that by 2020
noise pollution in the EU will have significantly decreased,
moving closer to World Health Organization (WHO) recommended levels. 

Lden: Long-term average indicator designed to assess annoyance and defined by the Environmental Noise Directive (END).
It refers to an annual average day, evening and night period of exposure with an evening weighting of 5 dB(A) and a night weighting of 10 dB(A). 
Lnight: Long-term average indicator defined by the END and designed to assess sleep disturbance.
It refers to an annual average night period of exposure.

Environmental noise causes approximately 16 600 premature deaths in Europe each year,
with almost 32 million adults suffering from annoyance and over 13 million suffering sleep disturbance.
The WHO has identified noise as the second most significant environmental cause of ill health in western Europe,
the first being air pollution.

The WHO has set a Night Noise Guideline level for Europe at 40 dB Lnight.

https://www.eea.europa.eu/themes/human/noise/sub-sections/noise-fact-sheets
Per-country summarizations of noise situation. In 2017

Data is tracked with 5dB bins above indicator (50/55 dbA).

For Norway.

* 100k people too much noise from railway
* 900k people too much noise from road day-evening-night, 500k at night
* Half of this in Oslo area
* 200k are sleep disturbed or highly sleep disturbed 
* Trends. "Oslo Data not provided or unsuitable for deriving trends" !!

### Application areas

'anleggseier'

School/kindergarden
House owners. Consumer. Price sensitive.

Property managers with guests.

### Noise measurements

Measurement standards.

IEC61672. Class 2, Class 1.
IEC61260. Performance requirements for analogue, sampled-data, and digital implementations of band-pass filters.
ANSI® S1.11-2004. Bandpass filter
Loudness (Zwicker Method- ISO 532 B).
ITU-R 468. 

TA Lärm. German standard.

### Noise monitoring
Continious

Wireless Sensor Networks.


### Noise source identification

Partial Octave bands
Machine learning.

### Existing solutions

Commercial products. Outdoor

- CESVA TA120.
https://www.cesva.com/en/products/sensors-terminals/TA120/
- Norsonic Nor1531
https://web2.norsonic.com/product/noise-monitoring-terminal-nor1531/
- Urbiotica U-Sound 
https://www.urbiotica.com/en/producto/u-sound-3/
- Scantek Scanmonitor
http://scantekinc.com/products/long-term-monitoring/scantek-scanmonitor2
- Rion NA-37A
https://rion-sv.com/products/10005/NA370009
- SoundEar3-320X
https://soundear.com/soundear3-320x/
- Cirrus MK427 Noise Sensor
https://www.aeroqual.com/product/cirrus-noise-sensor

Prices starting from € 2,000 (SoundEar3-320X)

Commercial products. Indoor

https://soundear.com/soundear-3/
Easy visual representation of level. Instant-feedback

NoiseAware. https://noiseaware.io/  Dec 3rd

Indoor and outdoor sensors available for preorder in USA. International launch in 2019.
Indoor. 199USD + 99USD/year. Plugs into socket. WiFI based connectivity.
Outdoor. 99USD per unit. Battery powered, connects to indoor unit. 


## Problem statement

### Scope

Technical focus is primarily Passive Acoustic sensors,
where each sensor works indepdendently with one or a few microphones.
No active transducer.

Multichannel audio is within scope, but multi-sensor microphone fusion is out-of-scope. 
Acoustic data can be transmitted in air.


Several aspects of the design may be transferrable to other medium-bandwidth sensor technologies,
such as vibration/accelerometer data or low-resolution imaging (visible,infrared).
This is generaly out-of-scope, but it may be relevant to comment briefly on this in the report.

# Requirements

Legal

* Designed-for-privacy. Does not record peoples conversations.

Functionality

* Continious monitoring. Noise measurements are made continiously.
* Noise source identification. Can identify the noise source (class).
* Alerts. Can send alert when problematic noise levels occur.
* History. Allows to view data for a particular sensor at a given time in the past.

Quality

* Standard compliant? Noise measurements follows standards .... `FIXME` reference standard(s)
* Weatherproof. Ability to operate outdoors, in Norwegian climate.
* Aestethic. Designed such that homeowners are willing to have it on their wall.

Costs

* Installation. Can be performed by end-user.
* Maintenance. Not more than once per year.

Updateable

* Sensor parameters can be updated.
* Any machine learning models can be updated.
* Any embedded software can be updated.
* Can optionally collect raw data, as training data for machine learning.

Details

* Reporting latency. Measurements updated at least daily.
* Mountable on wall.
* Size. Under 100x100x30 mm
* Weight. 500gram. Held by single screw.

## Undecided

Measurements. `TODO: can they be subsampled?`


Data quality.
Hard to ensure when end-user installs.
References. Crowdsourcing of data.



#### Costs

`TODO: find prices of existing continious monitoring systems`
Should be 1/10th of that. Enable new business models.
Target `<<1000 NOK`?

Production costs. Parts, manufacturing.

#### Physical placement
Position and orientation of microphone is important.
Should be consistent for all sensors installation.

At head level or higher. Normally away from reflective sources like walls.
4 meter specified in some measurements rules.

Example deployment scenarios

* Hanging from streetlamp, mics down
* Placed on streetlight pole, mics sideways


## Power budget

`TODO: calculate`

## Desireable

Extensible

- External microphone input.
- Temperature/humidity. Can be used to compensate for sound. Battery monitoring needs temp.
- Accelerometer. Structure born vibration.
- Solar irradiance. Could be used to estimate/plan possible future solar-powered system/extension

Verify working install. Test button?
Measures and sends immediately. Maybe go into test mode when first turned on. 


# Design

## System architecture
Sensor nodes. Central service.

No custom gateways.
No custom networks.

Dataprocessing. What happens where.

## Data management platform

Ingestion. In bulk. HTTP. MQTT.
Storage in time-series database. Ex. InfluxDB

`TODO: sanity check data amounts. Devices * daily rate`

## Power source

`TODO: include calculations. power budget, battery size`

Primarily battery-powered. Can run only on battery for 1 year+. Rechargeable.

Advantages.

- Simple install, power source not needed.
Energy harvesting like solar panels. Could get in conflict with other requirements.
Solar panels towards the sun. In an area away from.
At angle, avoid catching snow/leaves/dust.

- Simple design requirements. power budget given by battery capacity.
Energy harvesting depends on installation site. Indoor/outdoor

Challenge
- ultra-low-power design needed
- limits possible data transmission and signal processing. 

Disadvantage
- Does not last forever. Needs charging.
Would be a dealbreaker in rural settings.

Mitigation.
Also allow external low-voltage input (5-24V).
Add-ons for outdoor solar, indoor solar. Off-the-shelf or third-party.


## Connectivity

* WiFi, cellular. `??`

! WiFi needs a way to insert credentials.
! cellular costs NNN per month


## Firmware

### Data processing

Adjustable Data thinning. Based on battery / power drain.
Adaptive sampling. Sample noise details when noise level is high.

Parameters, can be adjusted in field. Per data-processing period.


## Physical

Sensor unit. Integrated battery.
Optional. External power source.

`TODO: image of physical pieces in deployment scenario`

Deployment scenarios.

* House indoors. Battery only
* House outdoor wall. Battery only
* Indoors, fixed power
* Road-pole. Solar power

`TODO: concept image of unit`

## Electronics

Power switch.
Indicator LEDs

`TODO: bill of materials`

`TODO: image of PCB`


# Conclusions

`TODO`

* Summarize features, main design choices
* Summarize costs
* Evaluate feasibility
* Evaluate suitability wrt requirements


# References
