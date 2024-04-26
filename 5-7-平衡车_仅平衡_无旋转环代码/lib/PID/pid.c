/**
 * @file pid.c
 * @author Master Qiao
 * @brief PID算法的解释可以参见 https://zhuanlan.zhihu.com/p/39573490
 * @version 0.1
 * @date 2024-04-12
 *
 * @copyright Copyright (c) 2024
 */
#include "pid.h"

extern float Kp, Ki, Kd; // 直立环参数
float err;				 // 此次误差
float last_err;			 // 上次误差
float err_sum = 0;		 // 误差累加
float err_difference;	 // 误差的差值

extern float VKp, VKi;	  // 速度环参数
float filt_velocity;	  // 滤波后的速度
float last_filt_velocity; // 上一次的滤波后的速度
float velocity_sum = 0;	  // 速度的累加

// 直立环：
int vertical_PID_value(float measurement, float targetPoint)
{

	err = measurement - targetPoint;			 // 误差
	err_sum += err;					 // 误差的累加
	err_difference = err - last_err; // 误差的差值
	last_err = err;					 // 此次误差记录为“上次误差”

	return Kp * err + Ki * err_sum + Kd * err_difference;
}

// 速度环：
int velocity_PID_value(int measurement, int targetPoint)
{
	targetPoint  = 0 ;											 // 小车平衡时，轮子的速度应该为 0。 
	int error_velocity = measurement - targetPoint ;
	float a = 0.3;												 // 滤波系数（反映滤波程度）
	filt_velocity = wave_filter((float)error_velocity, a); 			// 一阶速度滤波。这里的参数 a 是一个权重常数，可以自己调整。
	velocity_sum += filt_velocity;								 // 速度的累加
	I_Limiting(3000);											 // 累加限幅，不能超过 3000.
	last_filt_velocity = filt_velocity;							 // 将本次的速度保存到全局变量中，以便在下一次计算时，作为上一次的数值使用

	return VKp * filt_velocity + VKi * velocity_sum;
}
// 一阶速度滤波：
float wave_filter(float input, float weight){
	return weight * input + (1 - weight) * last_filt_velocity; // 一阶速度滤波。这里的参数 a 是一个权重常数，可以自己调整。
}
// I限幅：
void I_Limiting(int max)
{
	if (velocity_sum > max)
		velocity_sum = max;
	if (velocity_sum < -max)
		velocity_sum = -max;
}
