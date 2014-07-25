/* 
  This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").
 
 Contact information
 -------------------
 
 Mohammad Zobeer, Andrea Rossi
 Web      :  balancingrobot.altervista.org
 e-mail   :  amministrazione.zubeer@gmail.com or areds13@gmail.com
 */
 
double Angolo;
int drive = 0;
int setPoint=185;
float incomingByte;
void setup(){
 Serial.begin(115200);
  setGyro();
  setMotor();
  setupEncoder();
  
  
}
void loop(){ 
 
  
  	Angolo=getGyro();
        
//if(abs(Angolo-setPoint)<1) Angolo=setPoint;
	drive = updatePid(setPoint, Angolo); 
drive=map(drive,-255,255,170,10);
	  
	driveMotor(drive); 
	//Serial.print(Angolo); Serial.print("\t");Serial.println(drive);
 
}
