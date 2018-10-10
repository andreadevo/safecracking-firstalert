/*
   Andrea DeVore
   Kenzy O'Neil
   Kendle
   Safecracking Class Fall 2018
   License: Open Source
*/

const int encoder0PinA = 2;
const int encoder0PinB = 3;
volatile unsigned int encoder0Pos = 0;

const int dirPin = 5;         // outputs the direction to dir pin on motor controller
const int pwmPin = 6;         // outputs high/low to PWM pin on motor controller, controls if motor is on/off
const int switchPin = 4;      // input from the switch, on/pff
const int photoGatePin = 7;   // input pin from photogate

int switchState;              // current state of the switch
int photoState;               // current state of the photogate

bool stateAChange = false;    // check if change has happened on A
bool stateBChange = false;    // check if change has happened on B

int homePos;                  // tracks home positon of motor;

/////////////////////////////////////////////////////////////////////////////////////////////////////

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

  //LAUNCH MENU
  Serial.println("d)Dial position");
  Serial.println("h)Go home");

}

///////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  //USER INPUT
  byte incoming;
  if (Serial.available()) {
    incoming = Serial.read();
    Serial.print("You pressed: ");
    Serial.write(incoming);

    // ROTATE DIAL TO USER INPUT
    if (incoming == 'd') {
      rotateDial();
    }
    else if (incoming == 'h') {
      homePos = goHome();
      Serial.print("The home position is ");
      Serial.println(homePos);
    }
  }

  // CHECK IF ENCODER HAS MOVED
  if (stateAChange) {
    Serial.print ("A ");
    Serial.println (encoder0Pos, DEC);
    stateAChange = false;
  }
  if (stateBChange) {
    Serial.print ("B ");
    Serial.println (encoder0Pos, DEC);
    stateBChange = false;
  }
}

////////////////////////////////////////////////////////////////////////////////////

void launchMenu() {
  Serial.println("d)Dial position");
  Serial.println("h)Go home");
}

////////////////////////////////////////////////////////////////////////////////////

//CREATES BASELINE FOR DIAL
int goHome() {
  photoState = digitalRead(photoGatePin);
  Serial.println("Photostate reads: ");
  Serial.print(photoState);

  digitalWrite(pwmPin, HIGH);     //turns motor on
  while (photoState == HIGH) {
    photoState = digitalRead(photoGatePin);
  }
  digitalWrite(pwmPin, LOW);      // turns motor off
  homePos = encoder0Pos;
  return (homePos);               // returns home position
}

/////////////////////////////////////////////////////////////////////////////////

void rotateDial() {
  Serial.println("Use positive number for CW nd neg numbers for CCW.");
  Serial.print("Enter dial position: ");
  while (!Serial.available());
  int dialPos = Serial.parseInt();    // where we want the dial to go

  Serial.print("You told me to go to ");
  Serial.println(dialPos);
  
  Serial.print("Current position: ");
  Serial.println(encoder0Pos);
  Serial.print("Desired position: ");
  Serial.println(dialPos * 86);       // converts user input to be in encoder steps
  if (dialPos > encoder0Pos) {
    // CW
    Serial.println("CW");
    digitalWrite(dirPin, HIGH);
    while (encoder0Pos != dialPos) {
      digitalWrite(pwmPin, HIGH);
    }
    digitalWrite(pwmPin, LOW);
  }
  else {
    // CCW
    //dialPos = 8600 - (dialPos * 86);  // converts user input to be in encoder steps
    Serial.print("CCW");
    digitalWrite(dirPin, LOW);
    while (encoder0Pos != dialPos) {
      digitalWrite(pwmPin, HIGH);
    }
    digitalWrite(pwmPin, LOW);
  }
}

////////////////////////////////////////////////////////////////////////////////////

//USES SWITCH TO CHANGE DIRECTION
void manualDirectionChange() {
  switchState = digitalRead(switchPin);
  if (switchState == HIGH) {
    // switch on, CW
    digitalWrite(dirPin, HIGH);
  }
  else {
    // switch off, CCW
    digitalWrite(dirPin, LOW);
  }
}

////////////////////////////////////////////////////////////////////////////////////

// ENCODER CODE
// encoder code from: playground.arduino.cc/Main/RotaryEncoders
void doEncoderA() {
  stateAChange = true;
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  // must be a high-to-low edge on channel A
  else   {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}

void doEncoderB() {
  stateBChange = true;
  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }

  // Look for a high-to-low on channel B
  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}

//////////////////////////////////////////////////////////////////////////

int convertToSteps(int encoderPos) {
  //check for home, if no home, set start to 0
  //if homed, offset step from 0
  //take encoder values
}

//////////////////////////////////////////////////////////////////////////
