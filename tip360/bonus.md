
### Current situation in Norway and Oslo

For Norway.

* 100k people too much noise from railway
* 900k people too much noise from road day-evening-night, 500k at night
* 200k are sleep disturbed or highly sleep disturbed 
* Trends. "Oslo Data not provided or unsuitable for deriving trends" !!

https://www.eea.europa.eu/themes/human/noise/sub-sections/noise-fact-sheets

Per-country summarizations of noise situation. In 2017

`TODO: describe to which degree monitoring is done today`

Forskrift om begrensning av støy i Oslo kommune, Oslo
https://lovdata.no/dokument/OV/forskrift/1974-10-09-2
Last changed 2015.
Table 1: Allowed noise levels for construction work

"Tilgjengelighet og støynivå skal kartlegges hvert femte år i de stille områdene. Neste kartlegging er planlagt i 2021."

https://www.oslo.kommune.no/politikk-og-administrasjon/statistikk/miljostatus/trafikkstoy-og-stille-omrader/
14 designated quiet areas.

Handlingsplan mot Støy 2018-2023, Oslo Kommune.
https://www.oslo.kommune.no/getfile.php/13300984/Innhold/Politikk%20og%20administrasjon/Milj%C3%B8%20og%20klima/Handlingsplaner%20og%20strategier/Handlingsplan%20mot%20st%C3%B8y%20i%20Oslo%20byomr%C3%A5de.pdf

- Oslo Sporveiene: Utviklet måleprogram for støyovervåking. Årlig siden 2007
- Som del av kommuneplan 2015 er det i Oslo vedtatt avvikssoner for støy. Dette åpner for boligbygging i støyutsatte områder. Rød støysone. 
- Mangler prognoser for trafikkøkning og forventet økning i antall støyutsatte, basert på dagens handlingsplan
- Inspill: For lave ambisjoner mhp. stille områder i Oslo.

Oslo Kommune 2013 report

- 754 skole- og barnehagebygg har støynivåer fra veitrafikk over anbefalt grense på 55 dB,
hvorav 173 slike bygninger har svært høye støynivåer (over 65 dB).
- 103 skole- og barnehagebygg har støy fra skinnegående trafikk over 55 dB,
og 24 bygg har over 65 dB.

Oslo Kommune statistics on noise. Wrt quiet areas, educadtional building

http://statistikkbanken.oslo.kommune.no/webview/index.jsp?headers=r&Omrdesubset=1+-+15&stubs=Omrde&measure=common&virtualslice=Andel_value&layers=virtual&study=http%3A%2F%2F192.168.101.44%3A80%2Fobj%2FfStudy%2FTL-stille-omrader-prosent-areal&mode=cube&v=2&virtualsubset=Andel_value&Omrdeslice=1&rsubset=2006+-+2016&measuretype=4&rslice=2016&cube=http%3A%2F%2F192.168.101.44%3A80%2Fobj%2FfCube%2FTL-stille-omrader-prosent-areal_C1&top=yes


## Desirable

It is desirable that the system can be extended to support related usecases.

- External microphone input. For when specific microphone techology or placement is needed.
- Temperature/humidity sensor. Can be used to compensate for sound. Battery monitoring needs temp.
- Accelerometer. Can be used to compensate sound, and record structure born vibration.
- Can optionally collect raw data, as training data for machine learning.
- Solar irradiance. Could be used to estimate/plan possible future solar-powered system/extension


## EU

When developing noise management action plans, Member States' authorities are required to consult the concerned public.

"Health implication of road, railway and aircraft noise in the European Union"

Environmental Noise Guidelines for the European Region – Executive summary (2018)
http://www.euro.who.int/en/health-topics/environment-and-health/noise/publications/2018/environmental-noise-guidelines-for-the-european-region-executive-summary-2018
Environmental Noise Guidelines for the European Region (2018)
http://www.euro.who.int/en/publications/abstracts/environmental-noise-guidelines-for-the-european-region-2018
Now includes "leisure noise". Lnight down to 44dBA. EU still tracking

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

Oslo Havn støy
https://www.oslohavn.no/no/miljo/miljo_i_havna/stoy/
Yearly noise reports. Made by Sweco.
2 sensor stations. Monthly/week plots available
! data ends in July 2018?
http://www.akustikk.info/bekkelagsskraningen/uke_kveld.htm
http://www.akustikk.info/ormoya/mnd_dag.htm

## Requirements

Monitoring

* Sends battery level.
* Sends wireless reception level.
* Sends error log

Updateable over-the-air

* Sensor processing parameters can be updated.
* Sensor firmware can be updated.
* Any machine learning models can be updated.

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
