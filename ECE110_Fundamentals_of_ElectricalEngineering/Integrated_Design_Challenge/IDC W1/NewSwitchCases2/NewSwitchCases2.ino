#include <Servo.h>

// Pin definitions
const int lineSensor1 = 47;
const int lineSensor2 = 51;
const int lineSensor3 = 52;

// Thresholds
const int lowerThreshold = 250;
const int higherThreshold = 350;

// Servo objects
Servo servoLeft;
Servo servoRight;

// Enum for final values
enum FinalValues {
  FORWARD = 0,
  STOP = 7,
  TURN_RIGHT = 6,
  MOVE_ON_LINE = 5,
  TURN_RIGHT_2 = 4,
  TURN_LEFT = 3,
  TURN_LEFT_2 = 1
};

// Common function for setting servo positions
void setServoPositions(int left, int right, int duration) {
  servoLeft.writeMicroseconds(left);
  servoRight.writeMicroseconds(right);
  delay(duration);
}

// Function to read analog sensor value
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

// Function to get binary value based on sensor threshold
int getValue(int sensorValue) {
  if (sensorValue < lowerThreshold) {
    return 1;
  } else if (sensorValue > higherThreshold) {
    return 0;
  }
}

// Function to calculate the final value
int calculateFinalValue(int value1, int value2, int value3) {
  return (4 * value1) + (2 * value2) + value3;
}

// Function to perform actions based on the final value
void performAction(int finalValue) {
  if (finalValue == FORWARD) {
    moveForward();
  } else if (finalValue == STOP) {
    stop();
  } else if (finalValue == TURN_RIGHT || finalValue == TURN_RIGHT_2) {
    turnRight();
  } else if (finalValue == MOVE_ON_LINE) {
    moveOnLine();
  } else if (finalValue == TURN_LEFT || finalValue == TURN_LEFT_2) {
    turnLeft();
  }
}

// Function to move forward
void moveForward() {
  setServoPositions(1500, 1500, 1000);
}

// Function to stop
void stop() {
  // Add the stop logic here
}

// Function to turn right
void turnRight() {
  setServoPositions(1530, 1530, 25);
}

// Function to move on the line
void moveOnLine() {
  setServoPositions(1700, 1300, 25);
}

// Function to turn left
void turnLeft() {
  setServoPositions(1470, 1470, 25);
}

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
