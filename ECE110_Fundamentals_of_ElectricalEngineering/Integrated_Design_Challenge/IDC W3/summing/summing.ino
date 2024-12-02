#include <SoftwareSerial.h>

#define TxPin 14
SoftwareSerial mySerial = SoftwareSerial(255, TxPin); // Define SoftwareSerial instance for LCD

const int maxBots = 5; // Maximum number of bots in the network
int botID = 1; // Unique identifier for this bot
int receivedData[maxBots] = {0}; // Array to store received data from each bot

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  // Check for incoming messages
  receiveMessages();

  // Your existing code here...

  // Example: Send sensor data
  int sensorValue = analogRead(A0);
  sendSensorData(sensorValue);

  // Calculate the sum of received data
  int sum = calculateSum();
  Serial.print("Sum of received data: ");
  Serial.println(sum);

  // Delay for stability (adjust as needed)
  delay(1000);
}

void receiveMessages() {
  if (Serial2.available()) {
    String message = Serial2.readStringUntil(']');
    
    // Parse the message based on the agreed-upon format
    int senderID, receiverID, messageType, data;
    if (parseMessage(message, senderID, receiverID, messageType, data)) {
      // Check if the message is intended for this bot
      if (receiverID == botID || receiverID == 0 /* Broadcast ID */) {
        // Store the received data in the array
        receivedData[senderID - 1] = data;
      }
    }
  }
}

bool parseMessage(String message, int &senderID, int &receiverID, int &messageType, int &data) {
  // Format: [SenderID|ReceiverID|MessageType|Data]
  int separatorIndex1 = message.indexOf('|');
  int separatorIndex2 = message.indexOf('|', separatorIndex1 + 1);
  int separatorIndex3 = message.indexOf('|', separatorIndex2 + 1);

  if (separatorIndex1 == -1 || separatorIndex2 == -1 || separatorIndex3 == -1) {
    // Invalid message format
    return false;
  }

  senderID = message.substring(1, separatorIndex1).toInt();
  receiverID = message.substring(separatorIndex1 + 1, separatorIndex2).toInt();
  messageType = message.substring(separatorIndex2 + 1, separatorIndex3).toInt();
  data = message.substring(separatorIndex3 + 1).toInt();

  return true;
}

void sendSensorData(int sensorValue) {
  // Example: Send sensor data to bot with ID 2
  int receiverID = 2;

  // Format the message
  String message = "[" + String(botID) + "|" + String(receiverID) + "|1|" + String(sensorValue) + "]";

  // Send the message
  Serial2.print(message);
}

int calculateSum() {
  // Calculate the sum of received data
  int sum = 0;
  for (int i = 0; i < maxBots; i++) {
    sum += receivedData[i];
  }
  return sum;
}
