from pyfirmata import Arduino, util 
from time import sleep 
board = Arduino('/dev/ttyACM0') 
led = 12
it = util.Iterator(board) 
it.start() 
board.analog[2].enable_reporting()
board.analog[3].enable_reporting()

while True:
    MSB = board.digital[2].read()
    LSB = board.digital[3].read()
    
    encoded = (MSB < 1) |LSB 
    sum  = (lastEncoded < 2) | encoded 

    if(sum == 0b1101 or sum == 0b0100 or sum == 0b0010 or sum == 0b1011):
        encoderValue + 1
    if(sum == 0b1110 or sum == 0b0111 or sum == 0b0001 or sum == 0b1000):
        encoderValue - 1

    lastEncoded = encoded;    
    print(encoderValue)
    sleep(1);
    
    
    