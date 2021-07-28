import serial

import time
from time import sleep
import RPi.GPIO as GPIO
import joy as js

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

try:
    ser1 = serial.Serial('/dev/ttyACM1', 115200, timeout = 0.1) # change name, if needed
    ser2 = serial.Serial('/dev/ttyACM0', 115200, timeout = 0.1)
except:
    print("/dev/tty Port issue")


Yaw = 0
dist1 = 0
P_S = 0.0 #0.3
P_Y = 0
D_F = 0
D_Y = 0
I_Yaw = 0
I_Y = 0
offsetyaw = 0
presetyaw = 0
D_error =0 
P1 = 0
P2 = 0
error_dist1 = 0
reqdist1  = 60

PWM = [20 ,17 ,23 ,5]  
DIG = [21 , 27 , 24 , 6]

for x in PWM:
    GPIO.setup(x, GPIO.OUT) # set pin as output
for x in DIG:
    GPIO.setup(x, GPIO.OUT) # set pin as output
p = []
for i in range(0,4):
    p.append(GPIO.PWM(PWM[i], 100)) # set pwm for M1
    

def getdata():
    global Yaw , dist1
    l = [0,0,0]
    try:
  
        response = ser1.readline().decode('utf-8').rstrip()
        print(response)
        l = str(response).split('@') ##@Yaw@dist1@dist2@##
        if len(l) == 4 and len(response) > 12:
            Yaw = float(l[1]) + offsetyaw + presetyaw
            dist1 = float(l[2]) 
            print('Yaw '+str(Yaw)+' dist1 '+str(dist1))
    except:
        print("Yaw error")
        Yaw = 0
        
        
    
def calculate(speed , rotate,side):
    global errordist1 , I_Y , I_Yaw , D_Yaw , D_error,error_dist1

    error_dist1 = (reqdist1 -dist1)
    erroryaw = Yaw
    I_Yaw += I_Yaw *I_Y 
    D_Yaw = (D_error - Yaw)
    D_error = Yaw
    outyaw = P_Y *(Yaw) + I_Yaw + D_Yaw
    
    outSide = error_dist1*P_S
    
    #print(outyaw)
    #print(str(erroryaw) + " " + str(errordist1) + " " + str(errordist2))
    #print(str(int(outyaw)) + " " + str(int(speed)) + " " + str(int(rotate)))
    
    speedm1 = int(speed + rotate + side + outyaw + outSide +(speed*0.0))
    speedm2 = int(speed - rotate - side - outyaw - outSide +(speed*0.0))
    speedm3 = int(speed + rotate - side + outyaw - outSide +(speed*0.0))
    speedm4 = int(speed - rotate + side - outyaw + outSide +(speed*0.0))
    Speed = [speedm1 , speedm2 ,speedm3 ,speedm4]
    print(Speed)
    i = 0
    for spd in Speed:
        if abs(spd) > 99:
            spd = (abs(spd)/spd)*99
        if((spd) > 0):
             #print(i)
            GPIO.output(DIG[i], GPIO.HIGH)
            p[i].start(abs(spd))
            #sleep(0.05)
        else:
            GPIO.output(DIG[i], GPIO.LOW)
            p[i].start(abs(spd))
            #sleep(0.05)
        i = i + 1


        
 
def stop():
    for i in range(0,4):
        GPIO.output(DIG[i], GPIO.LOW)
        p[i].start(abs(0))


    

    
def fb():
    global offsetyaw , presetyaw, P_Y , Yaw ,  I_Y , I_Yaw ,D_Y,D_error,P1,P2,P_S
    jsVal = js.getJS()
    speed = (jsVal['axis2'])*70
    offsetyaw = (jsVal['axis3'])*40
    side = (-(jsVal['axis5']*70)+(jsVal['axis6']*70))/2
    P1 = jsVal['L1']
    P2 = jsVal['R1']
    
    
    
    if (jsVal['x'] == 1 and P_Y != 2.5):
       P_Y = 2.5
       I_Y =  0.001
       D_Y =  1
       presetyaw  = -Yaw
       Yaw = 0 
       time.sleep(1)
       
    if jsVal['o'] == 1 or P1 == 1 or P2 == 1:
        P_Y = 0
        I_Y =  0
        I_Yaw =  0
        D_Y = 0
        D_error = 0
        
    if jsVal['s'] == 1:
        P_S = 0.1
    elif jsVal['t'] == 1 or P1 == 1 or P2 == 1:
        P_S = 0
        stop()

    
    #print(str(speed)+" "+str(offsetyaw)+ " "+str(side)+" " + str(P_Y))
    
    
    calculate(speed , offsetyaw, side)

def getdata2():
    resp = ser2.readline()
    print(resp)
    

if __name__ == '__main__':
    while True:
        fb()
  
       # try:
          
        #except:
         #   stop()
          #  print("Exception Errrorrrrrrrrrrrrrrrrrrrrrrrrrr ")
        




