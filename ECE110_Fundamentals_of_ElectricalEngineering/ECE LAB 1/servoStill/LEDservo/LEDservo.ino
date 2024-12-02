#include <Servo.h>
Servo servoLeft;
Servo servoRight;

void setup() {
  servoLeft.attach(13);
  servoRight.attach(10);

  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);

}

void loop() {
  // put your main code here, to run repeatedly:

}
