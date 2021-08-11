import serial
import time

try:
    ser1 = serial.Serial('/dev/ttyACM1', 115200, timeout=0.1)  # change name, if needed

except:
    try:
        ser1 = serial.Serial('/dev/ttyACM0', 115200, timeout=0.1)
    except:
        print("/dev/tty Port issue")

def Com_arduino():
    getdata_com1(ser1)
    #message = "P1=" + str(0) + "@" + "P2=" + str(0) + "@" + "A1=0\r"
    #ser1.write(message.encode('utf-8'))



def getdata2():
    resp = ser1.readline().decode('utf-8').rstrip()
    print(resp)





def getdata_com1(ser1):
    global Yaw, dist1
    l = [0, 0, 0]
    try:
        response = ser1.readline().decode('utf-8').rstrip()
        #print(response)

        l = str(response).split('@')  ##@Yaw@dist1@dist2@##
        #print(len(l))
        #print(l)
        if len(l) == 5 and len(response) > 12:
            Yaw = float(l[1])
            dist1 = float(l[2])
            dist2 = float(l[3])
            #print('Yaw ' + str(Yaw) + ' dist1 ' + str(dist1)+' dist2 '+str(dist2))
    except:
        print("Yaw error")
        Yaw = 0
