/*
  29_eeprom_struct_save
  Demonstrates how to safely save and read an entire structure (multi-variable configuration)
  to persistent EEPROM memory using EEPROM.put() and EEPROM.get().
*/

#include <EEPROM.h>

// Define a custom configuration object structure
struct DeviceConfig {
  int systemID;
  float calibrationFactor;
  char deviceName[16];
  bool isActivated;
};

// Target memory offset in the EEPROM
const int EEPROM_START_ADDRESS = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for Serial Monitor

  Serial.println("\n--- EEPROM Struct Configuration Demo ---");

  // 1. Create a dummy configuration profile object
  DeviceConfig factorySettings = {
    4002,
    3.14159,
    "ArduinoNode_A",
    true
  };

  // 2. Write the whole struct to EEPROM
  // EEPROM.put uses EEPROM.update under the hood, writing bytes only if they changed
  Serial.println("Writing new configuration profile to EEPROM...");
  EEPROM.put(EEPROM_START_ADDRESS, factorySettings);
  Serial.println("Write complete!\n");

  // 3. Create a blank object variable to read data back into
  DeviceConfig activeConfig;

  // 4. Retrieve data from EEPROM
  Serial.println("Reading configuration profile back from EEPROM...");
  EEPROM.get(EEPROM_START_ADDRESS, activeConfig);

  // 5. Print results to confirm success
  Serial.println("--- Retrieved Configuration Results ---");
  Serial.print("Device System ID   : "); Serial.println(activeConfig.systemID);
  Serial.print("Calibration Factor : "); Serial.println(activeConfig.calibrationFactor, 5);
  Serial.print("Device Name Tag    : "); Serial.println(activeConfig.deviceName);
  Serial.print("Is Active Status   : "); Serial.println(activeConfig.isActivated ? "TRUE" : "FALSE");
}

void loop() {
  // Nothing to do in the main loop
}
