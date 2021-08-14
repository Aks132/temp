#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;

float servo = 120;
int count = 1;
int step_count = 0;

#define stepPin 2
#define dirPin 3
#define enblPin 4

void setup() {
  // Declare pins as output:

  Serial.begin(115200);
  Serial.setTimeout(20);


  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enblPin, OUTPUT);


  myservo1.attach(7);
  myservo2.attach(5);
  myservo3.attach(6);

  Serial.println("init");

  digitalWrite(enblPin, HIGH);
  delay(100);
  digitalWrite(enblPin, LOW);



  myservo1.write(90); //140 is closed position and 90 is total open for right servo
  myservo3.write(90);//90 is closed position and 40 is total open position for left servo

//close 50,130 open 90,90
}


//long Step_list[] = {2000 }; // assume 8000 = 20 degree

void Stepper_Set(int pos)
{

  if (pos == 1)
  { digitalWrite(dirPin, LOW);
    for (int i = 0; i < 100; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(100);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(100);
    }
  }

  else {
    digitalWrite(dirPin, HIGH);
    for (int i = 0; i < 100; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(100);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(100);
    }
  }

}


void loop()
{

  delayread(100);
  
  //Stepper_Set(1);

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

      if (char(sig4) == '1') {
        servo -= 0.5;
      }

      if (char(sig3) == '1') {
        servo += 0.5;
      }


    }
    myservo2.write(servo);

    if (char(sig1) == '1')
    { Stepper_Set(1);
    step_count += 10;
    }
    Serial.println(String(sig1) + " , " + String(sig2) + " , " + String(sig3) + " , " + String(sig4) + " , " + String(sig5) + " , " + String(servo)+ " "+String(step_count) + " ok ");

    
    if (char(sig2) == '1')
    { Stepper_Set(0);
    step_count -= 10;
    }

    if (char(sig5) == '1')
    {
      grip(); 
      sig5 = '0';
    }
    if (char(sig5) == '1')
    {
      grip(); 
      sig5 = '0';
    }

        if (char(sig6) == '1')
    {
      
    myservo1.write(45); //C 30,  O 150
    myservo3.write(125); //C 180, O 90
    delay(200);
    }
  }


}

void grip()
{

   myservo1.write(90); //C 30,  O 150
    myservo3.write(90); //C 180, O 90
    delay(200);



}
