/*
  59_crc8_packet_verification
  Implements a hardware-optimized Cyclic Redundancy Check (CRC-8) bitwise calculation algorithm 
  to validate data packet transmission integrity over noisy communication buses.
*/

// Standard SMBus CRC-8 Polynomial representation: X^8 + X^2 + X^1 + 1 (0x07)
const uint8_t CRC8_POLYNOMIAL = 0x07;

uint8_t calculateCRC8(const uint8_t *dataArray, size_t lengthWindow) {
  uint8_t calculatedCRC = 0x00; // Initialize remainder shift byte

  for (size_t i = 0; i < lengthWindow; i++) {
    calculatedCRC ^= dataArray[i]; // Fetch next payload byte into the state machine

    // Perform polynomial long division bit-by-bit across the byte frame
    for (uint8_t bit = 0; bit < 8; bit++) {
      if (calculatedCRC & 0x80) {
        calculatedCRC = (calculatedCRC << 1) ^ CRC8_POLYNOMIAL;
      } else {
        calculatedCRC <<= 1;
      }
    }
  }
  return calculatedCRC;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\n--- Polynomial CRC-8 Packet Check Verification Engine ---");

  // Sample data payload packet frame
  uint8_t dataPacket[4] = { 0x1E, 0xA2, 0x4F, 0x00 }; 
  
  // 1. Generate parity verification token for the data segment (first 3 bytes)
  uint8_t computedToken = calculateCRC8(dataPacket, 3);
  dataPacket[3] = computedToken; // Append checksum byte into final structural slot
  
  Serial.print("Generated Transmission CRC-8 Checksum Byte: 0x");
  Serial.println(computedToken, HEX);

  // 2. Validate data stream integrity upon reception
  uint8_t verificationCheckResult = calculateCRC8(dataPacket, 4);

  if (verificationCheckResult == 0) {
    Serial.println("[Integrity Check]: SUCCESS! The packet arrived completely uncorrupted.");
  } else {
    Serial.println("[Integrity Check]: FAILURE! Bit corruption detected in transmission payload.");
  }
}

void loop() {
  // Idle
}
