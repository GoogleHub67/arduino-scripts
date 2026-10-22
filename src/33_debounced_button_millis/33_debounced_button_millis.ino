/*
  33_debounced_button_millis
  Software debounces a momentary push button without blocking code execution,
  ensuring crisp state transitions and avoiding false double-press triggers.
*/

const int BUTTON_PIN = 2;
const int LED_PIN = 13;

int ledState = LOW;
int buttonState = HIGH;
int lastButtonState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY_MS = 50; // Stable filter window time

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  // If the switch changed due to noise or pressing, reset the debouncing timer
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Check if the reading has stayed stable longer than our target debounce delay window
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY_MS) {
    // If the button state has truly changed:
    if (reading != buttonState) {
      buttonState = reading;

      // Only toggle the target LED if the new state is pressed (LOW due to internal pull-up)
      if (buttonState == LOW) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
      }
    }
  }

  lastButtonState = reading;
}
