#include <WiFi.h>
#include "OOCSI.h"

// WiFi
const char* ssid = "";
const char* password = "";
const int reedPin = 14;

// OOCSI
const char* OOCSIName = "ESP32";
const char* hostserver = "oocsi.id.tue.nl";

OOCSI oocsi = OOCSI();

void processOOCSI() {
}

void setup() { 
  pinMode(reedPin, INPUT_PULLUP);
  Serial.begin(9600);
  delay(2000);

  Serial.println("Connecting to OOCSI...");

  oocsi.connect(
    "ESP32",
    "oocsi.id.tue.nl",
    ssid,
    password,
    processOOCSI
  );

  Serial.println("oocsi.connect() returned");
}

void loop() {
  if (digitalRead(reedPin) == LOW) 
  {
    Serial.println("Magnet Found");
    oocsi.newMessage("ESP-test");
    oocsi.addString("Message", "Magnet found");
    oocsi.sendMessage();
  } 
  else 
  {
    Serial.println("Magnet Lost");
  }

  delay(1000);
}