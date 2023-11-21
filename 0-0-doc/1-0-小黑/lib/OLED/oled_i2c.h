#ifndef __OLEDIIC_H
#define __OLEDIIC_H
#include "sys.h"

//IO方向设置
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}



#define SCL_PIN 8
#define OLED_IIC_SCL_PIN GPIO_Pin_8
#define SDA_PIN 9
#define OLED_IIC_SDA_PIN GPIO_Pin_9
#define OLED_IIC_PORT GPIOB
#define OLED_IIC_PORT_CLK RCC_APB2Periph_GPIOB


//IO操作函数
#define OLED_IIC_SCL PBout(SCL_PIN)    // SCL
#define OLED_IIC_SDA PBout(SDA_PIN)    // SDA
#define OLED_ICC_READ_SDA PBin(SDA_PIN)    // 输入SDA

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);
#endif

