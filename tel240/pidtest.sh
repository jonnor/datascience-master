
c++ -O3 -Wall -shared -std=c++11 -fPIC `pkg-config --cflags python3` pidmodule.cpp -o pid`python3-config --extension-suffix`

python3

import pid
reg = pid.PID()
reg.dt = 0.1
reg.kP = 2.0
reg.next(0.0, 1.0)
reg.next(2.0, 1.0)

