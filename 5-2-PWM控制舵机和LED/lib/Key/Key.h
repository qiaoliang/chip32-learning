#ifndef __KEY_H
#define __KEY_H
#include <stdint.h>

#define KEY_1 GPIO_Pin_1
#define KEY_2 GPIO_Pin_11

#define KEY_PORT GPIOB

#define KEY_RCC_CLK RCC_APB2Periph_GPIOB


void Key_Init(void);
uint8_t Key_GetNum(void);

#endif
