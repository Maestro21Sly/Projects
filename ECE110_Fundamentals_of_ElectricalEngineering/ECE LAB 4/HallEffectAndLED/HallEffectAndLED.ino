const int Hall_In = 0;
const float VCC = 5.0;
const float Hall_sensitivity = 0.005; // 5 mV/G
#define RED 5
#define GRN 4

void setup() {
  Serial.begin(9600);
  pinMode(RED,OUTPUT);
  pinMode(GRN, OUTPUT); 
}

void loop() {
  digitalWrite(RED,LOW);
  digitalWrite(GRN,LOW);
  float Hall_Reading = analogRead(Hall_In);
  float Hall_Voltage = Hall_Reading * 5.0 / 1023.0;
  float Hall_Gauss = (Hall_Voltage - (VCC/2)) / 0.005;
  Serial.print("Analog reading = ");
  Serial.print(Hall_Reading);
  Serial.print(" ");
  Serial.print("Analog voltage = ");
  Serial.print(Hall_Voltage);
  Serial.print(" ");
  Serial.print("Flux density = ");
  Serial.println(Hall_Gauss);
  delay(100);
  if(Hall_Gauss >= 200){
    digitalWrite(RED,HIGH);
    digitalWrite(GRN,LOW);
    delay(1000);
  }
  if(Hall_Gauss <= -200){
    digitalWrite(RED,LOW);
    digitalWrite(GRN,HIGH);
    delay(1000);
  if(Hall_Gauss<= 200 || Hall_Gauss>=-200 ){
    digitalWrite(RED,LOW);
    digitalWrite(GRN,LOW);
  }
  }
}