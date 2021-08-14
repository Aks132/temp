
float dist1, dist2, dist3;
String data = "Hello";

int stepen =  43;
int steps[5] =   {25, 29, 33, 37, 41}; //{25, 31, 37, 43, 49};
int stepdir[5] = {23, 27, 31, 35, 39}; //{27, 33, 39, 45, 51};


const int RELAY_PIN[5] = {45,47,49,51,53};//{53,51,49,47,45};

int shootcount = 0;
int stepcount[5] = {1000, 1000, 1000, 1000, 1000};
int stepcount_2[5] = { -1800, 1000, 1200, -1700, 1600};
int DIR[5] = {11, 9, 7, 5, 3};//{3, 5, 7, 9, 11};
int PWM[5] = {10 ,8, 6, 4, 2};//{2 ,4, 6, 8, 10};


char command = 0;
int count = 0;
int bc = 0;
char fire = '0';
char set = '0';
char ir = '0';
char lod_r_sig = '0';
int mode = 1;
int count_no = 0;
char st = '0';
long start_count_data = 0; 
long start_mode_data = 0;

int shootlist[5] = {0,3,4,1,2};


long lastTime = millis();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ir_setup();
  Serial.setTimeout(20);
  Serial.println("Ready ");
  Lidarsetup();

  for (int xy = 0; xy <= 4; xy++) {
    pinMode(RELAY_PIN[xy], OUTPUT);
    digitalWrite(RELAY_PIN[xy], HIGH);
  }
  for (int st = 0; st <= 4; st++) {
    pinMode(steps[st], OUTPUT);
    pinMode(stepdir[st], OUTPUT);
    pinMode(PWM[st], OUTPUT);
    pinMode(DIR[st], OUTPUT);


  }
  pinMode(stepen, OUTPUT);
  digitalWrite(stepen, HIGH);
  delay(100);
  digitalWrite(stepen, LOW);
  shootcount = 0;

}


void stepperset(int Sig)
{
  if (Sig == 1) {
    for (int xt = 0; xt < 5; xt++)
    {
      if (stepcount [xt] > 0) {
        digitalWrite(stepdir[xt], LOW);
        for (int i = 0; i < abs(stepcount[xt]); i++) {
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
  delayread(200);
  digitalWrite(RELAY_PIN[x], HIGH);
  delayread(500);
}

void jhonson_ir_set()
{
  for(int ty = 0 ; ty<= 4 ; ty++)
  {digitalWrite(DIR[ty], HIGH);
   analogWrite(PWM[ty], 255);
   delay(100);  
  }}

/*
void jhonson_set(int Si)
{
  if (Si == 1) {long start = millis();
 for (int yt = 0 ; yt <= 4; yt++) {
      digitalWrite(DIR[yt], LOW);
      analogWrite(PWM[yt], 255);
    }
    
  for(int t = 4; t>=0; t--){
  while(millis()-start < Timehalt[t])
  {delayread(50);  
  }
  
  int ix = 0;
  while(Timehalt_r[ix] != Timehalt[t])
  {ix++;}
  Serial.println(String(ix)+"  "+String(millis()-start));
  //stop ix motor
  digitalWrite(DIR[ix], LOW);
  analogWrite(PWM[ix], 0);
  
  }
  }
  else if (Si == 0)
  {
    for (int yt = 0 ; yt <= 4; yt++) {
      digitalWrite(DIR[yt], HIGH);
      analogWrite(PWM[yt], 255);
      delay(Timehalt[yt]);
      analogWrite(PWM[yt], 0);
    }
  }
}

*/
void delayread(int halt)
{
  long  start = millis();
  while (halt >= millis() - start)
  {long check = millis();
    
    getlidardata();
    getlidardata2();
    getlidardata3();

 
   
      ir_work(0);
    
    
    if (Serial.available())
    { 
      data = Serial.readStringUntil("/n");
      fire = char(data[1]);
      set = char(data[0]);
      char x = '0';
       x = char(data[2]);
      st = char(data[3]);
      lod_r_sig = char(data[4]);

      
      if (x == '1' && (millis()-start_count_data) >= 300) {
      start_count_data = millis();
      count_no += 1;

      if (count_no == 5)
        {
          count_no = 0;
        }
      }

      if (x == '2' && (millis()-start_mode_data) >= 300) 
      {
        start_mode_data = millis();
        if(mode == 1 )
        {mode =0;
          }
          else mode = 1;
      }
   


    Serial.println("##@" + String(dist1) + "@" + String(dist2) + "@" + String(dist3) + "@##"+String(count_no)+String(mode)+"  "+String(lod_r_sig)+" ");
    }
    else {
      Serial.println("##@" + String(dist1) + "@" + String(dist2) + "@" + String(dist3) + "@##"+String(millis()-check) + "  ");
    }

  }

}

void loop() {
  //Serial.println(digitalRead(32));
  //Serial.println(shootcount);
  //Serial.println(String(digitalRead(12))+" " + String(digitalRead(32))+" "+String(shootcount));
  delayread(100);
 
  if(mode == 0)
  {control_stepper(count_no , st);
    }
  if(mode == 1)
  {control_jhonson(count_no ,st);
  }


  if (set == '1')
  { Serial.println("YO MF I M DONE!!!! ");
    //stepperset(1);
    jhonson_ir_set();
  }

  if (fire == '1' && shootcount <= 4)
  {
    shoot(shootlist[shootcount]);
    Serial.println(shootlist[shootcount]);
    shootcount += 1 ;
  }
  if (shootcount >= 5) {
    Serial.println("okay here/");
    shootcount = 0;
  }

}
