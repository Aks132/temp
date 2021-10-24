
void PinB0()
{
  
  SigB[0] = +1;
   if(SigA[0] >= SigB[0])
   {
    Step_diff_time[0] = micros() - Step_starttime[0];
    Step_starttime[0] = micros();
    Steps[0] += 1; 
   }
  }



void PinA0()
{
  SigA[0] = +1;
   if(SigB[0] >= SigA[0])
   {
     Step_diff_time[0] = micros() - Step_starttime[0];
  Step_starttime[0] = micros();
    Steps[0] -= 1; 
   }
  
  }

  void PinB1()
{
  
  SigB[1] = +1;
     if(SigA[1] >= SigB[1])
   {
     Step_diff_time[1] = micros() - Step_starttime[1];
  Step_starttime[1] = micros();
    Steps[1] += 1; 
   }
   
  }



void PinA1()
{
  SigA[1] = +1;
  if(SigB[1] >= SigA[1])
   {
     Step_diff_time[1] = micros() - Step_starttime[1];
  Step_starttime[1] = micros();
    Steps[1] -= 1; 
   }
  
  }

  void PinB2()
{
  
  SigB[2] = +1;
     if(SigA[2] >= SigB[2])
   {
  Step_diff_time[2] = micros() - Step_starttime[2];
  Step_starttime[2] = micros();
    Steps[2] += 1; 
   }
  }



void PinA2()
{
  SigA[2] = +1;
  if(SigB[2] >= SigA[2])
   {
  Step_diff_time[2] = micros() - Step_starttime[2];
  Step_starttime[2] = micros();
    Steps[2] -= 1; 
   }

  }

  void PinB3()
{
  
  SigB[3] = +1;
     if(SigA[3] >= SigB[3])
   {
  Step_diff_time[3] = micros() - Step_starttime[3];
  Step_starttime[3] = micros();
    Steps[3] += 1; 
   }
  }



void PinA3()
{
  SigA[3] = +1;
  if(SigB[3] >= SigA[3])
   {
   Step_diff_time[3] = micros() - Step_starttime[3];
  Step_starttime[3] = micros();
    Steps[3] -= 1; 
   }

  
  }
