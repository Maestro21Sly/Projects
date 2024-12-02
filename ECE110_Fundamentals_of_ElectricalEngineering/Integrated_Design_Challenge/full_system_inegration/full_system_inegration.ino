//Pins for QTI connections on board
#define leftLineSensor 47
#define midLineSensor 51
#define rightLineSensor 52

// Threshold of QTI sensor
int leftThreshold = 325;
int midThreshold = 300;
int rightThreshold = 250;

// Set up for Servos:
#include <Servo.h>                           // Include servo library
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
int servoLeftPin = 12;
int servoRightPin = 11;

// onboard LED
#define redpin 45
#define greenpin 46
#define bluepin 44

// Set up for Thermal sensor:
#include <Wire.h> // I2C library, required for MLX90614
#include <SparkFunMLX90614.h> //Click here to get the library: http://librarymanager/All#Qwiic_IR_Thermometer by SparkFun
IRTherm therm; // Create an IRTherm object to interact with throughout
float tempThreshold = 58;

// By default, trickPosition == 2 == lame
int trickPosition = 0;
char scoreChar;

// Set up for LCD
#include <SoftwareSerial.h>
#define TxPin 14
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);

// Int array used to keep track of received scores
int scores[5]; 
int receivedIterations = 0; // number of scores received

// Declaration of finalScore, initialized to 0
int finalScore = 0;
int modFinalScore;

// Set up for our beautiful Canadian National Anthem (first 4 bars)
#define num 21

int durs[num]  = {214, 213, 212, 214, 212, 212, 212, 212, 212, 214, 212,
                  214, 213, 212, 214, 212, 212, 212, 212, 212, 214};
int octs[num]  = {215, 215, 215, 215, 215, 215, 215, 215, 216, 215, 215,
                  215, 215, 215, 215, 216, 216, 216, 216, 216, 215};
int notes[num] = {227, 230, 230, 223, 225, 227, 228, 230, 220, 225, 232,
                  227, 229, 229, 230, 220, 222, 222, 220, 220, 230};
void setup() {
  Serial.begin(9600); //start the serial monitor so we can view the output
  Serial2.begin(9600); // start serial 2 for printing character
  Wire.begin(); //Joing I2C bus

  servoLeft.attach(servoLeftPin);               // Attach left signal to left servo
  servoRight.attach(servoRightPin);          // Attach right signal to right servo

  set_RGB(255,255,255);

  // Set up thermal sensor:
  if (therm.begin() == false){ // Initialize thermal IR sensor
    Serial.println("Qwiic IR thermometer did not acknowledge! Freezing!");
  }
  Serial.println("Qwiic IR Thermometer did acknowledge.");
  
  therm.setUnit(TEMP_F); // Set the library's units to Farenheit (sic)
  // Alternatively, TEMP_F can be replaced with TEMP_C for Celsius or
  // TEMP_K for Kelvin.
  for (int i = 0; i < 5; i++) {
    scores[i] = -1; // Initialize received scores to be -1
  }

  // Start with LCD off
  mySerial.begin(9600);
  clearLCD();
}

void loop() {
  int state = readQTI();
  float red, green, blue;
  // Based on QTI input, choose action
  switch (state) {
    case 0:
      stop();
      break;
    case 1:
      turnRight();
      break;
    case 2:
      moveForward();
      break;
    case 3:
      turnRight();
      break;
    case 4:
      turnLeft();
      break;
    case 5:
      Serial.println("You should not be here");
      break;
    case 6:
      turnLeft();
      break;
    case 7:
      continueTask(); // At hashmark, turn into center a perform task, gets position

      servoLeft.detach();
      servoRight.detach(); // Prevents excess voltage from going to servo and harming servo in transmission code

      transmitLoop(trickPosition); // Transmit info

      finalScoreCalculation();

      servoLeft.attach(servoLeftPin);               // Attach left signal to left servo
      servoRight.attach(servoRightPin);   
      medalCelebration();
      break;
    default:
      break;
  }

  delay(100);

  Serial.println(state);  
  set_RGB(255,255,255);
}

// Reading QTI input
int readQTI() {
  int leftBinary = 0;
  int midBinary = 0;
  int rightBinary = 0;

  int qti1 = rcTime(leftLineSensor); 
  int qti2 = rcTime(midLineSensor);
  int qti3 = rcTime(rightLineSensor);
  
  Serial.print(qti1);
  Serial.print(" ");
  Serial.print(qti2);
  Serial.print(" ");
  Serial.print(qti3);
  Serial.println();

  if (qti1 > leftThreshold) {
    leftBinary = 1;
  } else {
    leftBinary = 0;
  }

  if (qti2 > midThreshold) {
    midBinary = 1;
  } else {
    midBinary = 0;
  }

  if (qti3 > rightThreshold) {
    rightBinary = 1;
  } else {
    rightBinary = 0;
  }

  return 4*leftBinary + 2*midBinary + rightBinary; // Convert qti input to binary, Dark = 1, light = 0

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

void set_RGB(int r, int g, int b){
  // Set RGB LED pins based on low=bright (default)
  analogWrite(redpin, r);
  analogWrite(greenpin, g);
  analogWrite(bluepin, b);
}

//Defines funtion 'rcTime' to read value from QTI sensor
// From Ch. 6 Activity 2 of Robotics with the BOE Shield for Arduino
long rcTime(int pin)
{
  pinMode(pin, OUTPUT);    // Sets pin as OUTPUT
  digitalWrite(pin, HIGH); // Pin HIGH
  delay(1);                // Waits for 1 millisecond
  pinMode(pin, INPUT);     // Sets pin as INPUT
  digitalWrite(pin, LOW);  // Pin LOW
  long time = micros();    // Tracks starting time
  while(digitalRead(pin)); // Loops while voltage is high
  time = micros() - time;  // Calculate decay time
  return time;             // Return decay time
}

// This function is all code in case 7 of the switch statement just in a function to make it more readable.
void continueTask(){
  stop();
  set_RGB(0,255,255); // Turn onboard RGB RED
  delay(1000);
  turnRight();
  delay(1000);
  set_RGB(255,255,255); // Turn onboard RGB OFF
  moveForward(); // Move to sick position
  delay(1300);
  stop();

  set_RGB(0,255,255); // Turn onboard RGB RED
  readTemperature(1); // Sense temperature at sick position
  delay(1000);
  set_RGB(255,255,255); // Turn onboard RGB OFF
  if (trickPosition == 1) { // If bottle at sick, stop looking for bottle
    return;
  }

  moveForward(); // Move to position 2, gnarly
  delay(1050);
  stop();

  set_RGB(0,255,255); // Turn onboard RGB RED
  readTemperature(2); // Sense temperature at gnarly position
  delay(1000);
  set_RGB(255,255,255); // Turn onboard RGB off
}

// Sense temperature
void readTemperature(int position) {

  // Call therm.read() to read object and ambient temperatures from the sensor.
  if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    // Use the object() and ambient() functions to grab the object and ambient
	// temperatures.
	// They'll be floats, calculated out to the unit you set with setUnit().
    Serial.print("Object: " + String(therm.object(), 2));
    Serial.println("F");
    Serial.print("Ambient: " + String(therm.ambient(), 2));
    Serial.println("F");
    Serial.println();
  }

  if (therm.object() < tempThreshold) {
    trickPosition = position; // if the cold water is at a position, set the global variable of the position of the trick to equal the position of the cold water
  }
}

void transmitLoop(int position) {
  switch (position) {
    case 0:
      scoreChar = 'G';
      break;
    case 1:
      scoreChar = 'H';
      break;
    case 2:
      scoreChar = 'I';
      break;
    default:
      break;
  }

  scores[2] = position;

  while (receivedIterations != 4){
    receiveInfo();
    displayScores();
    transmitInfo(scoreChar); // Transmit chracter 20 times, takes 10 seconds
  }
}

// Given position of trick, transmit info through XBee
void transmitInfo(char positionChar) {
  flashPurple();
  Serial2.print(positionChar);
  flashPurple();
  delay(100); // Loop takes 500ms as flashPurple called twice for 200ms and an extra 100 ms delay
}

// Function that flashes LED (takes 200ms)
void flashPurple() {
  set_RGB(0, 255, 0);
  delay(100);
  set_RGB(255,255,255);
  delay(100);
}

// receive info
void receiveInfo() {
  set_RGB(255, 0, 0);

  if (Serial2.available()) {
    char incoming = Serial2.read();
    int offset = (int)incoming - 62;
 
    int index = ((offset/3)-1);
    if (scores[index] == -1) { // If we haven't updated the score in the array, update array
      receivedIterations++;
      scores[index] = offset % 3; 
    }
  }
}

// Displays our team score first line, displays scores of everyone second line
void displayScores() {
  String output = "Our score " + String(scores[2]);
  clearLCD();
  mySerial.print(output);
  mySerial.write(13);
  for (int i = 0; i < 5; i++) {
    mySerial.print(String(scores[i]) + " ");
  }
}

// LCD clearing function
void clearLCD() {
  mySerial.write(12); // clear
  delay(10);
  mySerial.write(22); // no cursor no blink
  delay(10);
  mySerial.write(17); // backlight
  delay(10);
}

// Loops through area and calculates final score
void finalScoreCalculation() {
  for (int i = 0; i < 5; i++) {
    if (scores[i] != -1) {
      finalScore += scores[i];
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

  clearLCD();
  mySerial.print(finalBinary + " " + medal);
  mySerial.write(13);
  for (int i = 0; i < 5; i++) {
    mySerial.print(String(scores[i]) + " ");
  }
}

// Celebrate based on medal
void medalCelebration() {
  if (modFinalScore == 0) {
    dance();
  } else if (modFinalScore == 1){
    lightShow();
  } else if (modFinalScore == 2){
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
  delay(2550);
  stop();
  delay(100);
}

// Perform a light show
void lightShow() {
  // turn LED off
  for(int i = 0; i < 5; i ++) { // Each cycle is approx 3 seconds, 5 times
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
   for(long k=0; k<num; k++){
    
    mySerial.write(durs[k]); mySerial.write(octs[k]); mySerial.write(notes[k]);
    int len = 214 - durs[k];
    float del = 2000 / pow(2, len);
    delay(int(del*1.1));
  }
}
