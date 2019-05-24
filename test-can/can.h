#pragma once

#include <stdint.h>

#define CAN_DEV "can0"
#define DEBUG_CAN

#define LOCAL_ID  0x00
#define JOSTOF_ID 0x02
#define TX_CAN_ID ((uint32_t) ((((LOCAL_ID) & 0x3F) << 6) | ((JOSTOF_ID) & 0x3F)))
#define RX_CAN_ID ((uint32_t) ((((JOSTOF_ID) & 0x3F) << 6) | ((LOCAL_ID) & 0x3F)))
#define CAN_ID_MASK 0x7FF

int open_can();

uint8_t can_transmit(void *link_handler,
		     uint32_t can_id,
		     uint8_t *data,
		     uint16_t len,
		     uint32_t timeout);

// data must have at least 8 bytes available
int can_read(uint32_t *id, uint8_t *data);
