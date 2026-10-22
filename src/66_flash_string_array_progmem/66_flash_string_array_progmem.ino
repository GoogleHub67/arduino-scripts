/*
  66_flash_string_array_progmem
  Implements a formal two-tiered double pointer layout architecture inside FLASH memory (PROGMEM)
  to shield active global working SRAM frames from text string memory starvation.
*/

#include <avr/pgmspace.h>

// 1. Declare the raw character string tables directly inside raw program flash space
const char string_0[] PROGMEM = "SYSTEM_STATUS_CRITICAL_OVERHEAT";
const char string_1[] PROGMEM = "BUS_ERROR_I2C_NACK_ENCOUNTERED";
const char string_2[] PROGMEM = "PERIPHERAL_SPI_DATA_FRAMING_FAIL";
const char string_3[] PROGMEM = "KERNEL_SCHEDULER_STACK_OVERFLOW";

// 2. Establish a look-up table array mapping to hold flash pointer index references
const char* const errorDiagnosticTable[] PROGMEM = {
  string_0,
  string_1,
  string_2,
  string_3
};

void printFlashDiagnosticMessage(uint8_t tableIndex) {
  char operationalBuffer[35]; // Temporary local stack clearance buffer space

  // Read the targeted flash data memory reference address string location out of the table matrix
  char* targetFlashAddress = (char*)pgm_read_word(&(errorDiagnosticTable[tableIndex]));

  // Pull the raw character text string out of program space and structure it into local RAM memory
  strcpy_P(operationalBuffer, targetFlashAddress);

  Serial.print("Extracted Kernel Fault Trace String: ");
  Serial.println(operationalBuffer);
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\n--- Flash PROGMEM String Table Map Active ---");

  // Output test diagnostic message alerts natively
  printFlashDiagnosticMessage(1);
  printFlashDiagnosticMessage(3);
}

void loop() {
  // Idle
}
