/*
  67_dsp_fir_filter
  Implements a Finite Impulse Response (FIR) low-pass digital filter
  utilizing moving coefficient weights to smooth high-frequency sensor noise.
*/

#define FILTER_TAPS 5

// Pre-calculated filter coefficients (normalized sum matches 1.0)
const float firCoefficients[FILTER_TAPS] = { 0.10, 0.20, 0.40, 0.20, 0.10 };
float filterHistoryBuffer[FILTER_TAPS] = { 0.0 };

float processFIRSample(float rawInputSample) {
  // 1. Shift the older telemetry records down one index step position
  for (int i = FILTER_TAPS - 1; i > 0; i--) {
    filterHistoryBuffer[i] = filterHistoryBuffer[i - 1];
  }
  
  // 2. Insert the latest raw calculation record into the head slot
  filterHistoryBuffer[0] = rawInputSample;

  // 3. Perform the convolution computation loop (Multiply and Accumulate)
  float filteredOutputValue = 0.0;
  for (int i = 0; i < FILTER_TAPS; i++) {
    filteredOutputValue += filterHistoryBuffer[i] * firCoefficients[i];
  }

  return filteredOutputValue;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\n--- Real-Time DSP FIR Filter Engine Active ---");
}

void loop() {
  float mockRawInput = analogRead(A0) + random(-15, 16); // Simulate noisy line signal
  float structuralSignal = processFIRSample(mockRawInput);

  Serial.print("Raw_Signal:"); Serial.print(mockRawInput);
  Serial.print(",");
  Serial.print("Filtered_Signal:"); Serial.println(structuralSignal);

  delay(50);
}
