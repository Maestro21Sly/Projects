// Robotics with the BOE Shield - ForwardTenSeconds
// Make the BOE Shield-Bot roll forward for 6ft seconds, then stop.

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
 
void setup()                                 // Built-in initialization block
{
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  servoLeft.attach(12);
  servoRight.attach(11);
  // Full speed forward
  servoLeft.writeMicroseconds(1400);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1400);        // Right wheel clockwise
  delay(720);  

  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1700);        // Right wheel clockwise
  delay(660);                             // ...for 10 seconds
 
  servoLeft.writeMicroseconds(1300);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1630);        // Right wheel clockwise
  delay(12000);  
  servoLeft.detach();                        // Stop sending servo signals
  servoRight.detach();
}  
 
void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
}