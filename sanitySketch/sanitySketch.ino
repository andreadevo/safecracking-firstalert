//sanity sketch
//turns full rotation
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
int motorSpeed = 150;          // speed from 0-255, written to pwmPin

boolean currentDirection = 0;
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

void loop() {
  int fullRot = encoder0Pos - 1;
  Serial.println("Start: ");
  Serial.println(encoder0Pos);
  setDir(CCW);
  
  analogWrite(pwmPin, motorSpeed);     // turns motor on
  while (encoder0Pos != 8400 - (2*84));
  digitalWrite(pwmPin, LOW);      // turns motor off
  Serial.print("Stop: ");
  Serial.println(encoder0Pos);
  while (1);
}

void setDir(byte dir) {
  if (dir == CCW) {
    digitalWrite(dirPin, LOW);
    currentDirection = CW;
  }
  else if (dir == CW) {
    digitalWrite(dirPin, HIGH);
    currentDirection = HIGH;
  }
}

