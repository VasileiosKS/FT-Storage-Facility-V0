               //------Libraries------//
#include <SPI.h>
#include <Wire.h>
#include <Servo.h> 
#include <PubSubClient.h>
//------------------------------------------------------------//        
//Function Declaration to avoid errors that might show up during compilation
void Safe_Mode();
void FreeMode();
void ASerialCom();
void Serial_Mode();
void SingleKey();
void Plat_Home();
void Plat_End();
void Lift_Top();
void Lift_Home();
void Arm_Extend();
void Arm_Retract();
void Lift_Height();
void SafeMode();
void FreeMode();
void Move_Plat_to_Pos();
void Motor_Lift();
void Motor_Platform();
void Motor_Arm();
void Servo_Gripper();
void Diagnostics();
void SerRead();
void MotorDirections(); 
              //------DEBUG MODE Enable/Disable------//
#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#define debugR(x) Serial.read(x)
#else
#define debug(x)  
#define debugln(x)
#define debugR(x)
#endif
//-----------------------------------------------------------//                
               //------Constants & Variables------//
int Mode = 0;    
                                                                    //PIN DECLARATION/
              //------Limit Switches------//             
#define Mod_Plat_Home 15 //before 5
#define Mod_Lift_0 19
#define Mod_Arm_0 21
#define Mod_Arm_1 22
              //------Hall Sensor------//      
#define Mod_Hall_Lift 18           
              //------AS5600------//  
const int AS5600_ADDR = 0x36;
const int RAW_POS_REG = 0x0C;
              //------Servo------//    
Servo gripper;
#define gripp 14        
              //-------MOTOR: TBF6612FNG-------//
#define M5A 13
#define M5B 12
#define M6A 10
#define M6B 11
#define M3A 7
#define M3B 6
#define ENCA 16
#define ENCB 17
//------------------------------------------------------------//        
void setup() {
  Serial.begin(115200); 
  debugln("Entering Setup Operation");
  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();
  Wire.setClock(400000);
  pinMode(Mod_Hall_Lift, INPUT_PULLUP);
  pinMode(Mod_Plat_Home, INPUT_PULLUP);
  pinMode(Mod_Lift_0, INPUT_PULLUP);
  pinMode(Mod_Arm_0, INPUT_PULLUP);
  pinMode(Mod_Arm_1, INPUT_PULLUP);  
  pinMode(M6A, OUTPUT); 
  pinMode(M5A, OUTPUT); 
  pinMode(M3A, OUTPUT);
  pinMode(M6B, OUTPUT); 
  pinMode(M5B, OUTPUT);  
  pinMode(M3B, OUTPUT);  
  digitalWrite(M6A, LOW); 
  digitalWrite(M5A, LOW); 
  digitalWrite(M3A, LOW);
  digitalWrite(M6B, LOW); 
  digitalWrite(M5B, LOW);  
  digitalWrite(M3B, LOW);  
  gripper.attach(gripp);
  Calibration();
  Homing();
  debugln("SETUP COMPLETE");  
  debugln("Type HELP to display all available commands");  
  delay(100);  
}
//------------------------------------------------------------//   
void loop() {
  Serial_Mode();
}
