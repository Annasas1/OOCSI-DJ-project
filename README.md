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

### 1. Physical side
1. Wire the 4 reed switches: one leg of each switch to its GPIO pin (13, 14, 15, 16), the other leg to GND.
2. Open `esp32_esp32.ino` in the Arduino IDE.
3. Fill in your WiFi name and password in `ssid` and `password`. (Also ensure to add your own channel name + team names etc. to all documents, so we dont get conflicting data flow.)
4. Select your ESP32 board and the right port (Tools menu).
5. Upload the sketch.
6. Open the Serial Monitor (115200 baud) to check that the ESP32 starts and connects.

### 2. Digital side
1. Put `lampoRGBwithSOUND.html` together with the sound files and gif in one folder (see above).
2. Open the page in a browser. It must be served the same way as the other Lampo pages (e.g. hosted, or via a local server such as the VS Code Live Server extension), because the service worker does not work when opening a file directly.
3. To be able to test page freely (disconnected from physical side), you can also use mouse presses to change state, you can now test it by clicking on the page. (If you want this removed delete the touchEnded function) 
4. Make sure the browser has internet access, since the libraries and the OOCSI connection are loaded online.

### 3. Try it
1. Hold a magnet next to a reed switch: the screen should change from black to red.
2. Add more magnets: 2 = green, 3 = blue, 4 = disco.
3. Remove magnets to go back down. Going down changes the color but does not play the ding.


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
- [ ] Is the HTML page served via a server/hosting and not just double-clicked open?
- [ ] Are the mp3 files and `x.gif`  in the same folder as the HTML file, with exactly the same file names (for correct path name)?
- [ ] Does the screen still react when you tap it? If yes, the page works and the problem is on the ESP32/OOCSI side.

## Data flow:
<img width="1668" height="2154" alt="OOCSI-8 1" src="https://github.com/user-attachments/assets/6a6be8c3-353b-470e-8d81-ca91ebe434bd" />
