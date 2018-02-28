
## 1.1

A 6
B 1
C 9
D 2
E 13
F 4
G 12
H 11
I 8
J 5
L 7
M 10
K 3


## 1.2

### Plane
Controller    e) CPU
Actuators     c) Flaps...
Process       a) Plane
Disturbance   f) Crosswind
Sensors       d) Pilot tubes...
Reference input b) Yoke

### Chemical plant

Controller    b) PID
Controller    e) DCS
Process/plant d) Water tank
Disturbance   a) Leakage
State variable f) Temperature
Actuators      c) Valves

### Human body

Actuators     d) Muscles
Process/plant e) Human body
Controller    a) Gland
Sensors       b) Eyes
Controller and CPU f) Brain
State variable measurement  c) Blood sugar


## 2

### (a)
Derive the equations of motion from the forces that act on the AUV horizon-tally (by using Newton's second law).
Use the velocity `v` as a state variable.


What is the input in this model?

What is the model order?


### (b)
Derive the explicit solution to the differential equation that you found in (a).
For now you can assume that `u` is a constant.


### (c) 
Find an expression for the time constant in the system.


What does the time constant in a dynamical system describe?

What happens with the time constant if we increase `k` ?
What happens with the time constant if we increase the mass of the AUV?

Explain what happens with your own words.



### (d)
You can now assume that `u` is the input.

This means that the general differential equation is in the form.
`ẋ = ax + bu`.
The solution is, however, the same as you found in (b)

Find an expression for the gain of the system.

What happens with the gain as we increase `k`?

Explain what happens with your own words.
From now on, assume that `m = 200kg` and `k = 100kg/s`.

### (e)
Calculate the time constant and the gain.

Explain what this means.

### (f)
JUPYTER

### (g)
JUPYTER

### (h)
Consider an AUV holding a constant velocity of `3m/s`.

Find the required input `u` by:
(i) using the system gain;
(ii) assuming that the derivative part in item (a) is zero.

### (i)
Fig. 4 shows the response of two different AUVs with the same input.
Point out a few relevant differences between the two AUVs.
Consider in particular the differences in gain and time constant,
and explain with your own words what these differences mean.

### (j)
JYPUTER NOTEBOOK


## 3

Draw a block diagram with the temperature in the 'kokeplate' example (4.6 in Kompendium).
Recreate the same response as Figure 4.6.
Print out the response with same set of parameters as the example



