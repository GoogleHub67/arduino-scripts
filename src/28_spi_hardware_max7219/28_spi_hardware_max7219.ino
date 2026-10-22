/*
  28_spi_hardware_max7219
  Demonstrates hardware SPI communication by initializing and controlling
  a MAX7219 LED display driver without external device libraries.
*/

#include <SPI.h>

// Define the Chip Select pin (CS / Load)
const int CS_PIN = 10;

// MAX7219 Register Map Addresses
const byte REG_NOOP        = 0x00;
const byte REG_DIGIT0      = 0x01; // Can represent column 1 on matrices
const byte REG_DECODE_MODE = 0x09;
const byte REG_INTENSITY   = 0x0A;
const byte REG_SCAN_LIMIT  = 0x0B;
const byte REG_SHUTDOWN    = 0x0C;
const byte REG_DISPLAY_TEST= 0x0F;

// Helper function to transmit command and data to MAX7219 via SPI
void sendMAX7219(byte reg, byte data) {
  digitalWrite(CS_PIN, LOW);   // Select the chip
  SPI.transfer(reg);           // Send register address
  SPI.transfer(data);          // Send data byte
  digitalWrite(CS_PIN, HIGH);  // Latch the data
}

void setup() {
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);

  // Initialize Hardware SPI bus (Sets MOSI, MISO, and SCK pins automatically)
  SPI.begin();
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));

  // Initialize MAX7219 configuration
  sendMAX7219(REG_DISPLAY_TEST, 0x00); // Test mode OFF
  sendMAX7219(REG_SCAN_LIMIT, 0x07);   // Scan all 8 digits/rows
  sendMAX7219(REG_DECODE_MODE, 0x00);  // No decode (Direct bit mapping for matrices)
  sendMAX7219(REG_INTENSITY, 0x03);    // Medium brightness (0x00 to 0x0F)
  sendMAX7219(REG_SHUTDOWN, 0x01);     // Normal operation ON
}

void loop() {
  // Simple pattern: blink a diagonal line across an 8x8 matrix
  for (byte i = 1; i <= 8; i++) {
    sendMAX7219(i, (1 << (i - 1))); // Light up matching bit per row
  }
  delay(1000);

  // Alternate pattern
  for (byte i = 1; i <= 8; i++) {
    sendMAX7219(i, ~(1 << (i - 1))); // Invert pattern
  }
  delay(1000);
}
