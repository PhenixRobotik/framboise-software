#include "gas.h"
#include "asser.h"
#include "tof.h"
#include <unistd.h>

void gas_set_position(double x, double y, double theta, bool backward){
  //TODO : add timeout
  //TODO : errors codes, logs
  //TODO : hystérésis ?
  do{
    asser_set_position(x, y, theta, backward);
    while((asser_get_state() != ASSER_DONE)
	  && (check_direction(!backward))){
      usleep(50000);
    }
    if(asser_get_state() != ASSER_DONE){
      asser_stop();
      while(!check_direction(!backward) || asser_get_state() != ASSER_DONE){
	usleep(50000);
      }
    }else{
      break;
    }
  }while(1);
}

void gas_rotate(double theta){
  do{
    asser_rotate(theta);
    while((asser_get_state() != ASSER_DONE)
	  && (check_direction(true) && check_direction(false))){
      usleep(50000);
    }
    if(asser_get_state() != ASSER_DONE){
      asser_stop();
      while(!check_direction(true) || !check_direction(false) || asser_get_state() != ASSER_DONE){
	usleep(50000);
      }
    }else{
      break;
    }
  }while(1);
}
