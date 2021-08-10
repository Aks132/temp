#include "MPU9250.h"
MPU9250 mpu;
float e,f,g,x,y,z,y_g;
//Lidar
#include <TFMPlus.h>  // Include TFMini Plus Library v1.4.2
TFMPlus tfmP;         // Create a TFMini Plus object
TFMPlus tfmP2;         // Create a TFMini Plus object
TFMPlus tfmP3;         // Create a TFMini Plus object

// Initialize variables


void mpu_setup() {
  Wire.begin();
  delay(200);
  MPU9250Setting setting;
  setting.accel_fs_sel = ACCEL_FS_SEL::A16G;
  setting.gyro_fs_sel = GYRO_FS_SEL::G2000DPS;
  setting.mag_output_bits = MAG_OUTPUT_BITS::M16BITS;
  setting.fifo_sample_rate = FIFO_SAMPLE_RATE::SMPL_200HZ;
  setting.gyro_fchoice = 0x03;
  setting.gyro_dlpf_cfg = GYRO_DLPF_CFG::DLPF_92HZ;
  setting.accel_fchoice = 0x01;
  setting.accel_dlpf_cfg = ACCEL_DLPF_CFG::DLPF_99HZ;

  
  if (!mpu.setup(0x68,setting)) {  // change to your own address
    long start = millis();
    while (millis - start < 5000) {
      Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
      delay(1000);
    }
  }

     // mpu.selectFilter(QuatFilterSel::NONE);
    // mpu.selectFilter(QuatFilterSel::MADGWICK);
   mpu.selectFilter(QuatFilterSel::MAHONY);


  mpu.setAccBias(90.91, 88.44, 2.41);
  mpu.setGyroBias(-1.05, 1.09, -0.6);
  mpu.setMagBias(312.62, 256.85, -368.51);
  mpu.setMagScale(1.15,0.89,0.98);
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
   //LIDAR3
  Serial3.begin( 115200);  // Initialize TFMPLus device serial port.
  delay(20);
  tfmP3.begin( &Serial3);   // Initialize device library object and...
 
  Serial.print( "Data-Frame rate: ");
  if ( tfmP3.sendCommand( SET_FRAME_RATE, FRAME_100))
  {
    Serial.print( FRAME_100);
  }
  else tfmP3.printReply();


  
}


//--------------------CODE-------------------------------------

void getlidardata(){
  int16_t tfDist = 0;    // Distance to object in centimeters
  int16_t tfFlux = 0;    // Strength or quality of return signal
  int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
    if( tfmP.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
    {
      dist2 = 0.4*int(tfDist) + 0.6*dist2;   // display distance,
    }
}
void getlidardata2(){
     // delay(5);   // Loop delay to match the 20Hz data frame rate
     int16_t tfDist = 0;    // Distance to object in centimeters
    int16_t tfFlux = 0;    // Strength or quality of return signal
    int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
    if( tfmP2.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
    {
      dist1 = 0.4*int(tfDist) + 0.6*dist1;   // display distance,
    }
    }

void getlidardata3(){
     // delay(5);   // Loop delay to match the 20Hz data frame rate
     int16_t tfDist = 0;    // Distance to object in centimeters
    int16_t tfFlux = 0;    // Strength or quality of return signal
    int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
    if( tfmP3.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
    {
      dist3 = 0.4*int(tfDist) + 0.6*dist3;   // display distance,
    }
    }
void motion_sense(){
    if (mpu.update()) {
    static uint32_t prev_ms = millis();
    if (millis() > prev_ms + 25) {
    YAW = mpu.getYaw(), 2;

    
//    Serial.println(mpu.getMagZ());


    
    //Serial.println(mpu.getEulerZ());
    YAWfilter = 1*YAW + YAWfilter*0.0;
      prev_ms = millis();
    }
  }
  }
