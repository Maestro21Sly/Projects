// Include servo library
#include <Servo.h>
#include <SoftwareSerial.h>

//Pins for QTI connections on board
#define lineSensor1 49  // left sensor
#define lineSensor2 51  // middle sensor
#define lineSensor3 52  // right sensor

#define threshold1 200  // left
#define threshold2 150  // middle
#define threshold3 150  // right

// Define pins for built-in RGB LED
#define redpin 45
#define greenpin 46
#define bluepin 44

// diving platform thresholds
#define high 1.7
#define medium 2.7
#define low 4

#define TxPin 14

#define num 9

// define ping pin
const int pingPin = 50;

// Declare left and right servos
Servo servoLeft;
Servo servoRight;

// LCD display
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);

// for RGB
float red, green, blue;

// for score tracking
int myScore;
int finalScore;
String letter;
int teamScores[5];
int teams = 0;

// for LCD display
char val = 0;  // variable to store the data from the serial port
int len = 12;  //

void setup() {
  delay(1000);

  servoLeft.attach(11);   // Attach left signal to pin 11
  servoRight.attach(12);  // Attach right signal to pin 12

  Serial.begin(9600);    // start the serial monitor so we can view the output
  Serial2.begin(9600);   // initialize Xbee Tx/Rx
  mySerial.begin(9600);  // start LCD display

  // clear LCD display
  delay(100);
  mySerial.write(12);  // clear
  delay(10);
  mySerial.write(22);  // no cursor no blink
  delay(10);
  mySerial.write(17);  // backlight
  delay(10);

  // Set pin modes
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  // start with light off
  setRGB(255, 255, 255);
  red = 255;
  green = 255;
  blue = 0;

  // initialize score tracking
  myScore = -1;
  finalScore = 0;
  letter = "N";
  for (int i = 0; i < 5; i++) {
    teamScores[i] = -1;
  }
}

void loop() {
  // if sensing is complete
  if (myScore > -1) {
    // turn LED cyan
    setRGB(255, 128, 128);

    // receive data from XBee
    if (teams < 5) {
      if (Serial2.available()) {         // Is XBee data available?
        char incoming = Serial2.read();  // Read character

        int team = getTeam(incoming);
        int score = getScore(incoming);

        if (teamScores[team - 1] == -1) {
          teams += 1;
          teamScores[team - 1] = score;
        }
      }
    }

    // calculate final score
    finalScore = (teamScores[0] + teamScores[1] + teamScores[2] + teamScores[3] + teamScores[4]) % 3;

    // turn LED off
    delay(50);
    setRGB(255, 255, 255);

    // display on LCD
    displayLCD();

    // turn LED purple
    delay(50);
    setRGB(128, 255, 128);
    delay(50);
  
    // transmit score
    Serial2.print(letter);

    // turn LED off
    setRGB(255, 255, 255);
  }

  // if sensing is not complete
  if (myScore == -1) {
    // get QTI sensor values
    int qti1 = rcTime(lineSensor1);
    int qti2 = rcTime(lineSensor2);
    int qti3 = rcTime(lineSensor3);

    // get state
    int state = 4 * (qti1 < threshold1) + 2 * (qti2 < threshold2) + (qti3 < threshold3);

    // perform action with bot
    switch (state) {
      case 7:  // LLL: stop
        if (myScore == -1) {
          stop();
        }
        break;
      case 6:  // LLD: turn right
        turnRightInPlace();
        break;
      case 5:  // LDL: go straight
        forward();
        break;
      case 4:  // LDD: turn right
        turnRightInPlace();
        break;
      case 3:  // DLL: turn left
        turnLeftInPlace();
        break;
      case 2:  // DLD: highly unlikely: stop
        stop();
        break;
      case 1:  // DDL: turn left
        turnLeftInPlace();
        break;
      case 0:  // DDD: hashmark, go into circle
        hashmark();
        break;
      default:
        break;
    }
  }

  delay(25);
}

//Defines funtion 'rcTime' to read value from QTI sensor
// From Ch. 6 Activity 2 of Robotics with the BOE Shield for Arduino
long rcTime(int pin) {
  pinMode(pin, OUTPUT);     // Sets pin as OUTPUT
  digitalWrite(pin, HIGH);  // Pin HIGH
  delay(1);                 // Waits for 1 millisecond
  pinMode(pin, INPUT);      // Sets pin as INPUT
  digitalWrite(pin, LOW);   // Pin LOW
  long time = micros();     // Tracks starting time
  while (digitalRead(pin))
    ;                      // Loops while voltage is high
  time = micros() - time;  // Calculate decay time
  return time;             // Return decay time
}

void turnLeftInPlace() {
  servoLeft.writeMicroseconds(1350);   // Left wheel clockwise
  servoRight.writeMicroseconds(1350);  // Right wheel clockwise
}

void turnRightInPlace() {
  servoLeft.writeMicroseconds(1650);   // Left wheel counterclockwise
  servoRight.writeMicroseconds(1650);  // Right wheel counterclockwise
}

void forward() {
  servoLeft.writeMicroseconds(1575);   // Left wheel counterclockwise
  servoRight.writeMicroseconds(1350);  // Right wheel clockwise
}

void stop() {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}

void setRGB(int r, int g, int b) {
  // Set RGB LED pins based on low=bright (default)
  analogWrite(redpin, r);
  analogWrite(greenpin, g);
  analogWrite(bluepin, b);
}

void hashmark() {
  // stop bot
  stop();

  // turn on onboard LED for 1 second
  setRGB(red, green, blue);
  delay(1000);

  // turn off LED
  setRGB(255, 255, 255);

  int qti1 = rcTime(lineSensor1);
  int qti2 = rcTime(lineSensor2);
  int qti3 = rcTime(lineSensor3);

  // get state
  int state = 4 * (qti1 < threshold1) + 2 * (qti2 < threshold2) + (qti3 < threshold3);
  Serial.println(state);
  while (state != 0) {
    if (state == 4) {
      turnRightInPlace();
      delay(25);
    } else if (state == 1) {
      turnLeftInPlace();
      delay(25);
    }
  }

  forward();
  delay(250);
  stop();
  delay(500);

  // turn right
  turnRightInPlace();
  delay(725);

  stop();
  delay(500);

  // go into circle
  forward();
  delay(1525);
  stop();
  setRGB(red, green, blue);
  delay(1000);

  // use ping sensor to detect distance to diving platform
  float distance = detectHeight();

  // display height of platform
  if (distance <= high) {
    myScore = 2;
    letter = "C";
  } else if (distance <= medium) {
    myScore = 1;
    letter = "B";
  } else if (distance <= low) {
    myScore = 0;
    letter = "A";
  }

  setRGB(255, 255, 255);
  delay(500);

  setRGB(128, 255, 128);
  delay(1000);

  // save scores
  teamScores[0] = myScore;
  teams += 1;

  setRGB(255, 255, 255);

  // detach servos
  servoLeft.detach();
  servoRight.detach();
}

float detectHeight() {
  long duration;
  float inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  return inches;
}

float microsecondsToInches(long microseconds) {
  // The speed of sound is about 1125 ft/s
  // Sound takes about 74.074 us to travel 1 in
  return microseconds / 74.074 / 2;
}

float microsecondsToCentimeters(long microseconds) {
  // The speed of sound is about 343 m/s
  // Sound takes about 29.155 us to travel 1 cm
  return microseconds / 29.155 / 2.0;
}

int getTeam(char c) {
  // get team number
  int s = c - 62;
  return s / 3;
}

int getScore(char c) {
  // get score
  int s = c - 62;
  return s % 3;
}

void displayLCD() {
  // display information on LCD
  mySerial.write(12);  // clear
  delay(10);
  mySerial.write(22);  // no cursor no blink
  delay(10);
  mySerial.write(17);  // backlight
  delay(10);

  // display value on LCD
  String ourScoreData = "Our Score: " + String(myScore);
  mySerial.print(ourScoreData);

  delay(10);
  
  String scoreData = "";
  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
      scoreData += String(teamScores[i / 2]);
    } else {
      scoreData += " ";
    }
  }

  if (finalScore == 0) {
    scoreData += "0";
    scoreData += "0";
  } else if (finalScore == 1) {
    scoreData += "0";
    scoreData += "1";
  } else if (finalScore == 2) {
    scoreData += "1";
    scoreData += "0";
  }

  mySerial.write(148);
  delay(10);
  mySerial.print(scoreData);
  delay(50);
}
