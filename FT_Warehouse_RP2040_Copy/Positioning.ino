void Homing() { //Performing Home action where all axis move to position 0.
  Plat_Home();
  Lift_Home();
  Arm_Home();
  Servo_Gripper(0);
}
//------------------------------------------------------------//
void Plat_Home() { //Platform moves to home position
  debugln("Moving Platform To Home");
  while (digitalRead(Mod_Plat_Home) == HIGH) { 
    Motor_Platform(2);
  }
  debugln("Movement Completed");
  Motor_Platform(0);
}
//------------------------------------------------------------//
void Lift_Home() {//Lift moves down to home position
  debugln("Lowering Arm");
  while (digitalRead(Mod_Lift_0) == HIGH) {  
    Motor_Lift(1);
  }
  debugln("Movement Completed");
  Motor_Lift(0);
}
//------------------------------------------------------------//
// Instead of using an AS5600 magnetic sensor like the platform does, the lift uses a reed switch to move
void Lift_Height(int dir) { //
  boolean flag=true; 
  int currentHallState;
  int lastHallState; 
  Lift_Home();
  debugln("Lift Home");
  lastHallState = LOW;
  int Vpos = 0;
  debugln("Raising lift to: " + dir);
  while ((Vpos < dir)) {  
    currentHallState = digitalRead(Mod_Hall_Lift);
    if (currentHallState != lastHallState) {
      //debugln("currentHallState != lastHallState");
      if (currentHallState == LOW) {
        //debugln("MAGNET DETECTED");
        Vpos++;
        //debug(Vpos);
      } else {
        //debugln("currentHallState == lastHallState");
        Motor_Lift(2);
      }
      lastHallState = currentHallState;
    }
    delay(50);
  }
  debugln("Movement Completed");
  Motor_Lift(0);
  flag = false;
}
/*
//------------------------------------------------------------//
void Move_Plat_to_Pos(int dir) {
  Plat_Home();
  Serial.println("Plat in Home Pos");
  flag = true;
  lastHallState = LOW;
  Hpos = 0;
  while ((Hpos < dir)) {
    currentHallState = digitalRead(Mod_Hall_Plat);
    if (currentHallState != lastHallState) {
      Serial.println("currentHallState != lastHallState");
      if (currentHallState == LOW) {
        Hpos++;
        Serial.print(Hpos);
      } 
      else {
        Serial.println("currentHallState == lastHallState");
        Motor_Platform(2);
      }
      lastHallState = currentHallState;
    }
    delay(50);
  }
  Motor_Platform(0);
  Serial.println("Reached Destination");
  flag = false;
}
*/
//------------------------------------------------------------//
void Lift_Top() {
  Lift_Height(3);
}
//------------------------------------------------------------//
void Arm_Extend() {
  debugln("Moving Arm: Front");
  while (digitalRead(Mod_Arm_1) == HIGH) {
    Motor_Arm(1);
  }
  debugln("Movement Completed");
  Motor_Arm(0);
}
//------------------------------------------------------------//
void Arm_Home() {
  debugln("Moving Arm: Back");
  while (digitalRead(Mod_Arm_0) == HIGH) {
    Motor_Arm(2);
  }
  debugln("Movement Completed"); 
  Motor_Arm(0);
}
//------------------------------------------------------------//
void Shelf(int W) {
  debugln("Moving to Shelf: " + W);
  if(W>=1 && W<=6) {
    int x, y;
    switch (W) {
    case 1:
      x = 200;      y = 3;
      break;
    case 2:
      x = 260;      y = 3;
      break;
    case 3:
      x = 200;      y = 2;
      break;
    case 4:
      x = 260;      y = 2;
      break;
    case 5:
      x = 200;      y = 1;
      break;
    case 6:
      x = 260;      y = 1;
      break;
  }
    MOVE_TO(x);
    Lift_Height(y);
  }
  else {
    Serial.println("Error, input must be between 1 and 6");
    }
}
//------------------------------------------------------------//
void Retrieve(int N) {
  Homing();
  Shelf(N);
  Servo_Gripper(0);
  Arm_Extend();
  Servo_Gripper(170);
  Arm_Home(); 
  Plat_Home();
  Lift_Home();
  Servo_Gripper(0);
}
//------------------------------------------------------------//
void Place(int N) {
  Homing();
  Servo_Gripper(170);
  Arm_Home(); 
  Shelf(N);
  Arm_Extend();
  Servo_Gripper(0);
  Arm_Home();
  Lift_Home(); 
  MOVE_TO(0);
}