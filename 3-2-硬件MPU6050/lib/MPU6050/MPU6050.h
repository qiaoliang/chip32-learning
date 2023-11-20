#ifndef __MPU6050_H
#define __MPU6050_H
#define I2C2_GPIO_Port GPIOB
#define I2C2_SCL_Pin GPIO_Pin_10
#define I2C2_SDA_Pin GPIO_Pin_11

#include <stdint.h>

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);

void MPU6050_Init(void);
uint8_t MPU6050_GetID(void);
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);

#endif
