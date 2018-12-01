//OPEN SAFE WITH CORRECT SAVED COMBO
void openSafe() {
  int steps = 1;
  int nextNum = 88;           // next position on dial
  int numRot = 5;             // number of rotations
  int turnDir = 0;            // direction turning

  nextNumber(nextNum, numRot, turnDir);     // goes to next number in combo
  delay(5000);
  nextNumber(27, 3, 1);
  delay(5000);
  nextNumber(37, 2, 0);
  delay(5000);
  
  digitalWrite(dirPin, HIGH); // CW
  analogWrite(pwmPin, motorSpeed); // motor on
  while(encoder0Pos != 7812);
  analogWrite(pwmPin, 0);
}

void nextNumber(int nextNum, int numRot, int turnDir) {
  nextNum = nextNum * 84;         // change to encoder values
  digitalWrite(dirPin, turnDir);  // takes turnDir and goes CW or CCW
  analogWrite(pwmPin, motorSpeed);     // turn motor on
  for (int i = 0; i < numRot; i++) { // tracking the amount of rotations
    while (encoder0Pos != nextNum);   // rotating until we find nextNum
//    Serial.println(encoder0Pos);
    // change incrementing/decrementing ticks based on direction
    if (turnDir == 1){
      nextNum++;
    } else {
      nextNum--;
    }                  
  }
  analogWrite(pwmPin, 0);          // turn motor off
  tone(buzzerPin, 1000);
  delay(500);
  noTone(buzzerPin);
  //Serial.println(encoder0Pos);
}
