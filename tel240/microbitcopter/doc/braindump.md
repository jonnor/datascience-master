
## System

* Multicopter weight: 170 grams
* Barometer resolution: 0.083 meter
* Barometer noise: ?
* PID loop time: 20-50 Hz
* PID loop jitter: ?

## Requirements

Key

* Moves from ground level to specified height and then holds it
* Steady state variance `< 5 cm`
* Overshoot `< 20 cm` when making a step change
* Drift `< 10 cm` over 60 second

Bonus

* Smooth transition from manual to automatic mode

Limitations

* Multicopter is kept level. By operator or another stabilizing system
* 

## Combining IMU and barometric data

Barometer

* Which chip is used?? MPL115? BME260
* 

Approaches

* Barometer as height, IMU between steps
* 
* 

Alternate datasources

* Distance sensor. Ultrasonic, infrared, time-of-flight

Kalman filtering
Complementary filter



References

* [IMU data fusing](http://www.olliw.eu/2013/imu-data-fusing/).
Performing 1D
Compares complementary filter, the Kalman filter (constant matrices), and Mahony&Madgwick.
* [Reading a IMU Without Kalman: The Complementary Filter](http://www.pieter-jan.com/node/11).
For estimating angle, using gyro and accelerometer. Incl example code (C)
* [Tinkerforge/imu-barometer-fusion](https://github.com/Tinkerforge/imu-barometer-fusion).
Demo video looks good, Python code example
* FreeIMU. C++/Arduino code. GPLv3
[AltComp](https://github.com/mjs513/FreeIMU-Updates/blob/e99bc1739a175bf4d657531dc3b47f42c727af3d/libraries/AP_Filter/AltitudeComplementary.h),
combines Z acceleration and.
[getEstAltitude](https://github.com/mjs513/FreeIMU-Updates/blob/eda774c0ddce3cb221ac6653dc3e383a5e0aa06c/libraries/FreeIMU/FreeIMU.cpp#L2053)

Flow

* Read sensors. accel, gyro, magnetometer, barometer, temperature.
* Apply sensor calibration
* Calculate quaternion
* Compute acceleration wrt earth
* Combine barometer reading with Z-acceleration
* Regulate

### Record sensor data

Data

* Timestamp
* Gyro 
* Accelerometer XYZ
* Barometer

Scenarios

* Lying still on table
* Moving with (roughly) even speed. Upwards, downwards
* Semi-fast motion up and down
* Tilted sidewards



## TODO

Initial

* Setup Microbit toolchain
* Implement sensor readout
* Record initial sensor data
* Record PWM->force curves

Proof of Concept

Delivery

* Package as MicroBit library

