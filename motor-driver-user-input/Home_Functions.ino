//CREATES BASELINE FOR DIAL
int goHome() {
  photoState = digitalRead(photoGatePin);
  Serial.println("Photostate reads: ");
  Serial.print(photoState);

  digitalWrite(pwmPin, HIGH);     //turns motor on
  while (photoState == HIGH) {
    photoState = digitalRead(photoGatePin);
  }
  digitalWrite(pwmPin, LOW);      // turns motor off
  homePos = encoder0Pos;
  return (homePos);               // returns home position
}

void returnHome(){
  //move dial to homePos or move dial until it breaks the photogate 
}

