/*
   Andrea DeVore
   Kenzy O'Neil
   Kendle McDowell
   Safecracking Class Fall 2018
   License: Open Source
*/


//IGNORE THIS UNTIL PCB COMES IN//
//dirPin = D10
//pwmPin = D6
//motorReset = D8
//photoPin = D5
//redButton = D7
//whiteButton = A1
//servoPin = D9
//buzzerPin = D11
//////////////////////////////////


//setting

#include "nvm.h" //EEPROM locations for settings
#include <EEPROM.h> //For storing settings and things to NVM

const int encoder0PinA = 2;
const int encoder0PinB = 3;
volatile int encoder0Pos = 0;

const int dirPin = 10;         // outputs the direction to dir pin on motor controller
const int pwmPin = 6;         // outputs high/low to PWM pin on motor controller, controls if motor is on/off
const int switchPin = 4;      // input from the switch, on/pff
const int photoGatePin = 5;   // input pin from photogate
const int buzzerPin = 11;

int switchState;              // current state of the switch
int photoState;               // current state of the photogate

bool stateAChange = false;    // check if change has happened on A
bool stateBChange = false;    // check if change has happened on B

int flagPos;                  // tracks home positon of motor;
int cwOffset;                 // clockwise offset from 0
int ccwOffset;                // counterclockwise offset from 0
int posZero;                  // zero on dial
int goToHome;
int motorSpeed = 50;

///////////////////////////////////////////////////////////////////////////////////////

void setup() {
  // SETUP FOR ENCODER
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  // SETUP FOR CONTROLS
  pinMode(dirPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

///////////////////////////////////////////////////////////////////////////////////////

//USER INPUT
void loop() {
  int incoming;

  //autohome the robot before launching the menu

  //LAUNCH MENU
  Serial.println("1)Dial position");
  Serial.println("2)Go home");
  Serial.println("3)Find home");
  Serial.println("4)Test Saved Combo");
  Serial.println("5)Access EEPROM");
  Serial.println("6)CCW");
  Serial.println("7)CW");

  while (!Serial.available());            // do nothing, wait for user input

  incoming = Serial.parseInt();
  Serial.print("You pressed: ");
  Serial.println(incoming);

  //menu logic
  if (incoming == 1) {
    // user inputs where to go
    rotateDial();
  }

  else if (incoming == 2) {
    // homes to flag, gets EEPROM
    findFlag();
    EEPROM.get(FLAG_LOCATION, goToHome);
    Serial.println(goToHome);
  }

  else if (incoming == 3) {
    // user inputs flag position, puts EEPROM
    findHome();
  }

  else if (incoming == 4) {
    // uses code to open safe
    openSafe();
  }

  else if (incoming == 5) {
    // change EEPROM values
    Serial.println("1)Change speed");
    Serial.println("2)Change combination");
  }
  else if (incoming == 6) {
    digitalWrite(dirPin, LOW);      // CCW
    analogWrite(pwmPin, motorSpeed);

    photoState = digitalRead(photoGatePin);
    analogWrite(pwmPin, motorSpeed);     // turns motor on
    while (photoState == HIGH) {
      photoState = digitalRead(photoGatePin);
    }
    digitalWrite(pwmPin, LOW);      // turns motor off
  }
  else if (incoming == 7) {
    digitalWrite(dirPin, HIGH);     // CW
     analogWrite(pwmPin, motorSpeed);

    photoState = digitalRead(photoGatePin);
    analogWrite(pwmPin, motorSpeed);     // turns motor on
    while (photoState == HIGH) {
      photoState = digitalRead(photoGatePin);
    }
    digitalWrite(pwmPin, LOW);      // turns motor off
  }

  encoderState();     // check if encoder state has changed
}
