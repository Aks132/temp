import RPi.GPIO as GPIO
import joy as js
import serial
from time import sleep

try:
    ser2 = serial.Serial('/dev/ttyACM1', 115200, timeout=0.01)
    ser2.flush()
except:
    print("/dev/tty Port issue")
    sleep(10)



def Com_Arduino():
    try:
         if ser2.in_waiting > 0:
            jsVal = js.getJS()
            response = ser2.readline().decode('utf-8').rstrip()
            message = str((jsVal['R1']))+str((jsVal['R2']))+ str((jsVal['L1']))+str((jsVal['L2']))+str((jsVal['t']))+str((jsVal['s']))+"\n"
            print(response + "  "+ message)
            ser2.write(message.encode('utf-8'))
    except:
        print("error")