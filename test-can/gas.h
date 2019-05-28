#ifndef GAS_H
#define GAS_H

#include <stdbool.h>

typedef enum{GAS_FORWARD, DRAWROF_SAG}Gas_Dir;

void gas_set_position(double x, double y, double theta, bool backward);
void gas_rotate(double theta);

#endif
