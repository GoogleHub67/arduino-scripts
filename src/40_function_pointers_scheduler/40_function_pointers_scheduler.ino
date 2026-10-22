/*
  40_function_pointers_scheduler
  Implements a dynamic function pointer array to create a lightweight, 
  flexible loop event scheduler task matrix.
*/

// Define a structural function pointer type mapping to void worker tasks
typedef void (*TaskFunction)();

// Real-world worker task profiles
void sampleSensors() {
  Serial.println("[Task] Ingesting physical sensor networks...");
}

void updateDisplay() {
  Serial.println("[Task] Pushing visual frames to dashboard matrix...");
}

void checkSafetyLimits() {
  Serial.println("[Task] Running critical safety margin diagnostics...");
}

// Structure to track structural system profile state execution timers
struct ScheduledTask {
  TaskFunction runTask;     // Address point location of code block target
  unsigned long intervalMs; // Target execution delay window
  unsigned long lastRunMs;  // Historic tracking timeline point
};

// Populate task table row definitions explicitly
ScheduledTask taskList[] = {
  { checkSafetyLimits, 500,  0 },
  { sampleSensors,     2000, 0 },
  { updateDisplay,     5000, 0 }
};

const uint8_t TOTAL_TASKS = sizeof(taskList) / sizeof(taskList[0]);

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("\n--- Function Pointer Kernel Matrix Ready ---");
}

void loop() {
  unsigned long currentMillis = millis();

  // Parse task list continuously 
  for (uint8_t i = 0; i < TOTAL_TASKS; i++) {
    if (currentMillis - taskList[i].lastRunMs >= taskList[i].intervalMs) {
      taskList[i].lastRunMs = currentMillis;
      
      // Execute the task function directly via its memory address pointer mapping
      taskList[i].runTask(); 
    }
  }
}
