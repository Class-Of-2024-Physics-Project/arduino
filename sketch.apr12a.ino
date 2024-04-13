#include <Boards.h>
#include <Firmata.h>
#include <FirmataConstants.h>
#include <FirmataDefines.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>

#include <Servo.h>

Servo myservos[2]; // Array to store servo objects
int pos[2] = {0, 0}; // Array to store servo positions
int buttonPin[2] = {2, 3}; // Pins connected to the buttons
int buttonState[2] = {LOW, LOW}; // Variables to store the current state of the buttons
unsigned long lastDebounceTime[2] = {0, 0}; // Variables to store the last time the button state changed
unsigned long debounceDelay = 50; // Delay time to avoid button bouncing
int ledPin = 13; // Pin connected to the LED
bool lightState = false; // Variable to store the current state of the LED

void setup() {
  pinMode(buttonPin[0], INPUT_PULLUP); // Set button 1 pin as input with internal pull-up resistor
  pinMode(buttonPin[1], INPUT_PULLUP); // Set button 2 pin as input with internal pull-up resistor
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  myservos[0].attach(9); // Attach servo 1 to pin 9
  myservos[1].attach(8); // Attach servo 2 to pin 8
}

void loop() {
  for (int i = 0; i < 2; i++) {
    int reading = digitalRead(buttonPin[i]); // Read the state of the button

    if (reading != buttonState[i] && millis() - lastDebounceTime[i] > debounceDelay) {
      buttonState[i] = reading; // Update button state

      if (buttonState[i] == LOW) { // Button is pressed
        pos[i] = (pos[i] == 0) ? 180 : 0; // Toggle servo state (start/stop spinning)
        lightState = !lightState; // Toggle light state
        digitalWrite(ledPin, lightState ? HIGH : LOW); // Update light state
      }

      lastDebounceTime[i] = millis(); // Update debounce time
    }

    myservos[i].write(pos[i]); // Update servo positions
  }
}
