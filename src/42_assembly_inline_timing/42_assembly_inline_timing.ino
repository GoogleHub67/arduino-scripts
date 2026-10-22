/*
  42_assembly_inline_timing
  Demonstrates the injection of inline assembly instructions directly into the
  C++ codebase to generate exact, cycle-accurate timing profiles.
*/

const int TEST_PIN = 8; // Tied to PORTB Bit 0 on ATmega328P

void setup() {
  pinMode(TEST_PIN, OUTPUT);
}

void loop() {
  // Disable global interrupts to ensure completely deterministic hardware execution
  noInterrupts();

  // Fast pulse generation with exact instruction timing step windows
  // 'asm volatile' prevents the compiler from optimizing out or rearranging these lines
  PORTB |= (1 << PB0);   // Set Pin 8 HIGH instantly
  
  asm volatile(
    "nop \n\t"           // No Operation: Pauses the CPU for exactly 1 clock cycle (62.5ns at 16MHz)
    "nop \n\t"           // 2 cycles
    "nop \n\t"           // 3 cycles
    "nop \n\t"           // 4 cycles
  );
  
  PORTB &= ~(1 << PB0);  // Set Pin 8 LOW instantly

  interrupts();          // Re-enable interrupts cleanly
  delay(1000);           // Long pause between pulses
}
