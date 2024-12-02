#include <SoftwareSerial.h>

#define TxPin 14

SoftwareSerial mySerial = SoftwareSerial(255, TxPin);

#define num 21

int durs[num]  = {214, 213, 212, 214, 212, 212, 212, 212, 212, 214, 212,
                  214, 213, 212, 214, 212, 212, 212, 212, 212, 214};
int octs[num]  = {215, 215, 215, 215, 215, 215, 215, 215, 216, 215, 215,
                  215, 215, 215, 215, 216, 216, 216, 216, 216, 215};
int notes[num] = {227, 230, 230, 223, 225, 227, 228, 230, 220, 225, 232,
                  227, 229, 229, 230, 220, 222, 222, 220, 220, 230};

void setup() {
  mySerial.begin(9600);
  delay(100);
  mySerial.write(12); // clear
  delay(10);
  mySerial.write(22); // no cursor no blink
  delay(10);
  mySerial.write(17); // backlight
  delay(10);
  mySerial.print("Super Mario");
  mySerial.write(13);
  mySerial.print("Brothers!");
  play_song();

}

void loop() {

}

void play_song() {
 for(long k=0; k<num; k++){
    
    mySerial.write(durs[k]); mySerial.write(octs[k]); mySerial.write(notes[k]);
    int len = 214 - durs[k];
    float del = 2000 / pow(2, len);
    delay(int(del*1.1));
  }
}