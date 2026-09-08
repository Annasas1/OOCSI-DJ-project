# OOCSI + ESP32 Project

Short description of what this project does goes here.

## Team
- Name 1
- Name 2

## What it does
Describe the core idea in 2-3 sentences: what does the ESP32 sense/control, and what does it send/receive over OOCSI?

## Hardware
- ESP32 (board model: ______)
- Sensors/actuators used:
  - 
  - 

## OOCSI Setup
- OOCSI server used: (e.g. oocsi.id.tue.nl or your own)
- Channel(s) used:
  - `channel-name` — description of what's sent here
- Message format (example):
  ```json
  {
    "key": "value"
  }
  ```

## Repo Structure
```
/esp32   -> ESP32 Arduino sketch
/docs    -> wiring diagrams, notes, photos
```

## Setup / How to Run
1. Open `esp32/esp32.ino` in the Arduino IDE (or PlatformIO).
2. Install required libraries (see below).
3. Fill in your WiFi credentials and OOCSI server address in the sketch.
4. Flash to the ESP32.
5. Confirm connection in the OOCSI monitor / your client app.

## Required Libraries
- OOCSI for Arduino/ESP32
- (add others as you go)

## Wiring
See `docs/wiring.md` (add a diagram or photo here).

## Status / To-do
- [ ] Basic OOCSI connection working
- [ ] Sensor/actuator integrated
- [ ] Message format finalized
- [ ] Tested end-to-end
