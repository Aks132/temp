
#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;

#define stepPin 2
#define dirPin 3
#define enblPin 4
int phase_1 = 0;
int phase_2 = 0;
long lastTime = 0;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(20);

  myservo1.attach(9);
  myservo2.attach(5);
  myservo3.attach(6);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enblPin, OUTPUT);
  digitalWrite(stepPin, LOW);
  digitalWrite(enblPin, LOW);
  digitalWrite(dirPin, LOW);

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
void delayread(int halt)
{
  long  start = millis();
  while (halt >= millis() - start)
  { char sig3 = '0';
    char sig4 = '0';
    char sig1 = '0';
    char sig2 = '0';
    char sig5 = '0';

    if (Serial.available())
    { String data = Serial.readStringUntil("/n");
      sig1 = char(data[0]);
      sig2 = char(data[1]);
      sig3 = char(data[2]);
      sig4 = float(data[3]);
      sig5 = char(data[4]);

      if (char(sig1) == '1') {
        phase_1=1;
        Serial.println("PHASE 1 ACTIVATED");
        phase_2=0;
      }

      if (char(sig3) == '1') {
        phase_1=0;
        phase_2=1;
      } 
      
    Serial.println(String(sig1) + " , " + String(sig3) + " , " + " ok ");

  }


}
}

void stepper()
{
        digitalWrite(dirPin, LOW);
          Serial.println("i am here");
          for (int i = 0; i < 5000; i++){
            if (i < 5000){
              digitalWrite(stepPin, HIGH);
              delayMicroseconds(500);
              digitalWrite(stepPin, LOW);
              delayMicroseconds(500);
              }
  }
}

void stepper1(long elMS) {
  static long ledTime = 0;
  //do our single mech code here
  ledTime = elMS;
  Serial.println(ledTime);
  if (ledTime >= 1000 && ledTime <= 2675 ) {

    digitalWrite(dirPin, LOW);
    for (int i = 0; i < 500; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(200);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(200);
    }
}
}

void loading()
{
 // Set the spinning direction clockwise:
  //digitalWrite(dirPin, LOW);

  lastTime = millis();
  long  elTime = millis()- lastTime; 
  while(elTime < 6000)
  {
    Serial.println(elTime);
    elTime = millis()- lastTime;  
    stepper1(elTime);
  //servo1(elTime);
  
  }
}

void loop(){
  delayread(100);
  if(phase_1==1){
    Serial.println("i am in loop");
    loading();
    delay(1000);
    phase_1=0;
    }
  }
