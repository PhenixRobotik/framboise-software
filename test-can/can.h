#ifndef CAN_H
#define CAN_H

#include <stdint.h>

#define CAN_DEV "can0"
//#define DEBUG_CAN

#define LOCAL_ID  0x00
#define TSMR_ID   0x01
#define JOSTOF_ID 0x02
#define CAN_ID_MASK 0x7FF

#define JOSTOF_TX_CAN_ID ((uint32_t) ((((LOCAL_ID) & 0x3F) << 6) | ((JOSTOF_ID) & 0x3F)))
#define JOSTOF_RX_CAN_ID ((uint32_t) ((((JOSTOF_ID) & 0x3F) << 6) | ((LOCAL_ID) & 0x3F)))
#define TSMR_TX_CAN_ID   ((uint32_t) ((((LOCAL_ID) & 0x3F) << 6) | ((TSMR_ID) & 0x3F)))
#define TSMR_RX_CAN_ID   ((uint32_t) ((((TSMR_ID) & 0x3F) << 6) | ((LOCAL_ID) & 0x3F)))

int open_can();

uint8_t can_transmit(void *link_handler,
		     uint32_t can_id,
		     uint8_t *data,
		     uint16_t len,
		     uint32_t timeout);

// data must have at least 8 bytes available
int can_read(uint32_t *id, uint8_t *data);

#endif
