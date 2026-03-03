# Stage 1 Firmware — Servo Sweep
## Setup and Upload Guide

This guide walks you through setting up the Arduino IDE and uploading the servo sweep sketch to your ESP32.

**Skill level:** Beginner — every step is explained in full.

---

## What This Sketch Does

Once uploaded, the ESP32 will command the SG90 servo (on PCA9685 channel 0) to sweep smoothly back and forth from 0° to 180° and back again, continuously. The motion uses easing so it starts and stops gently rather than snapping between positions.

You can watch live angle updates in the Serial Monitor.

---

## Step 1 — Install Arduino IDE

1. Go to [arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Download **Arduino IDE 2** for your operating system (Windows, macOS, or Linux)
3. Run the installer and follow the prompts
4. Launch Arduino IDE

---

## Step 2 — Add ESP32 Board Support

Arduino IDE does not include ESP32 support by default. You need to add it.

1. Open Arduino IDE
2. Go to **File > Preferences** (Windows/Linux) or **Arduino IDE > Preferences** (macOS)
3. Find the field labelled **"Additional boards manager URLs"**
4. Paste this URL into that field:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
5. Click **OK**
6. Go to **Tools > Board > Boards Manager**
7. In the search box, type `esp32`
8. Find **"esp32 by Espressif Systems"** in the list
9. Click **Install** and wait for it to finish (this can take a minute or two)

---

## Step 3 — Install the Adafruit PWM Servo Driver Library

This library handles all the I2C communication with the PCA9685 board.

1. In Arduino IDE, go to **Tools > Manage Libraries** (or **Sketch > Include Library > Manage Libraries**)
2. In the search box, type `PCA9685`
3. Find **"Adafruit PWM Servo Driver Library" by Adafruit**
4. Click **Install**
5. If asked to install dependencies, click **Install All**

---

## Step 4 — Open the Sketch

1. In Arduino IDE, go to **File > Open**
2. Navigate to this file:
   ```
   firmware/stage-1-servo-sweep/stage-1-servo-sweep.ino
   ```
3. The sketch will open in a new window

---

## Step 5 — Select the Correct Board

1. Connect your ESP32 to your computer via USB
2. Go to **Tools > Board > esp32 > ESP32 Dev Module**
   - If you have a specific board name (e.g. "NodeMCU-32S", "DOIT ESP32 DevKit V1"), select that instead. "ESP32 Dev Module" works for most generic ESP32 boards.
3. Go to **Tools > Port**
4. Select the port that corresponds to your ESP32. It will appear as:
   - **macOS:** `/dev/cu.usbserial-XXXX` or `/dev/cu.SLAB_USBtoUART`
   - **Windows:** `COM3`, `COM4`, etc.
   - **Linux:** `/dev/ttyUSB0` or `/dev/ttyACM0`
   - If you see multiple ports and are unsure which is the ESP32, unplug it, check the list, plug it back in, and see which port appears.

---

## Step 6 — Upload the Sketch

1. Make sure the ESP32 is connected and the correct board and port are selected
2. Click the **Upload** button (the right-pointing arrow → in the toolbar)
3. Arduino IDE will compile the sketch and upload it to the ESP32
4. You will see output in the bottom panel — wait for **"Done uploading"**
5. If the upload fails with a timeout error, hold down the **BOOT** button on the ESP32 while clicking Upload, then release it once the upload starts. Some ESP32 boards require this.

---

## Step 7 — Open the Serial Monitor

1. Go to **Tools > Serial Monitor** (or press Ctrl+Shift+M / Cmd+Shift+M)
2. In the bottom-right of the Serial Monitor, set the baud rate to **9600**
3. Press the **Reset** button on the ESP32 (or unplug and replug the USB)
4. You should see output like this:

```
==============================================
  Robo-Actor — Stage 1 Servo Sweep
==============================================
Initialising PCA9685 over I2C...
PCA9685 ready.
Moving servo to start position (0°)...
Starting sweep. Watch the Serial Monitor for live angle updates.

Direction: -->  0 to 180 deg   |   Angle: 0 deg
Direction: -->  0 to 180 deg   |   Angle: 22 deg
Direction: -->  0 to 180 deg   |   Angle: 67 deg
Direction: -->  0 to 180 deg   |   Angle: 112 deg
Direction: -->  0 to 180 deg   |   Angle: 158 deg
Direction: -->  0 to 180 deg   |   Angle: 179 deg

--- Sweep complete. Now sweeping: <--  180 to 0 deg

Direction: <--  180 to 0 deg   |   Angle: 179 deg
...
```

---

## What to Expect

- The servo will pause briefly at 0°, then begin sweeping
- Each half-sweep (0°→180° or 180°→0°) takes **2 seconds**
- Motion is eased — it starts slowly, accelerates through the middle, then decelerates to a smooth stop
- The servo runs continuously — there is no end state
- The Serial Monitor updates every 250ms with the current direction and angle

---

## Troubleshooting

| Problem | Possible Cause | Fix |
|---------|---------------|-----|
| Upload fails / timeout | ESP32 not entering flash mode | Hold the BOOT button on the ESP32 while clicking Upload, release once you see "Connecting..." in the log |
| "Board not found" or no port in the menu | USB driver not installed | Install the CP2102 or CH340 driver for your ESP32 board. Search for the chip name printed on your board's USB adapter chip |
| Serial Monitor shows nothing | Wrong baud rate | Set Serial Monitor baud rate to exactly 9600 |
| "PCA9685 not found" in Serial Monitor | Wiring issue | Check SDA → GPIO 21 and SCL → GPIO 22. Check VCC → 3.3V and GND connections |
| Servo not moving | No servo power | Check that the power bank is connected to PCA9685 V+ and GND terminals. V+ and VCC are different pins. |
| Servo twitches but doesn't sweep smoothly | Shared ground missing | Make sure both the ESP32 GND and the power bank GND are connected to the PCA9685 GND |
| Servo reaches one end and makes a grinding noise | Servo at mechanical stop | The sweep range is 0°–180°. If your servo hits a stop before 180°, reduce `SERVO_MAX_TICKS` in the sketch by 20 ticks. Always run the test with the servo unattached to any mount. |
| Library not found / compile error | Library not installed | Go back to Step 3 and install "Adafruit PWM Servo Driver Library" |

---

## Adjusting the Sketch

You can customise the sweep behaviour by editing these values near the top of the sketch:

```cpp
// Change how long each sweep takes (in milliseconds)
const unsigned long SWEEP_DURATION_MS = 2000;   // 2000ms = 2 seconds

// Change the servo angle range
const uint16_t SERVO_MIN_TICKS = 102;   // 0° — increase to reduce minimum angle
const uint16_t SERVO_MAX_TICKS = 492;   // 180° — decrease to reduce maximum angle
```

After editing, click Upload again to push the updated sketch to the ESP32.
