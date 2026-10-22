/*
  69_numerical_integration_trapezoidal
  Implements real-time calculus tracking via Trapezoidal integration approximations
  to calculate the total accumulated mathematical area under an incoming signal curve.
*/

float totalIntegratedAreaSum = 0.0;
float historicalLastSampleValue = 0.0;
unsigned long historicalTimestampUs = 0;

void accumulateCalculusStep(float currentSignalReading) {
  unsigned long currentTimestampUs = micros();
  
  // Calculate execution time delta window in seconds cleanly
  float timeDeltaSeconds = (currentTimestampUs - historicalTimestampUs) / 1000000.0;
  historicalTimestampUs = currentTimestampUs;

  // Enforce boundary reset if system catches initialization outliers
  if (timeDeltaSeconds > 0.5 || timeDeltaSeconds <= 0.0) {
    historicalLastSampleValue = currentSignalReading;
    return;
  }

  // Trapezoidal Area Area Formula: ((y1 + y2) / 2) * dt
  float calculatedStepArea = ((historicalLastSampleValue + currentSignalReading) / 2.0) * timeDeltaSeconds;
  
  totalIntegratedAreaSum += calculatedStepArea;
  historicalLastSampleValue = currentSignalReading;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  historicalTimestampUs = micros();
  Serial.println("\n--- Real-Time Trapezoidal Integration Loop Online ---");
}

void loop() {
  float mockSignalValue = (analogRead(A0) * 5.0) / 1023.0; // Simulated sensor reading in volts
  accumulateCalculusStep(mockSignalValue);

  Serial.print("Input_Signal_Volts:"); Serial.print(mockSignalValue);
  Serial.print(",");
  Serial.print("Accumulated_Integrated_Value:"); Serial.println(totalIntegratedAreaSum, 4);

  delay(250);
}
