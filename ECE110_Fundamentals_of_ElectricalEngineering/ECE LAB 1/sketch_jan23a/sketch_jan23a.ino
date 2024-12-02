// Define pins for built-in RGB LED
#define redpin 45
#define greenpin 46
#define bluepin 44

void setup() {
Serial.begin(9600); // initialize serial monitor
Serial2.begin(9600); // initialize Xbee Tx/Rx
delay(500);
pinMode(2, INPUT);
  // Set pin modes
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  // start with light off
  set_RGB(255, 255, 255);
}

void loop() {
  if(Serial.available()) { // Is serial monitor data available?
    char outgoing = Serial.read(); // Read character
    Serial2.print(outgoing); // Send to XBee
  }
  if(Serial2.available()) { // Is XBee data available?
    char incoming = Serial2.read();
  if (incoming == A || incoming == E || incoming == I || incoming == O || incoming == U|| incoming == Y ){
  Serial.println(incoming); 
  Set_RGB(0, 255, 255);
  }
  else{ 
    set_RGB(255, 255, 255);
  }

}

void set_RGB(int r, int g, int b){
  // Set RGB LED pins based on low=bright (default)
  analogWrite(redpin, r);
  analogWrite(greenpin, g);
  analogWrite(bluepin, b);
}