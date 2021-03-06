
# TEL240: Control Theory

## Topics covered

Regulation
Purpose
Core concepts
Components of a regulated system
Analog

### System modelling

Dynamic systems

Linear systems

* First-order
* Second-order
* Higher-order
* Time delay

Characteristic polynomial

    The coefficients of the characteristic polynomial are all positive
    <=>
    The real part of the roots of the characteristic polynomial are negative

Factorizing polynomials

Natural vs forced response

Differential equations

* As multiple first-order functions

Disturbances

Non-linear phenomenon

* Saturation
* Deadband
* Linearization (lab3)
* Friction of moving body v**2
* Rotary joints. sin(q). Simple pendulum. Robot arm, 6 axis.

Causality
Time-domain
Continious time vs discrete time

Laplace transform, essay-1

* Principle,usefulness
* Forward transform
* Rewrite to forced+natural response
* Initial value theorem
* Final value theorem
* Inverse transform
* Method of Residuals. extra-2-2

Transfer functions

Interpreting. extra-1-5, essay-1
num higher order than den => non-causal
num order == den order => casual with direct transmission
num order < den order => casual without direct transmission

State-space
Matrix representation
From transfer function
To transfer function

Block diagrams

* Elementary blocks. Integral, Sum, Gain
* Formula from diagram
* Diagram from formula
* Simulink

Discretization

* z-transform
* Forward,Backward
* Euler,Tustin

### Regulators

Feedback
In Laplace/transfer domain

PID

* P-controller
* PI-controller
* PID-controller
* Discrete formulation
* Ziegler-Nichols methods. open/closed

Reference tracking
Challenges, solutions
Anti-windup on integral

Lyapunov-based regulation

Model-based regulation

* Forward coupling
* Predictive regulation

Full state feedback
Pole placement control
(pendelum lab)
MATLAB: place(A,B,poles)

Optimal regulation

### Stability
Open vs closed loop.
First-order linear
Second-order linear.
Routh-Hurwith criterion
General linear systems

Lyapunov stability. CA4
BIBO, Bounded Input/Bounded Output

### Example systems

Ship. Speed
Car. Speed
UAV. Speed,position

Watertank.
Pump vs valves as actuator.
Hysteresis, deadband

Heater. Temperature.

Pendelum.

Inverted Pendelum.
Balance one on top of another.
Unstable,non-linear.

Magnetic Levitation. Position
Non-linear
lab3

DC electric motor. Speed, position.
Field control

Car dampener-spring (lab4)
Calculating parameter limits from model

## Out-of-scope
z-domain

Linear-quadratic regulator (LQR)
linear full-state controller
quadratic cost function,
(weighted) sum of costs,
ex deviations from speed/position references,
energy spent on actuation
MATLAB: lqr(A,B,Q,R)
https://www.youtube.com/watch?v=1_UobILf3cc


## References

### Dynamic system models

#### 2. order linear

[1](https://apmonitor.com/pdc/index.php/Main/SecondOrderSystems)

Characterized by:

* Kp, process gain
* Ts, second-order time constant
* C, dampening
* Op, process time delay. Time shift in the input varible `u`.

Can use optimization to find these parameters by fitting model to measured data.
 
* Overdamped. ` C > 1`. Two real, distinct roots
* Critically damped. `C = 1`. Two real, equal roots
* Underdamped. `C < 1`. Two complex conjugate roots.


### Dynamic system simulation in Python

* [Process Dynamics and Control in Python](http://apmonitor.com/pdc/index.php), by Brigham Young University, Utah.
* [ModelsSimulation](http://apmonitor.com/pdc/index.php/Main/ModelSimulation).
Python examples for simulating first, second- and higher-order systems. Using different ways of representing:
(1) transfer function, (2) state space model, and (3) semi-explicit differential equation.

### Software implementation

* [Z transform for the Embedded System engineer](http://www.wescottdesign.com/articles/zTransform/z-transforms.html)
Lists and explains common transforms, relationship to Laplace. Covers implementation concerns including
precision, fixed/floating-point.
"A guideline is that the precision of your math needs to be
better than the precision of your input plus the precision required to accurately express each of the roots of the denominator"
can limit higher-order filters. Solution: break down transfer function to cascade of 1st and 2nd order filters.
Can then use 32bit words for most inputs. Example C++ code (using doubles) for second-order filter and PID.
Explains Bode-plot and gain-phase margins relationship to stability.
6dB and 60 degrees considered safe, 3dB and 30 degrees considered potentially unsafe.
* [Discrete control #3: Designing for the zero-order hold](https://www.youtube.com/watch?v=yetLPW9sQaI),
covers details of going between continious and discrete models. Different z-transform methods have different behavior,
and for correct modelling needs to match what our real-life system is doing.
To design in the s-domain when using Zero-order-hold DAC, can use Pade approximation. 

### Laplace transforms

* [Inverse Laplace transform](http://www.public.asu.edu/~ntao1/Teaching/ECE202/EEE202_Lec13%20[Compatibility%20Mode].pdf).
Incl Finger method, quick way of getting the coefficients from residue method.
Initial and Final Value Theorem can be used to check answers.
Sometimes need lHopitals Rule for Initial Value Theorem: limit of fraction 0/0 or inf/inf is limit of fraction with den/num derived.
* [Laplace tables](http://tutorial.math.lamar.edu/pdf/Laplace_Table.pdf)

### PID controller

Different forms. [1](http://blog.opticontrols.com/archives/124)

* Serial (interactive). Kc,Ti,Td. P gain, then I term, then D term.
* Non-interactive (standard,ideal). Kc,Ti,Td .P gain, then parallel D and I terms.
* Parallel. Kp,Kd,Ki. Not intuitive to tune, as should change D/I gains when changing P gain.

If D term is 0, serial and non-interactive are identical.

Some controllers use Proportional Band setting instead of Kc. PB = 100% / Kc.

Different transfer functions, so tuning parameters must match or be transformed.

### PID tuning

* Ziegler-Nichols.
Can reduce (half) gains to compensate.
Open-loop. Do a step command. Observe process gain, dead time, and time constant.
Assumes first-order system with time-delay. A overdampened second-order system is similar.
A series of first-order sytems is often also.
Cannot be used if output controller has a significant dead-band.
Should not be used on processes where the dead time is longer than half the length of the time constant.
Closed-loop.
Drawback: Will overshoot with resulting parameters (by design 25%, but can often be more).
Might become unstable if process parameters change.

Other tuning algorithms:

* Cohen-Coon. [1](http://blog.opticontrols.com/archives/383).
work well on processes where the dead time is less than two times the length of the time constant.
Has tuning rules for PD-controllers.
* Lambda tuning [1](http://blog.opticontrols.com/archives/260).
Very robust tuning, no overshoot.
Disadvantage: very slow recovery of disturbances, as integral time is set to process time constant.
* [Skogestad’s method](http://www.mic-journal.no/PDF/ref/Haugen2009.pdf), based on a transfer function model of plant.
Covers briefly getting model parameters from experiments.

Modern approaches.

* Selftest by injection of disturbances into live system.
Using frequency response to derive transfer functions for controller, the output rejection, and plant open loop.
[mstarlabs](http://www.mstarlabs.com/control/selftest.html)
* Iterative Feedback technique. Systematic process for which direction to change PI(D) parameters.
IE gives direction, and then using a 'learning rate' to step in that direction, re-test.
[mstarlabs](http://www.mstarlabs.com/control/selftune.html)

### Real system considerations

A number of problems can exist in the actuator that a regulator drives.
Good walkthrough: [Control Valve Problems](http://blog.opticontrols.com/archives/77)

* Deadband. An area where no change appears after changing direction. Can cause oscillation
* Stiction. Gets stuck until a large enough change is applied then moves full distance. Can cause oscillation
* Overshoot. Actuator temporarily goes to far after a change.
* Non-linearity. Changes in control dont result in equal change in output across the operating range.


## TODO

Exam

* Write a summary sheet

Post

* Do a simple project. Basic control with PID regulator
* Do an advanced project. Optimal control with LQR

## Project

### Ideas

* Regulator for 3d-printer hotend temperature
* Regulator for PLA synthesis chamber temperature
* Regulator for PLA recycler in oil temperature
* Closed-loop regulation for DC/brushless motor using optical encoder
* Hot-water mixer for showering.

