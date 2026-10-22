/*
  45_eeprom_wear_leveling
  Implements a custom circular wear-leveling algorithm across an EEPROM sector
  to prevent single-cell burn-out during high-frequency parameter logging.
*/

#include <EEPROM.h>

const int SECTOR_START = 10;
const int SECTOR_SIZE = 64; // Size of memory block to rotate through
const byte DATA_MARKER = 0xA5; // Token to identify the newest structural entry

struct LogPacket {
  byte marker;
  uint16_t sequenceNumber;
  int systemState;
};

void saveWearLeveledData(int stateValue) {
  static uint16_t globalSeq = 0;
  globalSeq++;

  int targetAddress = SECTOR_START;
  int oldestMarkerAddress = SECTOR_START;
  uint16_t highestSeq = 0;

  // Scan sector to find the current active head position
  for (int i = 0; i < SECTOR_SIZE; i += sizeof(LogPacket)) {
    int currentAddr = SECTOR_START + i;
    LogPacket tempPacket;
    EEPROM.get(currentAddr, tempPacket);

    if (tempPacket.marker == DATA_MARKER) {
      if (tempPacket.sequenceNumber > highestSeq) {
        highestSeq = tempPacket.sequenceNumber;
        targetAddress = currentAddr + sizeof(LogPacket); // Next slot
      }
    }
  }

  // Handle ring boundary rollover wraps
  if (targetAddress >= (SECTOR_START + SECTOR_SIZE)) {
    targetAddress = SECTOR_START;
  }

  // Clear the marker from the slot we are about to overwrite next to ensure integrity
  int nextSlotAhead = targetAddress + sizeof(LogPacket);
  if (nextSlotAhead >= (SECTOR_START + SECTOR_SIZE)) nextSlotAhead = SECTOR_START;
  EEPROM.write(nextSlotAhead, 0x00); 

  // Write our fresh data payload to the leveled cell block
  LogPacket activeWrite = { DATA_MARKER, globalSeq, stateValue };
  EEPROM.put(targetAddress, activeWrite);
}

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("\n--- EEPROM Wear Leveling Sector Controller Active ---");
  
  saveWearLeveledData(255); // Example tracking call
}

void loop() {
  // Idle
}
