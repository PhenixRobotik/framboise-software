#ifndef TOF_H
#define TOF_H

#include <stdbool.h>
#include "can.h"
#include "server.h"

#define NB_TOF 4

#define TOF_FRONT_LEFT  3
#define TOF_FRONT_RIGHT 2
#define TOF_REAR_LEFT   1
#define TOF_REAR_RIGHT  0

#define TOF_SAFE_DIST 200

void ToF_Update();
void ToF_Print();

//Return true if the direction is clear
bool check_direction(bool front);

#endif
