#ifndef __SERVER_H__
#define __SERVER_H__

#include "can/remote_call.h"
#include "main.h"

#define NB_FUNS 10
typedef enum Server_Functions_E{
  SET_STOP,
  SET_THETA,
  SET_THETA_SPEED,
  SET_TRANSLATION,
  SET_TRANSLATION_SPEED,
  SET_X_Y_THETA,
  GET_ODOMETRY,
  GET_STATE,
  ASSER_ENABLE,
  ASSER_DISABLE
}Server_Functions;

extern RP_Interface jostof_iface;
extern RP_Interface tsmr_iface;
extern RC_Client jostof_client;
extern RC_Client tsmr_client;

int init_jostof_rc();
int init_tsmr_rc();

#endif
