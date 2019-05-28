#ifndef ASSER_H
#define ASSER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define ASSER_POLLING_MS 100

typedef struct Position_S{
  double x, y, theta;
}Position;

typedef enum{ASSER_DONE, ASSER_BUSY}Asser_State;

// TODO : return RC/RP codes
void asser_stop();
Asser_State asser_get_state();
void asser_get_pos(Position *pos);
Asser_State asser_set_rotation_speed(double rdps);
Asser_State asser_set_translation_speed(double mmps);
Asser_State asser_rotate(double theta);
Asser_State asser_translate(double dist);
Asser_State asser_set_position(double x, double y, double theta, bool dir);
void asser_enable();
void asser_disable();

// TODO : check speed
// TODO : prevent comm deadlocks
Asser_State asser_wait_ready(int timeout_ms, bool stop_on_timeout);

#endif
