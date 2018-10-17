/*
   Andrea DeVore
   Kenzy O'Neil
   Kendle McDowell
   Safecracking Class Fall 2018
   License: Open Source
*/

//setting

#include "nvm.h" //EEPROM locations for settings
#include <EEPROM.h> //For storing settings and things to NVM

const int encoder0PinA = 2;
const int encoder0PinB = 3;
volatile int encoder0Pos = 0;

const int dirPin = 5;         // outputs the direction to dir pin on motor controller
const int pwmPin = 6;         // outputs high/low to PWM pin on motor controller, controls if motor is on/off
const int switchPin = 4;      // input from the switch, on/pff
const int photoGatePin = 7;   // input pin from photogate

int switchState;              // current state of the switch
int photoState;               // current state of the photogate

bool stateAChange = false;    // check if change has happened on A
bool stateBChange = false;    // check if change has happened on B

int homePos;                  // tracks home positon of motor;

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

  Serial.begin(9600);
}

///////////////////////////////////////////////////////////////////////////////////

//USER INPUT
void loop() {
  byte incoming;

  //autohome the robot before launching the menu
  
  //LAUNCH MENU
  Serial.println("1)Dial position");
  Serial.println("2)Find home");
  Serial.println("3)Go home");
  Serial.println("4)Test Saved Combo");
  
  if (Serial.available()) {
    incoming = Serial.read();
    Serial.print("You pressed: ");
    Serial.write(incoming);

    //menu logic
    if (incoming == '1') {
      rotateDial();
    }
    else if (incoming == '2') {
      homePos = goHome();
      Serial.print("The home position is ");
      Serial.println(homePos / 84);
    }
    else if (incoming == '3'){
      Serial.print("Returning Dial to Home Position: ");
      Serial.println(homePos / 84);
      //returnHome();
    }
  }

  // CHECK IF ENCODER HAS MOVED
  if (stateAChange) {
    //Serial.print ("A ");
    //Serial.println (encoder0Pos, DEC);
    stateAChange = false;
  }
  if (stateBChange) {
    //Serial.print ("B ");
    //Serial.println (encoder0Pos, DEC);
    stateBChange = false;
  }
}

////////////////////////////////////////////////////////////////////////////////////

//ENCODER CODE
void doEncoderA() {
  stateAChange = true;
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos - 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos + 1;         // CCW
    }
  }
  // must be a high-to-low edge on channel A
  else   {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = encoder0Pos - 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos + 1;          // CCW
    }
  }

  // Reset counter
  if (encoder0Pos > 8399) {
    encoder0Pos = 1;
  }
  else if (encoder0Pos < 0) {
    encoder0Pos = 8400;
  }
}

void doEncoderB() {
  stateBChange = true;
  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0Pos = encoder0Pos - 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos + 1;         // CCW
    }
  }

  // Look for a high-to-low on channel B
  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos = encoder0Pos - 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos + 1;          // CCW
    }
  }

  // Reset counter
  if (encoder0Pos > 8399) {
    encoder0Pos = 0;
  }
  else if (encoder0Pos < 0) {
    encoder0Pos = 8400;
  }
}

//////////////////////////////////////////////////////////////////////////
