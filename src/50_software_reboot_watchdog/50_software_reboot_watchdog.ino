/*
  50_software_reboot_watchdog
  Implements a safe, hardware-level software reset mechanism using the internal 
  Watchdog configuration registers, bypassing dangerous memory jumps.
*/

#include <avr/wdt.h>

void performHardwareSoftwareReset() {
  Serial.flush(); // Ensure all trailing serial messages clear the TX pipeline first
  
  // Enable the watchdog timeout counter down to its absolute lowest window limit (15ms)
  wdt_enable(WDTO_15MS);
  
  // Trap the execution loop right here, preventing the code from servicing the watchdog.
  // The system will drop into a true hardware initialization reboot cleanly in 15 milliseconds.
  while (true) {
    // Intentionally left blank: waiting for reset cascade
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("\n=================================");
  Serial.println("System Core Boot Cycle Initialized.");
  Serial.println("=================================");
  
  // Turn off the watchdog system immediately upon boot up to prevent infinite reset loops
  wdt_disable();
}

void loop() {
  for (int i = 5; i > 0; i--) {
    Serial.print("System scheduled to execute a full hardware-level reboot in ");
    Serial.print(i);
    Serial.println(" seconds...");
    delay(1000);
  }

  Serial.println("[Command Received]: Executing watchdog reset sequence NOW.");
  performHardwareSoftwareReset();
  
  // This line will never execute as the hardware restarts completely above
}
