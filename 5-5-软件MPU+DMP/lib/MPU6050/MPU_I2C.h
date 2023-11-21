#ifndef __MPU_I2C_H
#define __MPU_I2C_H
#include <stdint.h>
void MPU_I2C_Init(void);
void MPU_I2C_Start(void);
void MPU_I2C_Stop(void);
void MPU_I2C_SendByte(uint8_t Byte);
uint8_t MPU_I2C_ReceiveByte(void);
void MPU_I2C_SendAck(uint8_t AckBit);
uint8_t MPU_I2C_ReceiveAck(void);

#endif
