import RPi.GPIO as GPIO
import joy as js
import serial
from time import sleep
from multiprocessing import Process



GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)




reqfront = 640
reqside = 80
#Poddistlist = [50,(145 + 5 - 44),(145 + 5 - 24),(145 + 5),(145 + 5 + 24),(145 + 5 + 44)] #70 - 45 = 25
Poddistlist = [640,(640),(445),(640),(640),640] #70 - 45 = 25
Podlistside= [80,53,53,80,53,53]
pos = 1
PWM = [20, 17, 23, 13]
DIG = [21, 27, 24, 6]
Soft_PWM = []
speed = 0
offsetyaw = 0
side = 0
countpod = 0

GPIO.setup(14,GPIO.IN)
ir_1 = 0


GPIO.setup(2,GPIO.OUT)
GPIO.setup(3,GPIO.OUT)

GPIO.output(2,GPIO.LOW)
GPIO.output(3,GPIO.LOW)

# ----------------------------------------------------
Yaw = 0
frontdist = 0
sidedist = 0
sidedist2 = 0
ang_err =0

P_S = 0.0  # 0.3
P_Y = 0
P_F = 0
P_ER = 0

D_F = 0
D_S = 0
D_F = 0
D_Y = 0

I_A = 0
I_ang =0
I_Yaw = 0
I_Y = 0
I_Front = 0
I_F = 0
I_Side = 0
I_S = 0

offsetyaw = 0
presetyaw = 0

D_error = 0
DF_error = 0
DS_error = 0

try:
   # ser2 = serial.Serial('/dev/ttyACM0', 9600, timeout=0.01)
    ser1 = serial.Serial('/dev/ttyACM0', 115200, timeout=0.01)  # change name, if needed
    ser1.flush()
    #ser2 = serial.Serial('/dev/ttyACM0', 115200, timeout=0.01)
    #ser2.flush()
except:
    print("/dev/tty Port issue")

def arduino_out():
    jsVal = js.getJS()
    if jsVal['R1'] == 1:
        print("i am in phase 1")
        GPIO.output(2,GPIO.HIGH)
    elif jsVal['R1'] == 0:
        GPIO.output(2,GPIO.LOW)

    if jsVal['L1'] == 1:
        print("i am in phase 2")
        GPIO.output(3,GPIO.HIGH)
    elif jsVal['L1'] == 0:
        GPIO.output(3,GPIO.LOW)

def Com_Arduino():
    global Yaw, frontdist, sidedist,sidedist2,ang_err
         

    try:
        if ser1.in_waiting > 0:
            response = ser1.readline().decode('utf-8').rstrip()
            #print(response)
            l = str(response).split('@')  ##@Yaw@frontdist@sidedist@##
           # print(len(l))
           # print(len(response))
            jsVal = js.getJS()
            x,y = js.get_hats()
            if x == -1:
                x = 2
            if y == -1:
                y = 2
            ir_1 = 0   
            if(ir_read()==1):
            #    print('hello')
                ir_1 = 1
            message = str((jsVal['options']))+str((jsVal['R2']))+str(x)+str(y)+str(ir_1) + "\n"
            #print(message)
            ser1.write(message.encode('utf-8'))
            
            if len(l) >= 4 and len(response) > 20:
                Yaw = float(l[1]) + offsetyaw + presetyaw
                frontdist = float(l[3])
                sidedist = float(l[4])
                sidedist2 = float(l[2])
                if(sidedist-sidedist2 < 30):
                    ang_err = -(sidedist-sidedist2) 
               # print(int(ang_err))
               # print('Yaw ' + str(int(Yaw))+" " +str(presetyaw)+ ' frontdist ' + str(frontdist) + ' sidedist ' + str(sidedist)+ ' sidedist2 ' + str(sidedist2))

    
    except:
       print("Yaw error")



def motor_setup():
    for x in DIG:
        GPIO.setup(x, GPIO.OUT)  # set pin as output
    for x in PWM:
        GPIO.setup(x, GPIO.OUT)  # set pin as output
    for y in range(0, 4):
        Soft_PWM.append(GPIO.PWM(PWM[y], 300))  # set pwm frequenvy for M1
    for z in Soft_PWM:
        z.start(0)  # set pin as output


def motor_feed(speed, rotate, side):
    global P_ER, pos,D_S, countpod ,P_S,P_Y,I_Y, I_Yaw, D_Yaw, D_error, D_Y, presetyaw, P_F, Yaw, reqside
    global I_A , I_ang ,reqfront, I_Front, I_F, I_S, I_Side, DF_error, DS_error, D_F, D_Front, D_Side
    jsVal = js.getJS()

    if jsVal['o'] == 1 and P_Y == 0.8:
        presetyaw = 0
        P_ER,P_Y = 0,0
        I_Y = 0

        I_ang = 0
        I_A = 0
        I_Yaw = 0
        D_Y = 0
        D_error = 0

    if jsVal['x'] == 1 and P_Y != 0.8:
        print("Yaw correction start")
        P_ER = 2 #1.5
        D_Y = 1 #4    
        I_A = 0.0002 #0.0002
        
        #I_Y = 0.001

        P_Y = 0.8
   
        presetyaw = -Yaw
        Yaw = 0
        sleep(0.1)

    if jsVal['s'] == 1:
        P_F = 0.5 #0.3
        D_F = 0.4 
        I_F = 0.000 #0.001
        
        P_S = 2.5 #1.5
        I_S = 0.000 #0.0001
        D_S = 4.5 #6
        
    if jsVal['t'] == 1:
        P_F = 0.0
        D_F = 0
        I_F = 0.000
        I_Front = 0
        P_S = 0
        I_S = 0
        I_Side = 0
        D_S = 0
    
    
    if(jsVal['L2'] == 1 ):
        sleep(0.2)
        jsVal = js.getJS()
        if(jsVal['L2'] == 1 ):
           
            reqfront = Poddistlist[countpod]
            reqside = Podlistside[countpod]
            countpod += pos
            print(countpod)
            if abs(countpod) >=6  or countpod <= 0 :
                countpod = 0
                

    # YAW
    I_Yaw += Yaw * I_Y
   # D_Yaw = (D_error - Yaw)
 
    
    I_ang += ang_err * I_A
    outyaw = (P_ER *ang_err)
    D_Yaw = (D_error - ang_err)*D_Y
    D_error = ang_err
    outyaw = (P_ER *ang_err) + D_Yaw +I_ang
    #print(str(int(Yaw*P_Y)) + " " + str(int(I_Yaw)) + " " + str(int(D_Yaw)))


    # Side
    #print(int(sidedist+sidedist2)/2)
    
    error_side = -int(reqside - (sidedist+sidedist2)/2)
    I_Side += error_side * I_S
    D_Side = (DS_error - error_side)*D_S
    DS_error = error_side
    outSide = error_side*P_S + I_Side + D_Side

    # Front
    error_front = int(-(reqfront - frontdist))
    I_Front += error_front * I_F 
    D_Front = (DF_error - error_front)*D_F
    DF_error = error_front
    outfront = (error_front)*P_F + D_Front + I_Front
    
#    outSide = 0
    #print(str(int(outyaw))+"  "+str(int(ang_err)))
    #print(str(int(outyaw))+"  "+str(int(ang_err)))

   # print(" " +str(int(outyaw)) + " " + str(int(outSide)) + " " + str(int(outfront)))
    speedm1 = int(speed + rotate + side - outyaw + outSide + outfront + (speed * 0.0))
    speedm2 = int(speed - rotate - side + outyaw - outSide + outfront + (speed * 0.0))
    speedm3 = int(speed + rotate - side - outyaw - outSide + outfront + (speed * 0.0))
    speedm4 = int(speed - rotate + side + outyaw + outSide + outfront + (speed * 0.0))
    Speed = [speedm1, speedm2, speedm3, speedm4]
   # print(Speed)
    i = 0
    for spd in Speed:
        if abs(spd) > 99:
            spd = (abs(spd) / spd) * 99
        if spd > 0:
            # print(i)
            GPIO.output(DIG[i], GPIO.HIGH)
            Soft_PWM[i].ChangeDutyCycle(abs(spd))
            # sleep(0.05)
        else:
            GPIO.output(DIG[i], GPIO.LOW)
            Soft_PWM[i].ChangeDutyCycle(abs(spd))
            # sleep(0.05)
        i = i + 1


def stop():
    for i in range(0, 4):
        GPIO.output(DIG[i], GPIO.LOW)
        Soft_PWM[i].stop()


def get_input():
    global speed, offsetyaw, side
    jsVal = js.getJS()
    speed = (jsVal['axis2']) * 70
    offsetyaw = -(jsVal['axis1']) * 50
    side = -(jsVal['axis3']) * 50
 

    #print(str(speed)+" "+str(offsetyaw)+ " "+str(side)+" " + str(P_Y))


def ir_read():
    GPIO.setup(26, GPIO.IN)  # For Ir input purpose
    ir = GPIO.input(26)
    
    return ir
    
    
if __name__ == '__main__':
    motor_setup()


    while True:

        get_input()
        #ir_read()
        arduino_out()
        Com_Arduino()
        motor_feed(speed, offsetyaw, side)



'''       try:
            get_input()
            Com_Arduino()
            motor_feed(speed, offsetyaw, side)
            sleep(0.001)
        except:
            #stop()
            print("Exception Errrorrrrrrrrrrrrrrrrrrrrrrrrrr ")
'''
#orange ylw grn blue purple white  