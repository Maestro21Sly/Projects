void setup() {
  pinMode(13,OUTPUT);
  pinMode(10,OUTPUT);

}

void loop() {
  digitalWrite(13,HIGH);
  digitalWrite(10,HIGH);
  delay(500);
  digitalWrite(10,LOW);
  digitalWrite(10,LOW);

}
