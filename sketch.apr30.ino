#include <Boards.h>
#include <Firmata.h>
#include <FirmataConstants.h>
#include <FirmataDefines.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>
#include <Servo.h>

Servo myservos[4];          // Array to hold four servo objects
int pos[4] = { 90, 90, 90, 0 };  // Array to hold current position of each servo
int curPos[4];
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

void initializeArm(){
  for(int i=0;i<4;i++){
    curPos[i] = myservos[i].read();
    advanceServo(i,pos[i]);
    delay(20);
  }
}

void advanceServo(int servo, int degree){
  while(curPos[servo] != degree){
      curPos[servo] < degree ? curPos[servo]++ : curPos[servo]--;
      myservos[servo].write(curPos[servo]);
      delay(200);
    }
}


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
  
  initializeArm();
  
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
    myservos[servoIndex].write(pos[servoIndex]);
  }
}

void moveOppositeServo(int servoIndex, int pin) {
  // Check if the button is pressed
  if (digitalRead(pin) == LOW) {
    // Decrease the position by 1 step (if it's not already at minimum)
    pos[servoIndex] == 0 ?: pos[servoIndex]--;
    // Log the action
    Serial.println("Button pressed. Servo moved to LOW");
    myservos[servoIndex].write(pos[servoIndex]);
  }
}



void loop() {
  // Move the servos according to the button press
  //moveServo(0, RotateLeftPin);  // RotateLeftPin
  //moveOppositeServo(0, RotateRightPin);  // RotateRightPin
  //moveServo(1, ExtendUpPin);  // ExtendUpPin
  //moveOppositeServo(1, ExtendDownPin);  // ExtendDownPin
  //moveServo(2, ReachDownPin);  // ReachDownPin
  //moveOppositeServo(2, ReachUpPin);  // ReachUpPin
  //moveServo(3, ClawOpenPin);  // ClawOpenPin
  //moveOppositeServo(3, ClawClosePin);  // ClawClosePin
  

  
  // Delay to control the loop speed
  delay(20);
}




