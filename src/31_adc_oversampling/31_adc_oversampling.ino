/*
  31_adc_oversampling
  Oversamples a standard 10-bit analog pin to synthesize an 11-bit or 12-bit
  virtual resolution, smoothing out thermal or supply noise.
*/

const int ANALOG_INPUT_PIN = A0;

void setup() {
  Serial.begin(9600);
  pinMode(ANALOG_INPUT_PIN, INPUT);
  Serial.println("\n--- ADC Oversampling Filter Ready ---");
}

void loop() {
  // To increase resolution by N virtual bits, you must sum 4^N samples.
  // Let's increase resolution by 2 bits (from 10-bit to 12-bit). 4^2 = 16 samples.
  unsigned long accumulatedSum = 0;
  const int sampleSize = 16;

  for (int i = 0; i < sampleSize; i++) {
    accumulatedSum += analogRead(ANALOG_INPUT_PIN);
    delayMicroseconds(50); // Small delay to let ADC sample-and-hold circuit settle
  }

  // To get the scaled result for 12-bit resolution, scale down by shifting right by N bits (2)
  // Decimation step: sum >> N
  int oversampledValue = accumulatedSum >> 2; 

  // Standard 10-bit baseline read for clear comparison
  int rawBaseline = analogRead(ANALOG_INPUT_PIN);

  // Convert reading voltages
  float rawVoltage = (rawBaseline * 5.0) / 1023.0;
  float oversampledVoltage = (oversampledValue * 5.0) / 4095.0; // Scaled to 12-bit range (0-4095)

  Serial.print("Raw(10-bit): "); Serial.print(rawBaseline);
  Serial.print(" ["); Serial.print(rawVoltage, 3); Serial.print("V]");
  
  Serial.print("\tOversampled(12-bit): "); Serial.print(oversampledValue);
  Serial.print(" ["); Serial.print(oversampledVoltage, 4); Serial.println("V]");

  delay(1000);
}
