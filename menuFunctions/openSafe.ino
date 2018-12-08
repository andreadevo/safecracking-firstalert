///////////////////////////////////////
//OPEN SAFE WITH CORRECT SAVED COMBO //
///////////////////////////////////////

void openSafe() {
  int nextNum;            // next position on dial
  int numRot;             // number of rotations
  int turnDir;            // direction turning

  // call function to rotate and stop on each number
  nextNumber(97, 5, CCW);
  delay(5000);
  nextNumber(7, 3, CW);
  delay(5000);
  nextNumber(67, 2, CCW);
  delay(5000);

  // moves to fourth combination number
  setDir(CW);
  analogWrite(pwmPin, (motorSpeed/4)); // motor on
  while (encoder0Pos != 10);
  analogWrite(pwmPin, 0);
}


////////////////////////////////
// PUTS IN SINGLE COMBINATION //
////////////////////////////////

void nextNumber(int nextNum, int numRot, byte turnDir) {
  int destination = nextNum * ticks;
  int posDiff = 0;
  setDir(turnDir);
  analogWrite(pwmPin, motorSpeed);     // turn motor on
  for (int i = 0; i < numRot; i++) {   // tracking the amount of rotations
    //call slowdown ticks
    if (i == (numRot - 1)) {
      slowDown(4);
      while (encoder0Pos != (nextNum * ticks));
    }
    else if (i == (numRot - 2)) {
      slowDown(2);
      while (encoder0Pos != (nextNum * ticks));
    }
    else {
      while (encoder0Pos != (nextNum * ticks));    // rotating until we find nextNum
    }
    // change incrementing/decrementing ticks based on direction
    if (turnDir == CW) {
      nextNum += 1;
    } else {
      nextNum -= 1;
    }
  }
  analogWrite(pwmPin, 0);             // turn motor off
}
