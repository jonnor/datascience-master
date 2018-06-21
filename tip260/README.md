
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
* Bluetooth detection
* Cellphone detection

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


Audio works rather well for traffic density
Vehicular Traffic Density State Estimation Based on Cumulative Road Acoustics


# Key topics

Definition. What is it.
Motivation. What does it help solve
Representative. A picture
Example implementations?

Size: Half a page?
First research and hash out the overall

## Intelligent Traffic System

Traffic estimation/prediction
Adaptive traffic control
Traffic optimization

Road weather
Emergency vehicle notification
Automatic road enforcement
Variable speed limits
Dynamic traffic light sequence
Collision avoidance systems

## Wireless Sensor Network

Many small sensors
Geographically distributed

Sensor types
Connectivity types
NB-IoT, LoRa, Sigfox, 6LoWPAN, WiFi

Network topology
Star, cluster, mesh
Data hub -> Gateway -> nodes

Environmental monitoring
Traffic monitoring
Asset tracking
Machine monitoring
Process monitoring

Healty and safe environment
for workers, public


Energy. Battery, harvesting, fixed

Data all needs to go to a central place

http://www.ni.com/white-paper/7142/en/

## Industry 4.0
smart logistics
production quality system

## Asset tracking
RFID
GPS

## Simulations

Container flow. Inside the port



# Dream design
What would the ideal situation be
What does it take to get there

Shipping activity can be handled
with minimal disruptions on traffic
and local environment
without needing infrastructure investments

## Aspects
Wetport-dryport


## Questions
Thats needs to be answered,
either in daily opertions
or in planning


When should we move containers from/to wetport?
How many trucks/drivers do we need for internal transport?

How much area is needed in wetport?

What are our impacts on traffic,pollution? How to minimize?

## Understanding the problem
Where does containers go/come from?
Are there fixed lines between harbours

When does customer pick up the container to get it out of port?
Same day, same week?

## Maybe useful

### E6
Transportation time to/from Oslo

### Railway station
Passengers per day
Daily distribution
Weekly

## Simulation
Ships
    To port. From port.
    Has containers.
Cars.
    From ferry. To ferry. From outside sources.
Trucks.
    From port. To port. From ferry. To Ferry. From outside sources.
Containers.
    From ship. To ship.
    

### Simulation howto
Methods, tools

Discrete Event Simulation. SimPy
https://simpy.readthedocs.io/en/latest/examples/carwash.html

Traffic Simulation
https://en.wikipedia.org/wiki/Traffic_simulation
Microscopic. Individual car decisions simulated. Car-following model
Mesoscopic. Considers small homogenous groups
Macroscopic. Aggregated relationships like density/flow/mean speed.

SUMO. Interactive Java program. Microscopic sim. Open source. https://github.com/eclipse/sumo
TRANSIM. Open source. Old? Macroscopic? https://sourceforge.net/projects/transims/
Siemens VISSIM. Microscopic simulator. Commercial. Limited trial available. 

Streets4MPI. Python script. Takes Openstreetmap are and number of residents as input. http://jfietkau.github.io/Streets4MPI/

How to validate simulation model using data?
How to adapt model for real-time usage and decision support?
