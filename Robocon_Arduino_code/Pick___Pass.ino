#include <Servo.h>
Servo Arm1;
Servo Arm2;
Servo Arm3;
Servo Arm4;


void Armsetup() {
  Arm1.attach(2); // 70 , 120  
  Arm2.attach(3);  // 50 , 140 
  Arm3.attach(4); 
  Arm4.attach(5);
  Hold();

}

/*
void loop() {
//Hold();
delay(1000);
Pick();
delay(1000);
Hold();
delay(3000);
Pass();
delay(1000);
}
*/
void Pick(){
   Arm1.write(60); 
   delay(1000);

   Arm4.write(15); 
   delay(200);
   Arm3.write(47); 
   delay(200);
   Arm2.write(50);
   delay(200); 

   //grab
   for(int gr = 50; gr <=120 ; gr=gr+10){
   Arm1.write(gr); 
   delay(300);
   }
}

void Hold(){
   Arm4.write(180); 
   delay(200);
   Arm3.write(0); 
   delay(200);
   Arm2.write(50);
   delay(100); 
   Arm1.write(120); 
   delay(100);
}

void Pass(){
   Arm1.write(120);  //Grabbed 
   delay(200);
   for(int gr = 180; gr >=150 ; gr=gr-2){
   Arm4.write(gr); 
   delay(100);
   }  
   Arm3.write(0); 
   // Arm2.write(150); 
  // delay(600);
      Arm1.write(50);   
   delay(200);
    


}
