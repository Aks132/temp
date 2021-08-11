import joy as js

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

def calculat_PID():
    global errordist1, I_Y, I_Yaw, D_Yaw, D_error, error_dist1,D_Y,P_S,Yaw,dist1,dist2,P_Y,presetyaw
    jsVal = js.getJS()
    if jsVal['o'] == 1:
        P_Y = 0
        I_Y = 0
        I_Yaw = 0
        D_Y = 0
        D_error = 0

    if jsVal['s'] == 1:
        P_S = 0.
    elif jsVal['t'] == 1 :
        P_S = 0

    if jsVal['x'] == 1 and P_Y != 2.5:
        P_Y = 2.5
        I_Y = 0.001
        D_Y = 1
        presetyaw = -0.9*Yaw
        Yaw = 0


error_dist1 = (reqdist1 - dist1)
erroryaw = Yaw + presetyaw
print(erroryaw)
I_Yaw += I_Yaw * I_Y
D_Yaw = (D_error - erroryaw)
D_error = Yaw
outyaw = P_Y * (erroryaw) + I_Yaw + D_Yaw

outSide = error_dist1 * P_S

