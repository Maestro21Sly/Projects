#include <Servo.h>
Servo servoLeft;
Servo servoRight;

void setup() {
  servoLeft.attach(pin);
  servoRight.attach(pin);
//code to turn Left servo clockwise full speed
  servoLeft.writeMicroseconds(1300);
  delay(3000);

//code to turn Right servo clockwise full speed
  servoRight.writeMicroseconds(1300);
  delay(3000);

//code to turn Left servo anticlockwise full speed
  servoLeft.writeMicroseconds(1700);
  delay(3000);

//code to turn Right servo full speed anticlockwise
  servoRight.writeMicroseconds(1700);
  delay(3000);

//code to bring Right servo to still
  servoRight.writeMicroseconds(1500);

//code to bring Left servo to still
  servoLeft.writeMicroseconds(1500);
}

void loop(){
  
}