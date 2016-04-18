
#define   GUADAGNO   20.0    //un secondo          
double precedente_Cont;
//float K = 1.9 * 1.12;  // ruota da  80mm dim
float K = 1.9 *1.736 ;      // dipende dalla dimensione delle ruote
float Kp = 3.40;            //costante proporzionale               
float Ki = 0;               //inegrale         
float Kd = -6;              //derivativa
float Kp_ruota = 0.015;   
float Kd_ruota = 7;
double lol;
int integrated_error = 0;
float ptermine=0, itermine=0, dtermine=0, ptermine_ruota=0, dtermine_ruota=0;
long long tempo=0;   
long long precedente_tempo=0;
int error=0, precedente_error=0;
int integrated_count=0;
 
 
  double sens1;
  double sens2;
  double sens3;
 
int updatePid(int setPoint, int sensorPosition)   {
  
  sens1 = analogRead(A0);
  sens2 = analogRead(A1);
  sens3 = analogRead(A2);
  
  Kp=3.40;//proporzioni(sens1, 0, 1023, 0, 5);
  Ki=0;//proporzioni(sens2, 0, 1023, -3, 3);//proporzioni(sens2, 0, 1023, -5, 5);
  Kd=6;//proporzioni(sens3, 0, 1023, -7, 7);
     //Serial.print(Kp); Serial.print("\t");
     //Serial.print(Ki); Serial.print("\t");
     //Serial.println(Kd); Serial.print("\t");
     
 if(abs(count)>100000000) count=0;
  error = setPoint - sensorPosition; 
  ptermine = Kp * error;
  tempo=micros();
  integrated_error=(tempo-precedente_tempo)*(precedente_error+error)/2;
  integrated_count=integrated_count+integrated_error;
  itermine = Ki * constrain(integrated_count, -GUADAGNO, GUADAGNO); //constrain(integrated_error, -GUADAGNO, GUADAGNO);
  dtermine = Kd * ((error-precedente_error)/(tempo-precedente_tempo));                            
  ptermine_ruota = Kp_ruota * count;           //  -(Kxp/100) * count;
  dtermine_ruota = Kd_ruota * (count - precedente_Cont);                            
  precedente_Cont = count;
  double tempod=tempo-precedente_tempo;
  Serial.println(tempod);
  
  precedente_tempo=tempo;
  precedente_error=error;
  lol= -constrain(K*(ptermine + itermine + dtermine + ptermine_ruota + dtermine_ruota), -255, 255);
   //Serial.print(count); Serial.print("\t");Serial.println(lol);
  return lol;
 
}
void setPID(int newKP){
Kd=newKP;
}
 
double proporzioni(double x, double inmin, double inmax, double outmin, double outmax)
{
  return (x - inmin) * (outmax - outmin) / (inmax - inmin) + outmin;
}
