#include "asser.h"

#include "server.h"
#include "main.h"

//TODO : logs (RC, RP)
//TODO : communication thread
//

Asser_State asser_wait_ready(int timeout_ms, bool stop_on_timeout){
  uint32_t tick_timeout = get_tick() + timeout_ms;
  Asser_State state;
  while(((state = asser_get_state()) != ASSER_DONE) && (get_tick() <= tick_timeout));
  if(stop_on_timeout && (state == ASSER_BUSY)){
    asser_stop();
    state = ASSER_BUSY;
  }
  return state;
}

void asser_stop(){
  RC_Call(&tsmr_client, SET_STOP);
}

Asser_State asser_get_state(){
  Asser_State state;
  RC_Call(&tsmr_client, GET_STATE, &state);
  return state;
}

void asser_get_pos(Position *pos){
  RC_Call(&tsmr_client, GET_ODOMETRY, &pos->x, &pos->y, &pos->theta);
  pos->theta = -pos->theta; // Maxime fdp
}

Asser_State asser_set_rotation_speed(double rdps){
  Asser_State state;
  RC_Call(&tsmr_client, SET_THETA_SPEED, rdps, &state);
  return state;
}

Asser_State asser_set_translation_speed(double mmps){
  Asser_State state;
  RC_Call(&tsmr_client, SET_TRANSLATION_SPEED, mmps, &state);
  return state;
}

Asser_State asser_rotate(double theta){
  Asser_State state;
  RC_Call(&tsmr_client, SET_THETA, theta, &state);
  return state;
}

Asser_State asser_translate(double dist){
  Asser_State state;
  RC_Call(&tsmr_client, SET_TRANSLATION, dist, &state);
  return state;
}

Asser_State asser_set_position(double x, double y, double theta, bool dir){
  Asser_State state;
  RC_Call(&tsmr_client, SET_X_Y_THETA, x, y, theta, (uint8_t)dir, &state);
  return state;
}

void asser_enable(){
  RC_Call(&tsmr_client, ASSER_ENABLE);
  usleep(20000);
}

void asser_disable(){
  RC_Call(&tsmr_client, ASSER_DISABLE);
  usleep(20000);
}
