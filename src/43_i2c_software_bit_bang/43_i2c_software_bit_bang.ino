/*
  43_i2c_software_bit_bang
  Manually emulates an I2C protocol interface on any general purpose digital I/O pins
  by controlling raw microsecond delay windows and signal edge dependencies.
*/

// Define completely arbitrary pins as your soft communication bus lines
const int SOFT_SDA = 4;
const int SOFT_SCL = 5;

// Microsecond delay constant to establish standard I2C speed bus frames (~100kHz)
const int HALF_CLOCK_DELAY_US = 5;

void softI2C_Init() {
  pinMode(SOFT_SDA, INPUT);
  pinMode(SOFT_SCL, INPUT);
  digitalWrite(SOFT_SDA, LOW);
  digitalWrite(SOFT_SCL, LOW);
}

// Drive a clean I2C Start Condition sequence (SDA drops low while SCL remains high)
void softI2C_Start() {
  pinMode(SOFT_SDA, OUTPUT); // Pulls line LOW
  delayMicroseconds(HALF_CLOCK_DELAY_US);
  pinMode(SOFT_SCL, OUTPUT); // Pulls line LOW
  delayMicroseconds(HALF_CLOCK_DELAY_US);
}

// Drive a clean I2C Stop Condition sequence (SDA pulls high while SCL remains high)
void softI2C_Stop() {
  pinMode(SOFT_SCL, INPUT);  // Float SCL HIGH
  delayMicroseconds(HALF_CLOCK_DELAY_US);
  pinMode(SOFT_SDA, INPUT);  // Float SDA HIGH
  delayMicroseconds(HALF_CLOCK_DELAY_US);
}

// Transmit 1 byte (8 bits) sequentially down the data line, returning the ACK bit status
bool softI2C_WriteByte(uint8_t dataByte) {
  for (uint8_t mask = 0x80; mask; mask >>= 1) {
    if (dataByte & mask) {
      pinMode(SOFT_SDA, INPUT);  // Send 1 (Release line)
    } else {
      pinMode(SOFT_SDA, OUTPUT); // Send 0 (Pull down)
    }
    delayMicroseconds(HALF_CLOCK_DELAY_US);
    pinMode(SOFT_SCL, INPUT);    // Clock line HIGH
    delayMicroseconds(HALF_CLOCK_DELAY_US);
    pinMode(SOFT_SCL, OUTPUT);   // Clock line LOW
  }

  // Read Acknowledgement Bit (ACK) from slave device
  pinMode(SOFT_SDA, INPUT);      // Release data line for slave control
  delayMicroseconds(HALF_CLOCK_DELAY_US);
  pinMode(SOFT_SCL, INPUT);      // Clock HIGH
  bool ackReceived = (digitalRead(SOFT_SDA) == LOW);
  delayMicroseconds(HALF_CLOCK_DELAY_US);
  pinMode(SOFT_SCL, OUTPUT);     // Clock back LOW
  
  return ackReceived;
}

void setup() {
  Serial.begin(9600);
  softI2C_Init();
  Serial.println("\n--- Software Bit-Banged I2C Engine Online ---");
}

void loop() {
  // Example transaction: Ping target slave address 0x3C
  softI2C_Start();
  bool targetAcknowledged = softI2C_WriteByte(0x3C << 1); // Shift address for standard Write operation
  softI2C_Stop();

  Serial.print("Device Address 0x3C status connection response: ");
  Serial.println(targetAcknowledged ? "ACK SUCCESS" : "NACK FAILURE");

  delay(5000);
}
