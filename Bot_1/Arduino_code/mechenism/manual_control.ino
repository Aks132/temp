void control_jhonson(int x,char y)
{
    if (y == '2'){
      digitalWrite(DIR[x], LOW);
      analogWrite(PWM[x], 255);
      delayread(300);
      analogWrite(PWM[x], 0);
    
    }

    else if (y == '1'){
      digitalWrite(DIR[x], HIGH);
      analogWrite(PWM[x], 255);
      delayread(300);
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
