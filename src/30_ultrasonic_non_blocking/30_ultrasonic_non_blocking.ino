/*
  30_ultrasonic_non_blocking
  Reads an HC-SR04 ultrasonic sensor using a non-blocking state machine style with millis(),
  preventing the system from locking up during pulse delays.
*/

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

unsigned long previousMillis = 0;
const long interval = 60; // Read sensor every 60ms (standard safe cycle)

volatile unsigned long pulseStart = 0;
volatile unsigned long pulseEnd = 0;
volatile bool newPulse = false;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Attach pin change or hardware interrupts for precise, non-blocking time capture
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), echoISR, CHANGE);
  
  digitalWrite(TRIG_PIN, LOW);
  Serial.println("\n--- Non-Blocking Ultrasonic Sensor Ready ---");
}

void loop() {
  unsigned long currentMillis = millis();

  // Trigger pulse at explicit intervals
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Generate a clean 10-microsecond high pulse
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
  }

  // Process data when the interrupt captures a clean echo pulse return
  if (newPulse) {
    long duration = pulseEnd - pulseStart;
    
    // Calculate distance in centimeters (Speed of sound = ~340m/s)
    float distance = duration * 0.034 / 2.0;
    
    if (distance >= 2.0 && distance <= 400.0) {
      Serial.print("Distance: ");
      Serial.print(distance, 1);
      Serial.println(" cm");
    } else {
      Serial.println("Out of range measurement.");
    }
    
    newPulse = false; // Reset flag
  }
}

// Interrupt Service Routine captures rising and falling edges instantly
void echoISR() {
  if (digitalRead(ECHO_PIN) == HIGH) {
    pulseStart = micros();
  } else {
    pulseEnd = micros();
    newPulse = true;
  }
}
