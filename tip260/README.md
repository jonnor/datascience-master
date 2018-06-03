
# TIP260: Digital fabrication 2

## Project

Should ideally be related to an ongoing efforts:

* Embedded Machine Learning (master thesis)
* TapeCore fabricatable machines
* Bioplastic production & recycling

Should be designed, manufactured, tested and documented within 3 weeks.

## Background
Modernization of commercial cargo port in Moss,
using a nearby "dryport" where most of the cargo is stored. 
On-demand transportation, with high degree of automation.

Considerations

* How to create an efficient system?
* How to minimize negative impact on the city?

Understanding the problem

* How long are containers stored at the port? Averages,distribution.
Which factor drives this up/down? How can these be influenced?

### Ideas

EmbeddedML

* Sound-based sensor for (transport) noise level
* Veichle passing sensor. Inductive coil,
* Casing for sensor data collector
* Accelerometer-based sensor for vechile passing
* Power harvesting module. [Hackaday Challenge](https://hackaday.io/prize/details#two)

Bioplastic

* PreciousPlastic shredder redesign for wood + metal inserts.
* Flat-filament hotend + extruder. Partially designed already
* Profile dies for Filastruder. Hollow circle, square tube, 20x20 prof
* Extruder for profile extrusions.
Challenging to make the screw? Maybe it can be milled in slices?

#### Traffic impacts

* Pollution. Dust, CO2
* Noise. Sound level
* Road wear. Weight of car, Number of cars
* Accidents. Speed of cars, road/weather conditions, temperature,humidity

#### Vehicle detection

Sensor tech

* Ultrasound
* Piezoelectric
* Inductive loop
* Magnetic
* Infrared, active
* Millimeter radar
* Pnenumatic tubes
* Video analysis

https://www.quora.com/What-type-of-sensor-is-used-in-vehicle-detection
https://experts.umn.edu/en/publications/portable-roadside-sensors-for-vehicle-counting-classification-and

Features

* vehicle number
* vehicle type
* vehicle speed
+ lane position
++ no changes to road needed 
++ no data infra needed
++ no power infra needed
+ low price
+ also capture other relevant data


