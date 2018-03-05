
#include <stdio.h>

#include "pid.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(pid, m) {
    m.doc() = "PID regulator";

    py::class_<PID>(m, "PID")
        .def(py::init<>())
        .def_readwrite("kP", &PID::kP)
        .def_readwrite("kI", &PID::kI)
        .def_readwrite("kD", &PID::kD)
        .def_readwrite("dt", &PID::dt)
        .def("next", &PID::next);
}

