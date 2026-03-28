void Serial_Mode() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    debugln(input);
    input.trim();
    if (input.startsWith("MOVE_TO ")) {
      input = input.substring(7);
      float mm_input = input.toFloat();
      MOVE_TO(mm_input);
    }
    else if (input.startsWith("SHELF ")) {
      input = input.substring(6);
      int num = input.toInt();
      Shelf(num);
    }
    else if (input.startsWith("RETRIEVE ")) {
      input = input.substring(9);
      int num = input.toInt();
      Retrieve(num);
    }
    else if (input.startsWith("PLACE ")) {
      input = input.substring(6);
      int num = input.toInt();
      Place(num);
    }
    else if (input.startsWith("LIFT ")) {
      input = input.substring(5);
      int num = input.toInt();
      Lift_Height(num);
    }
    else if (input.startsWith("ARM ")) {
      input = input.substring(4);
      int num = input.toInt();
      
    }

    else if (input.startsWith("SERVO ")) {   
      input = input.substring(6);
      int ang = input.toInt();
      Servo_Gripper(ang);
    }
    else if (input== "HELP") {
      printHelp();
    }
    else if (input== "DIAGNOSTICS") {
      printDiagnostics();
    }
     else if (input== "WIRELESS") {
      printWireless();
    }
    else if (input== "MOTORS") {
      printMotors();
    }

    else if (input=="Q") {
      Plat_Home(); 
    }
    else if (input=="W") {
      Motor_Platform(0);
    }
    else if (input=="Z") {
      Arm_Extend();
    }
    else if (input=="X") {  
      Arm_Home();
    }
    else if (input=="C") {  
      Motor_Arm(0);
    }
  }
}
//------------------------------------------------------------------------------------------//
void printDiagnostics() {
    debugln(" ");
    debugln("|-------------------------------------|");
    debugln("|Diagnostics Menu                     |");
    debugln("|-------------------------------------|");
    debugln("|Sensor Data:                         |"); 
    if(digitalRead(Mod_Hall_Lift)==LOW) {
        debugln("|Mod_Hall_Lift: Contact               ");
    }
    else{
        debugln("|Mod_Hall_Lift: No Contact            |");
    }
    if(digitalRead(Mod_Plat_Home)==LOW) {
        debugln("|Mod_Plat_Home: Contact               |"); 
    }
    else{
        debugln("|Mod_Plat_Home: No Contact            |"); 
    }   
    if(digitalRead(Mod_Lift_0)==LOW) {
        debugln("|Mod_Lift_0: Contact                  |");
    }
    else{
        debugln("|Mod_Lift_0:    No Contact            |");
    }
    if(digitalRead(Mod_Arm_0)==LOW) {
        debugln("|Mod_Arm_0:     Contact               |");
    }
    else{
        debugln("|Mod_Arm_0:     No Contact            |");
    }
    if(digitalRead(Mod_Arm_1)==LOW) {
        debugln("|Mod_Arm_1:     Contact              |");
    }
    else{
        debugln("|Mod_Arm_1:     No Contact            |"); 
    }
}
//------------------------------------------------------------------------------------------//
void printWireless() {
    debugln("|Wireless Connection:                 |");
    debug  ("|-------------------------------------|");     
}
//------------------------------------------------------------------------------------------//
void printMotors() {
    debug  ("|-------------------------------------|");
    debugln(" ");
    debugln("|Motor Status:                        |");
    debugln("|-------------------------------------|");
}
//------------------------------------------------------------------------------------------//
void printHelp() {
  debugln("\n--- WAREHOUSE COMMAND MENU ---"); 
  debugln("CALIB            : Start full rail calibration (Finds max length)");
  debugln("MOVE_TO [val]    : Move to position in millimeters (0-253)");
  debugln("PLACE [val]      : Wipe memory and restart setup");
  debugln("RETRIEVE [val]   : Retrieve Object from ");
  debugln("HELP             : Display all available commands");
  debugln("DIAGNOSTICS      : Display status of all INPUTS");
  debugln("WIRELESS         : Display Wireless infornation");
  debugln("MOTORS           : Display Motor status");
  debugln("----------------------------------\n");
}
//------------------------------------------------------------------------------------------//
