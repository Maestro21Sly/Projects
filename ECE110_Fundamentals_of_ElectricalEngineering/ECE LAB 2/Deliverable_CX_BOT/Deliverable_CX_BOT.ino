void setup() {
  // declaring P$ as input and P2 as output with LED off
  pinMode(4, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  //initializing serial monitor 
  Serial.begin(9600);
}

void loop() {
  // read the state of P4
  int voltageStatus = digitalRead(4);
  Serial.print("Current voltage is");
  Serial.println(voltageStatus);

/*for analog reading
  int voltageValue = analogRead(P4);
  float voltage = voltageValue *(5.0/1023.0);
  Serial.println(voltage);
  */
  if (voltageStatus == HIGH){
    digitalWrite(2, HIGH);
    delay(1000);
  }
  else if (voltageStatus == LOW){
    digitalWrite(2, LOW);
    delay(1000);
  }
}
