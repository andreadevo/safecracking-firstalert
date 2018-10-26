//OPEN SAFE WITH CORRECT SAVED COMBO
void openSafe(){
  int count = 0;
  int nextNum = 97;           // next position on dial 
  int stopPos = 20;
  goToZero();
  
  // clear dial 
  digitalWrite(dirPin, LOW);   //CCW
  digitalWrite(pwmPin, HIGH);  //motor on
  
  for (int i=0; i<4; i++){
    while (encoder0Pos != 20);
//    stopPos = stopPos - 2;
    //Serial.println('h');
  }
  digitalWrite(pwmPin, LOW);    // turn motor off
  Serial.println(encoder0Pos);
 
//  digitalWrite(pwmPin, LOW);  //turn motor off
//  
//  encoder0Pos = 0;
//
//  
//  count = 0;
//  
//  //EEPROM.get(COMBO_POS_02, nextNum);
//  nextNum = 32;
//  //turn CW past nextNum 2 times then stop on nextNum
//  digitalWrite(dirPin, HIGH);   //CW
//  digitalWrite(pwmPin, HIGH);  //motor on
//  while(count != 3){
//    if(encoder0Pos == (nextNum * 84)){
//      count++;
//    }
//  }
//  digitalWrite(pwmPin, LOW);  //turn motor off
//  count = 0;
//  
//  //EEPROM.get(COMBO_POS_03, nextNum);
//  nextNum = 44;
//  //turn CCW past nextNum 1 time then stop on nextNum
//  digitalWrite(dirPin, LOW);   //CCW
//  digitalWrite(pwmPin, HIGH);  //motor on
//  while(count != 2){
//    if(encoder0Pos == (nextNum * 84)){
//      count++;
//    }
//  }
//  digitalWrite(pwmPin, LOW);  //turn motor off
//  count = 0;
//  
//  //EEPROM.get(COMBO_POS_04, nextNum);
//  nextNum = 0;
//  //turn CW to nextNum
//  digitalWrite(dirPin, HIGH);   //CW
//  digitalWrite(pwmPin, HIGH);  //motor on
//  while(encoder0Pos != (nextNum * 84));
//  digitalWrite(pwmPin, LOW);
}

