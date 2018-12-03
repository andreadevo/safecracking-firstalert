//////////////////////////////////////////////////
// ALGORITHM TO TEST EVERY POSSIBLE COMBINATION //
//////////////////////////////////////////////////

void crackTheSafe(){
   // do some math to decide what the first number is
   // for-loop
   // call checkCombinations for every i
   // what happens when winState is called in the middle of this for-loop?
   // is the for-loop still waiting?
}


////////////////////////////////////////////////////////
// CHECKS ALL COMBINATIONS WITH THE SAME FIRST NUMBER //
////////////////////////////////////////////////////////

void checkCombinations(firstCombo) {
  //calls checkIfOpen for every combination
  //if(true) save to EEPROM and call winState()
  //else keep going until we decide firstCombo is not a solution
}


////////////////////////////////
// CHECKS IF THE SAFE IS OPEN //
////////////////////////////////

bool checkIfOpen() {
  // moves dial CW full rotation plus some (103 or 104 numbers)
  // if it moves past 105 numbers it is not open
  digitalWrite(dirPin, HIGH); // CW
  analogWrite(pwmPin, motorSpeed); // motor on
  while(???); // stop the motor after the encoder has stopped changing values
  analogWrite(pwmPin, 0);

  // return whether or not safe is open
  if() {
    return true;
  }
  else {
    return false;
  }
}


////////////////////////////
// CELEBRATES OPENED SAFE //
////////////////////////////

void winState() {
  // Serial.print the combination
  tone(buzzerPin, 1000);
  delay(10000);
  noTone(buzzerPin);
  // should break out of everything
}

