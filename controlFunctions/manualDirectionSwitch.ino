//USES SWITCH TO CHANGE DIRECTION
void manualDirectionChange() {
  switchState = digitalRead(switchPin);
  if (switchState == HIGH) {
    // switch on, CW
    digitalWrite(dirPin, HIGH);
  }
  else {
    // switch off, CCW
    digitalWrite(dirPin, LOW);
  }
}
