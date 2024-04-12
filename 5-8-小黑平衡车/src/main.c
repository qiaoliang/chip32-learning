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
float balance_angle = -0.5;			   // 小车平衡时的角度
extern int velocity;		   // 速度测量值（编码器脉冲数，非真实速度）
extern float velocity_sum;	   // 速度积分
int motor_flag;				   // 电机使能标志：1使能  0失能

// 直立环PD参数:
// float Kp = -420, Ki = 0, Kd = -2000; // 调完速度环后精调

float Kp = -900, Ki = 0, Kd = -1500; // 第三步, 同时将Kp 和 Kd 数值乘0.6 , 开始调整速度环. -1300 * 0.6 = -780, -3500 * 0.6 = -2100
// float Kp = -1500, Ki = 0, Kd = -3000; // 第二步, 调整Kd 值, 改善振幅, 让小车变成小幅度高频摇摆振动
// float Kp = -1600,Ki =0,Kd=0;//第一步, 调整Kp, 小车大幅度摇摆振动

// 速度环PI参数:
float VKp = +100, VKi = 0.5;  // 第三步, 同时将Kp 和 Kd 数值乘0.6 , 开始调整速度环.  VKp 与 Vki之间是200的倍数关系.

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
		OLED_ShowPWM(velocity);	   // 显示速度（非真实速度）
	}
}