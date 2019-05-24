#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <math.h>
#include <unistd.h>

#include "can_protocol/remote_call.h"
#include "can_protocol/robotronik_protocol.h"

#define UART_PATH "/dev/serial0"
#define UART_SPEED B1000000

extern RC_Server server;
extern volatile sig_atomic_t run;
extern volatile sig_atomic_t stop;
