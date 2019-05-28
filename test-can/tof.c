#include "tof.h"

int tof_val[NB_TOF];

void ToF_Update(){
  RC_Call(&jostof_client, 0,
	  &tof_val[0],
	  &tof_val[1],
	  &tof_val[2],
	  &tof_val[3]);
}

void ToF_Print(){
  printf("ToF : "
	 "\tfl : \t%d" "\tfr : \t%d"
	 "\trl : \t%d" "\trr : \t%d"
	 "\n",
	 tof_val[TOF_FRONT_LEFT],
	 tof_val[TOF_FRONT_RIGHT],
	 tof_val[TOF_REAR_LEFT],
	 tof_val[TOF_REAR_RIGHT]);
}

bool check_direction(bool front){
  ToF_Update();
  int values[2];
  if(front){
    values[0] = tof_val[TOF_FRONT_LEFT];
    values[1] = tof_val[TOF_FRONT_RIGHT];
  }else{
    values[0] = tof_val[TOF_REAR_LEFT];
    values[1] = tof_val[TOF_REAR_RIGHT];
  }

  //TODO : stop sending 0 when it's not
  return !(((values[0] != 0) && (values[0] < TOF_SAFE_DIST))
	   || ((values[1] != 0) && (values[1] < TOF_SAFE_DIST)));
}
