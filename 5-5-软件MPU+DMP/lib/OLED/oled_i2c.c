#include "oled_i2c.h"
#include "delay.h"

//初始化IIC
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(OLED_IIC_PORT_CLK, ENABLE); // 使能GPIOB时钟

	GPIO_InitStructure.GPIO_Pin = OLED_IIC_SCL_PIN | OLED_IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OLED_IIC_PORT, &GPIO_InitStructure);
	GPIO_SetBits(OLED_IIC_PORT, OLED_IIC_SCL_PIN | OLED_IIC_SDA_PIN); // PB6,PB7 输出高
}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	OLED_IIC_SDA = 1;
	OLED_IIC_SCL = 1;
	Delay_us(4);
 	OLED_IIC_SDA=0;//START:when CLK is high,DATA change form high to low
	Delay_us(4);
	OLED_IIC_SCL = 0; // 钳住I2C总线，准备发送或接收数据
}
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	OLED_IIC_SCL = 0;
	OLED_IIC_SDA = 0; // STOP:when CLK is high DATA change form low to high
	Delay_us(4);
	OLED_IIC_SCL = 1;
	OLED_IIC_SDA = 1; // 发送I2C总线结束信号
	Delay_us(4);
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入
	OLED_IIC_SDA = 1;
	Delay_us(1);
	OLED_IIC_SCL = 1;
	Delay_us(1);
	while (OLED_ICC_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	OLED_IIC_SCL = 0; // 时钟输出0
	return 0;
}
//产生ACK应答
void IIC_Ack(void)
{
	OLED_IIC_SCL = 0;
	SDA_OUT();
	OLED_IIC_SDA = 0;
	Delay_us(2);
	OLED_IIC_SCL = 1;
	Delay_us(2);
	OLED_IIC_SCL = 0;
}
//不产生ACK应答
void IIC_NAck(void)
{
	OLED_IIC_SCL = 0;
	SDA_OUT();
	OLED_IIC_SDA = 1;
	Delay_us(2);
	OLED_IIC_SCL = 1;
	Delay_us(2);
	OLED_IIC_SCL = 0;
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void IIC_Send_Byte(u8 txd)
{
    u8 t;
	SDA_OUT();
	OLED_IIC_SCL = 0; // 拉低时钟开始数据传输
	for(t=0;t<8;t++)
    {
		OLED_IIC_SDA = (txd & 0x80) >> 7;
		txd<<=1;
		Delay_us(2);   //对TEA5767这三个延时都是必须的
		OLED_IIC_SCL = 1;
		Delay_us(2);
		OLED_IIC_SCL = 0;
		Delay_us(2);
    }
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
		OLED_IIC_SCL = 0;
		Delay_us(2);
		OLED_IIC_SCL = 1;
		receive<<=1;
		if (OLED_ICC_READ_SDA)
			receive++;
		Delay_us(1);
    }
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK
    return receive;
}



























