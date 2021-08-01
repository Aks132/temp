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

def calculat_PID(Yaw,dist1):
    global errordist1, I_Y, I_Yaw, D_Yaw, D_error, error_dist1
    error_dist1 = (reqdist1 - dist1)
    erroryaw = Yaw
    I_Yaw += I_Yaw * I_Y
    D_Yaw = (D_error - Yaw)
    D_error = Yaw
    outyaw = P_Y * (Yaw) + I_Yaw + D_Yaw

    outSide = error_dist1 * P_S

