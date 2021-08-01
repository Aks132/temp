import RPi.GPIO as GPIO
import joy as js
import Com_Arduino
import Auto_mode

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

PWM = [20, 17, 23, 5]
DIG = [21, 27, 24, 6]
Soft_PWM = []
speed = 0
offsetyaw = 0
side = 0


def motor_setup():
    for x in DIG:
        GPIO.setup(x, GPIO.OUT)  # set pin as output
    for y in range(0, 4):
        Soft_PWM.append(GPIO.PWM(PWM[y], 300))  # set pwm frequenvy for M1
    for z in Soft_PWM:
        z.start(0)  # set pin as output


def motor_feed(speed, rotate, side):
    # print(str(int(outyaw)) + " " + str(int(speed)) + " " + str(int(rotate)))

    speedm1 = int(speed + rotate + side)  # + outyaw + outSide + (speed * 0.0))
    speedm2 = int(speed - rotate - side)  # - outyaw - outSide + (speed * 0.0))
    speedm3 = int(speed + rotate - side)  # + outyaw - outSide + (speed * 0.0))
    speedm4 = int(speed - rotate + side)  # - outyaw + outSide + (speed * 0.0))
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
    offsetyaw = (jsVal['axis3']) * 40
    side = (-(jsVal['axis5'] * 70) + (jsVal['axis6'] * 70)) / 2

    # print(str(speed)+" "+str(offsetyaw)+ " "+str(side)+" " + str(P_Y))


if __name__ == '__main__':
    motor_setup()
    while True:
        get_input()
        Com_Arduino()
        motor_feed(speed, offsetyaw, side)


    # try:

    # except:
    #   stop()
    #  print("Exception Errrorrrrrrrrrrrrrrrrrrrrrrrrrr ")

'''
    if jsVal['o'] == 1 or P1 == 1 or P2 == 1:
        P_Y = 0
        I_Y = 0
        I_Yaw = 0
        D_Y = 0
        D_error = 0

    if jsVal['s'] == 1:
        P_S = 0.1
    elif jsVal['t'] == 1 or P1 == 1 or P2 == 1:
        P_S = 0
        stop()

    if jsVal['x'] == 1 and P_Y != 2.5:
        P_Y = 2.5
        I_Y = 0.001
        D_Y = 1
        presetyaw = -Yaw
        Yaw = 0
        time.sleep(1)

'''
