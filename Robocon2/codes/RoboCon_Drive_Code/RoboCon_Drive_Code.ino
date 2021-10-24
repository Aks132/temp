int encoderAPin[4] = {13,25,32,34}; # ISSUE WITH 34 35 PIN EXT PULLUP 
int encoderBPin[4] = {14,26,33,35}; #ISSE 12 PIN BOOT FAIL USE 27 OR MAY TRY 14

int Step_starttime[4] = {0,0,0,0};
int Step_diff_time[4] = {0,0,0,0};


volatile int SigA[4] = {0,0,0,0};
volatile int SigB[4] = {0,0,0,0};

int Steps[4] = {0,0,0,0};
int rpm[4] = {0,0,0,0};

// ------------------------

int DirPin[4] = {23,4,21,19};
int PwmPin[4]= {22,2,19,18};

#include <analogWrite.h>


  TaskHandle_t Task1;

 void Task(void * parameter)
  {
    
for(int i =0 ; i<+3; i++){
  pinMode(encoderAPin[i], INPUT_PULLUP);
  pinMode(encoderBPin[i], INPUT_PULLUP);

 
  pinMode(DirPin[i],OUTPUT);
  analogWrite(PwmPin[i], 12);

} 

  attachInterrupt(encoderAPin[0], PinA0, RISING);
  attachInterrupt(encoderBPin[0], PinB0, RISING);
   attachInterrupt(encoderAPin[1], PinA1, RISING);
  attachInterrupt(encoderBPin[1], PinB1, RISING);
   attachInterrupt(encoderAPin[2], PinA2, RISING);
  attachInterrupt(encoderBPin[2], PinB2, RISING);
   attachInterrupt(encoderAPin[3], PinA3, RISING);
  attachInterrupt(encoderBPin[3], PinB3, RISING);
    
  for(;;)
  {
    delay(10);
    }


  }
  
void setup() {
 Serial.begin (115200); #UART0 TX GPIO1 RX GPIO3
 Serial2.begin(115200); #UART2 TX GPIO17 RX GPIO16

/*    
for(int i =0 ; i <= 3; i++){
  pinMode(encoderAPin[i], INPUT_PULLUP);
  pinMode(encoderBPin[i], INPUT_PULLUP);


} 

  attachInterrupt(encoderAPin[0], PinA0, RISING);
  attachInterrupt(encoderBPin[0], PinB0, RISING);
   attachInterrupt(encoderAPin[1], PinA1, RISING);
  attachInterrupt(encoderBPin[1], PinB1, RISING);
   attachInterrupt(encoderAPin[2], PinA2, RISING);
  attachInterrupt(encoderBPin[2], PinB2, RISING);
   attachInterrupt(encoderAPin[3], PinA3, RISING);
  attachInterrupt(encoderBPin[3], PinB3, RISING);

*/  
 
  xTaskCreatePinnedToCore(
      Task,
      "T1",
      10000,  //STACK
      NULL,
      1,    // PRIORITY
      &Task1,
      0 ); //core

}

void loop(){

Serial.print(digitalRead(13));
Serial.print("  ");
Serial.print(digitalRead(12));
Serial.print("  ");
Serial.print(digitalRead(26));
Serial.print("  ");
Serial.print(digitalRead(25));
Serial.print("  ");
Serial.print(digitalRead(32));
Serial.print("  ");
Serial.print(digitalRead(33));
Serial.print("  ");
Serial.print(digitalRead(34));
Serial.print("  ");
Serial.print(digitalRead(35));
Serial.println("  ");

  //just here to slow down the output, and show it will workeven during a delay
}
