//Setiing Up Servos, LCD and Sensors
#include <SoftwareSerial.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

//Pins for QTIS
#define lineSensor1 47
#define lineSensor2 51
#define lineSensor3 52

//RGB LED
#define redpin 45
#define greenpin 46
#define bluepin 44

//Setting Threshold values
int qti1Threshold = 300;
int midqtiThreshold = 350;  // new inclusion
int qti3Threshold = 250;

//setting up LCD Display
#define TxPin 14
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);  // Define SoftwareSerial instance for LCD

//Setting up color sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
// Servo
Servo servoLeft;
Servo servoRight;

//Setting up variables to keep team statistics
int myScore = -1;
int finalScore = 0;
int teamScores[5];  //create array for team scores
int teams = 0;
char myLetter;
int modFinalScore;


// Set up for our beautiful Canadian National Anthem (first 4 bars)
#define num 21

int durs[num] = { 214, 213, 212, 214, 212, 212, 212, 212, 212, 214, 212,
                  214, 213, 212, 214, 212, 212, 212, 212, 212, 214 };
int octs[num] = { 215, 215, 215, 215, 215, 215, 215, 215, 216, 215, 215,
                  215, 215, 215, 215, 216, 216, 216, 216, 216, 215 };
int notes[num] = { 227, 230, 230, 223, 225, 227, 228, 230, 220, 225, 232,
                   227, 229, 229, 230, 220, 222, 222, 220, 220, 230 };


unsigned long startTime;

bool doneEarly = false;

void setup() {
  startTime = millis();
  Serial.begin(9600);
  Serial2.begin(9600);
  mySerial.begin(9600);
  delay(50);

  //clear LCD Display
  clearContentOnLCD();
  //mySerial.print("Hello");

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
    while (1)
      ;  // halt!
  }
  for (int i = 0; i < 5; i++) {
    teamScores[i] = -1;
  }
}

void loop() {
  int currentState = readQTI();
  performAction(currentState);
}

// Reading QTI input
int readQTI() {
  //initials
  int leftBinary = 0;
  int midBinary = 0;
  int rightBinary = 0;

  int qti1 = rcTime(lineSensor1);  //
  int qti2 = rcTime(lineSensor2);
  int qti3 = rcTime(lineSensor3);

  // Serial.print(qti1);
  // Serial.print(" ");
  // Serial.print(qti2);
  // Serial.print(" ");
  // Serial.print(qti3);
  // Serial.println();

  if (qti1 > qti1Threshold) {
    leftBinary = 0;  //dark
  } else {
    leftBinary = 1;  //light
  }

  if (qti2 > midqtiThreshold) {
    midBinary = 0;
  } else {
    midBinary = 1;
  }

  if (qti3 > qti3Threshold) {
    rightBinary = 0;
  } else {
    rightBinary = 1;
  }

  return 4 * leftBinary + 2 * midBinary + rightBinary;  // Convert qti input to binary, Dark = 0, light = 1
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
  //delay(1000);
}

void stop() {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(1000);
}

void turn90Degrees() {
  // Turn the bot 90 degrees in place
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(400);  // Adjust the delay based on the time needed to turn 90 degrees
  stop();      // Stop the bot after turning
}

void moveForward() {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(1000);
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

void moveBackward() {
  servoLeft.writeMicroseconds(1300);   // Left wheel clockwise
  servoRight.writeMicroseconds(1625);  // Right wheel counterclockwise
}

void set_RGB(int r, int g, int b) {
  analogWrite(redpin, r);
  analogWrite(greenpin, g);
  analogWrite(bluepin, b);
}

void changeLEDColortoGreen() {
  // Change the color of the on-board RGB LED based on your event ring color
  //Our ring is green
  set_RGB(255, 0, 255);
}

void performAction(int currentState) {
  switch (currentState) {
    case 7:
      searchForTrack();
      break;
    case 0:
      stop();
      changeLEDColortoGreen();
      delay(1000);
      turn90Degrees();
      set_RGB(255, 255, 255);
      moveForward();
      delay(1000);
      servoLeft.detach();
      servoRight.detach();
      stop();

      //sensing
      senseObjectColor();

      //mySerial.write(12);

      while (teams != 5) {
        if (millis() - startTime > 120000) {
          teams = 5;
          doneEarly = true;
          break;
        }
        flashPurple();
        Serial2.print(myLetter);
        printInfoOnLCD();

        if (Serial2.available()) {
          flashCyan();
          char incoming = Serial2.read();
          Serial.println(incoming);
          set_RGB(255, 255, 255);

          int team = getTeamID(incoming);
          int score = getTeamScore(incoming);
          if (teamScores[team - 1] == -1) {
            teams++;
          }
          teamScores[team - 1] = score;
        }
        //printInfoOnLCD();
      }

      calculatingFinalScore();

      servoLeft.attach(12);
      servoRight.attach(11);
     
      medalCelebration();
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
    case 2:
      break;
  }
}

void senseObjectColor() {
  float red, green, blue;
  delay(10);
  set_RGB(255, 0, 255);
  tcs.getRGB(&red, &green, &blue);
  delay(1500);
  set_RGB(255, 255, 255);  //Set RGBB off after sensing

  if (red >= 130) {
    myScore = 0;  // Red (Badminton)
    myLetter = 'M';
    Serial.println("Badminton - Score: 0");  //Red
  } else if (green >= 90) {
    myScore = 1;  // Green (Tennis)
    myLetter = 'N';
    Serial.println("Tennis - Score: 1");  // Green
  } else if (green >= 82 && red >= 116) {
    myScore = 2;  // Yellow (Volleyball)
    myLetter = 'O';
    Serial.println("Volleyball - Score: 2");  //Yellow
  }
  teamScores[4] = myScore;
  teams += 1;
}

int getTeamID(char c) {
  int s = (int)c - 62;
  return s / 3;
}

int getTeamScore(char c) {
  int s = (int)c - 62;
  return s % 3;
}

void printInfoOnLCD() {
  //displayying information on LCD
  clearContentOnLCD();
  //display athlete information on LCD
  String athleteInfo = "My Score: " + String(myScore);
  mySerial.print(athleteInfo);
  //displaying other athletes information
  mySerial.write(148);
  for (int i = 0; i < 5; i++) {
    mySerial.print(String(teamScores[i]) + " ");
  }
}

void flashGreen() {
  set_RGB(255, 0, 255);
  delay(100);
  set_RGB(255, 255, 255);
  delay(100);
}

void flashCyan() {
  set_RGB(255, 0, 0);
  delay(100);
  set_RGB(255, 255, 255);
  delay(100);
}

void flashPurple() {
  set_RGB(0, 255, 0);
  delay(100);
  set_RGB(255, 255, 255);
  delay(100);
}

void clearContentOnLCD() {
  mySerial.write(12);  // clear
  delay(10);
  mySerial.write(22);  // no cursor no blink
  delay(10);
  mySerial.write(17);  // backlight
  delay(10);
}

void calculatingFinalScore() {
  if (doneEarly) {
    finalScore = 1;
  } else {
    for (int i = 0; i < 5; i++) {
    if (teamScores[i] != -1 && teams == 5) {
      finalScore += teamScores[i];
    }
    }
  }
  String finalBinary;
  String medal;

  modFinalScore = finalScore % 3;
  switch (modFinalScore) {
    case 0:
      finalBinary = "00";
      medal = "Bronze";
      break;
    case 1:
      finalBinary = "01";
      medal = "Silver";
      break;
    case 2:
      finalBinary = "10";
      medal = "Gold";
      break;
    default:
      break;
  }
  clearContentOnLCD();
  medal = finalBinary + " " + medal;
  mySerial.print(medal);
  mySerial.write(148);
  for (int i = 0; i < 5; i++) {
    mySerial.print(String(teamScores[i]) + " ");
  }
}


// Celebrate based on medal
void medalCelebration() {
  while (millis() - startTime < 120000) {
    Serial2.print(myLetter);
  }
  if (modFinalScore == 0) {
    dance();
  } else if (modFinalScore == 1) {
    lightShow();
  } else if (modFinalScore == 2) {
    anthem();
  }
}

// Perform a coordinated dance
void dance() {
  moveBackward();
  delay(1000);
  stop();
  delay(100);
  turnRight();
  delay(1000);
  stop();
  delay(100);
}

// Perform a light show
void lightShow() {
  // turn LED off
  for (int i = 0; i < 5; i++) {  // Each cycle is approx 3 seconds, 5 times
    delay(500);
    //turn led off
    set_RGB(255, 255, 255);
    delay(500);
    // turn LED red
    set_RGB(0, 255, 255);
    delay(500);
    // turn LED white
    set_RGB(0, 0, 0);
    delay(500);
    //turn LED purple
    set_RGB(128, 255, 128);
    delay(500);
    //turn LED cyan
    set_RGB(255, 128, 128);
    delay(500);
  }
  set_RGB(255, 255, 255);
}

// Play the anthem
void anthem() {
  playSong();
}
// Code used to play the national anthem
void playSong() {
  for (long k = 0; k < num; k++) {

    mySerial.write(durs[k]);
    mySerial.write(octs[k]);
    mySerial.write(notes[k]);
    int len = 214 - durs[k];
    float del = 2000 / pow(2, len);
    delay(int(del * 1.1));
  }
}
