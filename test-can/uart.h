#ifndef __UART_H_
#define __UART_H_

#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/time.h>

#include "can/robotronik_protocol.h"
#include "can/remote_call.h"
#include "logger.h"
#include "main.h"

int open_uart(const char* path, speed_t speed);
uint8_t send_uart(void* link_handler, uint8_t *data, uint16_t len, uint32_t timeout);

#endif
