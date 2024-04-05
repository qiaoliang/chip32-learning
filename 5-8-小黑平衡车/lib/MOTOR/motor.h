#ifndef __MOTOR_H
#define __MOTOR_H

void motor_init(void);
void motor_gpio_init(void);
void PWM_Xianfu(int max,int *PWM);
void SETPWM(int PWM);
int read_encoder3(void);
int read_encoder2(void);
void motor_enable(float pitch); //鏍规嵁瑙掑害鍒ゆ柇鏄惁浣胯兘 or 鍏抽棴鐢垫満
void left_positive(void);       //宸﹁疆姝ｄ紶
void left_negative(void);       //宸﹁疆鍙嶈浆
void right_positive(void);      //鍙宠疆姝ｈ浆
void right_negative(void);      //鍙宠疆鍙嶈浆
#endif
