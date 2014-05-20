/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13. 
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead(). 
 
 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground
 
 * Note: because most Arduinos have a built-in LED attached 
 to pin 13 on the board, the LED is optional.
 
 
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe
 
 This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/AnalogInput
 
 */

int sensorPin = A0;    // select the input pin for the potentiometer
int gyroPin = A1;    // select the input pin for the potentiometer
int outPin1 = 5;    // select the input pin for the potentiometer
int outPin2 = 6;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int gyroValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(7, OUTPUT);  
  Serial.begin(57600);

}

void loop() {
  /*
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);  
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);          
  // turn the ledPin off:        
  digitalWrite(ledPin, LOW);   
  // stop the program for for <sensorValue> milliseconds:
  delay(sensorValue);   
  */
  
  sensorValue = analogRead(sensorPin)/2;
  gyroValue = analogRead(gyroPin);  
  Serial.print(gyroValue);
  Serial.print(" : ");
  Serial.println(sensorValue);
  if(sensorValue > 230 && sensorValue < 250){
    analogWrite(outPin1,1);
    analogWrite(outPin2,1);
  }else if(sensorValue > 255){
    analogWrite(outPin1,0);
    analogWrite(outPin2,sensorValue - 256);
  }else{
    analogWrite(outPin1,255 - sensorValue);
    analogWrite(outPin2,0);
  }
  //delay(30);
  //delay(30);
  
  /*
  analogWrite(outPin1,128);
  analogWrite(outPin2,0);
  delay(1000);
  analogWrite(outPin1,0);
  analogWrite(outPin2,128);
    delay(1000);
*/
}
