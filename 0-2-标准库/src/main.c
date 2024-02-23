#include "stm32f10x.h"
#include "Delay.h"
#define RCC_GPIOC RCC_APB2Periph_GPIOC
#define LEDBUILDIN GPIO_Pin_13
#define LEDPORT GPIOC
int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LEDBUILDIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LEDPORT, &GPIO_InitStructure);


	while (1)
	{


		GPIO_ResetBits(LEDPORT, LEDBUILDIN);
		Delay_ms(500);
		GPIO_SetBits(LEDPORT, LEDBUILDIN);
		Delay_ms(500);
	}
}
