
from bluepy import btle

import argparse
import time
import struct
import binascii


# Please see # Ref https://nordicsemiconductor.github.io/Nordic-Thingy52-FW/documentation
# for more information on the UUIDs of the Services and Characteristics that are being used
def Nordic_UUID(val):
    """ Adds base UUID and inserts value to return Nordic UUID """
    return btle.UUID("EF68%04X-9B35-4933-9B10-52FFA9740042" % val)


# Notification handles used in notification delegate
m_orient_handle = None
MOTION_SERVICE_UUID         = 0x0400
M_ORIENTATION_CHAR_UUID     = 0x0403
CCCD_UUID = 0x2902


class MotionService():
    """
    Motion service module. Instance the class and enable to get access to the Motion interface.
    """
    serviceUUID =           Nordic_UUID(MOTION_SERVICE_UUID)
    orient_char_uuid =      Nordic_UUID(M_ORIENTATION_CHAR_UUID)

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
            self.orient_cccd = self.orient_char.getDescriptors(forUUID=CCCD_UUID)[0]


    def set_orient_notification(self, state):
        if self.orient_cccd is not None:
            if state == True:
                self.orient_cccd.write(b"\x01\x00", True)
            else:
                self.orient_cccd.write(b"\x00\x00", True)


class MyDelegate(btle.DefaultDelegate):
    
    def handleNotification(self, hnd, data):
        #Debug print repr(data)
        if (hnd == m_orient_handle):
            teptep = binascii.b2a_hex(data)
            print('Notification: Orient: {}'.format(teptep))

        else:
            teptep = binascii.b2a_hex(data)
            print('Notification: UNKOWN: hnd {}, data {}'.format(hnd, teptep))
            

    def _str_to_int(self, s):
        """ Transform hex str into int. """
        i = int(s, 16)
        if i >= 2**7:
            i -= 2**8
        return i    



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

    print('Connecting to ' + args.mac_address)
    thingy = Thingy52(args.mac_address)
    print('Connected...')
    thingy.setDelegate(MyDelegate())

    try:
        # Enabling selected sensors
        print('Configuring sensors...')

        thingy.motion.enable()
        thingy.motion.set_orient_notification(True)

        # Allow sensors time to start up (might need more time for some sensors to be ready)
        print('Configured! Listening for changes')
        time.sleep(1.0)

        while True:            
            thingy.waitForNotifications(args.t)

    finally:
        thingy.disconnect()
        del thingy


if __name__ == "__main__":
    main()
