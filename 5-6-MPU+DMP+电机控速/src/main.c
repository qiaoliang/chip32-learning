#include "Delay.h"
#include "sys.h"
#include "OLED.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "Motor.h"
#include "Encoder.h"
#include "Key.h"

extern float pitch, roll, yaw; // 欧拉角测量值
float zhongzhi = 0;			   // roll理论值（小车平衡时的角度）
extern int velocity;		   // 速度测量值（编码器脉冲数，非真实速度）
extern float velocity_sum;	   // 速度积分
int motor_flag;				   // 电机使能标志：1使能  0失能

// 直立环PD参数:
float Kp = -420, Ki = 0, Kd = -2000; // 调完速度环后精调
// float Kp=-420,Ki=0,Kd=-960; //乘0.6
// float Kp=-700,Ki=0,Kd=-1600;
// float Kp=0,Ki=0,Kd=0;

// 速度环PI参数:
float VKp = +190, VKi = 0.95;
void Show_MPU6050(void)
{
	if (mpu_dmp_get_data(&pitch, &roll, &yaw) == 0) // 得到了欧拉角，存在pitch,roll,yaw里面
	{
		OLED_ShowAngle(pitch, roll, yaw); // oled显示角度
	}
}

void OLED_ShowVelocity(int velocity)
{

	if (velocity < 0)
	{
		OLED_ShowStr(50, 0, "-", 2); // 显示负号
		velocity = -velocity;
	}
	else
		OLED_ShowStr(50, 6, " ", 2); // 掩盖负号
	OLED_Shownum2(58, 6, velocity, 2);
}

int main(void)
{


	Delay_init();         //延时函数初始化
	OLED_Init();          //oled初始化
	MPU_Init();		        //MPU6050初始化
	DMP_Init();           //DMP初始化（DMP用来解算陀螺仪数据）
	MPU_exti_init();	  // 陀螺仪外部中断初始化（放最后）
	Motor_Init();		  // 直流电机初始化
	Key_Init();			  // 按键初始化
	Encoder_Init();		  // 初始化电机编码器

	/********************************************************
					  到此所有硬件准备完毕
	*********************************************************/

	OLED_ShowStr(0,0,"Pitch: ",2);
	OLED_ShowStr(0,2,"Roll: ",2);
	OLED_ShowStr(0,4,"Yaw: ",2);

	//不断地读取陀螺仪角度并显示
	while(1)
	{
		//Show_MPU6050();
		OLED_ShowAngle(pitch, roll, yaw); //oled显示角度
		OLED_ShowVelocity(velocity);
	}
}

/////////////////////////////////////////////////////////////////////

//第二种使用方式：用中断（陀螺仪的INT引脚会在读取到欧拉角后输出中断信号）
//#include "delay.h"
//#include "sys.h"
//#include "OLED.h"
//#include "mpu6050.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h"
//extern float pitch,roll,yaw; //欧拉角原始数据（在mpuexti.c定义）

//int main(void)
//{
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //2位抢占优先级，2位响应优先级
//	delay_init();    //延时函数初始化
//	OLED_Init();     //oled初始化
//	MPU_Init();		   //MPU6050初始化
//	DMP_Init();      //DMP初始化（DMP用来解算陀螺仪数据）
//
//
///********************************************************
//                  到此所有硬件准备完毕
//*********************************************************/
//
//	OLED_ShowStr(0,0,"Pitch: ",2);
//	OLED_ShowStr(0,2,"Roll: ",2);
//	OLED_ShowStr(0,4,"Yaw: ",2);
//
//	//陀螺仪角度的读取在外部中断服务函数中进行，此处仅进行oled显示
//	while(1)
//	{
//	  OLED_ShowAngle(pitch, roll, yaw); //oled显示角度
//	}
//}
