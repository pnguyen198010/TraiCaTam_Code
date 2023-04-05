// gui
#include <Arduino.h>
#include <LoRa.h>
#include <SoftwareSerial.h>
#define tx 1
#define rx 0
#define nut 12 // D2
#define led 2 // D10 
#define M1 8
#define M2 7
const char *ketqua1;
SoftwareSerial tai(tx,rx); 
/*****************************************/

void setup() {
Serial.begin(9600);  
tai.begin(9600); 
pinMode(nut,INPUT_PULLUP); 
pinMode(led,OUTPUT);
pinMode(M1, OUTPUT);
pinMode(M2, OUTPUT);


digitalWrite(led, LOW);
digitalWrite(M1, LOW);
digitalWrite(M2, LOW);
}

/*****************************************/

void loop() {

 int a = digitalRead(nut);
   
    if(a==LOW){
          ketqua1="1";         
          tai.write(ketqua1);
          digitalWrite(led, HIGH);
          Serial.println(ketqua1);
          delay(10);
              }
              
    else {
          ketqua1="2";
          tai.write(ketqua1);
          digitalWrite(led, LOW);
          Serial.println(ketqua1);
          delay(100);
         }
         
}
