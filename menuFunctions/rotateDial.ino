////////////////////////////////////////
// ROTATES DIAL TO POSITION FROM USER //
////////////////////////////////////////

void rotateDial() {
  Serial.println("Please enter a dial position between 0 and 99.");
  Serial.print("Enter dial position: ");
  while (!Serial.available());
  int dialPos = Serial.parseInt();    // where we want the dial to go

  Serial.print("You told me to go to ");
  Serial.println(dialPos);

  Serial.print("Current position: ");
  Serial.println(encoder0Pos);
  Serial.print("Desired position: ");
  Serial.println(dialPos);            // user input for dial position on safe
  if (dialPos > 99) {
    Serial.println("That number is not in the dial range. Please try again.");
  }

  // takes into account shortest distance before choosing CW or CCW
  else {
    int destination = dialPos * ticks;           // converts user input to be in encoder steps
    int currentPosition = encoder0Pos / ticks;   //  converts encoder into dial number

    //find the largest number
    if (dialPos > currentPosition) {
      if (dialPos - currentPosition >= 50) {  // this would be the longer distance
        Serial.println("CW 1");
        setDir(CW);
        // check for case when user inputs 0
        if (dialPos = 0) {
          destination = 30;
        }
        analogWrite(pwmPin, motorSpeed);
        while (encoder0Pos != (destination - offset));
        analogWrite(pwmPin, 0);
      } else {
        Serial.println("CCW 1");
        setDir(CCW);
        analogWrite(pwmPin, motorSpeed);
        while (encoder0Pos != (destination + offset));
        analogWrite(pwmPin, 0);
      }
    }
    else {
      if (currentPosition - dialPos >= 50) {
        Serial.println("CCW 2");
        setDir(CCW);
        analogWrite(pwmPin, motorSpeed);
        while (encoder0Pos != (destination + offset));
        analogWrite(pwmPin, 0);
      } else {
        Serial.println("CW 2");
        setDir(CW);
        if (dialPos = 0) {
          destination = totalTicks;
        }
        analogWrite(pwmPin, motorSpeed);
        while (encoder0Pos != (destination - offset));
        analogWrite(pwmPin, 0);
      }
    }
  }
}


///////////////////////////////
// CHANGE DIRECTION OF MOTOR //
///////////////////////////////
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

//////////////////////////////////////////////////////////////////
// early code that does not take into account shortest distance //
//////////////////////////////////////////////////////////////////
//  else {
//    dialPos = dialPos * ticks;           // converts user input to be in encoder steps
//    if (dialPos > encoder0Pos) {      // if moving to a higher number
//      digitalWrite(dirPin, LOW);      // CCW, increase numbers
//      analogWrite(pwmPin, motorSpeed);
//      while (encoder0Pos != dialPos);
//      analogWrite(pwmPin, 0);
//    }
//    else {                            // else moving to a lower number
//      digitalWrite(dirPin, HIGH);     // CW, decrease numbers
//      analogWrite(pwmPin, motorSpeed);
//      while (encoder0Pos != dialPos);
//      analogWrite(pwmPin, 0);
//    }
//  }
//}
