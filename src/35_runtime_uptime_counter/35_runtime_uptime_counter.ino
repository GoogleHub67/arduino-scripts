/*
  35_runtime_uptime_counter
  Saves and tracks hardware uptime execution metrics (Days, Hours, Minutes, Seconds)
  while safely handling rollover mechanics.
*/

unsigned long lastUpdateMillis = 0;
const unsigned long ONE_SECOND_MS = 1000;

unsigned long seconds = 0;
unsigned long minutes = 0;
unsigned long hours = 0;
unsigned long days = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("\n--- Uptime Metrics Tracker Active ---");
}

void loop() {
  unsigned long currentMillis = millis();

  // Evaluate delta time safely to survive 49.7-day millis() overflow loops natively
  if (currentMillis - lastUpdateMillis >= ONE_SECOND_MS) {
    lastUpdateMillis += ONE_SECOND_MS; // Maintain step lock accuracy
    seconds++;

    if (seconds >= 60) {
      seconds = 0;
      minutes++;
      
      if (minutes >= 60) {
        minutes = 0;
        hours++;
        
        if (hours >= 24) {
          hours = 0;
          days++;
        }
      }
    }

    // Print operational profile time strings neatly
    Serial.print("System Uptime: ");
    Serial.print(days); Serial.print("d ");
    Serial.print(hours); Serial.print("h ");
    Serial.print(minutes); Serial.print("m ");
    Serial.print(seconds); Serial.println("s");
  }
}
