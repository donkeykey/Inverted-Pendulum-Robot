/*

Copyright (c) 2012, 2013 RedBearLab

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

/*
 *    Chat
 *
 *    Simple chat sketch, work with the Chat iOS App.
 *    Type something from Arduino serial monitor to
 *    send to the Chat App or vice verse.
 *
 *    Remember to set "Both NL & CR" and "57600 baud"
 *    in the Serial Monitor.
 *
 */

//"services.h/spi.h/boards.h" is needed in every new project
#include <SPI.h>
#include <boards.h>
#include <ble_shield.h>
#include <services.h> 


double deg = 90;
int count = 0;
char dat[32];

void setup()
{  
  // Default pins set to 9 and 8 for REQN and RDYN
  // Set your REQN and RDYN here before ble_begin() if you need
  //ble_set_pins(3, 2);
  pinMode(6, OUTPUT);     
  pinMode(7, OUTPUT);  
  
  
  // Init. and start BLE library.
  ble_begin();
  
  // Enable serial debug
  Serial.begin(57600);
}



void loop(){
   if ( ble_available() ){
    dat[count] = ble_read();
    if (count > 30 || dat[count] == '=') {  // 文字数が既定の個数を超えた場合、又は終了文字を受信した場合
      dat[count] = '\0';                    // 末尾に終端文字を入れる
      count = 0;                            // 文字カウンタをリセット
    } else {
      count++;                              // 文字カウンタに 1 加算
    }
      //deg = dat;
      //deg_y = deg_y + 90;
      //Serial.print("x : ");
      deg = atof(dat);
      Serial.println(deg);
      //Serial.print(" , y : ");
      //Serial.println(deg_y);
      if(deg == 0){
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
      }else if(deg > 0){
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
      }else{
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
      }
  } 
  

  ble_do_events();
}

void doProccess(){

}
