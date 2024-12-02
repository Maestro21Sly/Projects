#include<servo.h>
Servo servoLeft;
Servo servoRight;

void setup() {
  servoLeft.attach(12);
  servoRight.attach(11);

//making a 90 degree left turn in place 
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(720);

//returning back to prior position
  servoLeft.writeMicroseco(1700);
  servoRIght.writeMicroseconds(1700);
  delay(timetoturn);

//making a 90 degrees right turn in place
  servoLeft.writeMicroseco(1700);
  servoRIght.writeMicroseconds(1700);
  delay(timetoturn);

//returning back to prior position
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(timetoturn90);

// Pivot forward-left
  servoLeft.writeMicroseconds(1500);   // Left wheel stop
  servoRight.writeMicroseconds(1300);  // Right wheel clockwise

 // Pivot forward-right
  servoLeft.writeMicroseconds(1700);   // Left wheel counterclockwise
  servoRight.writeMicroseconds(1500);  // Right wheel stop

 // Pivot backward-left
  servoLeft.writeMicroseconds(1500);   // Left wheel stop
  servoRight.writeMicroseconds(1700);  // Right wheel counterclockwise

 // Pivot backward-right
  servoLeft.writeMicroseconds(1300);     // Left wheel clockwise
  servoRight.writeMicroseconds(1500);    // Right wheel stop

  //Full speed forward : To straighten, keep the input signals between 1400 and 1600
  servoLeft.writeMicroseconds(1700);
  servoRIght.writeMicroseconds(1300);
  delay(12000);

  servoLeft.detach();
  servoRight.detach();

}

void loop() {
  // put your main code here, to run repeatedly:

}
