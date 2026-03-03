// ============================================================
//  Robo-Actor — Stage 1 Servo Sweep Test
// ============================================================
//
//  What this sketch does:
//    Smoothly sweeps a single SG90 servo back and forth from
//    0° to 180° and back again, on a continuous loop.
//    Motion is eased (gradual start and stop) so it looks
//    natural rather than mechanical.
//
//  Hardware required:
//    - ESP32 dev board (ESP32-WROOM-32 or similar)
//    - PCA9685 16-channel PWM/servo driver board
//    - SG90 micro servo connected to PCA9685 channel 0
//    - Power bank (5V) powering servo via PCA9685 V+/GND terminals
//    - ESP32 powered via its own USB connection to your computer
//
//  Wiring summary:
//    ESP32 GPIO 21 (SDA)  →  PCA9685 SDA
//    ESP32 GPIO 22 (SCL)  →  PCA9685 SCL
//    ESP32 3.3V           →  PCA9685 VCC   (logic power only)
//    ESP32 GND            →  PCA9685 GND
//    Power bank 5V        →  PCA9685 V+    (servo power)
//    Power bank GND       →  PCA9685 GND
//    SG90 servo           →  PCA9685 channel 0 header
//
//  Library required:
//    Adafruit PWM Servo Driver Library
//    (install via Arduino IDE > Tools > Manage Libraries)
//
//  Serial Monitor:
//    Set baud rate to 9600 to read status messages.
//
// ============================================================

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


// ── PCA9685 Setup ────────────────────────────────────────────
//
// Create a PCA9685 driver object using the default I2C address (0x40).
// This address is set by hardware jumpers on the board. If you have
// not soldered any address jumpers, the address is 0x40.
//
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);


// ── Servo Channel ─────────────────────────────────────────────
//
// The SG90 servo is plugged into channel 0 on the PCA9685 board.
// Channels are numbered 0 to 15, starting from the end of the board
// nearest the power screw terminals.
//
const uint8_t SERVO_CHANNEL = 0;


// ── Servo Pulse Width Range ───────────────────────────────────
//
// Servo motors respond to PWM pulses. The width (duration) of the
// pulse tells the servo what angle to hold.
//
// For the SG90:
//   500 microseconds  →  0° (fully counterclockwise)
//   2400 microseconds →  180° (fully clockwise)
//
// The PCA9685 uses 12-bit resolution at 50 Hz, which means it divides
// each 20ms cycle into 4096 steps (called "ticks").
// Each tick = 20,000µs ÷ 4096 ≈ 4.88µs.
//
// To find the tick values for 0° and 180°:
//   500µs  ÷ 4.88µs = ~102 ticks  →  SERVO_MIN_TICKS
//   2400µs ÷ 4.88µs = ~492 ticks  →  SERVO_MAX_TICKS
//
// If your servo does not quite reach its full range, try adjusting
// these values by ±10 ticks.
//
const uint16_t SERVO_MIN_TICKS = 102;   // pulse width at 0°
const uint16_t SERVO_MAX_TICKS = 492;   // pulse width at 180°


// ── Sweep Timing ──────────────────────────────────────────────
//
// How long each half-sweep takes, in milliseconds.
// 2000ms means 0° → 180° takes 2 seconds.
// Then 180° → 0° also takes 2 seconds.
// The full back-and-forth cycle takes 4 seconds total.
//
// Increase this value for a slower, more deliberate motion.
// Decrease it for a faster, more energetic motion.
//
const unsigned long SWEEP_DURATION_MS = 2000;


// ── State Variables ───────────────────────────────────────────
//
// These variables track what the servo is currently doing between
// loop() calls. They persist across each loop() iteration.
//
unsigned long sweepStartTime = 0;   // milliseconds when current sweep began
bool          movingForward  = true; // true = sweeping 0°→180°, false = 180°→0°


// ============================================================
//  HELPER FUNCTIONS
// ============================================================


// ── easeInOut() ───────────────────────────────────────────────
//
// Converts a linear progress value (0.0 to 1.0) into a smoothed
// version that starts slowly, speeds up through the middle, then
// slows down to a smooth stop. This is called "ease-in-out".
//
// Without easing: the servo jumps to speed instantly and stops abruptly.
// With easing: motion looks natural and puppetry-like.
//
// The formula uses a cosine curve:
//   0.5 - 0.5 × cos(progress × π)
// At progress = 0.0, result = 0.0 (starting point, speed = 0)
// At progress = 0.5, result = 0.5 (middle, maximum speed)
// At progress = 1.0, result = 1.0 (ending point, speed = 0)
//
float easeInOut(float progress) {
    return 0.5f - 0.5f * cos(progress * PI);
}


// ── angleToPwmTicks() ─────────────────────────────────────────
//
// Converts a servo angle in degrees (0.0 to 180.0) into the
// corresponding PCA9685 tick value.
//
// The tick value determines the PWM pulse width sent to the servo,
// which in turn determines the angle the servo moves to.
//
// The mapping is linear between SERVO_MIN_TICKS (at 0°) and
// SERVO_MAX_TICKS (at 180°).
//
uint16_t angleToPwmTicks(float angleDegrees) {
    // Calculate what fraction of the full range this angle represents.
    float fraction = angleDegrees / 180.0f;

    // Interpolate between the minimum and maximum tick values.
    return (uint16_t)(SERVO_MIN_TICKS + fraction * (float)(SERVO_MAX_TICKS - SERVO_MIN_TICKS));
}


// ── setServoAngle() ───────────────────────────────────────────
//
// Moves the servo on the given PCA9685 channel to the specified angle.
//
// Parameters:
//   channel      - PCA9685 channel number (0–15)
//   angleDegrees - target angle in degrees (0.0 to 180.0)
//
// setPWM(channel, on_tick, off_tick):
//   on_tick  = 0       → pulse starts at the beginning of each 20ms cycle
//   off_tick = ticks   → pulse ends after 'ticks' steps into the cycle
// This produces a pulse of width: ticks × 4.88µs
//
void setServoAngle(uint8_t channel, float angleDegrees) {
    uint16_t ticks = angleToPwmTicks(angleDegrees);
    pwm.setPWM(channel, 0, ticks);
}


// ============================================================
//  SETUP — Runs once when the ESP32 starts
// ============================================================

void setup() {
    // Start the Serial connection so we can print status messages.
    // Open the Serial Monitor in Arduino IDE (Tools > Serial Monitor)
    // and set the baud rate to 9600.
    Serial.begin(9600);
    Serial.println("==============================================");
    Serial.println("  Robo-Actor — Stage 1 Servo Sweep");
    Serial.println("==============================================");
    Serial.println("Initialising PCA9685 over I2C...");

    // Start the I2C bus.
    // On a standard ESP32, Wire uses GPIO 21 for SDA and GPIO 22 for SCL
    // automatically. No arguments needed here.
    Wire.begin();

    // Initialise the PCA9685. This sends the startup command over I2C
    // to wake the board from sleep mode.
    pwm.begin();

    // Set the internal oscillator frequency for accurate PWM timing.
    // 25,000,000 Hz (25 MHz) is the calibrated value for Adafruit PCA9685
    // breakout boards. This value corrects for slight timing drift.
    pwm.setOscillatorFrequency(25000000);

    // Set the PWM output frequency to 50 Hz.
    // 50 Hz is the standard signal frequency for hobby servo motors:
    // one 20ms cycle per second, with a variable-width pulse inside it.
    pwm.setPWMFreq(50);

    // Small pause to let the PCA9685 settle after configuration.
    delay(100);

    Serial.println("PCA9685 ready.");
    Serial.println("Moving servo to start position (0°)...");

    // Move the servo to 0° before starting the sweep.
    // This ensures the sweep always begins from a known position.
    setServoAngle(SERVO_CHANNEL, 0.0f);

    // Wait for the servo to physically reach 0° before starting the loop.
    delay(500);

    Serial.println("Starting sweep. Watch the Serial Monitor for live angle updates.");
    Serial.println();

    // Record the time the first sweep begins.
    sweepStartTime = millis();
}


// ============================================================
//  LOOP — Runs continuously after setup()
// ============================================================

void loop() {

    // ── Calculate How Far Through the Current Sweep We Are ────
    //
    // millis() returns the number of milliseconds since the ESP32 started.
    // Subtracting sweepStartTime gives how long this particular sweep has
    // been running.
    //
    unsigned long elapsedTime = millis() - sweepStartTime;

    // Convert elapsed time to a 0.0–1.0 progress value.
    // 0.0 = sweep just started.
    // 1.0 = sweep is complete.
    // Cap at 1.0 to avoid overshooting past the end position.
    //
    float progress = (float)elapsedTime / (float)SWEEP_DURATION_MS;
    if (progress > 1.0f) progress = 1.0f;


    // ── Apply Easing ──────────────────────────────────────────
    //
    // Raw progress is linear — the servo would move at constant speed.
    // Eased progress accelerates from a standstill, peaks in the middle,
    // then decelerates smoothly to a stop. This looks much more natural.
    //
    float easedProgress = easeInOut(progress);


    // ── Calculate the Target Angle ────────────────────────────
    //
    // Depending on direction, map the eased progress to an angle:
    //   Forward: 0° at progress 0.0 → 180° at progress 1.0
    //   Reverse: 180° at progress 0.0 → 0° at progress 1.0
    //
    float targetAngle;
    if (movingForward) {
        targetAngle = easedProgress * 180.0f;
    } else {
        targetAngle = (1.0f - easedProgress) * 180.0f;
    }


    // ── Move the Servo ────────────────────────────────────────
    //
    // Send the target angle to the PCA9685, which converts it to a
    // PWM pulse and drives the servo to that position.
    //
    setServoAngle(SERVO_CHANNEL, targetAngle);


    // ── Print Live Status to Serial Monitor ──────────────────
    //
    // Print the current direction and angle every 250ms.
    // Using a static variable and millis() keeps the printing
    // non-blocking — it doesn't slow down the servo updates.
    //
    static unsigned long lastPrintTime = 0;
    if (millis() - lastPrintTime >= 250) {
        lastPrintTime = millis();
        Serial.print("Direction: ");
        Serial.print(movingForward ? "-->  0 to 180 deg" : "<--  180 to 0 deg");
        Serial.print("   |   Angle: ");
        Serial.print((int)targetAngle);
        Serial.println(" deg");
    }


    // ── Check If the Current Sweep Is Complete ────────────────
    //
    // When elapsed time exceeds SWEEP_DURATION_MS, the servo has
    // reached its destination. Reverse direction and restart timing.
    //
    if (elapsedTime >= SWEEP_DURATION_MS) {
        movingForward = !movingForward;
        sweepStartTime = millis();

        Serial.println();
        Serial.print("--- Sweep complete. Now sweeping: ");
        Serial.println(movingForward ? "-->  0 to 180 deg" : "<--  180 to 0 deg");
        Serial.println();
    }


    // ── Short Pause Between Loop Iterations ──────────────────
    //
    // Wait 10 milliseconds before the next loop iteration.
    // This gives the servo roughly 100 position updates per second,
    // which is smooth enough for visual motion.
    //
    // This is NOT a long blocking delay — the millis() timing above
    // handles the overall sweep duration independently. Changing this
    // value does not change how long the sweep takes.
    //
    delay(10);
}
