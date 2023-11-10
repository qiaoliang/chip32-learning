#include "I2C.h"

/*引脚配置*/
#define SCL_PIN GPIO_Pin_8
#define SDA_PIN GPIO_Pin_9

#define W_SCL(x) GPIO_WriteBit(GPIOB, SCL_PIN, (BitAction)(x))
#define W_SDA(x) GPIO_WriteBit(GPIOB, SDA_PIN, (BitAction)(x))

void MyI2C_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  // 开漏输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = SCL_PIN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = SDA_PIN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    W_SCL(1);
    W_SDA(1);
}
/**
 * @brief  I2C开始
 * @param  无
 * @retval 无
 */
void I2C_Start(void)
{
    W_SDA(1);
    W_SCL(1);
    W_SDA(0);
    W_SCL(0);
}

/**
 * @brief  I2C停止
 * @param  无
 * @retval 无
 */
void I2C_Stop(void)
{
    W_SDA(0);
    W_SCL(1);
    W_SDA(1);
}

/**
 * @brief  I2C发送一个字节
 * @param  Byte 要发送的一个字节
 * @retval 无
 */
void I2C_SendByte(uint8_t Byte)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        W_SDA(Byte & (0x80 >> i));
        W_SCL(1);
        W_SCL(0);
    }
    W_SCL(1); // 额外的一个时钟，不处理应答信号
    W_SCL(0);
}