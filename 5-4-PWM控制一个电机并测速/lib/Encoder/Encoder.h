#ifndef __ENCODER_H
#define __ENCODER_H
#include <stdint.h>
#include "stm32f10x.h"
#define Encoder_TIMER_CLK RCC_APB1Periph_TIM3
#define Encoder_GPIO_CLK RCC_APB2Periph_GPIOA

#define Encoder_GPIO_Port GPIOA
#define Encoder_A_Pin GPIO_Pin_6
#define Encoder_B_Pin GPIO_Pin_7
#define Encoder_TIMER TIM3

void Encoder_Init(void);
int16_t Encoder_Get(void);

#endif
