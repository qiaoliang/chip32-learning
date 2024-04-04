#include "stm32f10x.h"
/*引脚配置*/
#define OLED_I2C_SDA_PIN GPIO_Pin_9
#define OLED_I2C_SCL_PIN GPIO_Pin_8
#define OLED_I2C_PORTx GPIOB
#define OLED_I2C_RCC_PORT RCC_APB2Periph_GPIOB
#define OLED_W_SCL(x) GPIO_WriteBit(OLED_I2C_PORTx, OLED_I2C_SCL_PIN, (BitAction)(x))
#define OLED_W_SDA(x) GPIO_WriteBit(OLED_I2C_PORTx, OLED_I2C_SDA_PIN, (BitAction)(x))

/*引脚初始化*/
void OLED_I2C_Init(void);
/**
 * @brief  I2C开始
 * @param  无
 * @retval 无
 */
void OLED_I2C_Start(void);

/**
 * @brief  I2C停止
 * @param  无
 * @retval 无
 */
void OLED_I2C_Stop(void);

/**
 * @brief  I2C发送一个字节
 * @param  Byte 要发送的一个字节
 * @retval 无
 */
void OLED_I2C_SendByte(uint8_t Byte);
