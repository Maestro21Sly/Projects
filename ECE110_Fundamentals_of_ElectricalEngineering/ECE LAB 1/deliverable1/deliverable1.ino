//Making sure Arduino bot can rotate 90 degrees in either direction and then move forwards for 6ft

#include<servo.h>
Servo servoLeft; //declare Left servo signal
Servo servoRight; // declare Right servo signal

void setup() {
  // put your setup code here, to run once:
  servoLeft.attach(); //Attach left signal pin
  servoRight.attach(); // Attach Right signal pin

}

void loop() {
  // put your main code here, to run repeatedly:

}
