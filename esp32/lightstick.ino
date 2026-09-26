#include <WiFi.h>
#include "OOCSI.h"
#include <FastLED.h> //install via library manager (FastLED by Daniel Garcia)

// WiFi
const char* ssid     = "";
const char* password = "";

// OOCSI
const char* OOCSIName   = "LightStick1";        
const char* hostserver  = "oocsi.id.tue.nl";
const char* inputChannel = "vinylTable"; // stick is listening to this channel

OOCSI oocsi = OOCSI();


#define LED_PIN     5 //GPIO Pin the led strips data line is wired too, js a value i put in for now, idk how it is on this board
#define NUM_LEDS    20 //not real count js test value
CRGB leds[NUM_LEDS]; // array so we can hold the color of every LED 

// state
// mirrors current_state in the p5 sketch: "red" | "green" | "blue" | "disco"
String current_state = "red"; //first state

// disco timing 
unsigned long lastDiscoStep = 0; //timestamp ms of last colro change
const unsigned long discoStepMs = 500;   // ~30 frames at 60fps
int discoPhase = 0; //which of the 3 colors we r currenly on cycles: 0->1->2->0

//  Handle incoming OOCSI message 
void processOOCSI() {
  //  table sends a raw magnet count (0-4) (i think this is better then string)
  if (oocsi.has("count")) {
    int count = oocsi.getInt("count");
    switch (count) {
      case 1: current_state = "red";   break;
      case 2: current_state = "green"; break;
      case 3: current_state = "blue";  break;
      case 4: current_state = "disco"; break;
      default: current_state = "off";  break;
    }
  }
}

//  Apply current_state to the LEDs 
void updateLightStick() {
  if (current_state == "red") {
    fill_solid(leds, NUM_LEDS, CRGB(255, 0, 0));
    FastLED.show();
  }
  else if (current_state == "green") {
    fill_solid(leds, NUM_LEDS, CRGB(0, 255, 0));
    FastLED.show();
  }
  else if (current_state == "blue") {
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 255));
    FastLED.show();
  }
  else if (current_state == "disco") {
    // non-blocking cycle R -> G -> B -> R, replaces p5's frameCount logic
    unsigned long now = millis(); //Different then delay() js, returns ms since ESP32 booted
    if (now - lastDiscoStep >= discoStepMs) { 
      lastDiscoStep = now;
      discoPhase = (discoPhase + 1) % 3;

      CRGB colors[3] = { CRGB(255,0,0), CRGB(0,255,0), CRGB(0,0,255) };
      fill_solid(leds, NUM_LEDS, colors[discoPhase]);
      FastLED.show();
    } //in a nutshell: every time 500ms have passes, step to the next color in the colors[] array and redraw, if less then 500ms has passed do nothing
  }
  else { // "off" / idle
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
  }
}

void setup() {
  Serial.begin(9600);
  delay(2000);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS); //I think since we use WorldSemi WS2812B
  updateLightStick(); // show initial state

  Serial.println("Connecting to OOCSI...");
  oocsi.connect(
    OOCSIName,
    hostserver,
    ssid,
    password,
    processOOCSI
  );
  Serial.println("oocsi.connect() returned");
}

void loop() {
  oocsi.check();       // keep OOCSI connection / message handling alive
  updateLightStick();  // re-applied every loop so disco mode keeps stepping
}
