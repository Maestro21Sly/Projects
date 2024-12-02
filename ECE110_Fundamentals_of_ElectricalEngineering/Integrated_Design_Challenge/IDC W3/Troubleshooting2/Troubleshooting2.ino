#include <SoftwareSerial.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

//Setting up pins for QTI sensors
#define lineSensor1 47
#define lineSensor2 51
#define lineSensor3 52

//Setting up on Board RBG
#define redpin 45
#define greenpin 46
#define bluepin 44

//Threshold values for QTIs which need to be adjusted
int lowerThreshold = 250;
int higherThreshold = 350;

//#define TxPin 14
//SoftwareSerial mySerial = SoftwareSerial(255, TxPin);  // Define SoftwareSerial instance for LCD

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Servo servoLeft;
Servo servoRight;

//bool enteredTrack = false;  //Creating a Flag to indicate when to turn on the TCS Sensor

int myScore;
int finalScore=0;
int teamScores[5];  //create array for team scores
int teams = 0;
char myLetter;

void setup() {

  delay(100);
  Serial.begin(9600);
  Serial2.begin(9600);
  mySerial.begin(9600);
  delay(50);
  //Serial.println("here");

  //attach servos
  servoLeft.attach(12);
  servoRight.attach(11);

  // Set pin modes for RGB LED
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  // Start with the LED off (white)
  set_RGB(255, 255, 255);

  //check sensor state
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);  // halt!
  }
  // initially setting all team's scores to 0
  for (int i = 0; i < 5; i++) {
    teamScores[i] = 0;
  }
}

void loop() {
  navigateToHashMark();
  delay(200);

  if(teams< 5){
    if(Serial2.available()){
      set_RGB(0,255,255);
      char incoming = Serial2.read();
      Serial.println(incoming);
      set_RGB(255,255,255);

      int team = getTeamID(incoming);
      int score = getTeamScore(incoming);
      teamScores[team -1] = score;
      teams +=1;
    }
  }
  for (int i =0; i< 5; i++){
    finalScore += teamScores[i];
  }
  
}

void navigateToHashMark() {
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


void set_RGB(int r, int g, int b) {
  analogWrite(redpin, r);
  analogWrite(greenpin, g);
  analogWrite(bluepin, b);
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

int getValue(int QTIsensorValue) {
  if (QTIsensorValue < lowerThreshold) {
    return 1;
  } else if (QTIsensorValue > higherThreshold) {
    return 0;
  }
}

int calculateFinalValue(int value1, int value2, int value3) {
  return (4 * value1) + (2 * value2) + value3;
}

void performAction(int finalValue) {
  switch (finalValue) {
    case 7:
      searchForTrack();
      break;
    case 0:
      changeLEDColortoGreen();
      delay(1000);
      set_RGB(255, 255, 255);  //turn off LED
      turn90Degrees();
      moveForward();
      delay(1000);
      senseObjectColor();

      servoLeft.detach();
      servoRight.detach();

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

void stop() {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(1000);
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
  delay(600);  // Adjust the delay based on the time needed to turn 90 degrees
  stop();      // Stop the bot after turning
}

void moveForward() {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(1000);
}

void senseObjectColor() {
  float red, green, blue;
  delay(60);
  tcs.getRGB(&red, &green, &blue);
  set_RGB(255, 0, 255);
  delay(200);
  set_RGB(255,255,255); //Set RGBB off after sensing

  if (red >= 130) {
    myScore = 0;  // Red (Badminton)
    myLetter = "M";
    Serial.println("Badminton - Score: 0");  //Red
  }
  else if (green >= 90) {
    myScore = 1;  // Green (Tennis)
    myLetter = "N";
    Serial.println("Tennis - Score: 1");  // Green 
  }
  else if (green >= 82 && red >= 116) {
    myScore = 2;  // Yellow (Volleyball)
    myLetter = "O";
    Serial.println("Volleyball - Score: 2");  //Yellow
  }
  teamScores[4] = myScore;
  teams+=1;
  
  set_RGB(0,255,0);
  Serial2.println(myLetter);
  delay(50);
  set_RGB(255,255,255);
}
void turnLeft() {
  servoLeft.writeMicroseconds(1470);
  servoRight.writeMicroseconds(1470);
  delay(25);
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

int getTeamID(char c) {
  int s = c - 62;
  return s / 3;
}

int getTeamScore(char c) {
  int s = c - 62;
  return s % 3;
}


