#include <Arduino.h>

#include "log.h"


Log_t myLog;


void setup() 
{
  Log_init();

  myLog.raw("This is log raw\n");
  myLog.fmt("(%lu) This is log format\n", millis());
  myLog.inf("This is log info");
  myLog.err("This is log err");
}


void loop() 
{
  static uint32_t intv = millis();

  if(millis() - intv < 5000)
  {
    myLog.upd("This is log upd");
  }

  else
  {
    intv = millis();
    myLog.inf("This is the last log");
    myLog.disable();
  }
}