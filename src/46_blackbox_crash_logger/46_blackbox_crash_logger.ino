/*
  46_blackbox_crash_logger
  Uses uninitialized RAM variables and the Watchdog reset architecture to 
  log crash codes that survive full system hardware reboots.
*/

#include <avr/wdt.h>

// The 'section(".noinit")' attribute prevents the C-runtime initialization script
// from clearing this specific variable to 0 during cold or warm system boot setups.
__attribute__((section(".noinit"))) uint8_t crashReasonCode;
__attribute__((section(".noinit"))) uint16_t crashLocationLine;

void triggerSoftwareCrash(uint16_t lineReference) {
  crashReasonCode = 0xEF; // Code token for user forced system exception hang
  crashLocationLine = lineReference;
  
  // Force a rapid hardware watchdog reset cascade loop
  wdt_enable(WDTO_15MS);
  while(true); // Wait for the hammer to drop
}

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("\n--- BlackBox Kernel Diagnostic System Online ---");

  // Read the hardware Reset MCUSR status flags
  if ((MCUSR & (1 << WDRF)) && crashReasonCode == 0xEF) {
    Serial.println("\n[CRITICAL]: SYSTEM WOKE FROM UNEXPECTED CRASH EXCEPTION!");
    Serial.print("[DIAG]: Crash Token ID: 0x"); Serial.println(crashReasonCode, HEX);
    Serial.print("[DIAG]: Source Code Line Crash Reference: "); Serial.println(crashLocationLine);
    
    // Clear tokens after extracting logs to prevent fake cyclic flag reads
    crashReasonCode = 0x00;
    crashLocationLine = 0;
  } else {
    Serial.println("System initialized normally with clean startup logs.");
  }

  MCUSR = 0; // Clear hardware reset tracking status flags
  wdt_disable(); // Keep watchdog disarmed during standard runtime operation
}

void loop() {
  delay(3000);
  Serial.println("Simulating structural thread operations... Everything normal.");
  delay(3000);
  
  Serial.println("Encountering fatal logic trap! Saving crash dump metrics...");
  triggerSoftwareCrash(__LINE__); // Pass execution line trace token
}
