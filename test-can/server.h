#ifndef __SERVER_H__
#define __SERVER_H__

#include "can/remote_call.h"
#include "main.h"

typedef enum Server_Functions_E{
  GET_ASSER_DATA,
}Server_Functions;

int load_pid_data();

void get_asser_data(RC_Server *server);

#endif
