

//Vcc 3.3volt
//SCL Analog 5
//SDA Analog 4
//SDO 3.3volt
//CS 3.3volt

#include <Wire.h>

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

int x;
int y;
int z;
int yi[3];
long previousMicros = 0;
float intervallo;
unsigned long currentMicros;
int i;
int gy=0;

int L3G4200D_Address = 105; //I2C address of the L3G4200D
void setup() {
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Motore canale A / if HIGH Avanti else Indietro
  pinMode(9, OUTPUT); //Freno canale A If LOW togli freno else metti freno
  setupL3G4200D(2000);
  delay(2000);
  previousMicros = micros();
  
  
}

void loop(){
  
  //forward @ full speed
  digitalWrite(12, HIGH); 
  digitalWrite(9, LOW);   
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed
  
  delay(3000);
  
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A

  delay(1000);
  
  //backward @ half speed
  digitalWrite(12, LOW); //Establishes backward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 123);   //Spins the motor on Channel A at half speed
  
  delay(3000);
  
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A
  
  delay(1003);
  
}


void valori(){
  previousMicros = micros();
  for(i=0;i<3;i++){
   getGyroValues();  // This will update x, y, and z with new values
  yi[i]=y;
}
currentMicros = micros();

intervallo = currentMicros-previousMicros;
 for(i=0;i<3;i++){
gy+=yi[i]*(intervallo/1000000);
//Questa funzione aggiorna i valori della variabile gy calcolandone l'angolo.
//Funziona male e i valori tendono a tornare a zero i calcoli sono perciò errati.
//Meglio usare i calcoli tramite velocià angolare
}
