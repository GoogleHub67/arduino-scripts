/*
  51_eeprom_circular_log
  Implements a FIFO circular logging engine inside EEPROM storage space,
  managing boundary limits and structural indices across active write cycles.
*/

#include <EEPROM.h>

struct DataLog {
  uint32_t logTime;
  int16_t primarySensor;
  int16_t auxiliarySensor;
};

const int LOG_STORAGE_START = 20;
const int MAX_LOG_ENTRIES = 10;
const int LOG_SIZE = sizeof(DataLog);

int currentWriteIndex = 0;

void appendSystemLog(int16_t s1, int16_t s2) {
  DataLog freshLog = { millis(), s1, s2 };
  
  // Calculate absolute target address alignment
  int targetAddress = LOG_STORAGE_START + (currentWriteIndex * LOG_SIZE);
  
  EEPROM.put(targetAddress, freshLog);
  
  // Shift index point forward and wrap tightly inside boundary bounds
  currentWriteIndex = (currentWriteIndex + 1) % MAX_LOG_ENTRIES;
  
  // Persist current positional head index in absolute memory space slot 0
  EEPROM.write(0, currentWriteIndex);
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  // Recover absolute write index tracking position from slot 0
  uint8_t storedIndex = EEPROM.read(0);
  if (storedIndex < MAX_LOG_ENTRIES) {
    currentWriteIndex = storedIndex;
  }
  
  Serial.println("\n--- Circular Storage Log System Online ---");
  appendSystemLog(512, -43);
}

void loop() {
  // Idle
}
