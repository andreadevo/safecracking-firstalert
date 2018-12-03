////////////////////////////////////////
// ROTATES DIAL TO POSITION FROM USER //
////////////////////////////////////////

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

  // takes into account shortest distance before choosing CW or CCW
  else {
    int destination = dialPos * 84;           // converts user input to be in encoder steps
    int currentPosition = encoder0Pos / 84;   //  converts encoder into dial number

    //find the largest number
    if (dialPos > currentPosition) {
      if (dialPos - currentPosition >= 50) {  // this would be the longer distance
        digitalWrite(dirPin, HIGH);     // CW
        analogWrite(pwmPin, motorSpeed);
        while (encoder0Pos != destination) {
//          Serial.println(encoder0Pos);
        }
        analogWrite(pwmPin, 0);
      }
      else {
        digitalWrite(dirPin, LOW);      // CCW
        analogWrite(pwmPin, motorSpeed);
        while (encoder0Pos != destination) {
//          Serial.print ("A ");
//          Serial.println (encoder0Pos, DEC);
        }
        analogWrite(pwmPin, 0);
      }
    }
    else {
      if (currentPosition - dialPos >= 50) {
        digitalWrite(dirPin, LOW);     // CCW
        analogWrite(pwmPin, motorSpeed);
        while (encoder0Pos != destination) {
//          Serial.print ("A ");
//          Serial.println (encoder0Pos, DEC);
        }
        analogWrite(pwmPin, 0);
      }
      else {
        digitalWrite(dirPin, HIGH);      // CW
        analogWrite(pwmPin, motorSpeed);
        while (encoder0Pos != destination) {
//          Serial.print ("A ");
//          Serial.println (encoder0Pos, DEC);
        }
        analogWrite(pwmPin, 0);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////
// early code that does not take into account shortest distance //
//////////////////////////////////////////////////////////////////
//  else {
//    dialPos = dialPos * 84;           // converts user input to be in encoder steps
//    if (dialPos > encoder0Pos) {      // if moving to a higher number
//      digitalWrite(dirPin, LOW);      // CCW, increase numbers
//      analogWrite(pwmPin, motorSpeed);
//      while (encoder0Pos != dialPos);
//      analogWrite(pwmPin, 0);
//    }
//    else {                            // else moving to a lower number
//      digitalWrite(dirPin, HIGH);     // CW, decrease numbers
//      analogWrite(pwmPin, motorSpeed);
//      while (encoder0Pos != dialPos);
//      analogWrite(pwmPin, 0);
//    }
//  }
//}
