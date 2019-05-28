#if 0
void RP_Packet_Received(RP_Interface *interface, RP_Packet *packet){
  (void)interface;
  (void)packet;
  if(true != false){
#ifdef DEBUG_CAN
    printf("Packet of %d bytes received.\n", packet->len);
    int i;
    for(i = 0; i < packet->len; i++){
      printf("0x%2.2X ", packet->data[i]);
    }
    printf("\n\n");
    fflush(stdout);
#endif
  }
}

void RP_Error_Handler(RP_Interface *iface, uint16_t error){
  (void)iface;
  switch(RP_ERROR_TYPE(error)){
  case RP_ERR_INTERNAL:
    //printf("Internal error: ");
    switch(RP_INTERNAL_ERROR(error)){
    case RP_ERR_ILLEGAL_ARGUMENTS:
      log_warning("Illegal arguments");
      break;
    case RP_ERR_BUFFER_OVERFLOW:
      log_warning("Buffer overflow");
      break;
    default:
      log_warning("Unknown");
      break;
    }
    break;
  case RP_ERR_LINK:
    //printf("Link error: ");
    switch(RP_LINK_ERROR(error)){
    case RP_ERR_TIMEOUT:
      log_warning("Timeout");
      break;
    case RP_ERR_UNEXPECTED_EOF:
      log_warning("Unexpected EOF. Synchronized.");
      break;
    default:
      log_warning("Unknown");
      break;
    }
    break;
  default:
    //printf("Unknown error\n");
    break;
  }
}


#if 0
  char str_start[RC_STR_SIZE]= {'s', 't', 'a', 'r', 't', '\0'},
    str_end[RC_STR_SIZE] = {'e', 'n', 'd', '\0'};
  uint8_t byte = 0;
  uint16_t half_word = 0;
  uint32_t u_word = 0;
  int word = 0;
  float simpleFloat = 0;
  double doubleFloat = 0;
#endif

  int tof[4] = {-1};
  double x, y, theta;

  /*
  //Receive data
  while(run && !stop){
    asser_enable();
    for(int i = 0; i < 100; ++i){
      usleep(50000);
      RC_Call(&tsmr_client, GET_ODOMETRY, &x, &y, &theta);
      printf("Odometry : x:\t%lf\t" "y:\t%lf\t" "theta:\t%lf\t" "\n", x, y, theta);
    }
    printf("----- RESET -----\n");
    asser_disable();
    usleep(20000);
    }*/

  /*  asser_set_rotation_speed(3.141592/2);
  asser_set_translation_speed(100);
  asser_rotate(4);
  asser_wait_ready(20000, true);
  asser_set_position(100, 100, 1.57, GAS_FORWARD);
  asser_wait_ready(10000, true);*/

    /* Test function */
#if 0
    usleep(200000);

    RC_Call(&jostof_client, 0,
      &tof[0], &tof[1], &tof[2], &tof[3]);
    printf("ToF :\t%d\t%d\t%d\t%d\n", tof[0], tof[1], tof[2], tof[3]);	    
   

    printf("Sending      %s, %u, %u, %u, %d, %f, %lf, %s\n",
      str_start, byte, half_word, u_word, word, simpleFloat, doubleFloat, str_end);
    RC_Call(&tsmr_client, 0,
	    str_start,  byte,  half_word,  u_word,  word,  simpleFloat,  doubleFloat, str_end,
	    str_start, &byte, &half_word, &u_word, &word, &simpleFloat, &doubleFloat, str_end);
    printf("New values : %s, %u, %u, %u, %d, %f, %lf, %s\n",
	   str_start, byte, half_word, u_word, word, simpleFloat, doubleFloat, str_end);
#endif

    //RC_Call(&tsmr_client, GET_ODOMETRY, &x, &y, &theta);
    //printf("Odometry : x:\t%lf\t" "y:\t%lf\t" "theta:\t%lf\t" "\n", x, y, theta);
#endif
