// nhận
#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <SoftwareSerial.h>
/*************************************/
#define tx 5
#define rx 4
int LED = 10;
int M1 = 11;
int M2 = 12;
int i;
char HC12ByteIn;  
String HC12ReadBuffer = "";
SoftwareSerial tai(tx,rx);

/*************************************/

struct PacketData{
  unsigned long hours;
  unsigned long minutes;
  unsigned long seconds;  
  };
PacketData data;
/*************************************/
int packetCounts[10];
int packetCountIndex = 0;
int packetCountTotal = 0;
#define AVG_SECONDS 10
int avgs [AVG_SECONDS];
int avgIndex = 0;
unsigned long avgTotal = 0;
/*************************************/
void setup(void) {
  
Serial.begin(9600);
tai.begin(9600); 
i=1;
pinMode(LED, OUTPUT);
pinMode(M1, OUTPUT);
pinMode(M2, OUTPUT);

digitalWrite(LED, LOW);
digitalWrite(M1, LOW);
digitalWrite(M2, LOW);
                       
HC12ReadBuffer.reserve(64);

memset (&data, 0, sizeof(PacketData));
memset (packetCounts,0,sizeof(packetCounts));
memset (avgs,0,sizeof(avgs));

data.hours = 0;
data.minutes = 0;
data.seconds = 0;

}
/*************************************/
unsigned long packetsRead = 0;
unsigned long lastScreenUpdate = 0;
unsigned long lastAvgUpdate = 0;
unsigned long lastRecvTime = 0;
unsigned long drops = 0;
unsigned long lastTick = 0;
/*************************************/
char ppsBuf[16];
char avgBuf[16];
char hmsBuf[16];
char statusBuf[16];
/*************************************/
void timer()
{
unsigned long now = millis();
if (now - lastTick >= 1000){
    data.seconds++;
   
  if (data.seconds >=60 ){
    data.seconds = 0;
    data.minutes++;
    }

 if (data.minutes >= 60){
    data.minutes = 0;
    data.hours++;  
    } 
    lastTick=now;
  }
  }
/*************************************/
void recvData()
{
  while (tai.available()){
    HC12ByteIn = tai.read();
    HC12ReadBuffer = char(HC12ByteIn);
    packetsRead++;
    lastRecvTime = millis();
    }

    if (HC12ReadBuffer=="2"){
    digitalWrite(LED,LOW);
    sprintf(statusBuf,"wait..");
      }

    if (HC12ReadBuffer=="1"){
    digitalWrite(LED,HIGH);
     i++;
    sprintf(statusBuf,"Sig!");
     
    }
  }
  
/*************************************/

void draw (void){

  Serial.println(ppsBuf);
  Serial.println(avgBuf);
  Serial.println(hmsBuf);
  Serial.println(statusBuf);

}
/*************************************/
void updateScreen(){
  unsigned long now = millis();
  if( now - lastScreenUpdate < 100)
  return;

   // move aver over 1 second
  packetCountTotal -= packetCounts[packetCountIndex];
  packetCounts[packetCountIndex] = packetsRead;
  packetCountTotal += packetsRead;

  packetCountIndex = (packetCountIndex+1) %10;
  packetsRead = 0;

  sprintf(ppsBuf, "PPS: %d", packetCountTotal);
  sprintf(avgBuf, "AVG: %ld", avgTotal/AVG_SECONDS);
  sprintf(hmsBuf, "HMS:%02ld:%02ld:%02ld",data.hours,data.minutes,data.seconds);

  draw();

  lastScreenUpdate = millis();

  if(now - lastAvgUpdate >= 1000){
    //moving aver of 1 second moving aver
    avgTotal -= avgs[avgIndex];
    avgs[avgIndex] = packetCountTotal;
    avgTotal += packetCountTotal;

    avgIndex = (avgIndex + 1) % AVG_SECONDS;
    lastAvgUpdate = millis();
    //
  }
}
/*************************************/
void loop(void) {
    timer();
    recvData();    
    updateScreen();

 
  /*
  if(tai.available()){
    HC12ByteIn = tai.read();
    HC12ReadBuffer = char(HC12ByteIn);
    if (HC12ReadBuffer=="2"){
      digitalWrite(LED,LOW);
      Serial.println("tat");
      delay(500);
      }
    
    
    if (HC12ReadBuffer=="1"){
    digitalWrite(LED,HIGH);
     Serial.println("sang");
    delay(500);
    }
    }
    */
}
/*************************************/
