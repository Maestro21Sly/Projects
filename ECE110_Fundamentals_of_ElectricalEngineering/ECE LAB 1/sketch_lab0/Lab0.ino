int counter;
void setup() {
  Serial.begin(9600);
  Serial.println("Hello World!");

}

void loop() {
  counter += 1;
  Serial.println(counter);
}
