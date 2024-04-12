#ifndef __PID_H
#define __PID_H

int vertical_PID_value(float measurement,float targetPoint); //直立环
int velocity_PID_value(int velocity);              //速度环
void I_Limiting(int max);                          // pwm限幅
#endif
