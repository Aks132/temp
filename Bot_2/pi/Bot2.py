import RPi.GPIO as GPIO
import joy as js
import serial
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

reqfront = 30
reqside = 176

Poddistlist = [(145),(310),(380),(545)]
pos = 1
PWM = [20, 17, 23, 5]
DIG = [21, 27, 24, 6]
Soft_PWM = []
speed = 0
offsetyaw = 0
side = 0
countpod = 0

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
D_Side = 0
D_Front = 0
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
    ser1 = serial.Serial('/dev/ttyACM1', 115200, timeout=0.01)  # change name, if needed

except:
    try:
        ser1 = serial.Serial('/dev/ttyACM0', 115200, timeout=0.01)
    except:
        print("/dev/tty Port issue")


def Com_Arduino():
    global Yaw, frontdist, sidedist,sidedist2,ang_err
    #try:

    response = ser1.readline().decode('utf-8').rstrip()
   # print(response)
        
    l = str(response).split('@')  ##@Yaw@frontdist@sidedist@##
  #  print(len(l))
    if len(l) >= 4 and len(response) > 12:
        Yaw = float(l[1]) + offsetyaw + presetyaw
        frontdist = float(l[3])
        
        sidedist = float(l[2])
        sidedist2= float(l[4])
        ang_err = sidedist-sidedist2 
        #print(sidedist)
        print('Yaw ' + str(int(Yaw))+" " +str(presetyaw)+ ' frontdist ' + str(frontdist) + ' sidedist ' + str(sidedist)+ 'sidedist2 ' + str(sidedist2))
    #except:
       # print("Yaw error")

    # message = "P1=" + str(0) + "@" + "P2=" + str(0) + "@" + "A1=0\r"
    # ser1.write(message.encode('utf-8'))


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
    global P_ER, pos, countpod ,P_S,P_Y,I_Y, I_Yaw, D_Yaw, D_error, D_Y, presetyaw, P_F, Yaw, reqside
    global I_A , I_ang ,reqfront, I_Front, I_F, I_S, I_Side, DF_error, DS_error, D_F, D_Front, D_Side
    jsVal = js.getJS()

    if jsVal['o'] == 1 and P_Y == 0.8:
        presetyaw = 0
        P_ER = 0
        P_Y = 0
        I_Y = 0
        I_ang = 0
        I_A = 0
        I_Yaw = 0
        D_Y = 0
        D_error = 0

    if jsVal['x'] == 1 and P_Y != 0.8:
        P_ER = 3
        P_Y = 0.8
        I_A = 0.001
        I_Y = 0.000
        D_Y = 0.2
        presetyaw = -Yaw
        Yaw = 0
        time.sleep(0.5)

    if jsVal['s'] == 1:
        P_F = 0.3
        P_S = 0.3
        I_S = 0.004
    if jsVal['t'] == 1:
        P_F = 0
        P_S = 0
        I_S = 0
        I_Side = 0
    
    
    if(jsVal['R1'] == 1 ):
        time.sleep(0.1)
        jsVal = js.getJS()
        if(jsVal['R1'] == 1 ):
           
            reqfront = Poddistlist[countpod]
            countpod += pos
            print(countpod)
            if abs(countpod) >= 3 or countpod <= 0 :
                pos = -pos
                

    # YAW
    I_Yaw += Yaw * I_Y
    D_Yaw = (D_error - Yaw)
    D_error = Yaw
    
    I_ang += ang_err * I_A
    outyaw = P_ER *ang_err
    #print(str(int(Yaw*P_Y)) + " " + str(int(I_Yaw)) + " " + str(int(D_Yaw)))


    # Side
    error_side = -(reqside - sidedist)*P_S
    I_Side += error_side * I_S
    D_Side = (D_error - sidedist)
    DS_error = sidedist
    outSide = error_side + I_Side

    # Front
    error_front = (reqfront - frontdist)*P_F
    I_Front += error_front * I_F
    D_Front = (D_error - frontdist)
    DF_error = frontdist
    outfront = error_front 
    
#    outSide = 0
    #print(outSide)
  

    print(str(int(outyaw)) + " " + str(int(outSide)) + " " + str(int(outfront)))
    speedm1 = int(speed + rotate + side + outyaw + outSide + outfront + (speed * 0.0))
    speedm2 = int(speed - rotate - side - outyaw - outSide + outfront + (speed * 0.0))
    speedm3 = int(speed + rotate - side + outyaw - outSide + outfront + (speed * 0.0))
    speedm4 = int(speed - rotate + side - outyaw + outSide + outfront + (speed * 0.0))
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
    speed = -(jsVal['axis2']) * 30
    offsetyaw = -(jsVal['axis3']) * 20
    side = (jsVal['axis1']) * 20
    
        

    print(str(speed)+" "+str(offsetyaw)+ " "+str(side)+" " + str(P_Y))


if __name__ == '__main__':
    motor_setup()
    while True:
        get_input()
        Com_Arduino()
        motor_feed(speed, offsetyaw, side)
        time.sleep(0.001)

'''       try:
            get_input()
            Com_Arduino()
            motor_feed(speed, offsetyaw, side)
            time.sleep(0.001)
        except:
            #stop()
            print("Exception Errrorrrrrrrrrrrrrrrrrrrrrrrrrr ")
'''
#orange ylw grn blue purple white