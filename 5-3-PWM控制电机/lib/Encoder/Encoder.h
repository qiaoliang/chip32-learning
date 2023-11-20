#ifndef __ENCODER_H
#define __ENCODER_H
#include <sys.h>
#define ENCODER_TIM_PERIOD (u16)(65535) // 不可大于65535 因为F103的定时器是16位的。

void Encoder_Init_TIM2(void);
void Encoder_Init_TIM3(void);

float Read_EncoderA(void);
float Read_EncoderB(void);

void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);

#endif