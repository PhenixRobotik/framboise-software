#include "can.h"

#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <unistd.h>

#include <stdio.h>


static int can_fd;

int open_can(){
  can_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  if(can_fd == -1){
    return -1;
  }

  struct ifreq ifr;
  strcpy(ifr.ifr_name, CAN_DEV);
  ioctl(can_fd, SIOCGIFINDEX, &ifr);
  
  struct sockaddr_can addr;
  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  if(bind(can_fd, (struct sockaddr *)&addr, sizeof(addr)) != 0){
    return -1;
  }
  
  return 0;
}

uint8_t can_transmit(void *link_handler,
		     uint32_t can_id,
		     uint8_t *data,
		     uint16_t len,
		     uint32_t timeout){
  (void)link_handler;
  (void)timeout;

  while(len){
    uint16_t frame_size = (len < 8)?(len):8;

    struct can_frame frame;
    frame.can_id = can_id;
    frame.can_dlc = frame_size;

    int i;
    for(i = 0; i < frame_size; ++i){
      frame.data[i] = data[i];
    }

    int written = 0;
    if((written = write(can_fd, &frame, sizeof(struct can_frame))) != sizeof(struct can_frame)){
      printf("%d written\n", written);
      fflush(stdout);
      return -1;
    }
    len -= frame_size;
    data += frame_size;
  }
  // TODO : timeout / retry
  
  return 0;
}

int can_read(uint32_t *id, uint8_t *data){
  struct can_frame frame;
  int count = read(can_fd, &frame, sizeof(struct can_frame));
  if((ulong) count < sizeof(struct can_frame)){
    return -1;
  }

  *id = frame.can_id;

#ifdef DEBUG_CAN
  printf("CAN_RX : %d bytes, id %d : ", frame.can_dlc, frame.can_id);
#endif
  
  int i;
  for(i = 0; i < frame.can_dlc; ++i){
    data[i] = frame.data[i];
    #ifdef DEBUG_CAN
    printf("%2.2X ", data[i]);
    #endif
  }
  #ifdef DEBUG_CAN
  printf("\n");
  fflush(stdout);
  #endif
  
  return frame.can_dlc;
}

