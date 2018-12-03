//////////////////////////////
// CREATES MAPPING FOR DIAL //
//////////////////////////////

void findHome() {
  findFlag();

  // user inputs location on dial
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
  Serial.println(encoder0Pos);

  //ask user to confirm the dial is mapped correctly
  Serial.println("Am I at 0?");
  Serial.println("'0' for NO");
  Serial.println("'1' for YES");
  while (!Serial.available());
  Serial.setTimeout(500);
  incoming = Serial.parseInt();
  
  if(incoming == 0) {                 // if the dial is not at 0 remap
    Serial.println("Where am I?");    // ask the user for the current dial position
    while (!Serial.available());
    Serial.setTimeout(500);
    incoming = Serial.parseInt();
    int currentPos = incoming * 84;   // convert user input to encoder values
    encoder0Pos = currentPos;         // reset encoder to user given position
    goToZero();                       // call goToZero to check the dial mapping again, keeps checking until the dial is mapped
  }
  else {                              // if the dial is at 0 exit
    Serial.println("The dial has been mapped correctly.");
  }
}

