#include <Servo.h>
const int pingPin = 35;
Servo servoLeft;
Servo servoRight;

void setup() {
  Serial.begin(9600);
  pinMode(37,OUTPUT);
  pinMode(39,OUTPUT);
  digitalWrite(37,HIGH);
  digitalWrite(39,LOW);

  servoLeft.attach(11);
  servoRight.attach(12);
}
float microsecondsToInches(long microseconds){
  return microseconds/ 74.074/2;
}

void loop() {
  long duration;
  float inches;
  //sending pulse
  pinMode(pingPin,OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin,HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin,LOW);

  //reading back signal
  pinMode(pingPin,INPUT);
  duration = pulseIn(pingPin,HIGH);

  inches = microsecondsToInches(duration);

  Serial.print("The distance of the object from the CXbot is ");
  Serial.print(inches);
  Serial.println();
  if (inches<= 6){
    Serial.println("Too close");
    servoLeft.writeMicroseconds(1300);
    servoRight.writeMicroseconds(1700);
   
  }
  else if (inches>= 10){
    Serial.println("Too far");
    servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1300);
    
  }
  else  {
    Serial.println("Just Right");
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
    delay(1500);

  }
 



}
