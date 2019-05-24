#pragma once

#include "can/remote_call.h"

typedef enum Server_Functions_E{
  GET_ASSER_DATA,
} Server_Functions;

int load_pid_data();

void get_asser_data(RC_Server *server);
