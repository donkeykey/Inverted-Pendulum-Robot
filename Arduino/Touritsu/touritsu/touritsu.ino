/* "A very easy and simple inverted pendulum balancing robot"
You need only half a day to make it, if you have some Materials.
Copyright (C) 2014 ArduinoDeXXX All Rights Reserved. */

#include <MsTimer2.h> //01

volatile int i = 0; //02
volatile byte countS = 0; //03
long zeroOmegaI = 0;// 04
volatile int recOmegaI[10]; //05
volatile int omegaI = 0; //06
volatile long thetaI = 0; //07
volatile long sumPower = 0; //08
volatile long sumSumP = 0; //09 
const int kAngle = 45; //10
const int kOmega = 85; //11
const long kSpeed = 57; //12
//const long kSpeed = 125; //12
const long kDistance = 60; //13
volatile long powerScale; //14
volatile int power; //15
volatile long vE5 = 0; //16
volatile long xE5 = 0; //17

void setup () { //18
 Serial .begin(9600); //19
 pinMode(4, OUTPUT); //20
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(9, OUTPUT);
 pinMode(13,OUTPUT);
 for ( i = 0 ; i < 10 ; i++ ) { recOmegaI[i] = 0; } //25
 delay(300);
 training();
 MsTimer2::set(5, chkAndCtl);
 MsTimer2::start();
 digitalWrite(13,HIGH);
} //30

void loop () { //31
 if ( power > 0 ) { 
 analogWrite( 6, power ); 
 digitalWrite( 4, HIGH ); 
 digitalWrite( 5, LOW ); //35
 analogWrite( 9, power ); 
 digitalWrite( 7, HIGH ); 
 digitalWrite( 8, LOW ); 
 } else {
 analogWrite( 6, - power ); //40
 digitalWrite( 4, LOW );
 digitalWrite( 5, HIGH );
 analogWrite( 9, - power );
 digitalWrite( 7, LOW );
 digitalWrite( 8, HIGH ); //45
 }
} //47

void training(){ //48
 delay (1000);
 for ( i = 0 ; i < 500 ; i++ ){ //50
 zeroOmegaI = zeroOmegaI + analogRead(A1);
 }
 zeroOmegaI = zeroOmegaI / i;
} //54

void chkAndCtl() { //55
 omegaI = analogRead(A1) - zeroOmegaI;
 if ( abs( omegaI ) < 5 ) { omegaI = 0; }
 recOmegaI[0] = omegaI;
 thetaI = thetaI + omegaI;
 countS = 0; //60
 for ( i = 0 ; i < 10 ; i++ ) {
 if ( abs( recOmegaI[i] ) < 4 ) { countS++; }
 }
 if ( countS > 9 ) {
 thetaI = 0; //65
 vE5 = 0;
 xE5 = 0;
 sumPower = 0;
 sumSumP = 0;
 } //70
 for ( i = 9 ; i > 0 ; i-- ) { recOmegaI[ i ] = recOmegaI[ i-1 ]; }
 powerScale = ( kAngle * thetaI / 200 ) + ( kOmega * omegaI / 78 ) + ( kSpeed * vE5 / 1000 ) + ( kDistance * xE5 / 1000 );
 power = max ( min ( 95 * powerScale / 100 , 255 ) , -255 );
 sumPower = sumPower + power;
 sumSumP = sumSumP + sumPower; //75
 vE5 = sumPower; //76
 xE5 = sumSumP / 1000; //77
}
