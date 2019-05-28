#ifndef GPIO_H
#define GPIO_H

#define GPIO_SELEC 22
#define GPIO_START 25

#define GPIO_LED_R 24
#define GPIO_LED_G 27
#define GPIO_LED_B 23

#define START_LEVEL  0
#define SELEC_YELLOW 0
#define SELEC_VIOLET 1

typedef enum Team_Color_E{
  TEAM_YELLOW = SELEC_YELLOW,
  TEAM_VIOLET = SELEC_VIOLET
}Team_Color;

void init_gpio();
void wait_start();
Team_Color readTeamColor();
void led_end();

#endif
