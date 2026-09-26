#include <WiFi.h>
#include "OOCSI.h"

// WiFi
const char* ssid = "";
const char* password = "";
const int reedPin1 = 13;
const int reedPin2 = 14;
const int reedPin3 = 15;
const int reedPin4 = 16;
int previousState = 0;

// OOCSI
const char* OOCSIName = "ESP32";
const char* hostserver = "oocsi.id.tue.nl";

OOCSI oocsi = OOCSI();

<<<<<<< HEAD
void setup() {
=======
void processOOCSI() {
}

void setup() { 
  pinMode(reedPin, INPUT_PULLUP);
  Serial.begin(9600);
  delay(2000);
>>>>>>> 233b1b4b18ee1b0b76661ea2c1408466670a3f0e

  pinMode(reedPin1, INPUT_PULLUP);
  pinMode(reedPin2, INPUT_PULLUP);
  pinMode(reedPin3, INPUT_PULLUP);
  pinMode(reedPin4, INPUT_PULLUP);

  Serial.begin(115200);
  delay(2000);

  oocsi.connect(
    "ESP32",
    "oocsi.id.tue.nl",
    ssid,
    password
  );
}

void loop() 
{
  int currentState = 0;

  if (digitalRead(reedPin1) == LOW) 
  {
    currentState += 1;
  } 

  if (digitalRead(reedPin2) == LOW) 
  {
    currentState += 1;
  } 

  if (digitalRead(reedPin3) == LOW) 
  {
    currentState += 1;
  } 

  if (digitalRead(reedPin4) == LOW) 
  {
    currentState += 1;
  } 

  if (currentState != previousState)
  {
    oocsi.newMessage("ESP_Test_Team_1");
    oocsi.addInt("Message", currentState);
    oocsi.sendMessage();
    previousState = currentState;
  }


  delay(1000);
}