/*
  37_low_power_external_interrupt
  Shuts down the CPU clock tree into Sleep Mode Power Down, reducing current
  consumption to micro-amps, waking up instantly via an external hardware pin interrupt.
*/

#include <avr/sleep.h>
#include <avr/power.h>

const int WAKE_PIN = 2; // INT0 is tied to Digital Pin 2 on ATmega328P
const int LED_PIN = 13;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(WAKE_PIN, INPUT_PULLUP); // Keeps pin HIGH until button pulls it to GND
  
  digitalWrite(LED_PIN, HIGH);
  delay(2000); // Visual indicator: Chip is awake and running setup
}

void loop() {
  delay(500); 
  digitalWrite(LED_PIN, LOW); // Flash off before entering deep sleep

  goToSleep();

  // --- CPU pauses here during sleep execution ---
  // --- Execution resumes here immediately upon hardware wakeup trigger ---

  digitalWrite(LED_PIN, HIGH); // Flash on to signal wakeup success
  delay(1000);
}

void goToSleep() {
  // Set the target sleep configuration architecture type
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  
  sleep_enable(); // Enable the sleep circuit safely

  // Attach interrupt vector to fire explicitly on LOW level constraint (required for Power Down wakeup)
  attachInterrupt(digitalPinToInterrupt(WAKE_PIN), wakeUpISR, LOW);

  // Shut down internal Analog-to-Digital Converter peripheral network to save absolute max power
  byte old_ADCSRA = ADCSRA;
  ADCSRA = 0;  

  sleep_cpu(); // Put chip directly to sleep mode right here

  /* ------------------------------------------------------- */
  /* THE MICROCONTROLLER IS NOW SLEEPING AND CONSUMING MINIMAL POWER */
  /* ------------------------------------------------------- */

  // FIRST LINE EXECUTED AFTER WAKING UP:
  sleep_disable();         // Clear sleep bits safely
  detachInterrupt(digitalPinToInterrupt(WAKE_PIN)); // Stop interrupt from looping
  ADCSRA = old_ADCSRA;     // Re-enable standard ADC registers
}

void wakeUpISR() {
  // Keep this empty. It serves strictly as an execution bridge vector to wake up the clock tree.
}
