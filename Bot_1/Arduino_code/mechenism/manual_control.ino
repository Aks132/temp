void control_jhonson(int x,char y)
{
    if (y == '2'){
      digitalWrite(DIR[x], LOW);
      analogWrite(PWM[x], 255);
      delay(100);
      delayread(200);
      analogWrite(PWM[x], 0);
    
    }

    else if (y == '1'){
      digitalWrite(DIR[x], HIGH);
      analogWrite(PWM[x], 255);
      delay(100);
      delayread(200);
      analogWrite(PWM[x], 0);
    
    }
  }

void control_stepper(int x , char y){

     if (y == '1'){
      
    for(int u = 0 ; u <= 1000 ; u++){
    digitalWrite(stepdir[x], LOW);
    digitalWrite(steps[x], HIGH);
    delayMicroseconds(200);
    digitalWrite(steps[x], LOW);
    delayMicroseconds(200);
    }
     }

     
    else if (y == '2'){
    for(int u = 0 ; u <= 1000 ; u++){
    digitalWrite(stepdir[x], HIGH);
    digitalWrite(steps[x], HIGH);
    delayMicroseconds(200);
    digitalWrite(steps[x], LOW);
    delayMicroseconds(200);}
  }

}
int sort_desc(const void *cmp1, const void *cmp2)
{
  // Need to cast the void * to int *
  int a = *((int *)cmp1);
  int b = *((int *)cmp2);
  // The comparison
  return a > b ? -1 : (a < b ? 1 : 0);
  // A simpler, probably faster way:
  //return b - a;
}

void IR_Sensor(){
  
  
  
  }
