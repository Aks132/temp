

void setup() {
  Serial.begin(115200);
  delay(20);  // Give port time to initalize

// mpu_setup();
// Lidarsetup()
Armsetup();
}
void loop() {

String data = Serial.readStringUntil('\n');


//------------Sensor data---------------
//getlidardata();
//getlidardata2();
//motion_sense();
//---------------------------------

delay(10);
Serial.println(" ok "+data);


}
