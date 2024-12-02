#include <Servo.h>

#define lineSensor1 47
#define lineSensor2 51
#define lineSensor3 52

int lowerThreshold = 250;
int higherThreshold = 350;

Servo servoLeft;
Servo servoRight;

void setup() {
  Serial.begin(9600);
  servoLeft.attach(12);
  servoRight.attach(11);
}

void loop() {
  int qti1 = rcTime(lineSensor1);
  int qti2 = rcTime(lineSensor2);
  int qti3 = rcTime(lineSensor3);
  delay(50);

  int value1 = getValue(qti1);
  int value2 = getValue(qti2);
  int value3 = getValue(qti3);

  int finalValue = calculateFinalValue(value1, value2, value3);
  Serial.println(finalValue);

  performAction(finalValue);
}

int getValue(int sensorValue) {
  if (sensorValue < lowerThreshold) {
    return 1;
  } else if (sensorValue > higherThreshold) {
    return 0;
  }
}

int calculateFinalValue(int value1, int value2, int value3) {
  return (4 * value1) + (2 * value2) + value3;
}

void performAction(int finalValue) {
  switch (finalValue) {
    case 0:
      moveForward();
      break;
    case 7:
      stop();
      break;
    case 6:
      turnRight();
      break;
    case 5:
      moveOnLine();
      break;
    case 4:
      turnRight();
      break;
    case 3:
      turnLeft();
      break;
    case 1:
      turnLeft();
      break;
  }
}

void moveForward() {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(1000);
}

void stop() {
  // Add the stop logic here
}

void turnRight() {
  servoLeft.writeMicroseconds(1530);
  servoRight.writeMicroseconds(1530);
  delay(25);
}

void moveOnLine() {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(25);
}

void turnLeft() {
  servoLeft.writeMicroseconds(1470);
  servoRight.writeMicroseconds(1470);
  delay(25);
}

long rcTime(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(1);
  pinMode(pin, INPUT);
  digitalWrite(pin, LOW);
  long time = micros();
  while (digitalRead(pin));
  time = micros() - time;
  return time;
}
