
## Oslo

"Når det gjennomsnittlige støynivået innendørs over døgnet overskrider 42 dB LpAeq,24h i eksisterende bygninger,
skal det gjennomføres tiltak etter § 5-9. Gjelder rom som er godkjent av bygningsmyndigheten til varig opphold."
Kartlegge støynivå ned til 35 dB LpAeq,24h. Kartleggingen skal oppdateres hvert femte år. 

"Utendørs støynivå skal beregnes med de metoder som er beskrevet i
direktiv 2002/49/EF annex II, som endret ved direktiv (EU) 2015/996."

The attachments defines the noise indicators, measuring setups and requirements for plans to remedy.


https://lovdata.no/dokument/SF/forskrift/2011-12-06-1357/KAPITTEL_3#KAPITTEL_3

https://osha.europa.eu/en/legislation/directives/82

http://stoyforeningen.no/Hva-er-stoey/Arbeidsplass-kontor-skole-barnehage

"Hørselstap som skyldes støy på arbeidsplassen, er den vanligste yrkesskaden i Europa.
Omlag halvparten av meldingene om yrkessykdom Arbeidstilsynet mottar, er meldinger om hørselskader."
https://www.arbeidstilsynet.no/tema/stoy/


## Sentilo

"We expect to release the 1.8 version before the end of the year or the early 19."
https://groups.google.com/forum/#!topic/sentilo/ZddHIuT9oas

`TODO: evaluate Sentilo API for noise measurements`.
Note, can use an adapter service for ingestion if not suitable.


## 

`TODO: image of physical pieces in deployment scenario`

Deployment scenarios.

* House indoors. Battery only
* House outdoor wall. Battery only
* Indoors, fixed power
* Road-pole. Solar power, or from streetlight 

`TODO: concept image of unit`

4 meter +-0.2m specified in some measurements standards.
Should require users to document their sensor placement.
Should re-confirm if power on/off has happened. Or accelerometer detects a move.
`TODO: How should data be adapted when deviating?`

Test mode. For verify working install. 
Measures and sends immediately. When switching hardware button, goes into test mode for N minutes.



## 

Care about accurate detection/inference/prediction.
But also need labeled raw data for evaluation/verification and supervised learning.
To develop the algorithms.

Should mostly run ML classification for sounds that exceed a certain threshold.

Event classification: What was this specific sound
Scene classification: What is the general acoustic sound scene

Questions

* How long does analysis window need to be? Frame length?
* Is it important to be able to calibrate/adjust existing classifications?
