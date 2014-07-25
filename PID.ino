
#define   GUARD_GAIN   20.0                // 20.0
double last_count;
//float K = 1.9 * 1.12;  // wheels 80mm
float K = 1.9 *1.736 ;      // dipende dalla dimensione delle ruote
float Kp = 3.40;            //costante proporzionale               
float Ki = 0;               //inegrale         
float Kd = -6;              //derivativa
float Kp_Wheel = 0.015;   
float Kd_Wheel = 7;
double lol;
int integrated_error = 0;
float pTerm=0, iTerm=0, dTerm=0, pTerm_Wheel=0, dTerm_Wheel=0;
long long time=0;    //fatte da noi
long long last_time=0;
int error=0, last_error=0;
int integrated_count=0;
 
 
  double sens1;
  double sens2;
  double sens3;
 
int updatePid(int targetPosition, int currentPosition)   {
  
  sens1 = analogRead(A0);
  sens2 = analogRead(A1);
  sens3 = analogRead(A2);
  
  Kp=3.40;//prop(sens1, 0, 1023, 0, 5);
  Ki=0;//prop(sens2, 0, 1023, -3, 3);//prop(sens2, 0, 1023, -5, 5);
  Kd=6;//prop(sens3, 0, 1023, -7, 7);
     //Serial.print(Kp); Serial.print("\t");
     //Serial.print(Ki); Serial.print("\t");
     //Serial.println(Kd); Serial.print("\t");
     
 if(abs(count)>100000000) count=0;
  error = targetPosition - currentPosition; 
  pTerm = Kp * error;
  time=micros();
  integrated_error=(time-last_time)*(last_error+error)/2;
  integrated_count=integrated_count+integrated_error;
  iTerm = Ki * constrain(integrated_count, -GUARD_GAIN, GUARD_GAIN); //constrain(integrated_error, -GUARD_GAIN, GUARD_GAIN);
  dTerm = Kd * ((error-last_error)/(time-last_time));                            
  pTerm_Wheel = Kp_Wheel * count;           //  -(Kxp/100) * count;
  dTerm_Wheel = Kd_Wheel * (count - last_count);                            
  last_count = count;
  double timed=time-last_time;
  Serial.println(timed);
  
  last_time=time;
  last_error=error;
  lol= -constrain(K*(pTerm + iTerm + dTerm + pTerm_Wheel + dTerm_Wheel), -255, 255);
   //Serial.print(count); Serial.print("\t");Serial.println(lol);
  return lol;
 
}
void setPID(int newKP){
Kd=newKP;
}
 
double prop(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
