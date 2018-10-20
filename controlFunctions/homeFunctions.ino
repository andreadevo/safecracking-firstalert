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
  flagPos = encoder0Pos;          // save the encoder position of the flag
  Serial.println("Where am I? ");
  while(!Serial.available());
  Serial.setTimeout(500);
  int incoming = Serial.parseInt();
  Serial.print("The dial position is ");
  Serial.println(incoming);
  ccwOffset = 8400 - encoder0Pos;
  cwOffset = encoder0Pos;
  EEPROM.put(LOCATION_HOME_CW_OFFSET, incoming*84);
  return (flagPos);               // returns home position
}

void returnHome(){
  //move dial to homePos or move dial until it breaks the photogate
  //find home position variable
  //move motor to encoder position based on closeness
}

