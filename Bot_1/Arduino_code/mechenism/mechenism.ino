int stepen[5] =  {23, 29, 35, 41, 47};
int steps[5] =   {25, 31, 37, 43, 49};
int stepdir[5] = {27, 33, 39, 45, 51};


int shootcount = 0;
int stepcount[5] = {1800, -1000, -1200, 1700, 1600};
int stepcount_2[5] = {-1800, 1000, 1200, -1700, 1600};
int DIR[5] = {3, 5, 7, 9, 11};
int PWM[5] = {2, 4, 6, 8, 10};
int Timehalt[5] = {1830, 5960, 3550, 760, 1000}; // mm per 100ms {3.6 , 3.15,5.55,5.1,5.1}

char command = 0;
int count = 0;
int bc = 0;




long lastTime = millis();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Ready ");
  //Serial.setTimeout(20);
  pinMode(34, INPUT);
  pinMode(12, INPUT);

  for (int xy = 0; xy <= 4; xy++) {
    pinMode(RELAY_PIN[xy], OUTPUT);
    digitalWrite(RELAY_PIN[xy], HIGH);
  }
  for (int st = 0; st <= 4; st++) {
    pinMode(stepen[st], OUTPUT);
    pinMode(steps[st], OUTPUT);
    pinMode(stepdir[st], OUTPUT);
    pinMode(PWM[st], OUTPUT);
    pinMode(DIR[st], OUTPUT);

    digitalWrite(stepen[st], HIGH);
    delay(100);
    digitalWrite(stepen[st], LOW);
  }



}


void stepperset(int Sig)
{
  if (Sig == 1) {
    for (int xt = 0; xt < 5; xt++)
    {
      if (stepcount > 0) {
        digitalWrite(stepdir[xt], LOW);
        for (int i = 0; i < abs(stepcount[0]); i++) {
          digitalWrite(steps[xt], HIGH);
          delayMicroseconds(500);
          digitalWrite(steps[xt], LOW);
          delayMicroseconds(500);
        }
      }
      else {
        digitalWrite(stepdir[xt], HIGH);
        for (int i = 0; i < abs(stepcount[xt]); i++) {
          digitalWrite(steps[xt], HIGH);
          delayMicroseconds(500);
          digitalWrite(steps[xt], LOW);
          delayMicroseconds(500);

        }
      }
    }

  }

  else if (Sig == 0)
  {
    for (int xt = 0; xt < 5; xt++)
    {
      if (stepcount_2 > 0) {
        digitalWrite(stepdir[xt], HIGH);
        for (int i = 0; i < abs(stepcount[0]); i++) {
          digitalWrite(steps[xt], HIGH);
          delayMicroseconds(500);
          digitalWrite(steps[xt], LOW);
          delayMicroseconds(500);
        }
      }
      else {
        digitalWrite(stepdir[xt], LOW);
        for (int i = 0; i < abs(stepcount[xt]); i++) {
          digitalWrite(steps[xt], HIGH);
          delayMicroseconds(500);
          digitalWrite(steps[xt], LOW);
          delayMicroseconds(500);

        }
      }
    }

  }
}



void shoot(int x)
{
  digitalWrite(RELAY_PIN[x], LOW);
  delay(1000);
  digitalWrite(RELAY_PIN[x], HIGH);
  delay(1000);
}


void jhonson_set(int Si)
{
  if (Si == 1) {
    for (int yt = 0 ; yt <= 4; yt++) {
      digitalWrite(DIR[yt], LOW);
      analogWrite(PWM[yt], 200);
      delay(Timehalt[yt]);
      analogWrite(PWM[yt], 0);
    }
  }
  else if (Si == 0)
  {
    for (int yt = 0 ; yt <= 4; yt++) {
      digitalWrite(DIR[yt], HIGH);
      analogWrite(PWM[yt], 200);
      delay(Timehalt[yt]);
      analogWrite(PWM[yt], 0);
    }
  }
}
void loop() {
  //Serial.println(digitalRead(32));
  //Serial.println(shootcount);
//Serial.println(String(digitalRead(12))+" " + String(digitalRead(32))+" "+String(shootcount));


 if (bc == 1 && digitalRead(12) == 1)
  { Serial.println("YO MF I M DONE!!!! ");
    stepperset(0);
    //jhonson_set(0);
    bc = 0;
  }
  if (digitalRead(12) == 1) {
    delay(1000);
    if (digitalRead(12) == 1) {
    Serial.println("Setup Start");
    stepperset(1);
    //jhonson_set(1);
    }
  }

 


  if (digitalRead(32) == 1 && shootcount < 5)
  {
    shoot(shootcount);
    Serial.println(shootcount);
    shootcount += 1 ;
  }
  else if (shootcount >= 5) {
    Serial.println("okay here/");
    bc = 1;
    shootcount = 0;
  }

}
