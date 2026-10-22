/*
  57_atomic_operations
  Demonstrates the application of atomic execution blocks to protect multi-byte variables 
  from thread corruption caused by asynchronous background interrupts.
*/

#include <util/atomic.h>

// A 32-bit variable requires 4 distinct CPU execution steps to read on an 8-bit architecture.
volatile uint32_t highFrequencyCounter = 0; 

void setup() {
  Serial.begin(9600);
  while (!Serial);

  noInterrupts();
  // Configure a fast hardware clock timer interrupt to simulate rapid background shifts
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A  = 50; // Trigger interrupt frequently
  TCCR2A |= (1 << WGM21); // Turn on CTC mode
  TCCR2B |= (1 << CS22);  // Scale prescaler
  TIMSK2 |= (1 << OCIE2A); // Enable interrupt vector mask
  interrupts();
  
  Serial.println("\n--- Atomic Thread Lock Engine Online ---");
}

// Background task updates the multi-byte register continuously
ISR(TIMER2_COMPA_vect) {
  highFrequencyCounter++;
}

void loop() {
  uint32_t dynamicLocalCopy = 0;

  // ATOMIC_RESTORESTATE completely isolates the data block by disabling interrupts 
  // and restoring the global interrupt bit immediately afterward.
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    dynamicLocalCopy = highFrequencyCounter; 
  }

  // It is now perfectly safe to process or print the 32-bit value without corruption
  Serial.print("Protected Data Extraction Token: ");
  Serial.println(dynamicLocalCopy);
  
  delay(1000);
}
