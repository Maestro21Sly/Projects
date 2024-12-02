// Set up Global variable
int NL = 2;

void setup()
{
  // Start Serial Monitor
  Serial.begin(9600);
  // Initialize pins for lights and set low (off)
  for (int light=2; light<=NL+1; light++){
    pinMode(light, OUTPUT);
    digitalWrite(light, LOW);
  }
}

void loop()
{
  for (int n=0; n<round(pow(2, NL)); n++)
  {
    Serial.println(n);
	send_to_lights(n);  
	delay(500);
  }
}

void send_to_lights(int val)
{
  for (int light=2; light<=NL+1; light++)
  {
    digitalWrite(light, bitRead(val, light-2));
  }
}