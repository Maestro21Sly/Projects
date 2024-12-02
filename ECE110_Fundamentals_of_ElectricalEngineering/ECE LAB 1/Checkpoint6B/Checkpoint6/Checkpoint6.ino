// Define pins for built-in RGB LED
#define redpin 45
#define greenpin 46
#define bluepin 44

void setup() {
  // Set pin modes
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  // start with light off
  set_RGB(255, 255, 255);

  //start serial connection
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(500); 
}

void loop() {

  if (Serial2.available()){
    char incoming = Serial2.read();
    delay(100);
    if (incoming == 65 || incoming == 69 || incoming == 73 || incoming == 79 || incoming == 85){
      set_RGB(0, 255, 0);
      delay(1000);
    }
    else if (incoming == 89){
      set_RGB(255, 255, 0);
      delay(1000);
    }
    else{
      set_RGB(0,255, 255);
      delay(1000);
    }
    Serial.println(incoming);
    set_RGB(255, 255, 255);
  }
  delay(50);
}
  void set_RGB(int r, int g, int b){
  // Set RGB LED pins based on low=bright (default)
  analogWrite(redpin, r);
  analogWrite(greenpin, g);
  analogWrite(bluepin, b);

}

//void set_RGBi(int r, int g, int b){
  // Set RGB LED pins based on high=bright 
  //set_RGB(255-r, 255-g, 255-b);
//}