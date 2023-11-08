#include "stm32f10x.h"

void Delay_ms(int ms)
{
    while (ms-- > 0)
    {
        volatile int x = 500;
        while (x-- > 0)
            __asm("nop");
    }
}
int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    while (1)
    {
        Delay_ms(100);
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        Delay_ms(100);
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    }
}