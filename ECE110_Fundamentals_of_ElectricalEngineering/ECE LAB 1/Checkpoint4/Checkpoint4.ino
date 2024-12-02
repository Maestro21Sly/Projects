const int buttonPin =2;
int buttonState = 0;
char uniqueCharacterToSend = 'P';


void setup() {
  pinMode(buttonPin, INPUT);
  Serial2.begin(9600);
  delay(500); 
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH){
    Serial2.write(uniqueCharacterToSend);
  }
  else{
  }
  delay(50);

}
