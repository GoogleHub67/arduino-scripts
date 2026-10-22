/*
  36_hardware_timer_ctc
  Configures ATmega328P Hardware Timer1 in CTC mode to execute a precise
  1Hz background task via hardware interrupts, completely bypassing loop().
*/

#include <avr/io.h>
#include <avr/interrupt.h>

const int LED_PIN = 13;
volatile bool toggleState = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  // Disable global interrupts during hardware register setup
  cli();

  // Clear Timer/Counter Control Registers for Timer1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0; // Initialize counter value to 0

  // Set Compare Match Register for 1 Hz target frequency
  // Formula: OCR1A = (Clock_Speed / (Prescaler * Target_Freq)) - 1
  // OCR1A = (16,000,000 / (1024 * 1)) - 1 = 15624
  OCR1A = 15624;

  // Turn on CTC (Clear Timer on Compare) mode
  TCCR1B |= (1 << WGM12);

  // Set CS10 and CS12 bits for a 1024 hardware prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  

  // Enable Timer1 Compare Match A Interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Re-enable global interrupts
  sei();
}

// Hardware Interrupt Vector Service Routine for Timer1 Compare Match A
ISR(TIMER1_COMPA_vect) {
  toggleState = !toggleState;
  digitalWrite(LED_PIN, toggleState ? HIGH : LOW);
}

void loop() {
  // The CPU can be completely idle or working here. 
  // The LED blinks exactly at 1Hz driven strictly by hardware gates.
}
