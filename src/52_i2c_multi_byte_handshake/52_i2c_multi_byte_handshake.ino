/*
  52_i2c_multi_byte_handshake
  Configures an advanced multi-byte structure payload transfer across I2C bus paths
  using strict sequence checking and pointer array formatting.
*/

#include <Wire.h>

const byte TARGET_I2C_ADDRESS = 0x42;

struct CommandPacket {
  uint8_t commandToken;
  uint16_t parameterValue;
  uint8_t checksum;
};

void transmitHandshakeCommand(uint8_t cmd, uint16_t val) {
  CommandPacket outPacket;
  outPacket.commandToken = cmd;
  outPacket.parameterValue = val;
  
  // Compute basic packet structure parity verification checksum
  outPacket.checksum = outPacket.commandToken ^ (uint8_t)(outPacket.parameterValue & 0xFF) ^ (uint8_t)(outPacket.parameterValue >> 8);

  // Cast packet to a direct sequential array stream pointer block
  uint8_t* rawData = (uint8_t*)&outPacket;

  Wire.beginTransmission(TARGET_I2C_ADDRESS);
  
  // Stream the full structure sequence block continuously in one transaction window
  Wire.write(rawData, sizeof(CommandPacket));
  
  byte transmissionStatus = Wire.endTransmission();
  
  if (transmissionStatus == 0) {
    Serial.println("[I2C Bus]: Multi-byte handshake packet passed successfully.");
  } else {
    Serial.print("[I2C Error]: Transaction aborted with status code: ");
    Serial.println(transmissionStatus);
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Join bus network topology as controller master
  Serial.println("\n--- Asynchronous I2C Handshake Bus Online ---");
}

void loop() {
  transmitHandshakeCommand(0xA3, 1024);
  delay(3000);
}
