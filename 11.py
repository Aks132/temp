import RPi.GPIO as GPIO          
from time import sleep
GPIO.setwarnings(False)

GPIO.setmode(GPIO.BOARD)                    ## Use BOARD pin numbering.
GPIO.setup(32, GPIO.OUT)
GPIO.setup(16, GPIO.OUT)
pwm = GPIO.PWM(32,100)
pwm.start(0)

while(1):
    GPIO.output(16,GPIO.LOW)
    pwm.ChangeDutyCycle(50)
    

