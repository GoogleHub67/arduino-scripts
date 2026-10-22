/*
  54_fixed_point_math
  Implements a Q16.16 fixed-point math system to execute fast fractional calculations
  using standard integers, avoiding slow floating-point software emulation.
*/

// Define type representations for 32-bit fixed point variables (16 bits integer, 16 bits fraction)
typedef int32_t fixed_q16;

#define FIXED_SHIFT 16
#define DOUBLE_TO_FIXED(x) ((fixed_q16)((x) * (double)(1 << FIXED_SHIFT)))
#define FIXED_TO_DOUBLE(x) ((double)(x) / (double)(1 << FIXED_SHIFT))

// Fast bitwise multiplication of two fixed-point structures
fixed_q16 multiplyFixed(fixed_q16 a, fixed_q16 b) {
  return (fixed_q16)(((int64_t)a * b) >> FIXED_SHIFT);
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\n--- Fixed-Point High-Speed Math Engine ---");

  // 1. Initialize variables (e.g., calculation of 3.5 * 2.25)
  fixed_q16 variableA = DOUBLE_TO_FIXED(3.5);
  fixed_q16 variableB = DOUBLE_TO_FIXED(2.25);

  // 2. Performance benchmark calculation test
  unsigned long startTimestamps = micros();
  fixed_q16 resultingProduct = multiplyFixed(variableA, variableB);
  unsigned long endTimestamps = micros();

  Serial.print("Fixed-Point Product Value (Raw Bit Pattern): ");
  Serial.println(resultingProduct);

  Serial.print("Converted back to Standard Floating Output: ");
  Serial.println(FIXED_TO_DOUBLE(resultingProduct), 4);

  Serial.print("Execution Speed Time Delta: ");
  Serial.print(endTimestamps - startTimestamps);
  Serial.println(" microseconds.");
}

void loop() {
  // Idle
}
