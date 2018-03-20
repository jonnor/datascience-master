
// TODO: Use Backward Euler with incremental formulation, 
// TODO: implement integrator anti-windup
// MAYBE, implement first-order filtering on D term
// http://www.mic-journal.no/PDF/ref/Haugen2010.pdf
// http://www.control.lth.se/media/Education/EngineeringProgram/FRTN01/2012/L8_12_Multi.pdf

typedef float pid_number;

class PID {
public:
    pid_number kP;
    pid_number kI;
    pid_number kD;
    pid_number dt;

    pid_number error_prev;
    pid_number error_sum;

public:
    PID()
        : kP(0)
        , kI(0)
        , kD(0)
        , dt(0)
        , error_prev(0)
        , error_sum(0)
    {
    }

    pid_number next(pid_number input, pid_number target) {
        const pid_number error = target - input;

        error_sum += error * dt;

        const pid_number P = (kP * error);
        const pid_number I = (kI * error_sum);
        const pid_number D = (kD * (error - error_prev) / dt);

        printf("e=%.2f, P=%.2f, I=%.2f, D=%.2f\n",
                error, P, I, D);

        error_prev = error;
        const pid_number out = P + I + D;

        return out;
    }
};

#ifdef HAVE_MICROFLO

/* microflo_component yaml
name: PidRegulator
description: First-order PID regulator 
inports:
  in:
    type: integer
    description: ""
    triggering: true
  target:
    type: integer
    description: "Target value for output (setpoint)"
  dt:
    type: integer
    description: "Time difference since last @in"
  kp:
    type: integer
    description: "Proportional gain"
    default: 0
  ki:
    type: integer
    description: "Integral gain"
    default: 0
  kd:
    type: integer
    description: "Derivative gain"
    default: 0
outports:
  out:
    type: integer
    description: ""
microflo_component */


// NOTE: no min/max limits, use Constrain component on @out
// NOTE: no staging on @target jumps, use a ExponentialMovingAverage component
class PidRegulator : public SingleOutputComponent {
private:
    PID reg;
    pid_number target;

public:

    virtual void process(Packet in, MicroFlo::PortId port) {
        using namespace PidRegulatorPorts;

        if (port == InPorts::target) {
            target = in.asFloat();
        } else if (port == InPorts::kp) {
            reg.kP = in.asFloat();
        } else if (port == InPorts::ki) {
            reg.kI = in.asFloat();
        } else if (port == InPorts::kd) {
            reg.kD = in.asFloat();
        } else if (port == InPorts::dt) {
            reg.dt = in.asFloat();
        } else if (port == InPorts::in) {
            const pid_number input = in.asFloat();
            const pid_number out = reg.next(input, target);
            send(out, OutPorts::out);
        }
    }
};

#endif
