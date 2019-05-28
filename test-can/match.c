#include "match.h"
#include "gpio.h"
#include "asser.h"
#include "gas.h"

void* match(void* arg){
  asser_enable();
  asser_set_translation_speed(200);
  asser_set_rotation_speed(1.57);

  gas_rotate(3.14/2);
  gas_rotate(-3.14/2);
  
  asser_wait_ready(20000, true);
  gas_set_position(500, 0, 0, GAS_FORWARD);
  asser_wait_ready(20000, true);
  gas_set_position(0, 0, 3.141592, GAS_FORWARD);
  asser_wait_ready(20000, true);
  gas_set_position(300, 0, 0, DRAWROF_SAG);
  asser_wait_ready(20000, true);

  return arg;
}
