#ifndef __I2C_H__
#define __I2C_H__
#include "stm32f10x.h"
void MyI2C_Init(void); // I2C初始化
void I2C_Start(void); // I2C开始
void I2C_Stop(void); // I2C停止
void I2C_SendByte(uint8_t Byte);
#endif