// CHECK IF ENCODER HAS MOVED
//playground.arduino.cc/Main/Rotary/Encoders

void encoderState() {
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

//ENCODER CODE
void doEncoderA() {
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
  
  //Serial.print("A: ");
  //Serial.println(encoder0Pos);
}

void doEncoderB() {
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

  // Reset counter
  if (encoder0Pos > 8399) {
    encoder0Pos = 0;
  }
  else if (encoder0Pos < 0) {
    encoder0Pos = 8399;
  }
  //Serial.print("B: ");
  //Serial.println(encoder0Pos);
}
