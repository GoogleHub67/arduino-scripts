/*
  38_watchdog_timer_wakeup
  Configures the internal standalone Watchdog Timer system as a periodic low-power 
  interrupt driver to create ultra-efficient long-term cyclic sensor loggers.
*/

#include <avr/wdt.h>
#include <avr/sleep.h>

const int LED_PIN = 13;
volatile bool wdtFired = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  // Configure Watchdog system settings safely
  MCUSR &= ~(1 << WDRF); // Clear any existing Watchdog reset flags
  
  // To modify configuration registers WDTCER, write a logical 1 to WDCE and WDE sequence
  WDTCSR |= (1 << WDCE) | (1 << WDE);

  // Set Watchdog configuration parameters: 
  // Interrupt mode enabled (not reset mode), timeout scale window set to ~8.0 seconds
  WDTCSR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0); 
}

void loop() {
  if (wdtFired) {
    wdtFired = false;
    
    // Perform rapid task (e.g., pulse sensor read profile)
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
  }

  // Sleep deeply until the 8-second watchdog countdown flag trips the wake interrupt
  enterCyclicSleep();
}

void enterCyclicSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  
  sleep_cpu(); // Sleep here
  
  sleep_disable(); // Wakeup vector resume point
}

// Watchdog Timer Interrupt Service Routine vector handler
ISR(WDT_vect) {
  wdtFired = true; // Flag the main loop state engine that timing window hit limit
}
