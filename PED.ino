#include <AFMotor.h>

const double kP = 2.5;
const int power = 110;
int lerror = 0;
const double kD = 0;
const double kI = 0;
int integral = 0;


AF_DCMotor LM1(1);
//AF_DCMotor LM2(3);
AF_DCMotor RM1(2);
//AF_DCMotor RM2(4);


void setup() {
 
  LM1.run(RELEASE);
//  LM2.run(RELEASE);
  RM1.run(RELEASE);
//  RM2.run(RELEASE);
}
void MOVE(int LM,int RM) {
  LM1.setSpeed(LM);
//  RM2.setSpeed(RM);
  RM1.setSpeed(RM);
//  LM2.setSpeed(LM);
  
  
  if(LM < 0) {
    LM1.run(BACKWARD);
//    LM2.run(BACKWARD);
  }
  else if (LM == 0) {
    LM1.run(RELEASE);
//    LM2.run(RELEASE);
  }
  else {
    LM1.run(FORWARD);
//    LM2.run(FORWARD);
  }
  if(RM < 0) {
    RM1.run(BACKWARD);
//    RM2.run(BACKWARD);
  }
  else if (RM == 0) {
    RM1.run(RELEASE);
//    RM2.run(RELEASE);
  }
  else {
    RM1.run(FORWARD);
//    RM2.run(FORWARD);
  }
  
}

void loop() {
  unsigned long StartTime = millis();
  int arr[2] = {analogRead(A0),analogRead(A2)};
  int error = (arr[1]) - (arr[0]);
  error = map(error,-1023,1023,-255,255);
  unsigned long EndTime = millis();
  unsigned long ElapsedTime = (EndTime - StartTime)/1000;
  int derivative = (error-lerror)/ElapsedTime;
  integral += error;
  int integ_mult = (integral/ElapsedTime)
  int turn = (error * kP) + (derivative * kD) + (integ_mult * kI);
  MOVE(power + turn , power - turn);
  lerror = error;
}
