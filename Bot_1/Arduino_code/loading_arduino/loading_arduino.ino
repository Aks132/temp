
#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;

#define stepPin 2
#define dirPin 3
#define enblPin 4

long lastTime = 0;

void setup() {
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

void stepper()
{
  }

void loop(){
  }
