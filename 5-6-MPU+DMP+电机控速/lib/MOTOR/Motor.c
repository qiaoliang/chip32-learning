#include "stm32f10x.h"                  // Device header
#include "PWM.h"

/**
  * 函    数：直流电机初始化
  * 参    数：无
  * 返 回 值：无
  */
void Motor_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						//将PA4和PA5引脚初始化为推挽输出

	PWM_Init();													//初始化直流电机的底层PWM
}

/**
  * 函    数：直流电机设置速度
  * 参    数：Speed 要设置的速度，范围：-100~100
  * 返 回 值：无
  */
void Motor_SetSpeed(int8_t Speed)
{
	if (Speed >= 0)							//如果设置正转的速度值
	{
		left_positive();
		right_positive();
		PWM_SetCompare2(Speed); // PWM设置为速度值
		//TIM_SetCompare1(TIM1, PWM_MAX - Speed); // 这里为什么是7200-PWM，因为高级定时器的某些通道PWM输出反相，示波器测一下就知道了，群公告里也有写
	}
	else									//否则，即设置反转的速度值
	{
		left_negative();
		right_negative();
		PWM_SetCompare3(-Speed); // PWM设置为负的速度值，因为此时速度值为负数，而PWM只能给正数
	    //TIM_SetCompare1(TIM1, PWM_MAX + Speed);
	}
}

void left_positive(){
	GPIO_SetBits(GPIOA, GPIO_Pin_4);   // PA4置高电平
	GPIO_ResetBits(GPIOA, GPIO_Pin_5); // PA5置低电平，设置方向为正转
}
void left_negative(){
	GPIO_ResetBits(GPIOA, GPIO_Pin_4); // PA4置低电平
	GPIO_SetBits(GPIOA, GPIO_Pin_5);   // PA5置高电平，设置方向为反转
}
void right_positive()
{
	// TODO:
}

void right_negative()
{
	// TODO:
}