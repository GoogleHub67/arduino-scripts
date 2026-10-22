/*
  32_custom_pwm_software
  Generates a manual Software PWM signal on a standard digital pin
  without interacting with hardware timers. Useful for driving LEDs on any pin.
*/

const int SOFTWARE_PWM_PIN = 4; // Any general purpose digital pin
const int targetFrequencyHz = 100; 
const int periodMicroseconds = 1000000 / targetFrequencyHz; // Total cycle window time (10,000us)

int dutyCyclePercent = 0; // Ranges 0 to 100%
int fadeDirection = 1;     // Controls breathing fade pulse direction
unsigned long lastFadeMillis = 0;
const int fadeIntervalMs = 20;

void setup() {
  pinMode(SOFTWARE_PWM_PIN, OUTPUT);
}

void loop() {
  // 1. Calculate active HIGH and LOW durations based on current duty cycle percent
  long highTimeUs = (periodMicroseconds * dutyCyclePercent) / 100;
  long lowTimeUs = periodMicroseconds - highTimeUs;

  // 2. Drive the custom Duty Waveform window manually
  if (highTimeUs > 0) {
    digitalWrite(SOFTWARE_PWM_PIN, HIGH);
    delayMicroseconds(highTimeUs);
  }
  
  if (lowTimeUs > 0) {
    digitalWrite(SOFTWARE_PWM_PIN, LOW);
    delayMicroseconds(lowTimeUs);
  }

  // 3. Dynamic adjustment: Breathe/Fade duty cycle up and down gracefully over time
  if (millis() - lastFadeMillis >= fadeIntervalMs) {
    lastFadeMillis = millis();
    dutyCyclePercent += fadeDirection;
    
    if (dutyCyclePercent <= 0 || dutyCyclePercent >= 100) {
      fadeDirection = -fadeDirection; // Invert fade sweep at boundaries
    }
  }
}
