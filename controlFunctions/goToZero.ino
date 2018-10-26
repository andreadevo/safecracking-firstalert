void goToZero(){
  Serial.print("Current Position: ");
  Serial.println(encoder0Pos);
  if(encoder0Pos > 4200){
    digitalWrite(dirPin, HIGH);   //CW
    digitalWrite(pwmPin, HIGH);  //start the motor
    while (encoder0Pos < 8399);
  }
  else{
    digitalWrite(dirPin, LOW);   //CCW
    digitalWrite(pwmPin, HIGH);  //start the motor
    while (encoder0Pos > 0);
  }
  digitalWrite(pwmPin, LOW);     //stop the motor
  Serial.println(encoder0Pos);
}
