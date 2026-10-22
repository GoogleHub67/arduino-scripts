/*
  61_spi_dma_ping_pong
  Implements a simulated dual-buffer ping-pong architecture for SPI data capture,
  allowing an interrupt-driven pipeline to fill one data buffer while the main execution
  loop processes the second frame background layer completely asynchronously.
*/

#define BUFFER_SIZE 64

volatile uint8_t pingBuffer[BUFFER_SIZE];
volatile uint8_t pongBuffer[BUFFER_SIZE];
volatile uint8_t* activeWriteBuffer = pingBuffer;
volatile uint8_t* activeReadBuffer = pongBuffer;

volatile bool bufferReadyFlag = false;
volatile uint8_t bufferIndex = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  noInterrupts();
  // Initialize hardware SPI control switches to Slave mode setup mapping
  SPCR |= (1 << SPE);  // Enable SPI system gates
  SPCR &= ~(1 << MSTR); // Force Slave configuration architecture mode
  SPCR |= (1 << SPIE); // Enable SPI Transfer Complete Interrupt vector
  interrupts();
  
  Serial.println("\n--- Asynchronous Ping-Pong SPI Pipeline Engaged ---");
}

// Hardware Interrupt Vector triggered when an external master shifts a byte over SPI
ISR(SPI_STC_vect) {
  uint8_t incomingByte = SPDR; // Grab raw shift register byte hardware output
  
  if (bufferIndex < BUFFER_SIZE) {
    activeWriteBuffer[bufferIndex++] = incomingByte;
  }
  
  // Boundary cross validation check: Switch buffer tracks immediately upon saturation
  if (bufferIndex >= BUFFER_SIZE) {
    bufferIndex = 0;
    
    if (activeWriteBuffer == pingBuffer) {
      activeWriteBuffer = pongBuffer;
      activeReadBuffer = pingBuffer;
    } else {
      activeWriteBuffer = pingBuffer;
      activeReadBuffer = pongBuffer;
    }
    bufferReadyFlag = true; // Signal primary engine that a layer frame is ready for analysis
  }
}

void loop() {
  if (bufferReadyFlag) {
    bufferReadyFlag = false; // Reset task barrier instantly
    
    // Process the snapshot matrix safely while the alternate buffer handles the active background stream
    uint32_t checksumAcc = 0;
    for (int i = 0; i < BUFFER_SIZE; i++) {
      checksumAcc += activeReadBuffer[i];
    }
    
    Serial.print("[Ping-Pong Frame]: Safe read cycle resolved. Parity value total: ");
    Serial.println(checksumAcc);
  }
}
