//Disclaimer: Portions of the following code were AI generated.
//By combining the Pico with an AS5600 magnetic encoder, position feedback and control were implemented via a PI controller, allowing the system to track its position in millimeters
//Precision is affected by the plastic worm screw and bent metal linear rods. 

//---- Mechanical Specs ---
const float MM_PER_ROTATION = 4.712; 
const float STEPS_PER_MM = 4096.0 / MM_PER_ROTATION;
bool mes_cal = false; 
float manual_limit_mm = 265.0;
long turns = 0;
int prev_angle = 0;
long total_steps = 0;
long target_steps = 0;
long home_offset = 0; 
// --- STABILITY TUNING ---
float kp = 0.15;           
int deadband = 150;         
int min_pwm = 110;          
int max_pwm = 170;         
//------------------------------------------------------------//
int getDigitalAngle() {
  Wire.beginTransmission(AS5600_ADDR);
  Wire.write(RAW_POS_REG);
  if (Wire.endTransmission() != 0) {
    return prev_angle;
  }
  Wire.requestFrom(AS5600_ADDR, 2);
  if (Wire.available() >= 2) {
    uint16_t highByte = Wire.read();
    uint16_t lowByte = Wire.read();
    return (int)((highByte << 8) | lowByte);
  }
  return prev_angle; 
}

void updatePosition() {
  int current_angle = getDigitalAngle();
  int delta = current_angle - prev_angle;

  // Multi-turn logic
  if (delta > 2048)      turns--; 
  else if (delta < -2048) turns++; 
  
  // FIXED: We now subtract the raw reading from 0 (or negate it) 
  // to ensure "Right" movement = "Positive" numbers.
  long absolute_raw = (turns * 4096) + current_angle;
  total_steps = (absolute_raw * -1) - home_offset; 
  
  prev_angle = current_angle;
}

void Calibration() {
  Serial.println("Calibration Process Initiated");
  Plat_Home();
  delay(500);
  Motor_Platform(0);
  int current_raw = getDigitalAngle();
  turns = 0;
  // Initialize home_offset using the inverted logic to match updatePosition
  home_offset = (turns * 4096 + current_raw) * -1; 
  prev_angle = current_raw;
  total_steps = 0; 
  target_steps = 0;
  Serial.println("Calibration Sequence Completed.");
}

void MOVE_TO(float mm_input) {
  mm_input = constrain(mm_input, 0, manual_limit_mm);
  target_steps = (long)(mm_input * STEPS_PER_MM);
  boolean stop = false;
  while(!stop){ 
    updatePosition();
    long error = target_steps - total_steps;
    if (abs(error) <= deadband) {
      Motor_Platform(3);
      stop= true;
    } 
    else {
      int speed = constrain((abs(error) * kp) + min_pwm, min_pwm, max_pwm);
      if (error > 0) {
        analogWrite(M6A, speed);  // Moving Right
        analogWrite(M6B, 0);
      } else {
        analogWrite(M6A, 0);
        analogWrite(M6B, speed);  // Moving Left
      }
    }
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 200) {
      Serial.print("Pos: ");
      Serial.print((float)total_steps / STEPS_PER_MM, 2);
      Serial.print(" / ");
      Serial.print(manual_limit_mm, 2);
      Serial.println("mm");
      lastPrint = millis();
    }
  }
  Motor_Platform(0);
}
