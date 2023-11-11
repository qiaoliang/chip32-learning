#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"

#define LED_1 GPIO_Pin_1
#define LED_2 GPIO_Pin_2

BitAction LED_Status[2] = {Bit_RESET, Bit_SET};
uint8_t LED1_Status = 0;
uint8_t LED2_Status = 0;

void LED_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED_1 | LED_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void LED1_turn()
{
    LED1_Status = 1 - LED1_Status;
    GPIO_WriteBit(GPIOA, LED_1, LED_Status[LED1_Status]);
}
void LED2_turn()
{
    LED2_Status = 1 - LED2_Status;
    GPIO_WriteBit(GPIOA, LED_2, LED_Status[LED2_Status]);
}
#endif