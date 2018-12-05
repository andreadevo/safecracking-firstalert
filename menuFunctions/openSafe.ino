///////////////////////////////////////
//OPEN SAFE WITH CORRECT SAVED COMBO //
///////////////////////////////////////

void openSafe() {
  int nextNum;            // next position on dial
  int numRot;             // number of rotations
  int turnDir;            // direction turning

  // call function to rotate and stop on each number
  nextNumber(88, 5, CCW); //95
  delay(5000);
  nextNumber(27, 3, CW); //20
  delay(5000);
  nextNumber(37, 2, CCW); //41
  delay(5000);

  // moves to fourth combination number
  setDir(CW);
  analogWrite(pwmPin, motorSpeed); // motor on
  while(encoder0Pos != 10);
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
    while (encoder0Pos != nextNum * ticks);    // rotating until we find nextNum
    
    // change incrementing/decrementing ticks based on direction
    if (turnDir == 1){
      nextNum++;
    } else {
      nextNum--;
    }                  
  }
  analogWrite(pwmPin, 0);             // turn motor off
}
