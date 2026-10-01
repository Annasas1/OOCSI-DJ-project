# OOCSI + ESP32 Project

For our module A and module B, we altered the Lampo code to make a browser reactive to magnet triggers. On the physical side, we have an ESP32 connected to reed sensors, we chose for 4 reed sensors. Module A counts the amount of sensors activated 0-4 and sends this number when a change is detected via its channel (in our case: ESP_Test_Team_1) as an integer. On the digital side we are subscribed to this channel, each number (0-4) corresponds to a state, aka color, the colors we chose are:
| Number | State |
|--------|-------|
| 0 | black |
| 1 | red |
| 2 | green |
| 3 | blue |
| 4 | disco |
Thus depending on the amount of reed sensors triggered by a magnet, the state will change and the color on the browser will also be altered. 
Note that only the *amount* of triggered sensors matters, not which specific sensors are triggered. Feel free to alter this if you feel it better suits your project! :) 

## Team 1
Anna Sas -
Jobst Knief -
Jana Kiš -
Benjamin Ackermans


## Hardware 
- ESP32
- Sensors/actuators used:
  - Reed switches
  - Magnets
- Wires
- Breadboard
- A screen that can be connected to a browser (IPad, PC..) 

## Digital component
Code: `lampoRGBwithSOUND.html` (the version without sound is `lampoRGB.html`)

- The page is built on the OOCSI Things / Lampo template and is registered as `LampoRGB` in teamspace `team-1`.
- It subscribes to the channel `ESP_Test_Team_1` and reads the integer `message.data.Message`. The number is translated to a state (see the table at the top) and stored in `current_state`.
- A p5.js canvas draws a full-screen colored rectangle in the color of the current state.
- Extras in `lampoRGBwithSOUND.html`:
  - **State 0 (black):** a pulsing dot with the text "place the vinyl piece...".
  - **Going up a state** (e.g. 1 to 2): a success "ding" sound and a burst of confetti.
  - **State 4 (disco):** the screen cycles through rainbow colors, rotating light beams, confetti cannons, a looping song and a gif.
- For testing without the ESP32, tapping/clicking the screen cycles through the states (`touchEnded()`). This changes the state locally and does not go through OOCSI.

Files that need to be in the same folder as the HTML file:
- `Pitbull, Ke$ha - Timber (featuring Ke$ha - Official Video).mp3` (disco music)
- `Success ding Sound Effect (download).mp3` (state-up sound)
- `pitbull.gif` (disco gif)
- `sw.js` and `manifest.json` (optional, for the installable web app / service worker)

## Physical component
Code: `esp32_esp32.ino`

- Each reed switch is connected between one ESP32 pin and GND. The pins are:

  | Reed switch | ESP32 pin |
  |-------------|-----------|
  | 1 | GPIO 13 |
  | 2 | GPIO 14 |
  | 3 | GPIO 15 |
  | 4 | GPIO 16 |

- The pins use `INPUT_PULLUP`, so a pin reads `LOW` when a magnet closes the switch and `HIGH` when it is open. No external resistors are needed.
- In `loop()` the ESP32 counts how many pins read `LOW` (0-4).
- If this count differs from the previous count, it sends the new count to OOCSI as an integer called `Message` on channel `ESP_Test_Team_1`.
- The ESP32 checks the sensors once per second (`delay(1000)`), so a change can take up to a second to show up in the browser.
- The ESP32 connects to the OOCSI server `oocsi.id.tue.nl` under the name `ESP32` using your WiFi credentials (`ssid` and `password` at the top of the sketch).

## Setup / How to Run
1. Connect the ESP32 to the ESP32 code
2. 

## Required Libraries (unfinished but visible in code)
**ESP32 (Arduino IDE)**
- ESP32 board support (Espressif "esp32" package in the Boards Manager). This also provides `WiFi.h`.
- OOCSI for Arduino/ESP32 (`OOCSI.h`), install via the Library Manager or from the OOCSI GitHub page.

**Browser (loaded automatically from the internet, nothing to install)**
- p5.js
- `oocsi-web.js` and `oocsi-things.min.js` (from `oocsi.id.tue.nl`)
- Pico CSS (from `oocsi.id.tue.nl`)
- canvas-confetti (from jsDelivr)


## A checklist to check before u run the code/ when u run into issues:
- [ ] Did you get all the necessary libraries?
- [ ] Are you running the physical code in Arduino IDE or did u alter it correctly to run in VSCode? (In VSCode with PlatformIO you need `#include <Arduino.h>` at the top, a `platformio.ini` for your ESP32 board, and the OOCSI library added under `lib_deps`.)
- [ ] Did you fill in your WiFi `ssid` and `password` in the sketch?
- [ ] Is the ESP32 on a WiFi network that can reach `oocsi.id.tue.nl`?
- [ ] Does the sketch compile? Check for leftover lines like a duplicate `void setup()` or an undefined `reedPin` (the pins are named `reedPin1` to `reedPin4`).
- [ ] Is the channel name exactly the same in both files (`ESP_Test_Team_1`, including capitals)?
- [ ] Is the message field named `Message` on both sides?
- [ ] Are the reed switches connected to the right pins and to GND?
- [ ] Does the Serial Monitor show the ESP32 starting up? (Baud rate 115200.)
- [ ] Is the HTML page served via a server/hosting and not just double-clicked open?
- [ ] Are the mp3 files and `pitbull.gif` in the same folder as the HTML file, with exactly the same file names?
- [ ] Did you click on the page once so the browser allows sound?
- [ ] Does the screen still react when you tap it? If yes, the page works and the problem is on the ESP32/OOCSI side.
- [ ] Still nothing? Open the browser console (F12), the page logs every message it receives from OOCSI.

## Data flow:
<img width="1668" height="2154" alt="OOCSI-8 1" src="https://github.com/user-attachments/assets/6a6be8c3-353b-470e-8d81-ca91ebe434bd" />
