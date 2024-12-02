#include "Adafruit_TCS34725.h"
#define redpin 45
#define greenpin 46
#define bluepin 44
// Initialize color sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


void setup() {
 Serial.begin(9600);
 Serial.println("Sensor Test!");

 if (tcs.begin()) {
   Serial.println("Found sensor");
 } else {
   Serial.println("No TCS34725 found ... check your connections");
   while (1); // halt!
 }
  
   // Set pin modes
 pinMode(redpin, OUTPUT);
 pinMode(greenpin, OUTPUT);
 pinMode(bluepin, OUTPUT);
 // start with light off

 set_RGB(255, 255, 255);

}

void loop() {
 float red, green, blue;

 delay(60);  // takes 50ms to read
 tcs.getRGB(&red, &green, &blue);

 Serial.print("R:\t"); Serial.print(int(red));
 Serial.print("\G:\t"); Serial.print(int(green));
 Serial.print("\tB:\t"); Serial.print(int(blue));
 Serial.print("\n");
 if (red>125)
   if(green>80)
   {
     set_RGB(0, 0, 255);
     delay(100);
   }
   else{
     set_RGB(0, 255, 255);
     delay(100);

     
   }
     
 else if (green>105)
 {
   set_RGB(255, 0, 255);
   delay(100);
 }
 else
 {
    set_RGB(255, 255, 255);

 }
}

void set_RGB(int r, int g, int b){
 // Set RGB LED pins based on high=bright 
 analogWrite(redpin, r);
 analogWrite(greenpin, g);
 analogWrite(bluepin, b);
}


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
Servo servoLeft;
Servo servoRight;

void setup() {
  Serial.begin(9600);
  servoLeft.attach(12);
  servoRight.attach(11);

  // Set pin modes for RGB LED
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  // Start with the LED off (white)
  set_RGB(255, 255, 255);
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
    case 7:
      searchForTrack();
      break;
    case 0:
      //if (digitalRead(lineSensor1) == LOW && digitalRead(lineSensor2) == LOW && digitalRead(lineSensor3) == LOW) {
      stop();
      changeLEDColortoGreen();  
      delay(1000);       
      turn90Degrees();
      moveForward();
      delay(200);
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
  stop();       // Stop the bot after turning
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

void set_RGB(int r, int g, int b) {
  analogWrite(redpin, r);
  analogWrite(greenpin, g);
  analogWrite(bluepin, b);
}
