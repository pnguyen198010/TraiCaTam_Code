

#include <Arduino.h>

#include "log.h"
#include "lora_service.h"


void setup() 
{
  Log_init();
  Lora_init();
}


void loop() 
{
  Lora_upd_turbidity();
}
