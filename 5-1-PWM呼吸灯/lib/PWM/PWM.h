#ifndef __PWM_H
#define __PWM_H
#include <stdint.h>


#define PWM_OUT_PIN GPIO_Pin_0
#define PWM_OUT_PORT GPIOA
#define PWM_OUT_CLK RCC_APB2Periph_GPIOA
#define PWM_TIMER_CLK RCC_APB1Periph_TIM2
#define TIMER_USED_BY_PWM TIM2
#define PWM_PRESCALER 720-1
#define PWM_ARR 100-1
#define PWM_CCR 50

void PWM_Init(void);
void PWM_SetCompare1(uint16_t Compare);

#endif
