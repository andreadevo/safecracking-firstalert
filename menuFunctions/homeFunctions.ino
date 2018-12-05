//////////////////////////////
// CREATES MAPPING FOR DIAL //
//////////////////////////////

void findHome() {
  findFlag();

  // user inputs location on dial
  Serial.println(encoder0Pos);
  Serial.println("Where am I? ");
  while (!Serial.available());
  Serial.setTimeout(500);
  int incoming = Serial.parseInt();
  Serial.print("The dial position is ");
  Serial.println(incoming);

  // map to the dial
  encoder0Pos = incoming * ticks;      // set encoder position to current location
  Serial.print("I am at: ");
  Serial.println(encoder0Pos);

  // move dial to zero to check mapping
  goToZero();
}


///////////////////////////////////////
// FINDS THE FLAG WITH THE PHOTOGATE //
///////////////////////////////////////

void findFlag() {
  // home flag, get previous user input
  photoState = digitalRead(photoGatePin);
  analogWrite(pwmPin, motorSpeed);     // turns motor on
  while (photoState == HIGH) {
    photoState = digitalRead(photoGatePin);
  }
  digitalWrite(pwmPin, LOW);      // turns motor off
}


///////////////////////////////////////////
// MOVES DIAL TO ZERO AND CHECKS MAPPING //
///////////////////////////////////////////

void goToZero() {
  int incoming;
  
  digitalWrite(dirPin, LOW);
  analogWrite(pwmPin, motorSpeed);
  while (encoder0Pos != 20);
  analogWrite(pwmPin, 0);
  if (encoder0Pos != 20){
    digitalWrite(dirPin, HIGH);
    analogWrite(pwmPin, motorSpeed/4);
    while (encoder0Pos != 20);
    analogWrite(pwmPin, 0);
  }
}

