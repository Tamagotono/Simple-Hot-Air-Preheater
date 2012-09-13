// *****************************************************************
//   ********************* FUNCTIONS *****************************
// *****************************************************************

// **************************** INTERRUPT1 ************************
// This is the Timer 1 CTC interrupt, it goes off once a second
SIGNAL(TIMER1_COMPA_vect) { 

  CurrentEncValue = Enc.read(); //this runs every 1/10th of a second
  if ( CurrentEncValue != LastEncValue ) {
    UpdateDisplay();
  }
  InterruptCounter++;

  if ( InterruptCounter == 9 ) { //Run this once per second
    // time moves forward!
    seconds_time++;

    // save the last reading for our slope calculation
    previous_temperature = airTemp;

    // we will want to know the temperatures in the main loop()
    // instead of constantly reading them, we'll just use this interrupt
    // to track them and save them once a second to 'airTemp' and 'chipTemp'
    airTemp = airTC.readCelsius();
    chipTemp = chipTC.readCelsius();


    // Sum the error over time
    Summation += target_temperature - airTemp;

    if ( (airTemp < (target_temperature * (1.0 - WINDUPPERCENT))) ||
      (airTemp > (target_temperature * (1.0 + WINDUPPERCENT))) ) {
      // to avoid windup, we only integrate within 5%
      Summation = 0;
    }
    InterruptCounter = 0;
  }
} 
// **************************************************************************



// ******************************* FormatTime ******************************
// This function takes no inputs and outputs the time as a String formatted as mm:ss
String FormatTime() {
  String StringTime = "";
  int time = seconds_time; //prevents the value changing during the processing of this function
  int minutes = (time / 60);
  int seconds = (time % 60);
  if ( minutes <= 9) { // add a leading space to the minute clock if less than 10 seconds
    StringTime="0";
  }    
  StringTime = StringTime + minutes; // minutes
  StringTime = StringTime + ":";
  if ( seconds <= 9) { // add a leading zero to the seconds clock if less than 10 seconds
    StringTime = StringTime + "0";
  }
  StringTime = StringTime + seconds; // seconds
  return StringTime;  
}
// **************************************************************************


// ***************************** FormatFanSpeed ****************************
String FormatFanSpeed(){
  //  Serial.println( FanSpeed );
  String StringFanSpeed = "";
  if ( FanSpeed < 100 ) { // right justify fan speed
    StringFanSpeed = " ";
    if ( FanSpeed < 10) {
      StringFanSpeed = StringFanSpeed + " ";
    }
  }
  StringFanSpeed = StringFanSpeed + FanSpeed;
  StringFanSpeed = StringFanSpeed + "%";
  return StringFanSpeed;
}
// **************************************************************************


// ***************************** PrintValues ********************************
void PrintValues(){
  Serial.print("\t\tKp = "); 
  Serial.print(Kp);
  Serial.print(" Ki = "); 
  Serial.print(Ki);
  Serial.print(" Kd = "); 
  Serial.println(Kd);
}
// **************************************************************************

// ***************************** Update Display *****************************
void UpdateDisplay(){
 x // Doesn't do anything yet!
}
// **************************************************************************
