/*
  48_binary_serialization_struct
  Demonstrates binary serialization by packing multiple variable types into a structured 
  byte array payload for high-speed, minimal-overhead telemetry transmission.
*/

#pragma pack(push, 1) // Prevents the compiler from adding padding bytes for memory alignment
struct TelemetryPacket {
  uint32_t timestamp;
  float internalTemperature;
  int16_t gyroX;
  int16_t gyroY;
  uint8_t systemStatusFlags;
};
#pragma pack(pop)

void setup() {
  Serial.begin(115200); // High baud rate for raw binary streaming
  while (!Serial);
  Serial.println("\n--- Binary Serialization Pipeline Online ---");
}

void loop() {
  // 1. Populate a dummy packet frame with mock runtime metrics
  TelemetryPacket currentFrame;
  currentFrame.timestamp = millis();
  currentFrame.internalTemperature = 24.57;
  currentFrame.gyroX = -312;
  currentFrame.gyroY = 894;
  currentFrame.systemStatusFlags = 0b00000101; // System OK, Logger Active

  // 2. Serialize the structure into a stream of raw bytes using pointer casting
  uint8_t* rawDataPointer = (uint8_t*)&currentFrame;
  size_t packetSize = sizeof(TelemetryPacket);

  // 3. Send a distinctive synchronization framing marker sequence (0xAA, 0xBB)
  Serial.write(0xAA);
  Serial.write(0xBB);

  // 4. Stream the raw byte payload down the TX hardware channel instantly
  Serial.write(rawDataPointer, packetSize);

  Serial.println("\n[Telemetry] Raw Packet Frame Streamed Cleanly.");
  delay(2000);
}
