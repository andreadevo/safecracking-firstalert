/*
   Andrea DeVore
   Kenzy O'Neil
   Kendle McDowell
   Safecracking Class Fall 2018
   License: Open Source
*/

//Key for PCB Pins//////////
//  dirPin = D10          //
//  pwmPin = D6           //
//  motorReset = D8       //
//  photoPin = D5         //
//  redButton = D7        //
//  whiteButton = A1      //
//  servoPin = D9         //
//  buzzerPin = D11       //
////////////////////////////

#include "nvm.h" //EEPROM locations for settings
#include <EEPROM.h> //For storing settings and things to NVM

const int encoder0PinA = 2;
const int encoder0PinB = 3;
volatile int encoder0Pos = 0;

const int dirPin = 10;        // outputs the direction to dir pin on motor controller
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
int goToHome;                 // saving home
int motorSpeed = 200;         // speed from 0-255, written to pwmPin
const int ticks = 85;         // number of ticks per dial position
int totalTicks = (ticks * 99) - 1; //total number of ticks in a rotation
int offset = 20;
bool win = false;


boolean currentDirection = 0; // track the direction to encoder
const byte CW = 0;
const byte CCW = 1;


///////////
// SETUP //
///////////

void setup() {
  // encoder setup
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



/////////////////////////
// LAUNCH MENU OPTIONS //
/////////////////////////

void loop() {
  int incoming;
  Serial.println("1)Home the Dial");
  Serial.println("2)Enter Dial Position");
  Serial.println("3)Test Saved Combo");
  Serial.println("4)Crack the Safe");
  Serial.println("5)Access EEPROM");
  Serial.println("6)CCW");
  Serial.println("7)CW");

  while (!Serial.available());            // do nothing, wait for user input

  incoming = Serial.parseInt();
  Serial.print("You pressed: ");
  Serial.println(incoming);

  ///////////////
  // MAIN MENU //
  ///////////////

  // ---------- HOME THE DIAL ----------
  if (incoming == 1) {
    // user inputs flag position, puts to EEPROM, maps the encoder to the dial
    findHome();
  }

  // ---------- ENTER THE DIAL POSITION ----------
  else if (incoming == 2) {
    // user inputs where to go
    rotateDial();
  }

  // ---------- TEST SAVED COMBO ----------
  else if (incoming == 3) {
    // uses code to open safe with a saved combo
    openSafe();
  }

  // ---------- CRACK THE SAFE ----------
  else if (incoming == 4) {
    // calls function to guess every combination until it finds the correct one
    while (win == false)
      crackTheSafe();
  }

  // ---------- ACCESS EEPROM ----------
  else if (incoming == 5) {
    // change EEPROM values
    int subIncoming;
    Serial.println("1)Change speed");
    Serial.println("2)Change combination");

    while (!Serial.available());            // do nothing, wait for user input
    subIncoming = Serial.parseInt();
    Serial.print("You pressed: ");
    Serial.println(subIncoming);

    if (subIncoming == 1) {
      Serial.println("Change speed");
    }
    else if (subIncoming == 2) {
      Serial.println("Change combination");
    }
    else {
      Serial.println("Not a valid menu option. Please try again.");
    }
  }

  // ---------- CCW ----------
  else if (incoming == 6) {
    setDir(CCW);
    analogWrite(pwmPin, motorSpeed);
    photoState = digitalRead(photoGatePin);
    analogWrite(pwmPin, motorSpeed);     // turns motor on
    while (photoState == HIGH) {
      photoState = digitalRead(photoGatePin);
    }
    digitalWrite(pwmPin, LOW);          // turns motor off
  }

  // ---------- CW ----------
  else if (incoming == 7) {
    setDir(CW);
    photoState = digitalRead(photoGatePin);
    analogWrite(pwmPin, motorSpeed);    // turns motor on
    while (photoState == HIGH) {
      Serial.println (encoder0Pos, DEC);
      photoState = digitalRead(photoGatePin);
    }
    digitalWrite(pwmPin, LOW);          // turns motor off
  }

  // ---------- DEFAULT: TRY AGAIN ----------
  else {
    Serial.println("Not a valid menu option. Please try again.");
  }
}
