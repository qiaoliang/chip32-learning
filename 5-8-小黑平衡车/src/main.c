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
float balance_angle = 0;			   // 小车平衡时的角度
extern int velocity;		   // 速度测量值（编码器脉冲数，非真实速度）
extern float velocity_sum;	   // 速度积分
int motor_flag;				   // 电机使能标志：1使能  0失能

// 直立环PD参数:
// float Kp = -420, Ki = 0, Kd = -2000; // 调完速度环后精调
//float Kp=-720,Ki=0,Kd=-1320; //上一步的数值乘0.6以后
// 6. float Kp = -1200, Ki = 0, Kd = -2200;  //OK, 需要
// 5. float Kp = -1000, Ki = 0, Kd =-1600 ;
// 4. float Kp = -1000, Ki = 0, Kd =-1000 ;
//float Kp = -600, Ki = 0, Kd = -2240; // 更大幅度的振动 * 0.6
//float Kp=-1300,Ki=0,Kd=-3800;//更大幅度的振动
float Kp = -400,Ki =0,Kd=0;//大幅度振动
// 1. float Kp=0,Ki=0,Kd=0;

// 速度环PI参数:
float VKp = +100, VKi = 0.5;

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