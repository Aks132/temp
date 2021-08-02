import RPi.GPIO as GPIO
import joy as js
import serial
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

PWM = [20, 17, 23, 5]
DIG = [21, 27, 24, 6]
Soft_PWM = []
speed = 0
offsetyaw = 0
side = 0

# ----------------------------------------------------
Yaw = 0
dist1 = 0
P_S = 0.0  # 0.3
P_Y = 0
D_F = 0
D_Y = 0
I_Yaw = 0
I_Y = 0
offsetyaw = 0
presetyaw = 0
D_error = 0
error_dist1 = 0
reqdist1 = 60

try:
    ser1 = serial.Serial('/dev/ttyACM1', 115200, timeout=0.1)  # change name, if needed

except:
    try:
        ser1 = serial.Serial('/dev/ttyACM0', 115200, timeout=0.1)
    except:
        print("/dev/tty Port issue")


def Com_Arduino():
    global Yaw, dist1, dist2
    try:

        response = ser1.readline().decode('utf-8').rstrip()
        print(response)
        l = str(response).split('@')  ##@Yaw@dist1@dist2@##
        if len(l) <= 4 and len(response) > 12:
            Yaw = float(l[1]) + offsetyaw + presetyaw
            dist1 = float(l[2])
            dist2 = float(l[2])
            print('Yaw ' + str(Yaw) + ' dist1 ' + str(dist1)) + ' dist1 ' + str(dist2)
    except:
        print("Yaw error")

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
    global errordist1, I_Y, I_Yaw, D_Yaw, D_error, error_dist1, D_Y, presetyaw
    jsVal = js.getJS()

    if jsVal['o'] == 1:
        P_Y = 0
        I_Y = 0
        I_Yaw = 0
        D_Y = 0
        D_error = 0

    if jsVal['x'] == 1 and P_Y != 2.5:
        P_Y = 2.5
        I_Y = 0.001
        D_Y = 1
        presetyaw = -Yaw
        Yaw = 0
        time.sleep(1)

    '''
        if jsVal['s'] == 1:
            P_S = 0.1
        elif jsVal['t'] == 1 or P1 == 1 or P2 == 1:
            P_S = 0
            stop()
    '''

    error_dist1 = (reqdist1 - dist1)
    erroryaw = Yaw
    I_Yaw += I_Yaw * I_Y
    D_Yaw = (D_error - Yaw)
    D_error = Yaw
    outyaw = P_Y * (Yaw) + I_Yaw + D_Yaw

    outSide = error_dist1 * P_S

    # print(str(int(outyaw)) + " " + str(int(outSide)) + " " + str(int(rotate)))

    speedm1 = int(speed + rotate + side + outyaw + outSide + (speed * 0.0))
    speedm2 = int(speed - rotate - side - outyaw - outSide + (speed * 0.0))
    speedm3 = int(speed + rotate - side + outyaw - outSide + (speed * 0.0))
    speedm4 = int(speed - rotate + side - outyaw + outSide + (speed * 0.0))
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
    offsetyaw = (jsVal['axis3']) * 20
    side = (-(jsVal['axis5'] * 70) + (jsVal['axis6'] * 70)) / 2

    # print(str(speed)+" "+str(offsetyaw)+ " "+str(side)+" " + str(P_Y))


if __name__ == '__main__':
    motor_setup()
    while True:
        get_input()
        Com_Arduino()
        motor_feed(speed, offsetyaw, side)
