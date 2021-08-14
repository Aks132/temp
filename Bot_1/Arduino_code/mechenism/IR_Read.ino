

byte ir_pinlist[5] = {A3,A4,A5,A6,A7};
int ir_data[5] = {0,0,0,0,0};
int count_ir[5] = {0,0,0,0,0};



void ir_setup()
{
  for (int o=0;o<=4;o++){
  pinMode(ir_pinlist[o], INPUT);

  }
}

 void ir_work(int lod_sig)
 {
/*  for(int i=0;i<=4;i++)
  {
    Serial.print(digitalRead(ir_pinlist[i]));
  }
  Serial.println();
  */
  for(int p =0; p <=4;p++){
  if(digitalRead(ir_pinlist[p]) == 1)// && ir_data[p] == 0)
  {
    //ir_data[p] = digitalRead(ir_pinlist[p]) ;
 
   digitalWrite(DIR[p], HIGH);
   analogWrite(PWM[p], 0);

  
  }
  }
 }
  
