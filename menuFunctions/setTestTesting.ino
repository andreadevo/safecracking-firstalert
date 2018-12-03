//////////////////////////////////////////
// CALIBRATE SET TESTING OF ALL 3 DISKS //
//////////////////////////////////////////

void testThirdDisk() {
  //turn 4 times CCW set first disk at 96
  nextNumber(96, 5, 0);
  //turn 2 times CW set second disk at 33
  nextNumber(33, 3, 1);
  //full rotation CCW ending on 33
  nextNumber(33, 1, 0);
  //CCW once to 36, this is where set test will start
  nextNumber(36, 1, 0);
  //CW to 36 check if correct
  nextNumber(36, 1, 1);
  //CCW 39
  nextNumber(39, 1, 0);
  //CW to 39 check
  nextNumber(39, 1, 1);
  //CCW to 42
  nextNumber(42, 1, 0);
  //CW to 42 to check
  nextNumber(42, 1, 1);
  //CCW to 45
  nextNumber(45, 1, 0);
  //CW to check, check should trigger win state
  nextNumber(45, 1, 1);
  bool isOpen = checkIfOpen();
  if(isOpen){
    winState();
  }
  else {
    Serial.println("Calibration Test Failed.");
  }
}

//These are the combos we'll test:
//(96,30,93)
//(96,30,96)
//(96,33,39)
//(96,33,42)
//(96,33,45)
void testSecondDisk() {
  //turn 4 times CCW set first disk at 96
  //turn two rotations CW and stop on 0
  //turn D2 CW to 30
  //turn D3 CCW to 30
  //turn D3 CCW to 93
  //turn D4 CW to 93 check
  //turn D3 CCW to 96
  //turn D4 CW to 96 check
  //turn D3 CCW to 96
  //turn D3 CCW to 30
  //turn D2 CCW to 33
  //turn D3 CW 2 rotations to 33
  //turn D3 CCW to 42
  //turn D4 CW to 42 check
  //turn D3 CCW to 45
  //turn D4 CW to 45 check
  //should open safe 
}


void testFirstDisk() {
  //no disks correct
//test first disk from 90 to 96 (3)
//with second disk testings from 93 to 96 (2)
//and third disk tests only for secondDisk +3 and secondDisk - 3 (2)
//total of 12 checks
//if calibrated, should open after this function is done
}

