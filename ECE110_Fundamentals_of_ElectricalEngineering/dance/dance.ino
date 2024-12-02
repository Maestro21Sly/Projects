// Set up for Servos:
#include <Servo.h>                           // Include servo library
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
int servoLeftPin = 12;
int servoRightPin = 11;

void setup() {
  // put your setup code here, to run once:
  servoLeft.attach(servoLeftPin);               // Attach left signal to left servo
  servoRight.attach(servoRightPin);          // Attach right signal to right servo

}

void loop() {
  // put your main code here, to run repeatedly:
  dance();
}

void dance() {
  moveBackward();
  delay(1000);
  stop();
  delay(100);
  turnRight();
  delay(2550);
  stop();
  delay(100);
}

// Movement based on QTI
void stop() {
  servoLeft.writeMicroseconds(1500);        
  servoRight.writeMicroseconds(1500);        
}

void moveForward () {
  servoLeft.writeMicroseconds(1600);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1400);        // Right wheel clockwise
}

void moveBackward() {
  servoLeft.writeMicroseconds(1300);         // Left wheel clockwise
  servoRight.writeMicroseconds(1625);        // Right wheel counterclockwise
}

void turnRight() {
  servoLeft.writeMicroseconds(1550);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1550);        // Right wheel counterclockwise
  delay(50);
}

void turnLeft(){
  servoLeft.writeMicroseconds(1450);         // Left wheel clockwise
  servoRight.writeMicroseconds(1450);        // Right wheel clockwise
  delay(50);
}