
int buttonState = 0;
char characterToSend = 65;





void setup() {
Serial.begin(9600); // initialize serial monitor
Serial2.begin(9600); // initialize Xbee Tx/Rx
delay(500);
pinMode(2, INPUT);


}
void loop() {
if(Serial.available()) { // Is serial monitor data available?
char outgoing = Serial.read(); // Read character
Serial2.print(outgoing); // Send to XBee
}
if(Serial2.available()) { // Is XBee data available?
char incoming = Serial2.read(); // Read character
Serial.println(incoming); // Send to serial monitor
}

buttonState =digitalRead(2)
if (butttonState == HIGH){
  digitalWrite(13,HIGH);
  Serial2.write(characterToSend);
}
else {
  digitalWrite(13,LOW);
}

}
delay(50);


}
