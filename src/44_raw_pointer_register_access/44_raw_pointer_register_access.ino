/*
  44_raw_pointer_register_access
  Bypasses core avr/io.h definitions entirely. Interacts directly with physical memory
  address lookups via raw pointer casting variables to alter pin states.
*/

// On the ATmega328P datasheet:
// DDRB lives at RAM Data memory physical address: 0x24
// PORTB lives at RAM Data memory physical address: 0x25
volatile uint8_t* const raw_DDRB  = (volatile uint8_t*)0x24;
volatile uint8_t* const raw_PORTB = (volatile uint8_t*)0x25;

const uint8_t TARGET_PIN_BIT = 5; // Pin 13 corresponds to Bit 5 of PORTB

void setup() {
  // Equivalent execution to: pinMode(13, OUTPUT) or DDRB |= (1 << 5);
  // De-reference the pointer variable directly to manipulate memory architecture gates
  *raw_DDRB |= (1 << TARGET_PIN_BIT);
}

void loop() {
  // Set Pin 13 HIGH directly by forcing memory state shifts
  *raw_PORTB |= (1 << TARGET_PIN_BIT);
  customHardwareDelay();

  // Set Pin 13 LOW directly by forcing memory state shifts
  *raw_PORTB &= ~(1 << TARGET_PIN_BIT);
  customHardwareDelay();
}

// Basic hardware loop execution delay mechanism bypassing timers
void customHardwareDelay() {
  for (volatile uint32_t i = 0; i < 100000; i++) {
    // Force CPU cycle loops intentionally to hold hardware states stable
  }
}
