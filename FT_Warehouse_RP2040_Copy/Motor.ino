//
//
//
//
//
void Disable_ALL(){
   Motor_Lift(0);
   Motor_Platform(0);
   Motor_Arm(0);
}
//------------------------------------------------------------// 
void Motor_Lift(int dir) {
  if (dir==1){    
    //Serial.println("Lowering Lift"); 
    digitalWrite(M5A,95);
    digitalWrite(M5B,LOW);
  }
  else if (dir==2) {
    //Serial.println("Raising Lift");
    digitalWrite(M5B,110);
    digitalWrite(M5A,LOW);
  }
  else if (dir==0) {
    //Serial.println("Shutting Down Lift");
    digitalWrite(M5A,LOW);
    digitalWrite(M5B,LOW);
  }
}
//------------------------------------------------------------// 
void Motor_Platform(int dir) {
  if (dir==1){    
    //Serial.println("Forward Platform"); 
    digitalWrite(M6A,180);
    digitalWrite(M6B,LOW);
  }
  else if (dir==2) {
    //Serial.println("Reversing Platform");
    digitalWrite(M6B,180);
    digitalWrite(M6A,LOW);
  }
  else if (dir==0) {
    //Serial.println("Shutting Down Platform");
    digitalWrite(M6A,LOW);
    digitalWrite(M6B,LOW);
  }
  else if (dir==3) {
    //Serial.println("Braking");
    digitalWrite(M6A,255);
    digitalWrite(M6B,255);
  }
}
//------------------------------------------------------------// 
void Motor_Arm(int dir) {
  if (dir==1){    
    //Serial.println("Forward Arm"); 
    digitalWrite(M3A,220);
    digitalWrite(M3B,LOW); 
  }
 else if (dir==2) {
    //Serial.println("Reversing Arm");
    digitalWrite(M3B,220);
    digitalWrite(M3A,LOW);
 }
  else if (dir==0) {
    //Serial.println("Shutting Down Arm");
    digitalWrite(M3A,LOW);
    digitalWrite(M3B,LOW);
  }
}
//------------------------------------------------------------// 
void Servo_Gripper(int ang) {
 if (ang>=0 && ang<=180) {
   gripper.write(ang);
 }
 else {
  debugln("Servo input must be between 0* and 180*");
 }
}
//------------------------------------------------------------//