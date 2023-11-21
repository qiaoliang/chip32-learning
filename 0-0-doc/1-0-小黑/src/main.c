/********************************************************************
 本程序仅供特训班内部学习使用，请勿外传

 程序：mpu6050例程

 功能介绍：在oled显示mpu6050计算出来的欧拉角
 pitch:俯仰角 精度:0.1°   范围:-90.0° <---> +90.0°
 roll:翻滚角  精度:0.1°   范围:-180.0°<---> +180.0°
 yaw:方位角   精度:0.1°   范围:-180.0°<---> +180.0

 硬件连接：
 a.oled:
 					 1.SCL:PB6
					 2.SDA:PB7

 b.mpu6050:
					 1.SCL:PB10
					 2.SDA:PB11
					 3.INT:PA12（下降沿中断）
					 4.AD0:PA15（给低电平，或悬空）

 作者：小黑(wgn)
 QQ：1501451224
*********************************************************************/


// 第一种使用方式：不用中断（初学可以用一下，以后不推荐）
#include "delay.h"
#include "sys.h"
#include "OLED.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

int main(void)
{
	float pitch,roll,yaw; //欧拉角原始数据

	delay_init();         //延时函数初始化
	OLED_Init();          //oled初始化
	//MPU_Init();		        //MPU6050初始化
	//DMP_Init();           //DMP初始化（DMP用来解算陀螺仪数据）

/********************************************************
                  到此所有硬件准备完毕
*********************************************************/

	OLED_ShowStr(0,0,"Pitch: ",2);
	OLED_ShowStr(0,2,"Roll: ",2);
	OLED_ShowStr(0,4,"Yaw: ",2);

	//不断地读取陀螺仪角度并显示
	while(1)
	{
		/**
				if(mpu_dmp_get_data(&pitch, &roll, &yaw)==0) //得到了欧拉角，存在pitch,roll,yaw里面
				{
					OLED_ShowAngle(pitch, roll, yaw); //oled显示角度
				}
			}*/
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
//	MPU_exti_init(); //陀螺仪外部中断初始化（放最后）
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
