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
  if (digitalRead(encoder0PinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
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
  // Reset counter
  if (encoder0Pos > 8399) {
    encoder0Pos = 0;
  }
  else if (encoder0Pos < 0) {
    encoder0Pos = 8399;
  }
}
