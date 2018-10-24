//CREATES BASELINE FOR DIAL
void goHome() {
  // stop motor at photogate
  photoState = digitalRead(photoGatePin);
  digitalWrite(pwmPin, HIGH);     //turns motor on
  while (photoState == HIGH) {
    photoState = digitalRead(photoGatePin);
  }

  // save dial position in encoder steps
  digitalWrite(pwmPin, LOW);      // turns motor off
  flagPos = encoder0Pos;          // save the encoder position of the flag
  EEPROM.put(FLAG_LOCATION, flagPos);

  // user inputs location
  Serial.println("Where am I? ");
  while (!Serial.available());
  Serial.setTimeout(500);
  int incoming = Serial.parseInt();
  Serial.print("The dial position is ");
  Serial.println(incoming);

  // map
  encoder0Pos = incoming * 84;      // set encoder position to current location
  Serial.print("I am at: ");
  Serial.println(encoder0Pos);
  // go ccw to zero
  digitalWrite(dirPin, LOW);   //CCW
  digitalWrite(pwmPin, HIGH);
  while (encoder0Pos > 20) {
    //Serial.println(encoder0Pos);
  }
  digitalWrite(pwmPin, LOW);
  Serial.println(encoder0Pos);
}

