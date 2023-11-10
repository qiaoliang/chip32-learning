#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
/**
 * @brief 使用两个开关分别控制两个LED灯.
 *        每按一次, LED 灯状态取反.
 *
 * @return int
 */
int main(void)
{
	LED_Init();
	KEY_Init();

	while (1)
	{
		uint8_t key = Key_GetNum();
		if (key & 0x01)	// 0x01 = 0b01 , 取第一个按键的按下动作
		{
			LED1_turn();
		}
		if(key & 0x02)  // 0x02 = 0b10 , 取第二个按键的按下动作
		{
			LED2_turn();
		}
	}
}
