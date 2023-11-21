#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "Encoder.h"

uint8_t KeyNum;		//定义用于接收按键键码的变量
int8_t Duty;		//定义度变量
int16_t CNT;		//定义CNT变量

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Motor_Init();		//直流电机初始化
	Key_Init();			//按键初始化
	Encoder_Init();		//初始化电机编码器

	/*显示静态字符串*/
	OLED_ShowString(1, 1, "Duty:");		//1行1列显示字符串占空比:
	OLED_ShowString(3, 1, "CNT:");
    int i = 0;
	while (1)
	{
		KeyNum = Key_GetNum();				//获取按键键码
		i++;
		if(i>1000){
		  i=0;
		  CNT = Encoder_Get();
		}
		if(KeyNum == 1) // 按键1按下
		{
			Duty += 20;						// 速度变量自增20
			if (Duty > 100)					// 速度变量超过100后
			{
				Duty = -100; // 速度变量变为-100
							 // 此操作会让电机旋转方向突然改变，可能会因供电不足而导致单片机复位
							 // 若出现了此现象，则应避免使用这样的操作
			}
		}
		Motor_SetSpeed(Duty);				// 设置直流电机的速度为速度变量
		OLED_ShowSignedNum(1, 7, Duty, 3);	// OLED显示速度变量
		OLED_ShowSignedNum(3, 7, CNT, 5); // 不断刷新显示编码器测得的最新速度
	}
}
