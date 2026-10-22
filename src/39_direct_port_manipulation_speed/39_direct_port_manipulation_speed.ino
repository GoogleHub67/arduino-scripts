/*
  39_direct_port_manipulation_speed
  Demonstrates high-speed I/O toggling via raw AVR port registers (PORTB/DDRB).
  Bypasses digitalWrite to achieve maximum execution speeds and true simultaneous multi-pin switches.
*/

#include <avr/io.h>

void setup() {
  // Configures Arduino Digital Pins 8 through 13 (which map directly to PORTB bits 0-5) 
  // as outputs by manipulation of the Data Direction Register B (DDRB)
  // B111111 sets PB0 through PB5 as OUTPUT lines simultaneously
  DDRB |= B111111; 
}

void loop() {
  // Force Digital Pin 13 (PORTB Bit 5) HIGH instantly while preserving pins 8-12 states
  PORTB |= (1 << PB5);
  
  // Force Digital Pin 13 (PORTB Bit 5) LOW instantly while preserving pins 8-12 states
  PORTB &= ~(1 << PB5);

  // --- ADVANCED SPEED BLOCK ---
  // The line below leverages a unique AVR hardware design feature: 
  // Writing a logical 1 to the input PIN register register (PINB) toggles the output hardware flip-flop state.
  // This produces an ultra-precise square wave in exactly 1 hardware clock cycle (62.5 nanoseconds at 16MHz).
  while(true) {
    PINB = (1 << PB5); 
  }
}
