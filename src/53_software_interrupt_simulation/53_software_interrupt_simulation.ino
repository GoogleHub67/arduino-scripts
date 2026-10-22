/*
  53_software_interrupt_simulation
  Forces a manual software-triggered interrupt sequence by writing to internal Pin Change 
  Interrupt configuration registers, forcing background execution loop jumps on demand.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile bool softInterruptFired = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  noInterrupts();

  // 1. Enable Pin Change Interrupt Mask 0 (PCIE0 activates ports PB0 to PB5)
  PCICR |= (1 << PCIE0);

  // 2. Enable Pin Change Mask Register 0 to monitor specifically Pin Change 4 (PCINT4 / Pin 12)
  PCMSK0 |= (1 << PCINT4);

  // Set digital line 12 as an OUTPUT gate channel path explicitly
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);

  interrupts();
  Serial.println("\n--- Software Interrupt Subsystem Engaged ---");
}

// Interrupt Vector routine handles execution switches whenever Pin 12 flips state values
ISR(PCINT0_vect) {
  // Check if edge transition moved to HIGH logic level state
  if (digitalRead(12) == HIGH) {
    softInterruptFired = true;
  }
}

void triggerSoftwareTask() {
  // Force a software-driven bit switch directly to trip the PCINT0 hardware vector framework
  digitalWrite(12, HIGH); 
  
  // Clear trace state instantly to normalize the virtual bus environment
  digitalWrite(12, LOW);  
}

void loop() {
  delay(4000);
  Serial.println("Main kernel engine executing normal calculations loop...");
  
  Serial.println("[Software Action]: Forcing immediate background hardware task switch...");
  triggerSoftwareTask();

  if (softInterruptFired) {
    softInterruptFired = false;
    Serial.println(" -> [SUCCESS]: Background ISR Vector caught the soft trigger cleanly!\n");
  }
}
