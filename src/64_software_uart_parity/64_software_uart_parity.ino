/*
  64_software_uart_parity
  Manually emulates a software UART serial transmitter on a standard digital pin,
  calculating and appending an Even Parity bit into the serial bit stream.
*/

const int SOFT_TX_PIN = 4;
const int BIT_DELAY_US = 104; // Microsecond window delay for 9600 Baud rate (1000000 / 9600)

void softUart_Init() {
  pinMode(SOFT_TX_PIN, OUTPUT);
  digitalWrite(SOFT_TX_PIN, HIGH); // IDLE line state is always HIGH in UART protocols
}

void softUart_TransmitByte(uint8_t payloadByte) {
  uint8_t parityBitAccumulator = 0;

  // 1. Send START Bit (Pull line LOW)
  digitalWrite(SOFT_TX_PIN, LOW);
  delayMicroseconds(BIT_DELAY_US);

  // 2. Stream 8 data bits sequentially, Least Significant Bit (LSB) first
  for (uint8_t i = 0; i < 8; i++) {
    bool currentBitState = (payloadByte >> i) & 0x01;
    digitalWrite(SOFT_TX_PIN, currentBitState ? HIGH : LOW);
    
    if (currentBitState) {
      parityBitAccumulator++;
    }
    
    delayMicroseconds(BIT_DELAY_US);
  }

  // 3. Calculate Even Parity: If the number of 1s is odd, parity bit must be 1 to make it even
  bool evenParityBit = (parityBitAccumulator % 2 != 0);
  digitalWrite(SOFT_TX_PIN, evenParityBit ? HIGH : LOW);
  delayMicroseconds(BIT_DELAY_US);

  // 4. Send STOP Bit (Pull line back HIGH to return to IDLE)
  digitalWrite(SOFT_TX_PIN, HIGH);
  delayMicroseconds(BIT_DELAY_US);
}

void setup() {
  softUart_Init();
}

void loop() {
  // Transmit the ASCII character 'A' (0x41 -> 01000001 binary) every 3 seconds
  softUart_TransmitByte(0x41);
  delay(3000);
}
