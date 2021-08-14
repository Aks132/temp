
//Lidar
#include <TFMPlus.h>  // Include TFMini Plus Library v1.4.2
TFMPlus tfmP;         // Create a TFMini Plus object
TFMPlus tfmP2;         // Create a TFMini Plus object
TFMPlus tfmP3;         // Create a TFMini Plus object



void Lidarsetup(){
//LIDAR2
 Serial2.begin(115200);  // Initialize TFMPLus device serial port.
  delay(20);
  tfmP2.begin( &Serial2);   // Initialize device library object and...
 
  Serial.print( "Data-Frame rate: ");
  if ( tfmP2.sendCommand( SET_FRAME_RATE, FRAME_100))
  {
    Serial.print( FRAME_250);
  }
  else tfmP2.printReply();

  //LIDAR
  Serial1.begin( 115200);  // Initialize TFMPLus device serial port.
  delay(20);
  tfmP.begin( &Serial1);   // Initialize device library object and...
 
  Serial.print( "Data-Frame rate: ");
  if ( tfmP.sendCommand( SET_FRAME_RATE, FRAME_100))
  {
    Serial.print( FRAME_250);
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
    Serial.print( FRAME_250);
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
