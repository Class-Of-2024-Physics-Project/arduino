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

void setup() {
  // Set button pins as input with internal pull-up resistors
  pinMode(RotateLeftPin, INPUT_PULLUP); 
  pinMode(RotateRightPin, INPUT_PULLUP);
  pinMode(ExtendUpPin, INPUT_PULLUP);
  pinMode(ExtendDownPin, INPUT_PULLUP);
  pinMode(ReachDownPin, INPUT_PULLUP);
  pinMode(ReachUpPin, INPUT_PULLUP);
  pinMode(ClawOpenPin, INPUT_PULLUP);
  pinMode(ClawClosePin, INPUT_PULLUP);

  // Attach servo motors to corresponding pins
  myservos[0].attach(10); // arm rotation (left to right)
  myservos[1].attach(11); // arm extension (up to down)
  myservos[2].attach(12); // arm reach (lift and drop)
  myservos[3].attach(13); // claw (open and close)
  
  // Begin serial communication at 9600 baud rate
  Serial.begin(9600);
}

void moveServo(int servoIndex, int pin) {
  // Check if the button is pressed
  if (digitalRead(pin) == LOW) {
    // Increase the position by 1 step (if it's not already at maximum)
    pos[servoIndex] == 180 ?: pos[servoIndex]++;
    // Log the action
    Serial.println("Button pressed. Servo moved to HIGH");
  }
}

void moveOppositeServo(int servoIndex, int pin) {
  // Check if the button is pressed
  if (digitalRead(pin) == LOW) {
    // Decrease the position by 1 step (if it's not already at minimum)
    pos[servoIndex] == 0 ?: pos[servoIndex]--;
    // Log the action
    Serial.println("Button pressed. Servo moved to LOW");
  }
}

void updateServoPosition(int servoIndex) {
  // Get the current time in milliseconds
  unsigned long currentTime = millis();
  // Check if it's time to update the servo position
  if (currentTime - lastUpdate[servoIndex] >= updateInterval) {
    // Move the servo to the target position
    if (pos[servoIndex] < targetPos[servoIndex]) {
      pos[servoIndex] += movementSpeed; // Move the servo forward
    } else if (pos[servoIndex] > targetPos[servoIndex]) {
      pos[servoIndex] -= movementSpeed; // Move the servo backward
    }
    // Update the servo position
    myservos[servoIndex].write(pos[servoIndex]);
    // Update the last update time
    lastUpdate[servoIndex] = currentTime;
  }
}

void loop() {
  // Move the servos according to the button press
  moveServo(0, RotateLeftPin);  // RotateLeftPin
  moveOppositeServo(0, RotateRightPin);  // RotateRightPin
  moveServo(1, ExtendUpPin);  // ExtendUpPin
  moveOppositeServo(1, ExtendDownPin);  // ExtendDownPin
  moveServo(2, ReachDownPin);  // ReachDownPin
  moveOppositeServo(2, ReachUpPin);  // ReachUpPin
  moveServo(3, ClawOpenPin);  // ClawOpenPin
  moveOppositeServo(3, ClawClosePin);  // ClawClosePin
  
  // Update the position of each servo
  for (int i = 0; i < 4; i++) {
    updateServoPosition(i);
  }
  
  // Delay to control the loop speed
  delay(20);
}
