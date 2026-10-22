/*
  34_ring_buffer_uart
  Implements a fixed-size ring (circular) buffer FIFO to safely enqueue
  and dequeue fast incoming serial data packets without index overflow risks.
*/

#define BUFFER_SIZE 16

class RingBuffer {
  private:
    uint8_t data[BUFFER_SIZE];
    volatile int head = 0;
    volatile int tail = 0;

  public:
    bool isFull() {
      return ((head + 1) % BUFFER_SIZE) == tail;
    }

    bool isEmpty() {
      return head == tail;
    }

    bool enqueue(uint8_t val) {
      if (isFull()) return false; // Buffer overflow protection
      data[head] = val;
      head = (head + 1) % BUFFER_SIZE;
      return true;
    }

    bool dequeue(uint8_t &val) {
      if (isEmpty()) return false; // Buffer underflow protection
      val = data[tail];
      tail = (tail + 1) % BUFFER_SIZE;
      return true;
    }
};

RingBuffer myBuffer;

void setup() {
  Serial.begin(9600);
  Serial.println("\n--- Ring Buffer UART Pipeline Ready ---");
}

void loop() {
  // Read incoming hardware data and push directly to the ring buffer
  while (Serial.available() > 0) {
    char inChar = Serial.read();
    if (!myBuffer.enqueue(inChar)) {
      Serial.println("\n[Error] Buffer Overflow!");
    }
  }

  // Dequeue and process bytes whenever the main loop has spare processing time
  if (!myBuffer.isEmpty()) {
    uint8_t processedByte;
    if (myBuffer.dequeue(processedByte)) {
      Serial.print("Processed: '");
      Serial.print((char)processedByte);
      Serial.println("'");
    }
  }
  
  delay(10); // Simulated system work overhead loop delay
}
