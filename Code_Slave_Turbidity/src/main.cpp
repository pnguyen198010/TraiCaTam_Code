#include <Arduino.h>

#include "log.h"


Log_t myLog;

void setup() 
{
  Log_init();

  myLog.raw("This is log raw\n");
  myLog.fmt("(%lu) This is log format\n", millis());
}


void loop() 
{

}