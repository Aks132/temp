#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;


int pos = 130;

#define stepPin 2
#define dirPin 3
#define enblPin 4

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


   myservo1.write(90); //140 is closed position and 90 is total open for right servo
   myservo3.write(90);//90 is closed position and 40 is total open position for left servo
    
}


long Step_list[] = {480000,-12000,20000 }; // assume 8000 = 20 degree

void Stepper_Set(int pos)
{
  
if(Step_list[pos] > 0)
    {digitalWrite(dirPin, LOW);
    for (int i = 0; i < abs(Step_list[pos]); i++) {
      digitalWrite(stepPin, LOW);
      delayMicroseconds(200);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(200);
    }
    }
      
else{
  digitalWrite(dirPin, HIGH);

    for (int i = 0; i < abs(Step_list[pos]); i++) {
      digitalWrite(stepPin, LOW);
      delayMicroseconds(200);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(200);
    }  
  }
    }

void servo()
{
  }


void loop()
{
  phase_1 = digitalRead(8);
  phase_2 = digitalRead(9);
  Serial.println(" Phase1 " + String(phase_1) + " Phase2 " + String(phase_2) );
  if (phase_1 == 1 ){
    Serial.println("in phase1");
    Stepper_Set(0);
    
    
  }
  if (phase_2 == 1 && millis() > 10000){
    Serial.println("in phase2");
    loading2();
  }
  
  }

  
