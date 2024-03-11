#include <SoftwareSerial.h>

#define A9G_TX_PIN 2 // Пін tx
#define A9G_RX_PIN 3 // Пін rx
#define BUTTON_PIN 4 // кнопка

SoftwareSerial A9GSerial(A9G_TX_PIN, A9G_RX_PIN);

void setup() {
  Serial.begin(9600);
  A9GSerial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    sendHelpRequest();
  }
}

void sendHelpRequest() {
  String gpsData = getGPSData();
  // повідомлення
  String message = "Допоможіть! Потрібна допомога. Координати: " + gpsData;
  
  A9GSerial.println(message);
  
  Serial.println("Відправлено повідомлення: " + message);
}

String getGPSData() {
  A9GSerial.println("AT+CGNSINF"); 
  
  delay(1000); 
  
  String gpsData = "";
  while (A9GSerial.available()) {
    gpsData += char(A9GSerial.read());
  }
  
  return gpsData;
}
