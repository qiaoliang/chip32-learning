#include <stm32f10x.h>
#include "delay.h"
#include "oled.h"
#include "sys.h"
#include "usart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "motor.h"

extern float pitch, roll, yaw; // 欧拉角测量值
float balance_angle = -0.45;   // 小车平衡时的角度
extern int velocity;		   // 速度测量值（编码器脉冲数，非真实速度）
extern float velocity_sum;	   // 速度积分
int motor_flag;				   // 电机使能标志：1使能  0失能

// 先调整直立环参数,
// 1, 速度环参数都为0, 然后调整直立环的Kp, 直到小车大幅度摇摆振动.
//   float Kp = -1100, Ki = 0, Kd = 0, VKp = 0, VKi = 0;

// 2,速度环参数都为0, 然后调整Kd 值, 改善振幅, 直到让小车变成小幅度高频摇
//   float Kp = -1100, Ki = 0, Kd = -4500, VKp = 0, VKi = 0; 摆振动

// 3, 同时将Kp 和 Kd 数值乘0.6 ,小车此时不振动了, 无法保持平衡.是正常现象.
// float Kp = -660, Ki = 0, Kd = -2700,  VKp = 0, VKi = 0;

//  开始调整速度环PI参数:  VKp 与 Vki之间是200的倍数关系
// 4, 保持直立环参数不变, 从 VKp = 100, Vki= 0.5 开始调整.让小车趋向平衡
float Kp = -660, Ki = 0, Kd = -2700,  VKp = 2400, VKi = 1.2;

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 2位抢占优先级，2位响应优先级
	delay_init();									// 延时函数初始化
	OLED_Init();									// oled初始化
	motor_init();									// 电机的 IO  pwm  编码器 初始化
	MPU_Init();										// MPU6050初始化
	DMP_Init();										// DMP初始化
	MPU_exti_init();								// mpu外部中断初始化（放最后）

	/*******************************************************************************
								到此所有模块初始化完毕
	********************************************************************************/

	while (1)
	{
		// 【1】安全装置：
		if (pitch < -30 || pitch > 30) // 小车可能已经倒了
		{
			motor_flag = 0;			 // 关闭电机
			velocity_sum = 0;		 // 速度积分清0
			TIM_SetCounter(TIM3, 0); // 编码器计数值清零
			TIM_SetCounter(TIM2, 0); // 编码器计数值清零
		}
		else
			motor_flag = 1; // 开启电机

		// 【2】状态显示：
		OLED_ShowAngle(pitch, roll, yaw); // 显示欧拉角
		OLED_ShowPWM(velocity);			  // 显示速度（非真实速度）
	}
}