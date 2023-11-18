#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

int main(void)
{

    OLED_Init();
	PWM_Init();
	PWM_SetCompare1(50);
	while (1)
	{
		for(int i=0;i<100;i++){
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
		for(int i=100;i>0;i--){
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
	}
}
