#include "gpio.h"

#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>

void init_gpio(){
  wiringPiSetup();
  pinMode(GPIO_SELEC, INPUT);
  pinMode(GPIO_START, INPUT);
  pinMode(GPIO_LED_R, OUTPUT);
  softPwmCreate(GPIO_LED_G, 0, 50);
  pinMode(GPIO_LED_B, OUTPUT);

  digitalWrite(GPIO_LED_R, 0);
  softPwmWrite(GPIO_LED_G, 0);
  digitalWrite(GPIO_LED_B, 0);
}

void wait_start(){
  int notGAS = 5;
  do{
    usleep(1000);
    if(digitalRead(GPIO_START) == START_LEVEL){
      notGAS--;
    }else{
      notGAS = 5;
    }
    readTeamColor();
  }while(notGAS);

  return;
}

Team_Color readTeamColor(){
  if(digitalRead(GPIO_SELEC) == SELEC_YELLOW){
    digitalWrite(GPIO_LED_R, 1);
    softPwmWrite(GPIO_LED_G, 18);
    digitalWrite(GPIO_LED_B, 0);
    return TEAM_YELLOW;
  }else{
    digitalWrite(GPIO_LED_R, 1);
    softPwmWrite(GPIO_LED_G, 0);
    digitalWrite(GPIO_LED_B, 1);
    return TEAM_VIOLET;
  }
}

void led_end(){
  digitalWrite(GPIO_LED_R, 1);
  softPwmWrite(GPIO_LED_G, 0);
  digitalWrite(GPIO_LED_B, 0);
}
