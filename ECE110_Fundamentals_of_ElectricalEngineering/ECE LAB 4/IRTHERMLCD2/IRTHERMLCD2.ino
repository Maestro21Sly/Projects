#include <Wire.h>
#include <SparkFunMLX90614.h>
#include <SoftwareSerial.h>

#define TxPin 14
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);

IRTherm therm;

#define num 9
int durs[num]  = {211, 212, 212, 211, 212, 212, 212, 212, 212};
int octs[num]  = {216, 216, 216, 216, 216, 216, 216, 215, 216};
int notes[num] = {227, 227, 227, 223, 227, 230, 232, 230, 232};

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Wire.begin();

  if (therm.begin() == false) {
    Serial.println("Qwiic IR thermometer did not acknowledge! Freezing!");
    while(1);
  }
  Serial.println("Qwiic IR Thermometer did acknowledge.");
  
  therm.setUnit(TEMP_F);
  pinMode(LED_BUILTIN, OUTPUT);

  delay(100);
  mySerial.write(12); // clear
  delay(10);
  mySerial.write(22); // no cursor no blink
  delay(10);
  mySerial.write(17); // backlight
  delay(10);
  mySerial.print("Temperature: ");
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);

  if (therm.read()) {
    float temperature = therm.object();
    Serial.print("Object Temperature: " + String(temperature, 2) + "F");
      mySerial.write(128 + 64); // set cursor to line 2
      mySerial.print("Temp: " + String(temperature, 2) + "F");

    if (temperature < 50.0) {
      mySerial.write(13);
      for (long k = 0; k < num; k++) {
        mySerial.write(durs[k]);
        mySerial.write(octs[k]);
        mySerial.write(notes[k]);
        int len = 214 - durs[k];
        float del = 2000 / pow(2, len);
        delay(int(del * 1.1));
      }
    }
    Serial.println();
    mySerial.write(128); // set cursor to line 1
  }

  digitalWrite(LED_BUILTIN, LOW);
  delay(10000); // 10 seconds delay
}
