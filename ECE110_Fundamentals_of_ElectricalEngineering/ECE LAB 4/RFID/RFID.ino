// Based on https://www.instructables.com/Reading-RFID-Tags-with-an-Arduino/
// Expanded by Michael R. Gustafson II to include hex / bin / dec values and 
// replace unprintable characters

char val = 0; // variable to store the data from the serial port

void setup() {
  Serial.begin(9600); // connect to the serial port for the monitor
  Serial1.begin(9600); // connect to the serial port for the RFID reader
  Serial.println("");
  Serial.println("Char\tHex\tDec\tBin");
}

void loop () {
  if(Serial1.available() > 0) {
  val = Serial1.read();

    // Handle unprintable / line skipping characters
    switch(val) {
      case 0x2: Serial.print("STX"); break; // start of transmission
      case 0x3: Serial.print("ETX"); break; // end of transmission
      case 0xA: Serial.print("LF");  break; // line feed
      case 0xD: Serial.print("CR");  break; // carriage return
      default:  Serial.print(val);   break; // actual character
    }
  Serial.print("\t");
    
  Serial.print(val, HEX); Serial.print("\t");
  Serial.print(val, DEC); Serial.print("\t");
  Serial.print(val, BIN); Serial.println("");
  }
}
