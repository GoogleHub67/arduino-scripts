/*
  68_fixed_point_matrix_vector
  Executes high-speed 2x2 vector transformations using scaled fixed-point numbers (Q16.16),
  bypassing slow runtime float math emulations.
*/

typedef int32_t fixed_q16;
#define FIXED_SHIFT 16
#define INT_TO_FIXED(x) ((fixed_q16)((int32_t)(x) << FIXED_SHIFT))
#define FIXED_TO_FLOAT(x) ((float)(x) / (float)(1 << FIXED_SHIFT))

fixed_q16 multiplyFixed(fixed_q16 a, fixed_q16 b) {
  return (fixed_q16)(((int64_t)a * b) >> FIXED_SHIFT);
}

struct Vector2D {
  fixed_q16 x;
  fixed_q16 y;
};

struct Matrix2x2 {
  fixed_q16 m00, m01;
  fixed_q16 m12, m13;
};

Vector2D transformVector(const Matrix2x2 &matrix, const Vector2D &vector) {
  Vector2D resultOut;
  // Matrix dot product multiplication formula: [M] x [V]
  resultOut.x = multiplyFixed(matrix.m00, vector.x) + multiplyFixed(matrix.m01, vector.y);
  resultOut.y = multiplyFixed(matrix.m12, vector.x) + multiplyFixed(matrix.m13, vector.y);
  return resultOut;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\n--- Fixed-Point Matrix Processor Engaged ---");

  // Create simple rotation mapping profile matrix
  Matrix2x2 transformMatrix = {
    INT_TO_FIXED(2),  INT_TO_FIXED(-1),
    INT_TO_FIXED(1),  INT_TO_FIXED(3)
  };

  Vector2D targetCoordinate = { INT_TO_FIXED(5), INT_TO_FIXED(10) };

  Vector2D outputCoordinate = transformVector(transformMatrix, targetCoordinate);

  Serial.print("Transformed Target Coordinate X: "); Serial.println(FIXED_TO_FLOAT(outputCoordinate.x));
  Serial.print("Transformed Target Coordinate Y: "); Serial.println(FIXED_TO_FLOAT(outputCoordinate.y));
}

void loop() {
  // Idle
}
