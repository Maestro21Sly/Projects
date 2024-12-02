#include <SoftwareSerial.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

#define lineSensor1 47
#define lineSensor2 51
#define lineSensor3 52

#define redpin 45
#define greenpin 46
#define bluepin 44

int lowerThreshold = 250;
int higherThreshold = 350;
//dark > 350
//light < 250
#define TxPin 14
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);  // Define SoftwareSerial instance for LCD

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Servo servoLeft;
Servo servoRight;


void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(50);
  Serial.println("here");


  servoLeft.attach(12);
  servoRight.attach(11);

  // Set pin modes for RGB LED
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  // Start with the LED off (white)
  set_RGB(0, 0, 0);
  delay(10000);  //turn LED off
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);  // halt!
  }
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
  //Serial.println(finalValue);

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
int objectColor = senseObjectColor();
//displayScore(objectColor);

void performAction(int finalValue) {
  switch (finalValue) {
    case 7:
      searchForTrack();
      break;
    case 0:
      //if (digitalRead(lineSensor1) == LOW && digitalRead(lineSensor2) == LOW && digitalRead(lineSensor3) == LOW) {
      stop();
      changeLEDColortoGreen();
      delay(1000);
      set_RGB(255, 255, 255);
      turn90Degrees();
      moveForward();
      delay(500);
      servoLeft.detach();
      servoRight.detach();
      senseObjectColor();
      displayScore(objectColor);



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

void searchForTrack() {
  // Initial movement to the right
  servoLeft.writeMicroseconds(1530);
  servoRight.writeMicroseconds(1470);
  delay(500);

  // Stop briefly
  stop();
  delay(500);

  // Movement to the left
  servoLeft.writeMicroseconds(1470);
  servoRight.writeMicroseconds(1530);
  delay(1000);

  // Stop briefly
  stop();
  delay(500);

  // Resume forward movement
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(1000);
}

void moveForward() {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(1000);
}

void stop() {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(1000);
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

void changeLEDColortoGreen() {
  // Change the color of the on-board RGB LED based on your event ring color
  //Our ring is green
  set_RGB(255, 0, 255);
}

void turn90Degrees() {
  // Turn the bot 90 degrees in place
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(570);  // Adjust the delay based on the time needed to turn 90 degrees
  stop();      // Stop the bot after turning
}

long rcTime(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(1);
  pinMode(pin, INPUT);
  digitalWrite(pin, LOW);
  long time = micros();
  while (digitalRead(pin))
    ;
  time = micros() - time;
  return time;
}

void set_RGB(int r, int g, int b) {
  analogWrite(redpin, r);
  analogWrite(greenpin, g);
  analogWrite(bluepin, b);
}
int senseObjectColor() {
  set_RGB(255, 0, 255);
  float red, green, blue;
  delay(60);
  tcs.getRGB(&red, &green, &blue);

  //Serial.print("R:\t"); Serial.print(int(red));
  //Serial.print("\tG:\t"); Serial.print(int(green));
  //Serial.print("\tB:\t"); Serial.print(int(blue));
  //Serial.print("\n");

  /**if (red > green && red > blue) {
    return 0;  // Red (Badminton)
  } else if (green > red && green > blue) {
    return 1;  // Green (Tennis)
  } else if (green>90 && blue >= 57) {
    return 2;  // Yellow (Volleyball)
  } else {
    return -1; // No specific color detected
  }
}*/
  if (red >= 150) {
    return 0;  // Red (Badminton)
  } else if (green >= 100) {
    return 1;  // Green (Tennis)
  } else if (green >= 80 && 100 < red <= 150) {
    return 2;  // Yellow (Volleyball)
  }
}



void displayScore(int color) {
  //Serial.print("Object Color: ");
  switch (color) {
    case 0:
      Serial.println("Badminton - Score: 0");  //Badminton
      mySerial.print("Badminton Score: 0");
      set_RGB(0, 255, 0);
      Serial2.print(0);
      break;
    case 1:
      Serial.println("Tennis - Score: 1");  //Green
      mySerial.print("Tennis Score: 1");
      set_RGB(0, 255, 0);
      Serial2.print(1);

      break;
    case 2:
      Serial.println("Volleyball - Score: 2");  //Yellow
      mySerial.print("Volleyball Score: 2");
      set_RGB(0, 255, 0);
      Serial2.print(2);
      break;
    default:
      Serial.println("No specific color detected");
      mySerial.print("No Color Detected");
      break;
  }
}
