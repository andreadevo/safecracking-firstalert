///////////////////////////////////////
//OPEN SAFE WITH CORRECT SAVED COMBO //
///////////////////////////////////////

void openSafe() {
  int nextNum;            // next position on dial
  int numRot;             // number of rotations
  int turnDir;            // direction turning

  // call function to rotate and stop on each number
  nextNumber(88, 5, 0);
  delay(500);
  nextNumber(27, 3, 1);
  delay(500);
  nextNumber(37, 2, 0);
  delay(500);

  // moves to fourth combination number
  digitalWrite(dirPin, HIGH); // CW
  analogWrite(pwmPin, motorSpeed); // motor on
  while(encoder0Pos != 7812);
  analogWrite(pwmPin, 0);
}


////////////////////////////////
// PUTS IN SINGLE COMBINATION //
////////////////////////////////

void nextNumber(int nextNum, int numRot, int turnDir) {
  nextNum = nextNum * 84;         // change to encoder values
  digitalWrite(dirPin, turnDir);  // takes turnDir and goes CW or CCW
  analogWrite(pwmPin, motorSpeed);     // turn motor on
  for (int i = 0; i < numRot; i++) { // tracking the amount of rotations
    while (encoder0Pos != nextNum);   // rotating until we find nextNum
    
    // change incrementing/decrementing ticks based on direction
    if (turnDir == 1){
      nextNum++;
    } else {
      nextNum--;
    }                  
  }
  analogWrite(pwmPin, 0);          // turn motor off
}
