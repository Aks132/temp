import serial
import joy as js
import RPi.GPIO as GPIO
import time





def serial2():
    try:
        ser2 = serial.Serial('/dev/ttyACM1', 115200, timeout=0.01)
        ser2.flush()
    except:
        print("port issue")


    while True:
        jsVal = js.getJS()
        response = ser2.readline().decode('utf-8').rstrip()
        print(response)
        print("ok")

class process_2():






    def arduino_fire(self):
        jsVal = js.getJS()
        if (jsVal['t'] == 1):
            print("shotinnnnng")
            GPIO.output(26, GPIO.HIGH)
        else:
            GPIO.output(26, GPIO.LOW)
        if (jsVal['o'] == 1):
            print("shotinnnnng")
            GPIO.output(19, GPIO.HIGH)
        else:
            GPIO.output(19, GPIO.LOW)

    def arduino_out(self):
        jsVal = js.getJS()
        GPIO.setup(18, GPIO.OUT)
        GPIO.setup(15, GPIO.OUT)
        if jsVal['L1'] == 1:
            print('out to arduino_L1')
            GPIO.output(18, GPIO.HIGH)
        else:
            GPIO.output(18, GPIO.LOW)
        if jsVal['R1'] == 1:
            print('out to arduino_R1')
            GPIO.output(15, GPIO.HIGH)
        else:
            GPIO.output(15, GPIO.LOW)

serial2()