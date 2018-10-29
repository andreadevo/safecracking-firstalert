//OPEN SAFE WITH CORRECT SAVED COMBO
void openSafe(){
  int steps = 8380;
  int nextNum = 97;           // next position on dial 
  goToZero();                 //dial is at encoder position 0
  
  // clear dial 
  digitalWrite(dirPin, LOW);   //CCW
  digitalWrite(pwmPin, HIGH);  //motor on

  //want to do 4 rotations, 8400 * 4
  //to move in encoder steps we add int steps to encoder0Pos and move there with a while loop
  for(int i=0; i < 4; i++){       //tracking the amount of rotations
    while(encoder0Pos < steps); //turn until we hit 8380
    steps++;
  }
  digitalWrite(pwmPin, LOW);
}

