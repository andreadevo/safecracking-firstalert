//////////////////////////////////////////////////
// ALGORITHM TO TEST EVERY POSSIBLE COMBINATION //
//////////////////////////////////////////////////

void crackTheSafe() {
  //repeatedly calls function to put in 3 digit combo for every solution
  for (int i = 3; i < 97; i++) {
    for (int j = 63; j < 97; j++) {
      nextNumber(98, 5, CCW);
      delay(500);
      nextNumber(i, 3, CW);
      delay(500);
      nextNumber(j, 2, CCW);
      delay(500);
      if (checkIfOpen()) {
        return;
      }
    }
  }
}


////////////////////////////////
// CHECKS IF THE SAFE IS OPEN //
////////////////////////////////

bool checkIfOpen() {
  //function turns dial CW to zero and then some
  //checks if safe is open
  setDir(CW);
  analogWrite(pwmPin, motorSpeed / 4);
  while (encoder0Pos != 20);
  analogWrite(pwmPin, motorSpeed / 8);
  delay(750);
  analogWrite(pwmPin, 0);
  if (encoder0Pos > 7800) {
    Serial.println(encoder0Pos);
    winState();
    win = true;
    return true;
  }
  else {
    Serial.println(encoder0Pos);
    return false;
  }
}


//////////////////////////////
//// CELEBRATES OPENED SAFE //
//////////////////////////////

void winState() {
    tone(buzzerPin, 1000);
    delay(300);
    noTone(buzzerPin);
    tone(buzzerPin, 1000);
    delay(300);
    noTone(buzzerPin);
    tone(buzzerPin, 1000);
    delay(250);
    noTone(buzzerPin);
    tone(buzzerPin, 1600);
    delay(500);
    tone(buzzerPin, 1500);
    delay(250);
    tone(buzzerPin, 1600);
    delay(500);
    noTone(buzzerPin);
}

