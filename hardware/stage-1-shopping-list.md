# Stage 1 — Shopping List
## Electronics Chain: ESP32 + PCA9685 + SG90 Servo

This is everything you need to build and test the Stage 1 electronics chain — an ESP32 microcontroller talking to a PCA9685 servo driver and sweeping a single SG90 servo.

**Total estimated cost: ~€20–26**

---

## Core Components

| # | Component | Qty | Est. Price | Where to Buy | Notes |
|---|-----------|-----|------------|--------------|-------|
| 1 | ESP32 Dev Board (ESP32-WROOM-32 or equivalent) | 1 | €6–8 | Tinytronics, Kiwi Electronics | The brain of the puppet. Any standard ESP32 dev board with a USB-C or Micro-USB connector works. Look for "ESP32 DevKit V1" or "ESP32-WROOM-32". |
| 2 | PCA9685 16-Channel I2C PWM/Servo Driver | 1 | €5–7 | Tinytronics, Kiwi Electronics, Reichelt | The board that controls up to 16 servos via I2C. Already has pull-up resistors built in — no extra resistors needed. |
| 3 | SG90 Micro Servo | 2 | €2–3 each | Tinytronics, Kiwi Electronics | You only need 1 for Stage 1, but buy 2. They are cheap and easy to accidentally damage by forcing them past their physical limit. |

---

## Non-Electronic Items

| # | Item | Qty | Est. Price | Where to Buy | Notes |
|---|------|-----|------------|--------------|-------|
| 4 | Breadboard (830-point, full-size) | 1 | €3–5 | Tinytronics, Kiwi Electronics | Used to connect components without soldering. Full-size (830-point) gives more space to work with. |
| 5 | Jumper Wire Kit (male-to-male + male-to-female) | 1 | €3–5 | Tinytronics, Kiwi Electronics | You'll need both types: male-to-male for breadboard connections, male-to-female for connecting ESP32 pins to the PCA9685 screw terminals. A mixed 120-piece kit covers everything. |
| 6 | USB-C Cable (for ESP32) | 1 | €2–4 | Any electronics shop | Used to power and program the ESP32. Check which connector your specific ESP32 board uses — some use Micro-USB. You probably already have one. |
| 7 | USB Power Bank (5V output, at least 1A) | 1 | Already owned | — | This powers the servo motor via the PCA9685 V+ terminal. A standard phone power bank works perfectly. Use a USB-A to bare-wire connection or a USB breakout to reach the screw terminal. Alternatively, a 5V USB wall adapter works too. |

---

## Optional but Recommended

### Resistor Assortment Kit

| # | Item | Est. Price | Where to Buy | Notes |
|---|------|------------|--------------|-------|
| 8 | 600-piece resistor assortment (mixed values) | €3–4 | Tinytronics, AliExpress EU warehouse | **Not needed for Stage 1** — the PCA9685 board already has I2C pull-up resistors built in, and the SG90 servo is a direct connection. However, as soon as you add an LED indicator (Stage 2+) or any other component, you will need resistors. Buying a 600-piece assortment now (covering 220Ω, 470Ω, 1kΩ, 4.7kΩ, 10kΩ and other common values) costs only ~€3–4 and avoids a parts-delivery delay mid-build later. |

---

## Recommended NL/EU Suppliers

| Supplier | Website | Notes |
|----------|---------|-------|
| **Tinytronics** | tinytronics.nl | Best local NL stock for ESP32, PCA9685, SG90, breadboards, wire kits. Fast shipping. |
| **Kiwi Electronics** | kiwi-electronics.com | Also NL-based. Good selection, slightly higher prices but excellent stock reliability. |
| **Reichelt** | reichelt.de | German supplier with huge stock. Slightly longer shipping to NL but often cheaper on passive components. |
| **Conrad** | conrad.nl | NL presence. Good for cables and accessories. |
| **AliExpress (EU warehouse)** | aliexpress.com | Cheap resistor assortments and backup components. Filter to "ships from EU" for faster delivery. |

---

## What Each Part Does

- **ESP32** — the microcontroller (tiny computer). Runs your firmware code, communicates with the PCA9685 over I2C (a two-wire communication protocol), and later will handle WiFi for wireless control.
- **PCA9685** — a dedicated servo driver board. The ESP32 sends simple commands to it over I2C, and the PCA9685 generates precise PWM signals (timed pulses) that servo motors respond to. It can drive up to 16 servos simultaneously, which is exactly how many you'll need for the full puppet.
- **SG90 servo** — a small hobby servo motor with a built-in position controller. You tell it what angle to go to (0°–180°) and it drives itself there. The full puppet will use 5 of these.
- **Breadboard** — a reusable prototyping board with spring-clip connectors. Push in wires and components to make circuits without any soldering.
- **Jumper wires** — short pre-made wires with connectors on each end for breadboard and pin connections.
- **Power bank** — provides 5V to power the servo motor. Servo motors draw more current than the ESP32's onboard pins can safely supply, so they always get their own power source.

---

## What to Search For

If you can't find the exact product name, these search terms work in most NL/EU shops:

- ESP32: `"ESP32 DevKit V1"` or `"ESP32 WROOM 32 development board"`
- PCA9685: `"PCA9685 servo driver"` or `"16 channel PWM I2C servo board"`
- SG90: `"SG90 micro servo 9g"` or `"SG90 servo motor"`
- Jumper wires: `"jumper wire kit 120 pcs"` or `"dupont wire assortment"`
