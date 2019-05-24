#include "main.h"


#include "low_level/can.h"
#include "low_level/uart.h"
#include "low_level/logger.h"


void sigterm_handler(int signo);
void sigint_handler(int signo);

RC_Client client;
volatile sig_atomic_t run;//uart loop
volatile sig_atomic_t stop = 0;//Ctrl+C

void RP_Packet_Received(RP_Interface *interface, RP_Packet *packet){
  if(interface == &f4_iface){
#ifdef DEBUG_CAN
    printf("Packet of %d bytes received.\n", packet->len);
    int i;
    for(i = 0; i < packet->len; i++){
      printf("0x%2.2X ", packet->data[i]);
    }
    printf("\n\n");
    fflush(stdout);
#endif

    //RC_Server_Get_Request(&server, packet);
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

int main(){
  LOG_Set_Level(LOG_INFO_LEVEL);
  log_info("Initializing...");

  //Signals initializations
  struct sigaction act_sigterm, act_sigint;
  sigemptyset(&act_sigterm.sa_mask);
  sigemptyset(&act_sigint.sa_mask);
  memset(&act_sigterm, 0, sizeof(act_sigterm));
  memset(&act_sigint, 0, sizeof(act_sigint));
  act_sigterm.sa_handler = sigterm_handler;
  act_sigint.sa_handler = sigint_handler;
  if(sigaction(SIGTERM, &act_sigterm, NULL) == -1){
    log_error("Could not affect SIGTERM handler");
  }
  if(sigaction(SIGINT, &act_sigint, NULL) == -1){
    log_error("Could not affect SIGINT handler");
  }

  //CAN Initialization
  if(open_can() == -1){
    log_error("Could not open CAN");
    exit(EXIT_FAILURE);
  }

  //Interface Robotronik Protocol
  RP_Init_Interface(&f4_iface, NULL, TX_CAN_ID, can_transmit, get_tick);

  RC_Client_Init(&client, &f4_iface, 0);
  RC_Client_Add_Function(&client, 0, "sbBuifFs", "sbBuifFs");

  RP_Sync(&f4_iface, 10);


  //Receive data
  run = 1;
  char str_start[RC_STR_SIZE]= {'s', 't', 'a', 'r', 't', '\0'},
    str_end[RC_STR_SIZE] = {'e', 'n', 'd', '\0'};
  uint8_t byte = 0;
  uint16_t half_word = 0;
  uint32_t u_word = 0;
  int word = 0;
  float simpleFloat = 0;
  double doubleFloat = 0;
  do{
    /* Test function */
    usleep(1000);

    /*printf("Sending      %s, %u, %u, %u, %d, %f, %lf, %s\n",
      str_start, byte, half_word, u_word, word, simpleFloat, doubleFloat, str_end);*/
    RC_Call(&client, 0,
	    str_start,  byte,  half_word,  u_word,  word,  simpleFloat,  doubleFloat, str_end,
	    str_start, &byte, &half_word, &u_word, &word, &simpleFloat, &doubleFloat, str_end);
    printf("New values : %s, %u, %u, %u, %d, %f, %lf, %s\n",
	   str_start, byte, half_word, u_word, word, simpleFloat, doubleFloat, str_end);
  }while(run && !stop);

  if(stop){
    //Stop the robot
  }

  // Close SocketCAN ?

  log_info("Main loop stopped. Idle state.");
  stop = 0;
  while(!stop);
  log_info("Quit");

  return EXIT_SUCCESS;
}

void sigterm_handler(int signo){
  if(signo == SIGTERM){
    printf("\n");
    log_warning("SIGTERM received.");
    stop = 1;
  }
}

void sigint_handler(int signo){
  if(signo == SIGINT){
    printf("\n");
    log_warning("SIGINT received.");
    stop = 1;
  }
}
