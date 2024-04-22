#include <Boards.h>
#include <Firmata.h>
#include <FirmataConstants.h>
#include <FirmataDefines.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>
#include <Servo.h>

Servo myservos[4];          // Array to hold four servo objects
int pos[4] = { 0, 0, 0, 0 };  // Array to hold current position of each servo
int targetPos[4] = { 90, 90, 90, 90 };  // Array to hold target position of each servo
unsigned long lastUpdate[4] = { 0, 0, 0, 0 }; // Last update time for each servo
const int updateInterval = 15; // Time interval between each servo update (milliseconds)
const int movementSpeed = 1;   // Speed of servo movement

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

void moveServo(int servoIndex, int pin) {
  if (digitalRead(pin) == LOW) {
    pos[servoIndex] == 180 ?: pos[servoIndex]++;
    Serial.println("Button pressed. Servo moved to HIGH");
  }
}

void moveOppositeServo(int servoIndex, int pin) {
  if (digitalRead(pin) == LOW) {
    pos[servoIndex] == 0 ?: pos[servoIndex]--;
    Serial.println("Button pressed. Servo moved to LOW");
  }
}

void updateServoPosition(int servoIndex) {
  unsigned long currentTime = millis();
  if (currentTime - lastUpdate[servoIndex] >= updateInterval) {
    if (pos[servoIndex] < targetPos[servoIndex]) {
      pos[servoIndex] += movementSpeed;
    } else if (pos[servoIndex] > targetPos[servoIndex]) {
      pos[servoIndex] -= movementSpeed;
    }
    myservos[servoIndex].write(pos[servoIndex]);
    lastUpdate[servoIndex] = currentTime;
  }
}

void loop() {
  moveServo(0, RotateLeftPin);  // RotateLeftPin
  moveOppositeServo(0, RotateRightPin);  // RotateRightPin
  moveServo(1, ExtendUpPin);  // ExtendUpPin
  moveOppositeServo(1, ExtendDownPin);  // ExtendDownPin
  moveServo(2, ReachDownPin);  // ReachDownPin
  moveOppositeServo(2, ReachUpPin);  // ReachUpPin
  moveServo(3, ClawOpenPin);  // ClawOpenPin
  moveOppositeServo(3, ClawClosePin);  // ClawClosePin
  
  for (int i = 0; i < 4; i++) {
    updateServoPosition(i);
  }
  
  delay(20);
}
