

#include <Arduino.h>

#include "log.h"
#include "lora_service.h"
#include "turbidity.h"


void setup() 
{
  Log_init();
  Lora_init();
  Turbidity_init();
}


void loop() 
{
  Lora_upd_turbidity();
}
