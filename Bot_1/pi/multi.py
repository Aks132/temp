import serial
import joy

def multi():
    try:

         ser2 = serial.Serial('/dev/ttyACM0', 115200, timeout=0.01)
         ser2.flush()
    except:
        try:
            ser2 = serial.Serial('/dev/ttyACM0', 115200, timeout=0.01)

        except:
            print("/dev/tty Port issue")

        while True:
            jsVal = joy.getJS()

