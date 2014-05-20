#include <MsTimer2.h>

int goff=0;
long angle=0;
double gyro_z,k=0.0067/*V/deg/sec*/,Vref=5.0,backup_gyro_z,V0;



void gyro() {
  gyro_z=(analogRead(A1)-V0)*Vref/(k*(double)(2<<8-1));
}

void setup(){
V0=analogRead(A1);
Serial.begin(9600);
Serial.println("start");
MsTimer2::set(10, gyro); 
MsTimer2::start();
}

void loop(){
angle += (backup_gyro_z+gyro_z)/2*0.01;
Serial.print(gyro_z);
Serial.print(" ");
Serial.println(angle);
delay(100);
}
