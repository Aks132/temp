import RPi.GPIO as GPIO
import time
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

GPIO.setup(26,GPIO.IN) #GPGPIO 14 -> IR sensor as input


while 1:

    if(GPIO.input(26)==True): #object is far
        print('i am here')
    
    if(GPIO.input(26)==False): #object is near
        print('hello')