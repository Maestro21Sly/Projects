#include <Servo.h>
Servo servoLeft;
Servo servoRight;

void setup() {
  pinMOde(pin, OUTPUT);

}

void loop() {
  digitalWrite(pin,HIGH);
  delay(170);
  digitalWrite(13,LOW);
  delay(1830);

}


//make both left and right servo stay still

void setup(){
  servoLeft.attach(pin);
  servoRight.attach(pin);

  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(3000);
}

void loop(){

}
