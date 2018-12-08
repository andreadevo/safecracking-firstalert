////////////////////////////////////////
// ROTATES DIAL TO POSITION FROM USER //
////////////////////////////////////////

void rotateDial() {
  Serial.println("Please enter a dial position between 0 and 99.");
  Serial.print("Enter dial position: ");
  while (!Serial.available());
  int dialPos = Serial.parseInt();    // where we want the dial to go
  int posDiff = 0;
  Serial.print("You told me to go to ");
  Serial.println(dialPos);

  Serial.print("Current position: ");
  Serial.println(encoder0Pos);
  Serial.print("Desired position: ");
  Serial.println(dialPos);

  // CHECK IF VALID INPUT
  if (dialPos > 99) {
    Serial.println("That number is not in the dial range. Please try again.");
  }

  // takes into account shortest distance before choosing CW or CCW
  else {
    int destination = dialPos * ticks;           // converts user input to be in encoder steps
    int currentPosition = encoder0Pos / ticks;   //  converts encoder into dial number

    // find the largest number
    if (dialPos > currentPosition) {
      posDiff = dialPos - currentPosition;
      if (posDiff >= 50) {
        Serial.println("CW 1");
        moveDialCW(destination, posDiff);
      } else {
        Serial.println("CCW 1");
        moveDialCCW(destination, posDiff);
      }
    }
    else {
      posDiff = currentPosition - dialPos;
      if (posDiff >= 50) {
        Serial.println("CCW 2");
        moveDialCCW(destination, posDiff);
      } else {
        Serial.println("CW 2");
        moveDialCW(destination, posDiff);
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
    currentDirection = CCW;
  }
  else if (dir == CW) {
    digitalWrite(dirPin, HIGH);
    currentDirection = CW;
  }
}

//////////////////////////////
// SLOW DOWN CALIBRATION CW //
//////////////////////////////

//if we are going CW then the numbers are decreasing
//this means we need to slow down at numbers higher than our desired dial position
//we must make an initial check for the points at which we slow down
//then we can call our slowdown function at those points
//we do not really need to have cases if we are always doing at least one full rotation before each dial position
//we will always have 30 dial positions before the number we're trying to reach

void moveDialCW(int destination, int posDiff) {
  setDir(CW);
  // slowdown function based on dial position
  if (posDiff <= 20) {
    slowDown(4);
    while (encoder0Pos != destination - offset);
    analogWrite(pwmPin, 0);
  }
  else if (posDiff <= 60) {
    slowDown(2);
    while (encoder0Pos != (destination + (ticks * 20)));
    slowDown(4);
    while (encoder0Pos != destination - offset);
    analogWrite(pwmPin, 0);
  }
  else {
    analogWrite(pwmPin, motorSpeed);
    while (encoder0Pos != (destination + (ticks * 40)));
    slowDown(2);
    while (encoder0Pos != (destination + (ticks * 20)));
    slowDown(4);
    while (encoder0Pos != destination - offset);
    analogWrite(pwmPin, 0);
  }
}

///////////////////////////////
// SLOW DOWN CALIBRATION CCW //
///////////////////////////////

//if we are going CCW then the numbers are increasing
//this means we need to slow down at numbers lower than our desired dial position

void moveDialCCW(int destination, int posDiff) {
  setDir(CCW);
  // slowdown function based on dial position
  if (posDiff <= 20) {
    slowDown(4);
    while (encoder0Pos != (destination + offset));
    analogWrite(pwmPin, 0);
  }
  else if (posDiff <= 60) {
    slowDown(2);
    while (encoder0Pos != (destination - (ticks * 20)));
    slowDown(4);
    while (encoder0Pos != (destination + offset));
    analogWrite(pwmPin, 0);
  }
  else {
    analogWrite(pwmPin, motorSpeed);
    while (encoder0Pos != (destination - (ticks * 40)));
    slowDown(2);
    while (encoder0Pos != (destination - (ticks * 20)));
    slowDown(4);
    while (encoder0Pos != (destination + offset));
    analogWrite(pwmPin, 0);
  }
}

///////////////
// SLOW DOWN //
///////////////

void slowDown(int var) {
  analogWrite(pwmPin, motorSpeed / var);
}


