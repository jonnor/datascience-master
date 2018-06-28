
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


Environmental sensors

Introduction
Motivation. Public concerns, health&safety for workers.

* Add section on Water Quality Monitoring

Results
* IMAGE: Map of sensors. Air Quality, Noise

* Recommendations



DATA STRATEGY

* IMAGE: show how data flows to central point
Alternative: Table with datapoints
* IMAGE: how a terminal operating system can look


MAYBE

* Mention automated gates in technical review 




## Terminal Operating System

Keywords

* Container Terminal Operations
* terminal operating system (TOS)
* container terminal operating system
* terminal automation



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

Self-service Gate Kiosks with Truck Driver ID card

Crane OCR

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


GPS truck tracking

Tracking the position of transport trucks over time with a Global Positioning System (GPS) unit
can be used to know exactly where the trucks travel. In a real-time GPS systems with wireless connectivity
this data is available immediately to the logistics operator.
When used by a logistic organisation, such tracking often go under the umbrella term Fleet Management.

The historical data can be used to calculate the typical
and maximum expected transport time from location A to B,
to be used when planning.
Using machine learning, a prediction model can be built,
giving predictions for a specific day and time of day.
The data can be further used to pinpoint problematic areas along the road,
suggesting alternative routes.
Data can then be provided to road authorities when discussing need for improvements.

Due to privacy of the truck drivers GPS tracking use in Norwegian industry
is regulated by Datatilsynet. However usage is allowed for Fleet Management provided that certain conditions are met.
https://www.datatilsynet.no/samfunnsomrader/personvern-pa-arbeidsplassen/gps-sporing_yrkesbiler/

GPS systems are available in many new trucks (Volvo Dynafleet, Scania Fleet Management, MAN Telematics),
or can be installed on existing trucks via a third-party addon (iTracker, Ecofleet).
To facilitate data integration with Terminal Operation System, a real-time GPS
with an Application Programming Interface (API) is preferred.


### Keywords

Fleet management
GPS tracking
GPS logging
Elektronisk kjorebok


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

## Noise sensors

Noise Monitoring is traditionally done by a sound technician using a handheld device
or stationary device for some hours. Afterwards a written report is delivered.
The labour intensive nature means it is costly to perform each measurement.
As a consequence noise measurements are done seldom and covering only few locations. 

Noise Monitoring Terminals are stationary sensors that continiously measure noise
and report to a central system over a wireless connection (WiFi,3G).
Products suitable for monitoring of outdoor environment include
CESVA TA120, Urbiotica U-Sound and Norsonic Nor1531.
Event triggers can be set up to warn when sound levels exceed a defined threshold.
This enables proactive stance to noise pollution, which
makes it easier to respond to complaints and verify compliance with regulations.

### Research

Keywords:

* Noise Monitoring Terminal
* Ambient Noise Monitoring
* personal noise dosemeter

Noise

IEC61672
Class 2, Class 1

CESVA TA120.
https://www.cesva.com/en/products/sensors-terminals/TA120/

Norsonic Nor1531
https://web2.norsonic.com/product/noise-monitoring-terminal-nor1531/

Urbiotica U-Sound 
https://www.urbiotica.com/en/producto/u-sound-3/

Reporting

http://www.miljostatus.no/kart/
Moss havn ikke kartlagt

https://www.vegvesen.no/fag/fokusomrader/Miljo+og+omgivelser/Stoy/Stoykart/Akershus

## Air Quality

Pollution in the air is produced by a range of sources, including transportation vechiles and industrial processes.
A number of health problems like heart disease, stroke and lung cancer are highly related to air pollution.
People breathing in air of poor quality could suffer from difficulty in breathing, coughing, wheezing and asthma.
This can affect both workers of a site, and other people frequenting in the surrounding area.

Because of this the EU has introduces target and limit values for a number of harmful pollutants.

TABLE

Low-cost sensors that can detect many of these pollutants have become available over the last years.
Either designed as a portable device for personal use, or for autonomous stationary operation in a Wireless Sensor Network.
These supplement official measuring stations which give very high quality measurements,
but very limited resolution in time and space due to their costs.
While data quality of low-cost sensors remains a challenge, the higher resolution can give
useful insights in the variation of pollution and possible patterns.
The data can be used for early warning systems, or be analyzed to determine root causes.

Example of low-cost Air Quality Monitors for real-time continious monitoring include
Aeroqual Dust Profiler and AQMesh.

http://ec.europa.eu/environment/air/quality/standards.htm

https://ec.europa.eu/jrc/en/publication/evaluation-low-cost-sensors-air-pollution-monitoring-effect-gaseous-interfering-compounds-and

Keywords:

* Air Quality Monitor
* Air Quality Station

References

Pollutants and treshold values
http://ec.europa.eu/environment/air/quality/standards.htm

http://www.mdpi.com/journal/sensors/special_issues/air_pollution_sensors
MDPI Special Issue, August 2017
In the last five years, the emergence of small-scale air quality sensors has led to a significant paradigm shift in the approach to measuring air quality beyond those afforded by traditional methods that use large, stationary, and expensive analyzers.  These sensors are, not only small, but also can be portable, providing data in near-real time at relatively low costs and using low amounts of power. As a result, sensors allow air quality to be measured with unprecedented temporal and spatial resolution, transforming the way we understand our environment.

Sensors are currently available or being developed to measure ambient concentrations of air pollutants found in air,
e.g., NO, NO2, O3, CO2, CO, CH4, VOC, organic species,
as well as particulate matter (PM) mass in one or more size ranges and components of PM, e.g., black carbon. 

Measuring air pollution with low-cost sensors
https://ec.europa.eu/jrc/en/publication/brochures-leaflets/measuring-air-pollution-low-cost-sensors

Low-cost air quality sensors are attracting more and more attention
They offer air pollution monitoring at a lower cost than conventional methods,
making air quality monitoring possible in many more locations.
"Too good to be true? At the current stage of development, unfortunately yes."
! without quantifying how

Informational brocure summarizing types
http://publications.jrc.ec.europa.eu/repository/bitstream/JRC107461/low_cost_sensors_web.pdf

Electrochemical sensors 
photo ionization detector 
Optical particle counters
Optical sensors
Metal oxide sensors


Evaluation of low-cost sensors for air pollution monitoring: Effect of gaseous interfering compounds and meteorological conditions
https://ec.europa.eu/jrc/en/publication/evaluation-low-cost-sensors-air-pollution-monitoring-effect-gaseous-interfering-compounds-and

Tested electrochemical
for ozone, nitrogen dioxide, carbon monoxide and nitrogen monoxide

"By using calibration coefficient equal to the averages of the effects given in this report, reasonable calibration function could be established.
This result is promising, allowing for future increase of the use of sensors for low cost for air pollution monitoring both by expert institutes and citizen science projects"

Heart disease, Chronic Obstructive Pulmonary Disease (COPD),
stroke and lung cancer are highly related to air pollution.
People breathing in air of poor quality could suffer from difficulty in breathing, coughing, wheezing and asthma.


https://www.aeroqual.com/outdoor-air-quality/particulate-dust-monitors

Benefits of continuous real-time monitoring
Traditional sampling methods like high volume samplers are great for accurate measurement of dust and particulate matter at a fixed point in time or over a 24 hour period, but they cannot indicate exactly when an emissions event occurred. An industrial site needs to know immediately when a problem has occurred so they can put into practice control measures.

https://www.epa.gov/sites/production/files/2015-08/documents/ron_williams-presentation_4_21.pdf

Value of Continuous Measures
• Provides greater understanding of time and location changes
of environmental conditions
• Has the potential of defining critical episodic events that
would otherwise not be discovered
• Helps to define the validity of the data measurement itself
• Needed anytime a mobile measurement is required

!Benzene
VOC. From Gasoline

https://www.sciencedirect.com/science/article/pii/S0160412016309989
Environment International, February 2017

Evaluation of low cost AQMesh units.
In Oslo, between April - September, 2015 

The European Air Quality Directive (EU, 2008) defines the Data Quality Objective (DQO) that monitoring methods need to comply with to be used as indicative measurements for regulative purposes. The DQO is a measure of the acceptable uncertainty for indicative measurements. According to the Directive, allowed uncertainties are 50% for PM10 and PM2.5, 30% for O3 and 25% for CO, NOx, NO2 and SO2.

necessary to perform a field calibration for each sensor individually
NO, PM10 and PM2.5, the expanded uncertainty meets the DQO criteria as defined in the Air Quality Directive
However, other pollutants, e.g., CO, NO2 and O3, show a highly expanded uncertainty that exceeded the DQO for indicative methods
recent studies show that the application of field calibrations based on machine learning techniques can reduce the expanded uncertainty

Good indicator of trends in time

NOT READ YET
http://www.mdpi.com/1424-8220/17/10/2263


Review of Portable and Low-Cost Sensors for the Ambient Air Monitoring of Benzene and Other Volatile Organic Compounds
https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5539520/
2017 Jun 

In Europe, the European Air Quality Directive (AQD [3]) defines as mandatory the monitoring of benzene in ambient air. The AQD states that the reference method for the measurement of BTEX consists of active or on-line sampling followed by desorption and gas chromatography [4]. This method is time consuming, expensive to implement and it needs skilled personnel to perform complex operations.

limit had to be increased up to 5000 € because of the lack of commercial instruments within the 1000 € range.

### Products

Both particle matter and Gas sensors 

Aeroqual Dust Profiler
AQMesh

## Water Quality


* Pollution. Dust, CO2
* Oilspill detection

Early warning
Health & Safety

Workers
Public

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


## Review notes

Frontpage 

    Full-page
    image

Executive Summary

    missing conclusion/recommendation

Introduction
    High level, global -> Regional/Moss -> This report
    Global shipping 
    Economically sustainable

Stakeholders

    Add
    Construction companies
    BaneNOR
    Vegvesnet
    Suppliers

Problem statement

    2 sentences summary of
    Highlight problem statement BIG
    End result is ... understanding of digital technologies relevant to

Goals/objective

    Optimize logistics
        Quantify traffic situation
        Quantify
    
    Finding->Identify
    Drop first bullets level
    Drop indents in financial/economic, own sections
    Rename to sustinability

Project Scope

Key concepts

    Split out self-driving trucks from robotics

Rotterdam
    Quantify size
    Number of TEUs/year, area used

    Add what information is shared

Larvik
    Mention that Greencarrier
    Add figure text

Moss port current sitatution
    Add picture

Terminal operating system
    

Environmental monitoring
    Put into own section

Shore power
    IMAGE: going into ship

Technology/solutions -> rename Available technology

Results
    Total price in mill NOKs

    Sentence about conclusion truck driving

Define that we are planning to move most of the containers
    In results?

Technical Review
    Maybe add a Summary
    Can we move some Results in there?

Added business value
    Predictability
    Guaranteed times
    
    Avoiding peak times

Sustainability
    Environmental impact


Discussion
    Pro/cons

    Feasability of moving all containers to inland port

    Night time transport
    BaneNOR influence

    Financial analysis

    RTG vs stackers

    Environmental. Ref

    Barriers/Challenges for implementing proposed solution

    Our numbers are estimates

Recommendation
    Short term mainly
    One paragraph


Target: Moss Port


