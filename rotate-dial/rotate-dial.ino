const int encoder0PinA = 2;
const int encoder0PinB = 3;
volatile int encoder0Pos = 0;

const int dirPin = 5;         // outputs the direction to dir pin on motor controller
const int pwmPin = 6;         // outputs high/low to PWM pin on motor controller, controls if motor is on/off

bool stateAChange = false;    // check if change has happened on A
bool stateBChange = false;    // check if change has happened on B

void setup() {
  // put your setup code here, to run once:
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

  Serial.begin(9600);

  // LAUNCH MENU
  Serial.println("d)Dial position");

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pwmPin, HIGH);
  digitalWrite(dirPin, LOW);

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
