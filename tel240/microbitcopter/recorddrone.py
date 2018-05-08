import serial
import sys

def main():
    port = '/dev/ttyACM0'
    device = serial.Serial(port=port, baudrate=115200, timeout=0.2) 
    print("Opened", port, file=sys.stderr)

    state = 'wait'
    index = None
    buf = '' 

    def parser1():
        if state == 'wait':
            if d == 'T':
                state = 'controller'
            if d == 'D':
                state = 'drone'
        elif state == 'controller':
            if d == 'D':
                state = 'drone'      
        elif state == 'drone':
            buf += d
            if d == 'N':
                state = 'controller'  
                s = buf.split(',')
                if len(s) == 7:
                    press, pressavg, error, throttle, accI, time, _ = s
                    print(s)
                else:
                    print('err', buf, s)

                buf = ''  

    while True:
        message = device.readline()

        print('m', state, message.strip())
        #for d in data.decode('utf8'):


      


if __name__ == '__main__':
    main()


