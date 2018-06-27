
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

* Write definition for Terminal Operating System

* Write technical review of traffic sensors.
Traffic sensors, GPS in truck
* Write technical review of environment senors

* IMAGE: Map of sensors. Traffic,environment
* IMAGE: Dashboard frontpage mockup


## Management system

Keywords

* Container Terminal Operations
* terminal operating system (TOS)
* container terminal operating system
* terminal automation

## Key term
Terminal Operating System

A Terminal Operating Sytem (TOS) is a software application tailored for managing shipping terminal operations.
Its primary purpose is to track the movement of cargo in the port.
A real-time TOS can use data from asset tracking systems to 
automatically keep an updated location of goods and machines.
Common added functionality include gate control and billing.

Using reports from data collected in the TOS, terminal operators can
analyze effectivity and plan improvements. 

Using Electronic Data Exchange (EDI) shipment information can be automatically communicated 
between Terminal Operator, Freight Forwarder and Shipping Line.


### Aspects

* Inventory tracking. Containers, location
* vessel operation
* loading or unloading operations
* Yard Planning
* Yard management. Tracking machines moving around. Warehouse levels
Container stacking, localization
* gate operations
Inland port transportation
Truck management 
* Communication with external actors.
Electronic data interchange (EDI)
EDIFACT,
ANSI X12
Shipping Schedule X12 862 or EDIFACT DELJIT
* billing


## External actors

    Terminal Operators
    Freight forwarder
    Shipping line or shipping agent
    Container Operators
    Port Authority
    Customs Office

### Benefits

Data-driven decision making

## Available

Master Terminal by Jade Logistics

iPortman TOS by Envision.
List of features, https://www.envisionesl.com/products/iportman/solutions/container-terminal-operations/

Navis N4.
http://navis.com/get-more-n4

Octopi.
For small and medium ports. Hosted webservice. https://octopi.co/

Autostore TOS.
https://www.tba.group/autostoretos/

TGI OSCAR.
Small to medium terminals. https://www.tgims.com/en/oscar/

Intermodal Pro by Tideworks.

SaaS based. Intermodal terminal operating system

TOPS EXPERT by RBS EMEA.

### Related


TGIBox. 3D container positioning

https://www.camco.be/solutions/container-terminals/

Micro Location Technology
measures the position of any container
or container handling equipment on your terminal and
can be applied to improve operational efficiency.
It’s based on a combination of UWB distance ranging, DGPS and INS

Crane OCR
Self-service Gate Kiosks with Truck Driver ID card

### References

https://www.porttechnology.org/news/how_to_choose_a_terminal_operating_system
Document the Requirements
Business Process Mapping (BPM)
Turn the Vision and Requirements documents into a Request for Proposal (RFP)

https://www.rbs-emea.com/glossary/container-terminal-operating-system-tos/
Nice overview/definition.

## Datapoints

Average time for container pickup. 4.1 days. Source

In our analysis 100% of containers go to the inland port

## Optimization approach

If wanting to optimize the port operation using machine learning,
what data would be needed.

## GPS tracking

### Keywords

Fleet management
GPS tracking
GPS logging
Elektronisk kjorebok



Internal transport time tracking
How long each transport run takes
Can be collected by ID, for instance in automated gates

Where time was spent
Useful for
GPS tracker on truck

Requirements

Recording interval, 1 minute or more often
Real-time update preferred
API to get data. Realtime and/or historical export


Containers


Trucks

Allowed in Norway for fleet management if there is need
must be discussed with worker representatives
need must be regularly reevaluated
cannot be used for checking on employees
notification must be sent to Datatilsynet

https://www.datatilsynet.no/samfunnsomrader/personvern-pa-arbeidsplassen/gps-sporing_yrkesbiler/
https://lastebil.no/Aktuelt/Nyhetsarkiv/2010-og-eldre/2010/GPS-og-sporing-i-yrkesbiler
GPS OG SPORING I YRKESBILER Veileder, 2017
https://www.datatilsynet.no/globalassets/global/regelverk-skjema/veiledere/gps-og-sporing-2017-030317.pdf

TrackYourTruck
https://www.trackyourtruck.com/fleet-tracking-systems/truck-tracking/


https://ecofleet.no/

Fastpris
https://unitracker.no/flatestyring/

https://itracker.no/gps-tracker/elektronisk-kjorebok

SAGAsystem
Vehco

Dedicated tracking unit

Integrated with navigation system

Integrated with truck
Volvo Dynafleet
Scania Fleet Management
MAN Telematics
Iveco Blue&Me

ODB devices

Independent software for standard GPS devices

https://trackme.lk/devices.php
supports over 50 different device, many protocols
Rest API for. Can be integrated with own software


https://www.traccar.org/devices/

Open Source
Apache License, Version 2.0
https://github.com/traccar/traccar


## Environmental sensors

* Noise. Sound level
* Pollution. Dust, CO2
* Oilspill detection

Early warning
Health & Safety

Workers
Public

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
    TEU loaded/unloaded last hour
    TEU transported last hour
    Waiting time for truck unloading/loading

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
    Loads/unloads containers from boat
Forklift
    Organizes containers inside the port
    Can carry 1 container
Transporter.
    Truck that moves containers between ports.
    Can carry N=(1,2) container
Container.
    Unit of cargo that is transported.
Depot
    Stores containers.
    Has N containers

Cars.
    From ferry. To ferry. From outside sources.
    

Ship -> Crane -> Forklift -> Seaport depot -> Forklift -> Transporter -> Forklift -> Inlandport depot
    unload               stack           unstack       load    unload      stack

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

## Notes Jun 26


Inland port first
Minimize seaport
Technological solutions to make this possible

Traffic looks doable from capacity
How small can the port become.
What benefits does this have
! economic. Depends on ability to charge customers more

Picking service. Move to inland

Faster pickup time
Communicate ideal pickup time to Forwarder.


## RTG versus forkflift comparison

Space utilization. Smaller space. Could calculate based on the type Oslo has
Taller than forklifts
Might not be able to stack so high. Is it a regulatory limit?
Investment costs


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

* autonomous vehicles
* special truck loading solution
* knowing BastoFosen ferry traffic?

Ideas

* Use a service/API for traffic predictions?
HERE, GoogleMaps

## Internal transporation
Do we need to run also at night? Looks like no
How much does electric trucks improve noise?
What are regulations for running at night?

-> google doc

## Container stacking
Container transport prioritized by when they will be picked up by customer
Priority queue

