#include "MPU9250.h"
MPU9250 mpu;

//Lidar
#include <TFMPlus.h>  // Include TFMini Plus Library v1.4.2
TFMPlus tfmP;         // Create a TFMini Plus object
TFMPlus tfmP2;         // Create a TFMini Plus object

// Initialize variables

float YAW,YAWfilter;
int dist2 = 0;
int dist1 = 800;
float offset_yaw = -60;
float I_YAW = 0; 
boolean mpusetup = false;



void mpu_setup() {
  Wire.begin();
  delay(200);
  if (!mpu.setup(0x68)) {  // change to your own address
    long start = millis();
    while (millis - start < 5000) {
      Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
      delay(1000);
    }
  }

  mpu.setAccBias(-87.91, -7.44, -30.48);
  mpu.setGyroBias(-1.65, 1.09, 0.7);
  mpu.setMagBias(223.69, 28.85, -180.51);
  mpu.setMagScale(1.05,0.98,0.98);
  mpu.setMagneticDeclination(0.26);

}

void Lidarsetup(){
//LIDAR2
 Serial2.begin( 115200);  // Initialize TFMPLus device serial port.
  delay(20);
  tfmP2.begin( &Serial2);   // Initialize device library object and...
 
  Serial.print( "Data-Frame rate: ");
  if ( tfmP2.sendCommand( SET_FRAME_RATE, FRAME_100))
  {
    Serial.print( FRAME_100);
  }
  else tfmP2.printReply();

  //LIDAR
  Serial1.begin( 115200);  // Initialize TFMPLus device serial port.
  delay(20);
  tfmP.begin( &Serial1);   // Initialize device library object and...
 
  Serial.print( "Data-Frame rate: ");
  if ( tfmP.sendCommand( SET_FRAME_RATE, FRAME_100))
  {
    Serial.print( FRAME_100);
  }
  else tfmP.printReply();
  //------------------------------------------------------------
}


//--------------------CODE-------------------------------------

void getlidardata(){
  int16_t tfDist = 0;    // Distance to object in centimeters
  int16_t tfFlux = 0;    // Strength or quality of return signal
  int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
    if( tfmP.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
    {
      dist2 = int(tfDist);   // display distance,
    }
}
void getlidardata2(){
     // delay(5);   // Loop delay to match the 20Hz data frame rate
     int16_t tfDist = 0;    // Distance to object in centimeters
    int16_t tfFlux = 0;    // Strength or quality of return signal
    int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
    if( tfmP2.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
    {
      dist1 = int(tfDist);   // display distance,
    }
    }
void motion_sense(){
    if (mpu.update()) {
    static uint32_t prev_ms = millis();
    if (millis() > prev_ms + 25) {
    YAW = mpu.getYaw(), 2;
    YAWfilter = 0.4*YAW + YAWfilter*0.6;
      prev_ms = millis();
    }
  }
  }
