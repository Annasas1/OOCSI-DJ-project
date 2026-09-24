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
enum State {
    OFF, //0
    RED_SOLID,
    GREEN_SOLID,
    BLUE_SOLID,
    DISCO_MODE //4
    
};

//0 state
State current_state = OFF;

CRGB RED = CRGB(255, 0, 0);
CRGB GREEN = CRGB(0, 255, 0);
CRGB BLUE = CRGB(0, 0, 255);
CRGB BLACK = CRGB(0, 0, 0);
CRGB stateColor[5] = { BLACK, RED, GREEN, BLUE, BLACK }; 



// disco timing 
unsigned long lastDiscoStep = 0; //timestamp ms of last colro change
const unsigned long discoStepMs = 500;   // ~30 frames at 60fps
int discoPhase = 0; //which of the 3 colors we r currenly on cycles: 0->1->2->0
CRGB discoColors[3] = { RED, GREEN, BLUE };

//  Handle incoming OOCSI message 
void processOOCSI() {
  //  table sends a raw magnet count (0-4) (i think this is better then string)
  if (oocsi.has("count")) {
    int count = oocsi.getInt("count", 0);
    
    count = constrain(count, 0, 4);
    current_state = (State)count;
    
  }
}

void updateLightStickColor(CRGB Color) {
    fill_solid(leds, NUM_LEDS, Color);
    FastLED.show();
}

void updateLightStick() {
  if (current_state == DISCO_MODE) {
    unsigned long now = millis();
    if (now - lastDiscoStep >= discoStepMs) {
      lastDiscoStep = now;
      discoPhase = (discoPhase + 1) % 3;
      updateLightStickColor(discoColors[discoPhase]);
    }
  } else {
    updateLightStickColor(stateColor[current_state]);
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
