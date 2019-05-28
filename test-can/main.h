#ifndef __MAIN_H_
#define __MAIN_H_

#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <math.h>
#include <unistd.h>

#include "can/robotronik_protocol.h"
#include "can/remote_call.h"
#include "uart.h"
#include "logger.h"
#include "server.h"

#define UART_PATH "/dev/serial0"
#define UART_SPEED B1000000

extern RP_Interface f4_iface;
extern RC_Server server;
extern volatile sig_atomic_t run;
extern volatile sig_atomic_t stop;

uint32_t get_tick();

#endif
