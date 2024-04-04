#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f10x.h"
#include "Delay.h"

#define KEY_1 GPIO_Pin_1
#define KEY_2 GPIO_Pin_11


void KEY_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = KEY_1 | KEY_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * 函    数：按键获取键码
 * 参    数：无
 * 返 回 值：按下按键的键码值，范围：0~2，返回0代表没有按键按下
 * 注意事项：此函数是阻塞式操作，当按键按住不放时，函数会卡住，直到按键松手
 */
uint8_t Key_GetNum(void)
{
    uint8_t KeyNum = 0; // 定义变量，默认键码值为0

    if (GPIO_ReadInputDataBit(GPIOB, KEY_1) == 0) // 读PB1输入寄存器的状态，如果为0，则代表按键1按下
    {
        Delay_ms(20); // 延时消抖
        while (GPIO_ReadInputDataBit(GPIOB, KEY_1) == 0)
            ;         // 等待按键松手
        Delay_ms(20); // 延时消抖
        KeyNum = 0x01;   // 置键码为0b01
    }

    if (GPIO_ReadInputDataBit(GPIOB, KEY_2) == 0) // 读PB1输入寄存器的状态，如果为0，则代表按键1按下
    {
        Delay_ms(20); // 延时消抖
        while (GPIO_ReadInputDataBit(GPIOB, KEY_2) == 0)
            ;         // 等待按键松手
        Delay_ms(20); // 延时消抖
        KeyNum = KeyNum | 0x02; // 保存状态键码为0b10
    }
    return KeyNum; // 返回键码值，如果没有按键按下，所有if都不成立，则键码为默认值0
}
#endif