// OOCSI + ESP32 starter sketch


#include <WiFi.h>
// #include <OOCSI.h>  // TODO: include  OOCSI library once installed

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

//  OOCSI settings 
//const char* oocsiServer = "OOCSI_SERVER";  
//const char* oocsiName = "CLIENT_NAME";     
//const char* oocsiChannel = "CHANNEL_NAME";  

void setup() {
  Serial.begin(115200);

  // TODO: connect to WiFi
  // TODO: connect to OOCSI
  // TODO: subscribe to channel(s) if receiving data
}

void loop() {
  // TODO: read sensor / check input
  // TODO: send data over OOCSI
  // TODO: handle incoming OOCSI messages HELLOOOOOOOOO
}
