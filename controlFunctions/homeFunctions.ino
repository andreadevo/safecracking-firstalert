//CREATES HOMING BASELINE FOR DIAL
void findHome() {
  // user inputs flag position
  findFlag();

  // user inputs location
  Serial.print("Encoder Position: ");
  Serial.println(encoder0Pos);
  Serial.println("Where am I? ");
  while (!Serial.available());
  Serial.setTimeout(500);
  int incoming = Serial.parseInt();
  Serial.print("The dial position is ");
  Serial.println(incoming);

  // map to the dial
  encoder0Pos = incoming * 84;      // set encoder position to current location
  Serial.print("I am at: ");
  Serial.println(encoder0Pos / 84);

  //save to EEPROM
  goToHome = encoder0Pos;           // can't save a volatile int to EEPROM, so save to new variable
  EEPROM.put(FLAG_LOCATION, goToHome);

  digitalWrite(dirPin, LOW);
  analogWrite(pwmPin, motorSpeed);
  while (encoder0Pos != 20);
  analogWrite(pwmPin, 0);
  Serial.println(encoder0Pos);


  //rotateDial();
}

void findFlag() {
  // home flag, get previous user input
  photoState = digitalRead(photoGatePin);
  analogWrite(pwmPin, motorSpeed);     // turns motor on
  while (photoState == HIGH) {
    photoState = digitalRead(photoGatePin);
  }
  digitalWrite(pwmPin, LOW);      // turns motor off
}

