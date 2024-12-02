// Set up Global variable
int NL = 4;

// Set up Global variables to track correct and total guesses
int correct = 0;
int total = 0;

void setup()
{
  // Start Serial Monitor
  Serial.begin(9600);
  // Initialize pins for lights and set low (off)
  for (int light = 2; light <= NL + 1; light++)
  {
    pinMode(light, OUTPUT);
    digitalWrite(light, LOW);
  }
}

void loop(){
  int n = random(0,16);
  Serial.println(n);
	send_to_lights(n);  
	delay(100);

  Serial.println("Guess an integer between 0 inclusive and 16: ");
  // Check whether there is information on the Serial Monitor
  while (Serial.available() == 0)
  {
  }
  // Once there is information on the Serial Monitor
  // grab it, convert the information to an integer, and store it
  int guess = Serial.parseInt(); 
  // get rid of extra carriage return
  char blah = Serial.read();
  // Increment the total number of times the game has been played
  total = total + 1;
  // Check to see if the answer is correct; keep track if it is
  if (guess==n)
  {
    Serial.print("Correct! ");
    correct = correct + 1;
  }
  else
  {
    Serial.print("Incorrect! ");
  }
  // Print the rest of the message to the user
  Serial.print("The answer was: ");
  Serial.println(n);  
  Serial.print("You have gotten ");
  Serial.print(correct);
  Serial.print(" out of ");
  Serial.print(total);
  Serial.println(" correct");
}

void send_to_lights(int val)
{
  for (int light = 2; light <= NL + 1; light++)
  {
    digitalWrite(light, bitRead(val, light - 2));
  }
}
