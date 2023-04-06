

#include <Arduino.h>

#include "log.h"
#include "lora_service.h"
#include "turbidity.h"
#include "bell.h"


void setup() 
{
  Log_init();
  Lora_init();
  Turbidity_init();
  Bell_init();
}


void loop() 
{
  Lora_upd_bellState();
  Bell_alert();
}
