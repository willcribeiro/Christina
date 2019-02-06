#include <Servo.h>
Servo rm;  //Right Motor

void setup() 
{
  rm.attach(9);  //Attach the motor on digital port 9
}

void loop() 
{ 
  //rm.writeMicroseconds(1500);  //Stop the motor
  //delay(20);                          //200 millisecond delay
  //rm.writeMicroseconds(1000);  //(Try to) reverse motor
  //delay(200);
  //rm.writeMicroseconds(1500);  //Stop motor again
  //delay(200);
  rm.writeMicroseconds(1850);  //Move motor forward
  delay(1.10);
  rm.writeMicroseconds(1150);  //Move motor forward
  delay(200000000000000);
}
