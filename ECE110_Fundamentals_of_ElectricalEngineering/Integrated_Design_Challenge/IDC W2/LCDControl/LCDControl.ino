#include <SoftwareSerial.h>

#define TxPin 14
SoftwareSerial mySerial = SoftwareSerial(255,TxPin); // Define SoftwareSerial instance for LCD

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  delay(100);
  mySerial.write(12); // clear
  delay(10);
  mySerial.write(22); // no cursor no blink
  delay(10);
  mySerial.write(17); // backlight
  delay(10);
  mySerial.print("Statement1");
}

void loop() {
  mySerial.write(128); // set cursor to line 1
  mySerial.print("Statement 2");
  delay(2000); // Wait for 2 seconds

  mySerial.write(128 + 64); // set cursor to line 2
  mySerial.print("Statement 3");
  mySerial.write(12); // clear // Clear the LCD screen

  delay(2000); // Wait for 2 seconds
}

