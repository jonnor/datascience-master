
# TIP260: Digital fabrication 2

## Project
Feasibility study on how Moss port can

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

## TODO


* Write technical review of traffic sensors. Traffic sensors, GPS in truck
* Write technical review of environment senors
* IMAGE: Map of sensors. Traffic,environment
* IMAGE: Dashboard frontpage mockup

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

An Intelligent Traffic System (ITS) is an integrated
digital system that allows to monitor and manage traffic.
Such systems are most often applied for road-based transport,
but can in principle apply to any mode of transportation.

Common applications include automatic toll road payments,
variable speed limits depending on road conditions,
and dynamic traffic light sequences to reduce congestion.

A central part of the ITS system is the collection of relevant traffic data,
such as vehicles numbers by type and the time taken to cover a distance.
This data makes it possible to build realistic traffic models
that perform traffic predictions and simulations.
Such models can help optimize traffic flow based using adaptive traffic control,
evaluate effectiveness of policy changes and estimate robustness to external factors.



## Wireless Sensor Network

In a Sensor Network many individual sensors continiously record data 
and transmits it to a central location for storage and analysis.
They are used across industries for applications such as
Asset tracking, predictive maintenance, process and environmental monitoring.

Wireless Sensor Networks (WSN) are based on wireless radio communication
and frequently use battery power or energy harvesting to be independent from a electricity grid.
This independence lowers cost, simplifies installation of fixed location sensors,
and opens up new possibilities using portable sensors.

Usecases that require when geographically distributed to give good data coverage
like traffic and environmental monitoring benefit especially from wireless sensors. 

Wireless Sensor Network can be based on a network operated by telecom vendor (GSM,NB-IoT),
dedicated on-site networks (LoRa,6LoWPAN) or off-the-shelf consumer technology (WiFi, Bluetooth Low Energy).

http://www.ni.com/white-paper/7142/en/

## Industry 4.0
smart logistics
production quality system

## Asset tracking
RFID
GPS

## Simulation types

Container flow. Inside the port
Traffic

Operational research
Scheduling. When to transport from wet-dry
Warehouse management. Storage,manpower,loading/unloading

Supply chain management
Product Lifecycle Management

Material flow analysis. Tracks individual materials through processes. Mass balance.
Siemens PLM Plant Simulation


# Dream design
What would the ideal situation be
What does it take to get there

Shipping activity can be handled
with minimal disruptions on traffic
and local environment
without needing infrastructure investments

## Dashboard

Frontpage

    Expected TEUs. Incoming/outgoing
    Utilization/capacity in wetport,dryport. TEUs
    TEU transported last hour

    Timeperiod: today

Details

    Internal transport

    Ships incoming/outgoing.

Where are the containers.

    Time to dryport
    Time to wetport
    Loading/unloading times


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
Crane
    Takes containers off boat
Lifttrucks
    Organizes containers
Trucks.
    From port. To port. From ferry. To Ferry. From outside sources.
Containers.
    From ship. To ship.
Cars.
    From ferry. To ferry. From outside sources.


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


## Notes Jun 25

### Solution package
Solution

* Internal transport solution
  * Electrics trucks
  * Fit into existing traffic pattern
  * Traffic monitoring
* (maybe) crane,stackers
* shore electricity for ships
* asset tracking for containers. Solution
* Logistic management solution

Not needed?

* autonomous vechiles
* special truck loading solution
* knowing BastoFosen ferry traffic?

Ideas

* Use a service/API for traffic predictions? HERE, GoogleMaps

## Internal transporation
Do we need to run also at night? Looks like no
How much does electric trucks improve noise?
What are regulations for running at night?

-> google doc

## Container stacking
Container transport prioritized by when they will be picked up by customer
Priority queue

