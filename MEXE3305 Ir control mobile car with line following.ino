#include <IRremote.hpp>
#define IR_SENSOR_RIGHT A0
#define IR_SENSOR_LEFT A1
#define MOTOR_SPEED 130

int irpin = 11;
int mot11 = 7, mot12 = 6, mot21 = 5, mot22 = 4;
int ena1 = 8, ena2 = 9;
int line = false, ir = false; 

IRrecv IR(irpin);
decode_results results;

void setup(){
  IR.enableIRIn();
  pinMode(mot11, OUTPUT);
  pinMode(mot12, OUTPUT);
  pinMode(mot21, OUTPUT);
  pinMode(mot22, OUTPUT);
  pinMode(ena1, OUTPUT);
  pinMode(ena2, OUTPUT);
  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  rotateMotor(0,0);  
  Serial.begin(9600);
}
void forward(){
  digitalWrite(mot11, HIGH);
  digitalWrite(mot12, LOW);
  digitalWrite(mot21, HIGH);
  digitalWrite(mot22, LOW);
}
void reverse(){
  digitalWrite(mot11, LOW);
  digitalWrite(mot12, HIGH);
  digitalWrite(mot21, LOW);
  digitalWrite(mot22, HIGH);
}
void left(){
  digitalWrite(mot11, HIGH);
  digitalWrite(mot12, LOW);
  digitalWrite(mot21, LOW);
  digitalWrite(mot22, HIGH);
}
void right(){
  digitalWrite(mot11, LOW);
  digitalWrite(mot12, HIGH);
  digitalWrite(mot21, HIGH);
  digitalWrite(mot22, LOW);
}
void stop(){
  digitalWrite(mot11, LOW);
  digitalWrite(mot12, LOW);
  digitalWrite(mot21, LOW);
  digitalWrite(mot22, LOW);
}
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  
  if (rightMotorSpeed < 0)
  {
    digitalWrite(mot21,LOW);
    digitalWrite(mot22,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(mot21,HIGH);
    digitalWrite(mot22,LOW);      
  }
  else
  {
    digitalWrite(mot21,LOW);
    digitalWrite(mot22,LOW);      
  }
  if (leftMotorSpeed < 0)
  {
    digitalWrite(mot12,LOW);
    digitalWrite(mot11,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(mot12,HIGH);
    digitalWrite(mot11,LOW);      
  }
  else 
  {
    digitalWrite(mot12,LOW);
    digitalWrite(mot11,LOW);      
  }
  analogWrite(ena1, abs(rightMotorSpeed));
  analogWrite(ena2, abs(leftMotorSpeed));    
}

void linefollow(){
while(line){
   ir = false;
  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

  //If none of the sensors detects black line, then go straight
  if (rightIRSensorValue == LOW && leftIRSensorValue == LOW)
  {
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
  //If right sensor detects black line, then turn right
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW )
  {
      rotateMotor(-MOTOR_SPEED, MOTOR_SPEED); 
  }
  //If left sensor detects black line, then turn left  
  else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH )
  {
      rotateMotor(MOTOR_SPEED, -MOTOR_SPEED); 
  } 
  //If both the sensors detect black line, then stop 
  else 
  {
    rotateMotor(0, 0);
  }
  if (IR.decode()) {
       // Check if the received button press interrupts the loop
        if (IR.decodedIRData.decodedRawData == 0xB847FF00) {
        line = false;
        ir = false;
        stop();
      }
      IR.resume();  // Receive the next IR signal
    }
}
}

void loop(){
  if(IR.decode()){
    //movement
    if (IR.decodedIRData.decodedRawData == 0xBA45FF00){
      ir = true;
      
      while(ir){
         line = false;
      if(IR.decode()){
      if (IR.decodedIRData.decodedRawData == 0xE718FF00){
        right();
       }
      else if (IR.decodedIRData.decodedRawData == 0xAD52FF00){
        left();
       }
      else if (IR.decodedIRData.decodedRawData == 0xF708FF00){
        forward();
       }
      else if (IR.decodedIRData.decodedRawData == 0xA55AFF00){
        reverse();
       }
      else if (IR.decodedIRData.decodedRawData == 0xE31CFF00){
        stop();
       } IR.resume();
      }
      if (IR.decode()) {
       // Check if the received button press interrupts the loop
        if (IR.decodedIRData.decodedRawData == 0xB847FF00) {
        ir = false;
        line = false;
      }
      IR.resume();  // Receive the next IR signal
    }
      }
    }
    if (IR.decodedIRData.decodedRawData == 0xB946FF00)
    {
      line = true;
      linefollow();
    }
    if (IR.decodedIRData.decodedRawData == 0xBB44FF00){
        stop();
       }
    IR.resume();
  }
}