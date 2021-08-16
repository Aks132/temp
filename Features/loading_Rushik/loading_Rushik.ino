/* Example sketch to control a stepper motor with TB6600 stepper motor driver and Arduino without a library: number of revolutions, speed and direction. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#include <Servo.h>

Servo myservo1;// create servo object to control a servo
Servo myservo2;
Servo myservo3;
float servo = 120;

int step_count = 0;

// twelve servo objects can be created on most boards

int pos = 130;
int count = 0;
#define stepPin 2
#define dirPin 3
#define enblPin 4

#define stepsPerRevolution 1700

int phase_1 = 0,phase_2 = 0,phase_3=0;
long lastTime = 0;

void setup() {
  // Declare pins as output:

  Serial.begin(115200); 
  Serial.setTimeout(20);
  myservo1.attach(6);
  myservo2.attach(5);
  myservo3.attach(7);
  count=0;
  
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

   myservo1.write(50); //140 is closed position and 90 is total open for right servo
   myservo2.write(90);
   myservo3.write(130);//90 is closed position and 40 is total open position for left servo



}


void stepper(int steps,int sec_steps) {

  if (steps > 0){
    digitalWrite(dirPin, LOW);
    for (int i = 0; i < steps ; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(200);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(200);
    }
    if(sec_steps>0)
    {
      digitalWrite(dirPin, LOW);
      for(int i=0;i<sec_steps;i++)
      {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
      }
    }
    count += 1;
    delay(500);
}
 else if (steps < 0){
    digitalWrite(dirPin, HIGH);
    for (int i = 0; i < abs(steps) ; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(200);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(200);
    }
    if(sec_steps<0)
    {
      digitalWrite(dirPin, HIGH);
      for(int i=0;i<abs(sec_steps);i++)
      {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
      }
    }
    count += 1;
}


}


  
void loop() {
  //Serial.println(lastTime);
  //phase_1 = digitalRead(8);
  //phase_2 = digitalRead(9);
  delayread(100);

  
  Serial.println(" Phase1: " + String(phase_1) + " Phase2: " + String(phase_2) + " Phase 3: " + String(phase_3) + "  " + String(count) );
  if (phase_1 == 1){
    if(count==0){
    stepper(8000,0); //8730
    myservo1.write(50);//open
    myservo2.write(90);
    myservo3.write(130);//open
    delay(500);
    phase_1=0;
    }
  }
  if (phase_2 == 1){
    if(count==1)
    {
    stepper(-2500,-200);
    delay(2000);
    myservo2.write(105);  //gripping
    delay(2000);
    int x=50;
    int y=130;
    for(int i=0;i<5;i++)
    {
      x=x+10;
      y=y-10;
      myservo1.write(x);
      myservo3.write(y);
      delay(500);
    }
//    myservo1.write(90); //close
//    myservo3.write(90);//close
    }
    
   else if(count==2)
    {
      stepper(1,1800);
      myservo1.write(90);//close
      myservo2.write(110);
      myservo3.write(90);//close
      delay(500);
    }
    phase_2=0;
  }
  if(phase_3 == 1)
  {
    if(count==3)
    {
      myservo2.write(60);
      stepper(1,2200);
      int x=60;
      for(int i=0;i<5;i++)
      {
        x=x-10;
        myservo2.write(x);
        delay(100);
      }
      myservo2.write(10);
      myservo1.write(90);
      myservo3.write(90);
      delay(2000);
    }
    if(count==4)
    {
//      int x=35,y=145;
//      for(int i=0;i<5;i++)
//      {
//        x=x+10;
//        y=y-10;
//        myservo1.write(x);
//        myservo2.write(0);
//        myservo3.write(y);
//        delay(500);
//      }
      myservo1.write(50);
      myservo3.write(130);
      delay(1000);
      count++;
    }
    if(count==5)
    {
      stepper(-2000,-7000);
      myservo2.write(90);
    }
    phase_3=0;
  }
}



void delayread(int halt)
{
  long  start = millis();
  while (halt >= millis() - start)
  { char sig3 = '0';
    char sig4 = '0';
    char sig1 = '0';
    char sig2 = '0';
    char sig5 = '0';
    char sig6 = '0';
  
    if (Serial.available())
    { String data = Serial.readStringUntil("/n");
      sig1 = char(data[0]);
      sig2 = char(data[1]);
      sig3 = char(data[2]);
      sig4 = float(data[3]);
      sig5 = char(data[4]);
      sig6 = char(data[5]);

      //Serial.println(String(sig1) + " , " + String(sig3) );//+ " , " + String(sig3) + " , " + String(sig4) + " , " + String(sig5) + " , " + String(servo)+ " "+String(step_count) + " ok ");

      if (char(sig1) == '1')
    { 
      phase_1=1;
    }
      if (char(sig3) == '1')
    { 
      phase_2=1;
    }
    if(char(sig2)=='1')
    {
      phase_3=1;
    }
    
    }
  }
}
