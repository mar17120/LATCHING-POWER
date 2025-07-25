const int buttonPin = 2;      // Push button connected to pin D2
const int ledPin = 3;         // NMOS Gate connected to pin D3 (controls LED)

bool isOn = false;            // Current power state
unsigned long startTime = 0;  // Time when the output was turned ON
unsigned long autoOffDelay = 10000; // Auto-off delay in milliseconds (10 seconds)

int lastButtonState = HIGH;   // Previous button state
int buttonState;              // Current button state
unsigned long lastDebounceTime = 0; // Last debounce time
unsigned long debounceDelay = 50;   // Debounce delay time

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor for the button
  pinMode(ledPin, OUTPUT);           // Set LED pin as output
  digitalWrite(ledPin, LOW);         // Ensure LED is off initially
}

void loop() {
  int reading = digitalRead(buttonPin); // Read the button state

  // Check if the button state changed (for debounce)
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // If enough time has passed, consider the reading stable
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If button state changed
    if (reading != buttonState) {
      buttonState = reading;

      // If button is pressed (LOW because of pull-up)
      if (buttonState == LOW) {
        isOn = !isOn; // Toggle the power state

        if (isOn) {
          digitalWrite(ledPin, HIGH);  // Turn ON the LED (activate MOSFET)
          startTime = millis();        // Reset the timer
        } else {
          digitalWrite(ledPin, LOW);   // Turn OFF the LED (deactivate MOSFET)
        }
      }
    }
  }

  lastButtonState = reading;

  // Automatically turn off after delay
  if (isOn && (millis() - startTime >= autoOffDelay)) {
    isOn = false;
    digitalWrite(ledPin, LOW);
  }
}
