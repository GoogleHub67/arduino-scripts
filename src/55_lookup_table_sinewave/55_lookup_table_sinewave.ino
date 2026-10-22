/*
  55_lookup_table_sinewave
  Uses FLASH memory structures (PROGMEM) to store pre-calculated mathematical arrays,
  enabling microsecond-accurate trigonometric wave generation without runtime CPU math overhead.
*/

#include <avr/pgmspace.h>

// Pre-baked 8-bit resolution Sine table mapping over a full 360-degree sweep window (256 discrete points)
const uint8_t sineLookupTable[256] PROGMEM = {
  128, 131, 134, 137, 140, 143, 146, 149, 152, 156, 159, 162, 165, 168, 171, 174,
  176, 179, 182, 185, 188, 191, 193, 196, 199, 201, 204, 206, 209, 211, 213, 216,
  218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 237, 239, 240, 242, 243, 245,
  246, 247, 248, 249, 250, 251, 252, 252, 253, 254, 254, 254, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 254, 254, 254, 253, 252, 252, 251, 250, 249, 248, 247,
  246, 245, 243, 242, 240, 239, 237, 236, 234, 232, 230, 228, 226, 224, 222, 220,
  218, 216, 213, 211, 209, 206, 204, 201, 199, 196, 193, 191, 188, 185, 182, 179,
  176, 174, 171, 168, 165, 162, 159, 156, 152, 149, 146, 143, 140, 137, 134, 131,
  128, 124, 121, 118, 115, 112, 109, 106, 103,  99,  96,  93,  90,  87,  84,  81,
   79,  76,  73,  70,  67,  64,  62,  59,  56,  54,  51,  49,  46,  44,  42,  39,
   37,  35,  33,  31,  29,  27,  25,  23,  21,  19,  18,  16,  15,  13,  12,  10,
    9,   8,   7,   6,   5,   4,   3,   3,   2,   1,   1,   1,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   1,   1,   1,   2,   3,   3,   4,   5,   6,   7,   8,
    9,  10,  12,  13,  15,  16,  18,  19,  21,  23,  25,  27,  29,  31,  33,  35,
   37,  39,  42,  44,  46,  49,  51,  54,  56,  59,  62,  64,  67,  70,  73,  76,
   79,  81,  84,  87,  90,  93,  96,  99, 103, 106, 109, 112, 115, 118, 121, 124
};

void setup() {
  Serial.begin(115200);
  Serial.println("\n--- Instant Flash Lookup Waveform Generation ---");
}

void loop() {
  static uint8_t phaseAccumulator = 0;

  // Read data values directly from Flash program space using special macro wrappers
  uint8_t outputAmplitude = pgm_read_byte(&sineLookupTable[phaseAccumulator]);

  // Output direct visual mapping plots into the serial plotter pipeline
  Serial.println(outputAmplitude);

  phaseAccumulator++; // Automatically rolls back to 0 when passing 255 limits
  delay(5);
}
