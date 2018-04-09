
# TEL240: Control Theory


## References

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

## TODO

* Complete CA3
* Implement PID regulator in MicroFlo
* Complete LAB1,LAB2,LAB3,LAB4
* Decide on project
* Complete 1 previous exam. Write down weakspots
* Complete CA4
* Complete project
* Complete all previous exams

