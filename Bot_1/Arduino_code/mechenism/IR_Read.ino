

byte ir_pinlist[5] = {A3,A4,A5,A6,A7};
int ir_data[5] = {0,0,0,0,0};

void ir_setup()
{
  for (int o=0;o<=4;o++){
  pinMode(ir_pinlist[o], INPUT);

  }
}

 void ir_work()
 {
  for(int p =0; p <=4;p++){
  if(digitalRead(ir_pinlist[p]) == 1)// && ir_data[p] == 0)
  {
    //ir_data[p] = digitalRead(ir_pinlist[p]) ;
   digitalWrite(DIR[p], HIGH);
   analogWrite(PWM[p], 0);
 
   //digitalRead(ir_pinlist[p]) = 0;
/*   if(x == '1')
   {
   digitalWrite(DIR[p], HIGH);
   analogWrite(PWM[p], 255);
   delay(100);
    
    }
   */
  }
  }
 }
  
