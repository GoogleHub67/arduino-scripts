/*
  41_runtime_stack_heap_sniffer
  Calculates the exact amount of remaining dynamic SRAM memory between 
  the heap allocations and stack frame in real time. Prevents silent crashes.
*/

extern int __heap_start;
extern void *__brkval;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("\n--- SRAM Safety Integrity Scanner Online ---");
}

void loop() {
  int dynamicSRAMLeft = getFreeSRAM();
  
  Serial.print("Available Working Memory Space: ");
  Serial.print(dynamicSRAMLeft);
  Serial.println(" bytes clean.");

  if(dynamicSRAMLeft < 150) {
    Serial.println("[CRITICAL ALERT]: Approaching Stack-Heap Collision Threshold!");
  }
  
  delay(3000);
}

// Low level pointer checking calculation
int getFreeSRAM() {
  int topOfStackVariable; // This variable lives natively right on the current executing Stack frame

  // If heap allocation pool is empty (__brkval pointer is 0), default to the start boundary address
  int currentHeapAddress = (int)__brkval;
  if (currentHeapAddress == 0) {
    currentHeapAddress = (int)&__heap_start;
  }

  // Free memory is the space between the top of the stack and the highest boundary of the dynamic heap pool
  int calculatedFreeBytes = (int)&topOfStackVariable - currentHeapAddress;
  
  return calculatedFreeBytes;
}
