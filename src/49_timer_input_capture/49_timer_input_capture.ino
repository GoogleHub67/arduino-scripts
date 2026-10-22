/*
  49_timer_input_capture
  Uses the hardware Input Capture Unit (ICR1) on Timer1 (Pin 8) to calculate the 
  exact period and frequency of an external square wave with absolute clock accuracy.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t pulseCapturedPeriod = 0;
volatile bool newPulseReady = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(8, INPUT); // ICP1 (Input Capture Pin) on ATmega328P is Digital Pin 8

  noInterrupts();
  
  TCCR1A = 0; // Standard timer setup
  TCCR1B = 0;
  TCNT1  = 0;

  // Set Timer1 Prescaler to 8 (16MHz / 8 = 2MHz clock rate -> 0.5 microseconds per tick)
  TCCR1B |= (1 << CS11);

  // Enable Input Capture Noise Canceler (ICNC1) and set trigger edge to Rising Edge (ICES1)
  TCCR1B |= (1 << ICNC1) | (1 << ICES1);

  // Clear pending flags and enable the Input Capture Interrupt (ICIE1)
  TIFR1 |= (1 << ICF1);
  TIMSK1 |= (1 << ICIE1);

  interrupts();
  Serial.println("\n--- Precision Hardware Input Capture Active ---");
}

// Hardware Interrupt Vector triggered instantly when a rising edge hits Digital Pin 8
ISR(TIMER1_CAPT_vect) {
  static uint16_t previousCaptureTime = 0;
  
  // Read the captured timer value from the dedicated hardware register
  uint16_t currentCaptureTime = ICR1; 
  
  // Calculate elapsed time ticks while safely handling 16-bit timer overflows automatically
  pulseCapturedPeriod = currentCaptureTime - previousCaptureTime;
  previousCaptureTime = currentCaptureTime;
  
  newPulseReady = true;
}

void loop() {
  if (newPulseReady) {
    noInterrupts();
    uint16_t currentPeriodTicks = pulseCapturedPeriod;
    newPulseReady = false;
    interrupts();

    // 1 tick = 0.5 microseconds (since prescaler is 8 on a 16MHz base clock)
    float wavePeriodMicroseconds = currentPeriodTicks * 0.5;
    float waveFrequencyHz = 1000000.0 / wavePeriodMicroseconds;

    Serial.print("Wave Period: "); Serial.print(wavePeriodMicroseconds, 1); Serial.print(" us");
    Serial.print("\tMeasured Frequency: "); Serial.print(waveFrequencyHz, 2); Serial.println(" Hz");
  }
}
