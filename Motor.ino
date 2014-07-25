#include <Servo.h>
 
Servo Motor_R;
Servo Motor_L;
 
int PWM_R=9;
int PWM_L=10;
int encodPOWER=4;
int encodPinA1=2;
int encodPinB1=5;
int encodPinA2=3;
int encodPinB2=6;
volatile boolean up;
 double count=0; 
 
void setMotor(){
Motor_R.attach(PWM_R);
Motor_L.attach(PWM_L);
}
 
 
void driveMotor(int torque)  {
	Motor_R.write(torque);
	Motor_L.write(torque);
}
 
 
void setupEncoder()  {
  pinMode(encodPOWER, OUTPUT);
  digitalWrite(encodPOWER, HIGH);
  digitalWrite(encodPinA1, HIGH); // turn on pullup resistor
  digitalWrite(encodPinB1, HIGH);
  attachInterrupt(1, isr, FALLING);
}
 
void isr()  { // pulse and direction, direct port reading to save cycles      
 
     if (PIND & 0b01000000)    count++;
  else                      count--;
 
}
