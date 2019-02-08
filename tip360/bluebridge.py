
import gevent


from bluepy import btle

import argparse
import time
import struct
import binascii

sensor_data = dict()

import flask
from flask import Flask
app = Flask(__name__)

@app.route("/data")
def get_data():
    return flask.jsonify(sensor_data)

@app.route('/')
def get_index():
    html = open('index.html', 'r').read()
    return (html, 200, { 'content-type': 'text/html' })

@app.route('/app.js')
def get_app():
    html = open('app.js', 'r').read()
    return (html, 200, { 'content-type': 'text/javascript' })

import gevent.pywsgi


# Notification handles used in notification delegate
# FIXME: pass to delegate explicitly
m_orient_handle = None

class MotionService():
    """
    """
    serviceUUID =         btle.UUID('00000000-0001-11e1-9ab4-0002a5d5c51b') 
    orient_char_uuid =      btle.UUID("04000000-0001-11e1-ac36-0002a5d5c51b")
    CCCD_UUID = 0x2902

    def __init__(self, periph):
        self.periph = periph
        self.motion_service = None

        self.orient_char = None
        self.orient_cccd = None

    def enable(self):
        """ Enables the class by finding the service and its characteristics. """
        global m_orient_handle
 
        if self.motion_service is None:
            self.motion_service = self.periph.getServiceByUUID(self.serviceUUID)

        if self.orient_char is None:
            self.orient_char = self.motion_service.getCharacteristics(self.orient_char_uuid)[0]
            m_orient_handle = self.orient_char.getHandle()
            self.orient_cccd = self.orient_char.getDescriptors(forUUID=self.CCCD_UUID)[0]

    def set_orient_notification(self, state):
        if self.orient_cccd is not None:
            if state == True:
                self.orient_cccd.write(b"\x01\x00", True)
            else:
                self.orient_cccd.write(b"\x00\x00", True)

def parse_audiolevel(buf):
    assert len(buf) == 3, len(buf)

    timestamp = int.from_bytes(buf[:2], byteorder='little')
    level = int.from_bytes(buf[2:], byteorder='little')

    return timestamp, level

class MyDelegate(btle.DefaultDelegate):
    
    def handleNotification(self, hnd, data):
        if (hnd == m_orient_handle):
            t, level = parse_audiolevel(data)
            print('Notification: Audio Level: {}'.format(level))
            sensor_data['sensor1'] = level
        else:
            teptep = binascii.b2a_hex(data)
            print('Notification: UNKOWN: hnd {}, data {}'.format(hnd, teptep))



class Thingy52(btle.Peripheral):
    """
    Thingy:52 module. Instance the class and enable to get access to the Thingy:52 Sensors.
    The addr of your device has to be know, or can be found by using the hcitool command line 
    tool, for example. Call "> sudo hcitool lescan" and your Thingy's address should show up.
    """
    def __init__(self, addr):
        btle.Peripheral.__init__(self, addr, addrType=btle.ADDR_TYPE_RANDOM)
        self.motion = MotionService(self)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('mac_address', action='store', help='MAC address of BLE peripheral')
    parser.add_argument('-t',action='store',type=float, default=2.0, help='time between polling')

    args = parser.parse_args()

    #mac = args.mac_address
    mac = 'C0:6E:41:31:38:48'

    print('Connecting to ' + mac)
    thingy = Thingy52(mac)
    print('Connected...')
    thingy.setDelegate(MyDelegate())

    # Enabling selected sensors
    print('Configuring sensors...')

    thingy.motion.enable()
    thingy.motion.set_orient_notification(False)
    time.sleep(0.5)
    thingy.motion.set_orient_notification(True)


    def check_sensor():
        while True:            
            thingy.waitForNotifications(args.t)
            gevent.sleep(0.1)
    gevent.spawn(check_sensor)

    # Allow sensors time to start up (might need more time for some sensors to be ready)
    print('Configured! Listening for changes')
    time.sleep(1.0)

    
    http_server = gevent.pywsgi.WSGIServer(('', 5000), app)
    http_server.serve_forever()

    #finally:
    #    thingy.disconnect()
    #    del thingy


if __name__ == "__main__":
    main()
