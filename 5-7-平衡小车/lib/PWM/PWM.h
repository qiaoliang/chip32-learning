#ifndef __PWM_H
#define __PWM_H
#include <stdint.h>
#include "stm32f10x.h"

#define PWM_MAX 7000
#define PWM_MIN 0
void PWM_Limited(int *PWM);
void PWM_Init(void);
void PWM_SetCompare3(uint16_t Compare); // 对应 PA3 引脚
void PWM_SetCompare2(uint16_t Compare);  // 对应 PA2 引脚
#endif
