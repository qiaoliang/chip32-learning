#ifndef __ENCODER_H
#define __ENCODER_H
#include <stdint.h>
#include "stm32f10x.h"

// TIM3 for Left Encoder
#define Encoder_Left_TIMER_CLK RCC_APB1Periph_TIM3
#define Encoder_Left_GPIO_CLK RCC_APB2Periph_GPIOA

#define Encoder_Left_GPIO_Port GPIOA
#define Encoder_Left_A_Pin GPIO_Pin_6
#define Encoder_Left_B_Pin GPIO_Pin_7
#define Encoder_Left_TIMER TIM3

// TIM4 for Right Encoder
#define Encoder_Right_TIMER_CLK RCC_APB1Periph_TIM4
#define Encoder_Right_GPIO_CLK RCC_APB2Periph_GPIOB

#define Encoder_Right_GPIO_Port GPIOB
#define Encoder_Right_A_Pin GPIO_Pin_6
#define Encoder_Right_B_Pin GPIO_Pin_7
#define Encoder_Right_TIMER TIM4

void Encoder_Init(void);
int16_t Encoder_Left_Get(void);
int16_t Encoder_Right_Get(void);

#endif
