import pygame
import RPi.GPIO as GPIO # using RPi.GPIO module
from time import sleep # import function sleep for delay

GPIO.setmode(GPIO.BCM) # GPIO numbering
GPIO.setwarnings(False) # enable warning from GPIO

AN1 = 14 
AN2 = 17 
AN3 = 23 
AN4 = 9 
DIG1 = 15 
DIG2 = 27 
DIG3 = 24 
DIG4 = 11 


GPIO.setup(AN2, GPIO.OUT) # set pin as output
GPIO.setup(AN1, GPIO.OUT) # set pin as output
GPIO.setup(DIG2, GPIO.OUT) # set pin as output
GPIO.setup(DIG1, GPIO.OUT) # set pin as output
GPIO.setup(AN3, GPIO.OUT) # set pin as output
GPIO.setup(AN4, GPIO.OUT) # set pin as output
GPIO.setup(DIG3, GPIO.OUT) # set pin as output
GPIO.setup(DIG4, GPIO.OUT) # set pin as output

sleep(1) # delay for 1 seconds

p1 = GPIO.PWM(AN1, 100) # set pwm for M1
p2 = GPIO.PWM(AN2, 100) # set pwm for M2
p3 = GPIO.PWM(AN3, 100) # set pwm for M3
p4 = GPIO.PWM(AN4, 100) # set pwm for M4


pygame.init()

j = pygame.joystick.Joystick(0)
j.init()

try:
    while True:
        events = pygame.event.get()
        for event in events:
            if event.type == pygame.JOYBUTTONDOWN:
                print("Button Pressed")
                if j.get_button(6):
                    print("Left")
                    GPIO.output(DIG1, GPIO.LOW) # set DIG1 as high, dir2 = forward
                    GPIO.output(DIG2, GPIO.HIGH) # set DIG2 as high, dir1 = forward
                    GPIO.output(DIG3, GPIO.HIGH) 
                    GPIO.output(DIG4, GPIO.LOW)
                    p1.start(50) # set speed for M1, speed=0 – 100
                    p2.start(50) # set speed for M2, speed=0 – 100
                    p3.start(50)
                    p4.start(50) 
                elif j.get_button(7):
                    print("Right")
                    GPIO.output(DIG1, GPIO.HIGH) # set DIG1 as high, dir2 = forward
                    GPIO.output(DIG2, GPIO.LOW) # set DIG2 as high, dir1 = forward
                    GPIO.output(DIG3, GPIO.LOW) 
                    GPIO.output(DIG4, GPIO.HIGH)
                    p1.start(50) # set speed for M1, speed=0 – 100
                    p2.start(50) # set speed for M2, speed=0 – 100
                    p3.start(50)
                    p4.start(50) 
                elif j.get_button(4):
                    print("Backward")
                    GPIO.output(DIG1, GPIO.LOW) # set DIG1 as high, dir2 = forward
                    GPIO.output(DIG2, GPIO.LOW) # set DIG2 as high, dir1 = forward
                    GPIO.output(DIG3, GPIO.LOW) 
                    GPIO.output(DIG4, GPIO.LOW)
                    p1.start(50) # set speed for M1, speed=0 – 100
                    p2.start(50) # set speed for M2, speed=0 – 100
                    p3.start(50)
                    p4.start(50) 
                elif j.get_button(5):
                    print("Forward")
                    GPIO.output(DIG1, GPIO.HIGH) # set DIG1 as high, dir2 = forward
                    GPIO.output(DIG2, GPIO.HIGH) # set DIG2 as high, dir1 = forward
                    GPIO.output(DIG3, GPIO.HIGH) 
                    GPIO.output(DIG4, GPIO.HIGH)
                    p1.start(50) # set speed for M1, speed=0 – 100
                    p2.start(50) # set speed for M2, speed=0 – 100
                    p3.start(50)
                    p4.start(50)
                elif j.get_button(1):
                    print("DiagonalR")
                    GPIO.output(DIG1, GPIO.HIGH) # set DIG1 as high, dir2 = forward
                    GPIO.output(DIG2, GPIO.LOW) # set DIG2 as high, dir1 = forward
                    GPIO.output(DIG3, GPIO.LOW) 
                    GPIO.output(DIG4, GPIO.HIGH)
                    p1.start(50) # set speed for M1, speed=0 – 100
                    p2.start(0) # set speed for M2, speed=0 – 100
                    p3.start(0)
                    p4.start(50)
                elif j.get_button(2):
                    print("DiagonalL")
                    GPIO.output(DIG1, GPIO.LOW) # set DIG1 as high, dir2 = forward
                    GPIO.output(DIG2, GPIO.HIGH) # set DIG2 as high, dir1 = forward
                    GPIO.output(DIG3, GPIO.HIGH) 
                    GPIO.output(DIG4, GPIO.LOW)
                    p1.start(0) # set speed for M1, speed=0 – 100
                    p2.start(50) # set speed for M2, speed=0 – 100
                    p3.start(50)
                    p4.start(0)
                elif j.get_button(3):
                    print("360")
                    GPIO.output(DIG1, GPIO.HIGH) # set DIG1 as high, dir2 = forward
                    GPIO.output(DIG2, GPIO.LOW) # set DIG2 as high, dir1 = forward
                    GPIO.output(DIG3, GPIO.HIGH) 
                    GPIO.output(DIG4, GPIO.LOW)
                    p1.start(50) # set speed for M1, speed=0 – 100
                    p2.start(50) # set speed for M2, speed=0 – 100
                    p3.start(50)
                    p4.start(50)
                elif j.get_button(0):
                    print("Stop")
                    p1.start(0) # set speed M1=0
                    p2.start(0) # set speed M2=0
                    p3.start(0) # set speed M3=0
                    p4.start(0) # set speed M4=0
                
                elif event.type == pygame.JOYBUTTONUP:
                    p1.start(0) # set speed M1=0
                    p2.start(0) # set speed M2=0
                    p3.start(0) # set speed M3=0
                    p4.start(0) # set speed M4=0
                    print("Button Released")

except KeyboardInterrupt:
    p1.start(0) # set speed M1=0
    p2.start(0) # set speed M2=0
    p3.start(0) # set speed M3=0
    p4.start(0) # set speed M4=0
    print("EXITING NOW")
    j.quit()
