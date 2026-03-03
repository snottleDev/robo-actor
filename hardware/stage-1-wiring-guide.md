# Stage 1 — Wiring Guide
## ESP32 + PCA9685 + SG90 Servo

This guide walks you through connecting all three components for the Stage 1 electronics test. Read the whole guide before touching any wires.

**The golden rule: keep servo power and ESP32 logic power separate.** The servo draws too much current to share the ESP32's power pin. Using separate supplies prevents voltage noise from crashing the microcontroller.

---

## What You're Building

```
[ Computer ]           [ Power Bank ]
     │                      │
     │ USB                  │ USB 5V
     │                      │
┌────▼─────────────┐   ┌────▼───────────────────────────────┐
│  ESP32 Dev Board │   │  PCA9685 Servo Driver              │
│                  │   │                                    │
│  3.3V ───────────┼───┼─► VCC  (logic power, 3.3V)        │
│  GND  ───────────┼───┼─► GND  (shared ground)            │
│  GPIO 21 (SDA) ──┼───┼─► SDA  (I2C data)                 │
│  GPIO 22 (SCL) ──┼───┼─► SCL  (I2C clock)                │
│                  │   │                                    │
└──────────────────┘   │   V+   ◄─── 5V from power bank    │
                        │   GND  ◄─── GND from power bank   │
                        │                                    │
                        │   CH 0 [PWM] [V+] [GND]           │
                        └──────────┬──────┬──────┬──────────┘
                                   │      │      │
                              ┌────▼──────▼──────▼────┐
                              │  SG90 Servo           │
                              │  ORG    RED    BRN    │
                              │ signal power  ground  │
                              └───────────────────────┘
```

---

## Step-by-Step Connections

### Step 1 — Connect ESP32 to PCA9685 (I2C + Logic Power)

These four wires connect the ESP32 to the PCA9685 for communication and logic power.

| ESP32 Pin Label | → | PCA9685 Pin Label | Wire Colour Suggestion |
|-----------------|---|-------------------|----------------------|
| `3.3V` | → | `VCC` | Red |
| `GND` | → | `GND` | Black |
| `GPIO 21` (SDA) | → | `SDA` | Blue or Green |
| `GPIO 22` (SCL) | → | `SCL` | Yellow |

**How to find the pins:**
- The ESP32 has labels printed next to each pin on the board. Look for `3.3V`, `GND`, `21`, and `22`.
- The PCA9685 has a 6-pin header at one end labelled `VCC`, `GND`, `OE`, `SCL`, `SDA`, `ADRR`. You only need `VCC`, `GND`, `SCL`, and `SDA`. Ignore `OE` and `ADRR`.

> ⚠️ **VCC is NOT the same as V+**. VCC powers the PCA9685's own logic chip from the ESP32's 3.3V rail. V+ (a separate screw terminal) powers the servos from your 5V power bank. Do not mix them up.

---

### Step 2 — Connect Power Bank to PCA9685 (Servo Power)

The servos need 5V at up to 1A of current — more than the ESP32's pins can provide. The power bank supplies this directly to the PCA9685.

| Power Bank | → | PCA9685 Terminal |
|------------|---|-----------------|
| `5V` (USB positive) | → | `V+` |
| `GND` (USB negative) | → | `GND` |

**How to connect the power bank:**
- The PCA9685 has screw terminals labelled `GND` and `V+` near the servo connector headers.
- Use a USB breakout board (a small board with a USB socket and exposed pads) to access the 5V and GND pins from a USB cable. These cost about €1 at Tinytronics.
- Alternatively, cut a USB-A to bare wire cable and connect the red wire (5V) to `V+` and the black wire (GND) to `GND`. Double-check polarity before powering on.

> ⚠️ **Always connect GND first, then V+.** Reversed polarity (+ and − swapped) can permanently damage the PCA9685.

---

### Step 3 — Connect SG90 Servo to PCA9685 Channel 0

The SG90 comes with a 3-wire connector (white/yellow/orange, red, brown/black). Plug it into the **first servo header on the PCA9685** (the end of the row labelled `0`).

| SG90 Wire Colour | Meaning | PCA9685 Channel 0 Pin |
|-----------------|---------|----------------------|
| Orange or White/Yellow | PWM signal | `PWM` (top pin on header) |
| Red | Power (5V) | `V+` (middle pin on header) |
| Brown or Black | Ground | `GND` (bottom pin on header) |

**How to find channel 0:** The 16 servo headers are numbered 0–15. Channel 0 is at the end of the row nearest the power screw terminals.

The three pins on each header are: signal (top), power (middle), ground (bottom) — matching the servo connector orientation. The connector only fits one way if the PCA9685 header has the white plastic shroud; if it doesn't, check the cable order carefully.

> ⚠️ **Remove the servo from any mount before testing.** If the servo hits a mechanical stop at full power, it will stall and can strip its plastic gears. Run Stage 1 with the servo unscrewed and free to rotate.

---

## Powering Up

1. Connect the ESP32 to your computer via USB — this powers the ESP32 and the PCA9685 logic.
2. Connect the power bank to the PCA9685 `V+` and `GND` terminals — this powers the servo.
3. Upload the firmware sketch (see firmware README).
4. Open the Arduino IDE Serial Monitor at **9600 baud** — you should see status messages from the ESP32.
5. The servo should begin sweeping back and forth within a second or two.

---

## Common Mistakes and How to Avoid Them

| Mistake | Symptom | Fix |
|---------|---------|-----|
| Connecting servo power to ESP32 3.3V instead of PCA9685 V+ | ESP32 resets or freezes when servo moves | Use the PCA9685 V+ terminal fed from the power bank |
| Swapping SDA and SCL | "PCA9685 not found" error in Serial Monitor | Check GPIO 21 = SDA, GPIO 22 = SCL |
| Reversed V+ / GND on power bank connection | PCA9685 gets warm or doesn't work | Disconnect immediately. Verify red = V+, black = GND |
| Plugging servo into wrong channel | Servo doesn't move | The sketch uses channel 0. Count from the end nearest the screw terminals |
| Missing shared ground between ESP32 and PCA9685 power sources | Servo moves erratically or not at all | ESP32 GND and power bank GND must be connected together |
| Servo mounted and hitting stop during test | Grinding noise, servo gets warm | Remove servo from any bracket before running the sweep test |
| VCC and V+ confused | Servo doesn't move or PCA9685 logic fails | VCC = 3.3V logic power from ESP32. V+ = 5V servo power from power bank |

---

## The Shared Ground Rule

The ESP32 and the power bank are two separate power sources. For them to communicate correctly, they must share a common ground reference. The PCA9685 already bridges this — its `GND` terminal is used for both the logic ground (from the ESP32) and the servo ground (from the power bank). As long as both GND connections go to the same PCA9685 `GND` pin or terminal, the circuit will work correctly.
