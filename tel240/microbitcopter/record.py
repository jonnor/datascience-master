import serial
import sys

def main():
    port = '/dev/ttyACM0'
    device = serial.Serial(port=port, baudrate=115200, timeout=0.2) 
    print("Opened", port, file=sys.stderr)
    

    while True:
        line = device.readline()
        if line:
            v = line.decode('utf8')
            sys.stdout.write(v)
            sys.stdout.flush()

if __name__ == '__main__':
    main()


