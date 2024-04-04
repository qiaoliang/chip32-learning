#ifndef __MPU_IIC_H
#define __MPU_IIC_H
#include <stdint.h>

#define MPU6050_ADDRESS 0xD0 // MPU6050的I2C从机地址

/*引脚配置*/
#define MPU_IIC_RCC_PORT RCC_APB2Periph_GPIOB
#define MPU_IIC_PORTx GPIOB
#define MPU_IIC_SCL_PIN GPIO_Pin_10
#define MPU_IIC_SDA_PIN GPIO_Pin_11

void MPU_IIC_Init(void);
void MPU_IIC_Start(void);
void MPU_IIC_Stop(void);
void MPU_IIC_SendByte(uint8_t Byte);
uint8_t MPU_IIC_ReceiveByte(void);
void MPU_IIC_SendAck(uint8_t AckBit);
uint8_t MPU_IIC_ReceiveAck(void);

#endif
