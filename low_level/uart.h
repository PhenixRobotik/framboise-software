#pragma once

#include <stdint.h>
#include <termios.h>

int open_uart(const char* path, speed_t speed);
uint8_t send_uart(void* link_handler, uint8_t *data, uint16_t len, uint32_t timeout);
uint32_t get_tick();
