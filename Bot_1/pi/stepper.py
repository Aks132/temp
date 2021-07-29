import time
import RPi.GPIO as GPIO


GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

stepen = 8
steps = 7
stepdir = 1
GPIO.setup(stepen, GPIO.OUT)
GPIO.setup(steps, GPIO.OUT)
GPIO.setup(stepdir, GPIO.OUT)

def step_setup():
    GPIO.output(stepen, GPIO.HIGH)
    time.sleep(0.1)
    GPIO.output(stepen, GPIO.LOW)
    
def step_run(direction):
    if direction == 1:
        GPIO.output(stepdir, GPIO.HIGH)
        for i in range(0,5):
            GPIO.output(steps, GPIO.HIGH)
            time.sleep(0.001)
            GPIO.output(steps, GPIO.LOW)
            time.sleep(0.001)
            #print(i)
        #GPIO.output(stepdir, GPIO.HIGH)
    elif direction == -1:
            GPIO.output(stepdir, GPIO.LOW)
            for i in range(0,5):
                GPIO.output(steps, GPIO.HIGH)
                time.sleep(0.001)
                GPIO.output(steps, GPIO.LOW)
                time.sleep(0.001)
        