/**
 * @file pid.c
 * @author Master Qiao
 * @brief PID算法的解释可以参见 https://zhuanlan.zhihu.com/p/39573490
 * @version 0.1
 * @date 2024-04-12
 *
 * @copyright Copyright (c) 2024
 */

#ifndef __PID_H
#define __PID_H

int vertical_PID_value(float measurement,float targetPoint); //直立环
int velocity_PID_value(int velocity,int targetPoint);              //速度环
void I_Limiting(int max);                          // pwm限幅
float wave_filter(float input, float weight);
#endif
