//playground.arduino.cc/Main/Rotary/Encoders

////////////////////////////////
// CHECK IF ENCODER HAS MOVED //
////////////////////////////////

void encoderState() {
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

////////////////////
// ENCODER A CODE //
////////////////////

void doEncoderA() {
  // look for a low-to-high on channel A
  stateAChange = true;
  if (currentDirection == CW) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }

  // Reset counter
  if (encoder0Pos > 8399) {
    encoder0Pos = 0;
  }
  else if (encoder0Pos < 0) {
    encoder0Pos = 8399;
  }
}

////////////////////
// ENCODER B CODE //
////////////////////

void doEncoderB() {
  // look for a low-to-high on channel B
  stateBChange = true;
  if (currentDirection == CW) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }
  // Reset counter
  if (encoder0Pos > 8399) {
    encoder0Pos = 0;
  }
  else if (encoder0Pos < 0) {
    encoder0Pos = 8399;
  }
}
