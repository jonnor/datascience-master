
\newpage
# Introduction

## Background

### Environmental noise

Noise pollution is a major environmental health problem in Europe.

Environmental noise causes approximately 16 600 premature deaths in Europe each year,
with almost 32 million adults suffering from annoyance and over 13 million suffering sleep disturbance.
The WHO has identified noise as the second most significant environmental cause of ill health in western Europe,
the first being air pollution.

Road traffic is the most widespread source of environmental noise,
with more than 100 million people affected by harmful levels in the EEA-33 member countries.
Noise from railways, air traffic and industry are also important sources of noise.

Ref [@EuNoiseSources]

The various directives for common noise sources:
Road traffic noise, Aircraft noise, Railway noise, Noise from Equipment for Use Outdoors


Population exposure to environmental noise
https://www.eea.europa.eu/data-and-maps/indicators/exposure-to-and-annoyance-by-2/assessment-2
Published 19 Jul 2018.
Based on country submissions and redeliveries of the 2012 round of reporting,
eceived by the EEA at the end of March 2017.


The European Union's Seventh Environment Action Programme (7th EAP) sets the objective that by 2020
noise pollution in the EU will have significantly decreased,
moving closer to World Health Organization (WHO) recommended levels. 

The WHO has set a Night Noise Guideline level for Europe at 40 dB Lnight.

For Norway.

* 100k people too much noise from railway
* 900k people too much noise from road day-evening-night, 500k at night
* Half of this in Oslo area
* 200k are sleep disturbed or highly sleep disturbed 
* Trends. "Oslo Data not provided or unsuitable for deriving trends" !!

https://www.eea.europa.eu/themes/human/noise/sub-sections/noise-fact-sheets
Per-country summarizations of noise situation. In 2017


### Regulations

Ref [@EuNoiseDirective]

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


EU indicators for noise pollution
Lden: day-evening-night, 55dB
Lnight: night, 50dB

Lden: Long-term average indicator designed to assess annoyance and defined by the Environmental Noise Directive (END).
It refers to an annual average day, evening and night period of exposure with an evening weighting of 5 dB(A) and a night weighting of 10 dB(A). 
Lnight: Long-term average indicator defined by the END and designed to assess sleep disturbance.
It refers to an annual average night period of exposure.


In Norway, the coverning legislation for noise pollution is [@Forurensningsloven]

"Når det gjennomsnittlige støynivået innendørs over døgnet overskrider 42 dB LpAeq,24h i eksisterende bygninger,
skal det gjennomføres tiltak etter § 5-9. Gjelder rom som er godkjent av bygningsmyndigheten til varig opphold."
Kartlegge støynivå ned til 35 dB LpAeq,24h. Kartleggingen skal oppdateres hvert femte år. 

"Utendørs støynivå skal beregnes med de metoder som er beskrevet i
direktiv 2002/49/EF annex II, som endret ved direktiv (EU) 2015/996."

Attachments, defines the noise indicators, measuring setups and requirements for plans to remedy.


### Noise measurements

Standards

    IEC61672-1. Sound Level Meters. Class 2, Class 1.

    IEC 61252:1993 +AMD1:2000 Personal Sound Exposure Meters
    IEC 61252 Ed 1.1 (2002-03) Personal Sound Exposure Meters
    ANSI S1.25:1991 (R2017) Personal Noise Dosimeters

    IEC 61260-1:2014 Class 2 (Octave Bands from 63Hz to 8kHz)
    ANSI S1.11-2014 Class 2 (Octave Bands from 63Hz to 8kHz)


### Noise monitoring
Continious

Wireless Sensor Networks.


### Noise source identification

Noise meters often report noise in. Octave bands or 1/3 octave bands.
Bandpass filters defined in IEC61260.

1/3 Partial Octave bands.

Machine learning.

### Who may want to track noise

Noise pollutants: To ensure compliance with noise regulations, and protect against false accusations.

* Operators of road, railroad, airports and ports
* Construction and industry companies
* Hotel and apartment managers. Ensure guests dont cause too much noise.
* Restaurants, bar and club managers.

Those affected by noise pollution

* House owners
* Workers
* Pedestrians and bicyclists

Those that are responsible for services where noise pollution can be an issue.

* Hospitals
* Schools, kindergarden
* Municipalities
* Departments for roads and infrastructure

`TODO: describe to which degree monitoring is done today`

https://www.oslo.kommune.no/politikk-og-administrasjon/statistikk/miljostatus/trafikkstoy-og-stille-omrader/
14 designated quiet areas.

"Tilgjengelighet og støynivå skal kartlegges hvert femte år i de stille områdene. Neste kartlegging er planlagt i 2021."

Sporveien. Every year. `TODO: import source`

Handlingsplan mot Støy 2018-2023, Oslo Kommune.
https://www.oslo.kommune.no/getfile.php/13300984/Innhold/Politikk%20og%20administrasjon/Milj%C3%B8%20og%20klima/Handlingsplaner%20og%20strategier/Handlingsplan%20mot%20st%C3%B8y%20i%20Oslo%20byomr%C3%A5de.pdf


### Existing solutions

There are a number of commercially available products for continious noise monitoring for industrial and smart-city usage.
For outdoor monitoring, examples include [@CesvaTa120], [@NorsonicNor1531], [@UrbioticaUSound],
[@ScantekScanmonitor], [@RionNa37a] and [@SoundEar320x].
Of these only the SoundEar3-320X has pricing available,
stating that it is the "most affordable external noise monitoring with system prices starting from €2,000".

Fewer products seem to be dediated for continiously indoor noise monitoring alone,
however some "weather station" devices also support sound level (in addition to temperature, humidity and air quality). 
Examples include [@NetatmoHomecoach] and [@ArchosWeatherStation].

One of the few noise sensor companies that explicitly target consumers is [@NoiseAware].
They provide an indoor sensor which plugs into a mains power socket and communicates over over WiFi,
and an outdoor unit, which is battery powered and communicates via the indoor unit.
As of this time, their units are available for preorder in USA, with international launch "planned for 2019".
The indoor sensors costs 199USD per unit, and the outdoor unit an additional 99USD.
To utilize the sensor, one must also have a subscription at 99USD/year.

In addition to commercial products, a number of research projects have deployed sensor networks for acoustic noise.
This includes [@Sonyc] in New York City, [@].


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

Monitoring

* Battery level.
* Wireless reception level.
* Error log

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

Ref [@BarcelonaSoundSensorSpecification]

* IEC 60529: IP65
* Microphone protection. Windscreen, wind/rain, birds
* correct acoustic functioning: -10oC to +40oC
* battery charge and discharge: 0oC to +40oC
* Independent batteries/without power: the battery life must be a minimum of 3 years
* Connection to the street lighting network: the device must function correctly
between 185-230v. Battery capacity minimum of 19 hours, maximum charge time 5 hours
* Has to send on HTTPS to Sentilo platform. Battery power, 
* Integration time. Min 1 second - max 1 minute
* Must send: Continuous sound level weighting A (LAeqT) in dB(A)
* Frequency weighting: Frequency weighting A, according to 61672-1
* Tolerance: Maximum allowed variance LAeq±2dB(A) and/or compliance of tolerance
limits Class 2 according to IEC 61672-1: from 10 to 20,000 Hz
* Measurement range: Measurement range from 40 to 90 dB(A)
* Linear range without change of scales: 50dB


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

Pre-made.

Sentilo.
http://www.sentilo.io/
Open source platform developed and used by city of Barcelona since 2013.
Have many noise sensors integrated around the city, from multiple manufacturers.
https://github.com/sentilo/sentilo
"We expect to release the 1.8 version before the end of the year or the early 19."
https://groups.google.com/forum/#!topic/sentilo/ZddHIuT9oas

`TODO: evaluate Sentilo API for noise measurements`

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

`TODO: define date-rate needed`

WiFi, cellular.

! WiFi needs an existing network. And a way to configure credentials.
! cellular is zero configuration (for end user). But costs NNN per month

Bluetooth only relevant as an intemediate, for gateways.

`TODO: decide if we can have both`


## Data processing

In firmware

Adjustable Data thinning. Based on battery / power drain.
Adaptive sampling. Sample noise details when noise level is high.

Parameters, can be adjusted in field. Per data-processing period.

In cloud


## Physical

Sensor unit. Integrated battery.
Optional. External power source.

`TODO: image of physical pieces in deployment scenario`

Deployment scenarios.

* House indoors. Battery only
* House outdoor wall. Battery only
* Indoors, fixed power
* Road-pole. Solar power, or from streetlight 

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
