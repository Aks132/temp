/* Example sketch to control a stepper motor with TB6600 stepper motor driver and Arduino without a library: number of revolutions, speed and direction. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#include <Servo.h>

Servo myservo1;// create servo object to control a servo
Servo myservo2;
Servo myservo3;


// twelve servo objects can be created on most boards

int pos = 130;

#define stepPin 2
#define dirPin 3
#define enblPin 4

#define stepsPerRevolution 1700

int phase_1 = 0,phase_2 = 0;

long lastTime = 0;

void setup() {
  // Declare pins as output:

  Serial.begin(115200);
  myservo1.attach(11);
  myservo2.attach(12);
  myservo3.attach(13);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enblPin, OUTPUT);
  digitalWrite(stepPin, LOW);
  digitalWrite(enblPin, LOW);
  digitalWrite(dirPin, LOW);

  pinMode(8, INPUT);
  //digitalWrite(phase_1, LOW);

  Serial.println("init");

  digitalWrite(enblPin, HIGH);
  delay(100);
  digitalWrite(enblPin, LOW);

for(int x = 0; x<10; x++){
   myservo1.write(30); //140 is closed position and 90 is total open for right servo
    myservo3.write(130);//90 is closed position and 40 is total open position for left servo
    delay(100);
}
}

void stepper1(long elMS) {
  static long ledTime = 0;
  //do our single mech code here
  ledTime = elMS;
  //Serial.println(ledTime);
  if (ledTime >= 1000 && ledTime <= 4675 ) {

    digitalWrite(dirPin, LOW);
    for (int i = 0; i < 500; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(200);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(200);
    }
}
}
void stepper2(long elMS) {
  static long ledTime = 0;
  //do our single mech code here
  ledTime = elMS + 9000;
   
   if (ledTime >= 9100 && ledTime <= 9900 ) {//2700
    //step forward 100 steps
    digitalWrite(dirPin, HIGH);
    for (int i = 0; i < 500; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(150);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(150);

    }
    digitalWrite(dirPin, LOW);
  }
   else if (ledTime >= 14800 && ledTime <= 16400 ) {//2700
    //step forward 100 steps

    for (int i = 0; i < 500; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(265);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(265);

    }
    digitalWrite(dirPin, LOW);
  }
   else if (ledTime >= 21500 && ledTime <= 22050 ) {//2700
    //step forward 100 steps

    for (int i = 0; i < 500; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(300);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(300);

    }
   digitalWrite(dirPin, LOW);
    }
  /*
  else if (ledTime >= 25000 && ledTime <= 31200 ) {//2700
    //step forward 100 steps
    digitalWrite(dirPin, HIGH);
    for (int i = 0; i < 500; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(300);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(300);

    }
    digitalWrite(dirPin, HIGH);
  }/*/
}

//////##########////////########//////#################

void servo1(long elMS) {
  static long ledTime = 0;
  //do our single mech code here
  ledTime = elMS;

  if (ledTime >= 2000 && ledTime <= 4500 ) {
    myservo1.write(40);//90 is closed position and 40 is total open position for left servo
    myservo2.write(160);//main motor
    myservo3.write(140);//140 is closed position and 90 is total open for right servo

    //Serial.println("running");

  }
}

//////////////////////////////////////////////////////////////////
void servo2(long elMS) {
  static long ledTime = 0;
  //do our single mech code here
  ledTime = elMS + 9000;
  //Serial.println(ledTime);
  if (ledTime >= 12000 && ledTime <= 14000 ) {
    //run motor in backward direction

    myservo1.write(140);
    myservo2.write(160);
    myservo3.write(40);
  }
  else if (ledTime >= 15000 && ledTime <= 15900  ) {


    myservo1.write(140);
    myservo2.write(180);
    myservo3.write(40);

  }
  else if (ledTime >= 17000 && ledTime <= 18000  ) {
    for(int xt = 180;xt > 50;xt = xt - 2){
      myservo2.write(xt);
      myservo1.write(140);
      myservo3.write(40);
      delay(19);
      }
    
    
    Serial.print("Once ledTime");

  }
  else if (ledTime >= 21500 && ledTime <= 22000  ) {

    myservo1.write(140);
    myservo2.write(60);
    myservo3.write(40);

  }
   else if (ledTime >= 23000 && ledTime <= 24000  ) {

    myservo1.write(60);
    myservo2.write(50);
    myservo3.write(70);
   //Serial.println("code is over!");
   
  }
   else if (ledTime >= 24000 && ledTime <= 25000  ) {

    myservo1.write(60);
    myservo2.write(160);
    myservo3.write(80);
   //Serial.println("code is over!");
   
  }
}

void loading()
{
 // Set the spinning direction clockwise:
  //digitalWrite(dirPin, LOW);

  lastTime = millis();
  long  elTime = millis()- lastTime; 
  while(elTime < 9000)
  {
    Serial.println(elTime);
   elTime = millis()- lastTime;  
  stepper1(elTime);
  servo1(elTime);
  
  }
}
void loading2()
{
 // Set the spinning direction clockwise:
  //digitalWrite(dirPin, LOW);

  lastTime = millis();
  long  elTime = millis()- lastTime; 
  while(elTime < 30000)
  {
   //Serial.println(elTime);
   elTime = millis()- lastTime;  
  stepper2(elTime);
  servo2(elTime);
  
  }
  }
void loop() {
  //Serial.println(lastTime);
  phase_1 = digitalRead(8);
  phase_2 = digitalRead(9);
  Serial.println(" Phase1 " + String(phase_1) + " Phase2 " + String(phase_2) );
  if (phase_1 == 1 ){
    Serial.println("in phase1");
    loading();
  }
  if (phase_2 == 1 && millis() > 10000){
    Serial.println("in phase2");
    loading2();
  }
  
}
