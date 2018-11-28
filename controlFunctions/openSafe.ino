//OPEN SAFE WITH CORRECT SAVED COMBO
void openSafe() {
  int steps = 1;
  int nextNum = 3;           // next position on dial
  int numRot = 5;             // number of rotations
  int turnDir = 0;            // direction turning
  goToZero();                 // dial is at encoder position 0
  nextNumber(nextNum, numRot, turnDir);     // goes to next number in combo
  delay(1000);
  nextNumber(32, 3, 1);
  delay(1000);
  nextNumber(56, 2, 0);
  delay(1000);
  
  digitalWrite(dirPin, HIGH); // CW
  analogWrite(pwmPin, motorSpeed); // motor on
  while(encoder0Pos != 0);
  analogWrite(pwmPin, 0);
}

void nextNumber(int nextNum, int numRot, int turnDir) {
  nextNum = nextNum * 84;         // change to encoder values
  digitalWrite(dirPin, turnDir);  // CCW
  analogWrite(pwmPin, motorSpeed);     // turn motor on
  for (int i = 0; i < numRot; i++) { // tracking the amount of rotations
    while (encoder0Pos != nextNum);   // rotating until we find nextNum
    Serial.println(encoder0Pos);
    // change incrementing/decrementing ticks based on direction
    if (turnDir == 1){
      nextNum--;
    } else {
      nextNum++;
    }                  
  }
  analogWrite(pwmPin, 0);          // turn motor on
  Serial.println(encoder0Pos);
}
