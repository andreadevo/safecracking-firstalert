//function to rotate dial with user input
void rotateDial() {
  Serial.println("Please enter a dial position between 0 and 99.");
  Serial.print("Enter dial position: ");
  while (!Serial.available());
  int dialPos = Serial.parseInt();    // where we want the dial to go

  Serial.print("You told me to go to ");
  Serial.println(dialPos);

  Serial.print("Current position: ");
  Serial.println(encoder0Pos);
  Serial.print("Desired position: ");
  Serial.println(dialPos);            // user input for dial position on safe
  if (dialPos > 99) {
    Serial.println("That number is not in the dial range. Please try again.");
  }
  else {
    dialPos = dialPos * 84;           // converts user input to be in encoder steps
    if (dialPos > encoder0Pos) {
      //Serial.println("CCW");
      digitalWrite(dirPin, LOW);     // CCW
      analogWrite(pwmPin, motorSpeed);
      while (encoder0Pos != dialPos);
      analogWrite(pwmPin, 0);
    }
    else {
      //Serial.println("CW");
      digitalWrite(dirPin, HIGH);     // CW
      analogWrite(pwmPin, motorSpeed);
      while (encoder0Pos != dialPos);
      analogWrite(pwmPin, 0);
    }
  }
}
