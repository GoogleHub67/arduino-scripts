/*
  58_nested_interrupt_vectors
  Demonstrates nesting interrupts by enabling global interrupt gates inside an active ISR,
  allowing critical real-time signals to intercept standard background execution blocks.
*/

#include <avr/interrupt.h>

const int LOW_PRIORITY_INTERRUPT_PIN = 2;  // INT0 Vector
const int CRITICAL_PRIORITY_INTERRUPT_PIN = 3; // INT1 Vector

void setup() {
  Serial.begin(9600);
  
  pinMode(LOW_PRIORITY_INTERRUPT_PIN, INPUT_PULLUP);
  pinMode(CRITICAL_PRIORITY_INTERRUPT_PIN, INPUT_PULLUP);

  // Attach standard hardware interrupt configurations mapping to level triggers
  attachInterrupt(digitalPinToInterrupt(LOW_PRIORITY_INTERRUPT_PIN), lowPriorityISR, LOW);
  attachInterrupt(digitalPinToInterrupt(CRITICAL_PRIORITY_INTERRUPT_PIN), criticalPriorityISR, FALLING);
  
  Serial.println("\n--- Nested Vector Execution Core Online ---");
}

void lowPriorityISR() {
  Serial.println("[ISR 0]: Low-priority task engaged. Simulating long operation loop...");

  // Re-enable global interrupts inside this routine to allow high-priority nesting.
  // Hardware gates block same-pin re-triggering automatically until exit.
  sei(); 

  // Simulate a heavy data calculation block that can now be interrupted
  for (volatile uint32_t i = 0; i < 200000; i++) {
    // Awaiting override trigger pulse on Pin 3
  }

  Serial.println("[ISR 0]: Low-priority task finished safely.");
}

void criticalPriorityISR() {
  // This vector will fire immediately even if the CPU is trapped deep inside lowPriorityISR!
  Serial.println(" --> [CRITICAL OVERRIDE]: High-priority vector nested successfully!");
}

void loop() {
  // System main loop application actions
}
