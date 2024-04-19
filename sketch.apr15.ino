#include <Boards.h>
#include <Firmata.h>
#include <FirmataConstants.h>
#include <FirmataDefines.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>

#include <Servo.h>

Servo myservos[4];          // Array to hold four servo objects
int pos[4] = { 90, 0, 0, 0 };  // Array to hold current position of each servo

int RotateLeftPin = 2;  // Pin numbers for your buttons
int RotateRightPin = 3;
int ExtendUpPin = 4;
int ExtendDownPin = 5;
int ReachDownPin = 6;
int ReachUpPin =  7;
int ClawOpenPin = 8;
int ClawClosePin = 9;

int ledPin = 13;          // Pin connected to the LED
bool lightState = false;  // Variable to store the current state of the LED

void setup() {
  pinMode(RotateLeftPin, INPUT_PULLUP); // Set button pins as input with internal pull-up resistors
  pinMode(RotateRightPin, INPUT_PULLUP);
  pinMode(ExtendUpPin, INPUT_PULLUP);
  pinMode(ExtendDownPin, INPUT_PULLUP);
  pinMode(ReachDownPin, INPUT_PULLUP);
  pinMode(ReachUpPin, INPUT_PULLUP);
  pinMode(ClawOpenPin, INPUT_PULLUP);
  pinMode(ClawClosePin, INPUT_PULLUP);

  myservos[0].attach(10); // arm rotation (left to right)
  myservos[1].attach(11); // arm extension (up to down)
  myservos[2].attach(12); // arm reach (lift and drop)
  myservos[3].attach(13); // claw (open and close)
  
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 4; i++) { 
    // Servo 0 rotation ^
    if (digitalRead(RotateLeftPin) == LOW) {
      pos[0] == 180 ?: pos[0]++;
      Serial.println("Arm was Rotated to LOW");
    }

    if (digitalRead(RotateRightPin) == LOW) {
      pos[0] == 0 ?: pos[0]--;
      Serial.println("Arm was Rotated to HIGH");
    }
    // Servo 1 Extension
    if (digitalRead(ExtendUpPin) == LOW) {
      pos[1] == 180 ?: pos[1]++;
      Serial.println("Arm was extended LOW");
    }

    if (digitalRead(ExtendDownPin) == LOW) {
      pos[1] == 0 ?: pos[1]--;
      Serial.println("Arm was extended HIGH");
    }
    // Servo 2 Reach 
    if (digitalRead(ReachDownPin) == LOW) {
      pos[2] == 180 ?: pos[2]++;
      Serial.println("Arm reached LOW");
    }

    if (digitalRead(ReachUpPin) == LOW) {
      pos[2] == 0 ?: pos[2]--;
      Serial.println("Arm reached HIGH");
    }
    // Servo 3 Claw
    if (digitalRead(ClawOpenPin) == LOW) {
      pos[3] == 180 ?: pos[3]++;
      Serial.println("Clawed was opened");
    }

    if (digitalRead(ClawClosePin) == LOW) {
      pos[3] == 0 ?: pos[3]--;
      Serial.println("Claw was closed");
    }
    myservos[i].write(pos[i]);  // Update servo positions
  }
  delay(20);
}
