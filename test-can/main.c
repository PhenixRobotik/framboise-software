#include "main.h"

#include "can.h"
#include "server.h"
#include "asser.h"
#include "gpio.h"
#include "gas.h"
#include "main.h"
#include "match.h"
#include <pthread.h>

static void sig_init();
void sigterm_handler(int signo);
void sigint_handler(int signo);

volatile sig_atomic_t run;//uart loop
volatile sig_atomic_t stop = 0;//Ctrl+C

pthread_mutex_t mutex_send = PTHREAD_MUTEX_INITIALIZER;
int main(){
  LOG_Set_Level(LOG_INFO_LEVEL);
  log_info("Initializing...");

  sig_init();

  //CAN Initialization
  if(open_can() == -1){
    log_error("Could not open CAN");
    exit(EXIT_FAILURE);
  }

  //Interface Robotronik Protocol
  init_jostof_rc();
  init_tsmr_rc();
  init_gpio();
  
  run = 1;

  pthread_t match_thread;
  wait_start();
  pthread_create(&match_thread, NULL, match, NULL);
  sleep(100);
  pthread_cancel(match_thread);
  asser_disable();
  led_end();

  log_info("Match thread stopped.");
  
  do{
    
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

static void sig_init(){
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
}

uint32_t get_tick(){
  struct timeval t;
  gettimeofday(&t, NULL);
  return (t.tv_sec * 1000) + (t.tv_usec / 1000);
}
