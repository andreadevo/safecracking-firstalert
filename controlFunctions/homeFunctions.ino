//CREATES HOMING BASELINE FOR DIAL
void findHome() {
  // user inputs flag position
  goHome();

  // user inputs location
  Serial.println("Where am I? ");
  while (!Serial.available());
  Serial.setTimeout(500);
  int incoming = Serial.parseInt();
  Serial.print("The dial position is ");
  Serial.println(incoming);

  // map to the dial
  encoder0Pos = incoming * 84;      // set encoder position to current location
  Serial.print("I am at: ");
  Serial.println(encoder0Pos);

  //save to EEPROM
  EEPROM.put(FLAG_LOCATION, encoder0Pos);

  // go ccw to zero
  goToZero();
}

void goHome() {
  // home flag, get previous user input
  photoState = digitalRead(photoGatePin);
  digitalWrite(pwmPin, HIGH);     //turns motor on
  while (photoState == HIGH) {
    photoState = digitalRead(photoGatePin);
  }
  digitalWrite(pwmPin, LOW);      // turns motor off
}

