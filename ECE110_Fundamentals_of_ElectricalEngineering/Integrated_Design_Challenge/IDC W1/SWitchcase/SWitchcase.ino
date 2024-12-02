//Pins for QTI connections on board
#define lineSensor1 47 
#define lineSensor2 51
#define lineSensor3 52
#include <Servo.h>
int value1;
int value2;
int value3;
int lowerthreshold = 250;
int higherthreshold = 350
Servo servoLeft;
Servo servoRight;
void setup() {
  Serial.begin(9600); //start the serial monitor so we can view the output
  servoLeft.attach(12);
  servoRight.attach(11);

}
void loop() {
  int qti1 = rcTime(lineSensor1);
  int qti2 = rcTime(lineSensor2);
  int qti3 = rcTime(lineSensor3);
  delay(50);
  //Serial.println(qti1);
  //Serial.println(qti2); 
  //Serial.println(qti3);
  if (qti1 < 250){
    value1 = 1;
  }
  else if (qti1> 350){
    value1 =0;
  }
  if (qti2 < 250){
    value2 = 1;
  }
  else if (qti2> 350){
    value2 =0;
  }
  if(qti3 < 250){
    value3 = 1;
  }
  else if(qti3> 350){
    value3 =0;
  }
  int finalValue = ((4*value1)+ (2*value2)+(value3));
  Serial.println(finalValue);
  switch (finalValue) {
    case 0:// Straightforward for line 90 for circle 
      //servoLeft.writeMicroseconds(1500);
      //servoRight.writeMicroseconds(1500);
      //delay(1000);
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1300);
      delay(25);
      //servoLeft.writeMicroseconds(1300);
      //servoRight.writeMicroseconds(1300);
      //delay(1000);

      break;
    case 7: //LLL stop
      //servoLeft.writeMicroseconds(1500);
      //servoRight.writeMicroseconds(1500);
      //delay(10);
      //break;
    case 6:// turn right
      servoLeft.writeMicroseconds(1530);
      servoRight.writeMicroseconds(1530);
      delay(25);
      break;
    case 5://onn line move forward 
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1300);
      delay(25);
      break;
    case 4://turn right
    servoLeft.writeMicroseconds(1530);
    servoRight.writeMicroseconds(1530);
    delay(25);
    break;

    case 3:// turn left 
    servoLeft.writeMicroseconds(1470);
    servoRight.writeMicroseconds(1470);
    delay(25);
    break;
    case 1://left
    servoLeft.writeMicroseconds(1470);
    servoRight.writeMicroseconds(1470);
    delay(25);
    break;
  }   
}

//Defines funtion 'rcTime' to read value from QTI sensors
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
//changing QTI readings to a single value 
//dark > 350
//light < 250


//switch cases 



