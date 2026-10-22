/*
  65_dynamic_array_reindexing
  Implements a real-time shift-and-insert tracking matrix buffer.
  Automatically slides historic indices down while dropping overflow data points safely.
*/

#define REALTIME_TRACKING_LIMIT 8

struct VectorSnapshot {
  uint32_t systemTimestamp;
  int16_t positionalAxisX;
};

VectorSnapshot telemetryStream[REALTIME_TRACKING_LIMIT];
uint8_t activeTrackingSize = 0;

void pushNewSnapshot(int16_t activeX) {
  // 1. If the index array is full, slide elements left to drop the oldest entry (index 0)
  if (activeTrackingSize >= REALTIME_TRACKING_LIMIT) {
    for (uint8_t i = 0; i < REALTIME_TRACKING_LIMIT - 1; i++) {
      telemetryStream[i] = telemetryStream[i + 1];
    }
    activeTrackingSize = REALTIME_TRACKING_LIMIT - 1; // Open up the final slot
  }

  // 2. Insert the fresh telemetry tracking packet into the tail endpoint position
  telemetryStream[activeTrackingSize].systemTimestamp = millis();
  telemetryStream[activeTrackingSize].positionalAxisX = activeX;
  activeTrackingSize++;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\n--- Shift-And-Insert Memory Matrix Ready ---");
}

void loop() {
  static int16_t mockIncrementer = 100;
  pushNewSnapshot(mockIncrementer);
  mockIncrementer += 15;

  // Print array states to trace shifts visually
  Serial.print("Current Array Pool Load: [");
  for (uint8_t i = 0; i < activeTrackingSize; i++) {
    Serial.print(telemetryStream[i].positionalAxisX);
    if (i < activeTrackingSize - 1) Serial.print(", ");
  }
  Serial.println("]");

  delay(1500);
}
