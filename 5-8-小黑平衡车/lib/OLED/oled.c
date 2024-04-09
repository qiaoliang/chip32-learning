#include "oled.h"
#include "codetab.h" //oled字符库
/**
 * @brief 显示PWM值
 *
 * @param PWM
 */
void OLED_ShowPWM(int PWM)
{
	if (PWM < 0)
	{
		OLED_ShowStr(10, 6, "PWM: -", LARGE_FONT); // 显示负号
		PWM = -PWM;
	}
	else
		OLED_ShowStr(10, 6, "PWM: ", LARGE_FONT); // 掩盖负号
	OLED_ShowNumber(58, 6, PWM, LARGE_FONT);	 // 显示PWM
}

/**
 * @brief 显示角度
 *
 * @param roll  翻滚角
 * @param yaw  显示航向角
 */
void OLED_ShowAngle(float pitch, float roll, float yaw)
{

	int Pitch, Roll, Yaw;
	Pitch = (int)(pitch * 10);
	Roll = (int)(roll * 10);
	Yaw = (int)(yaw * 10);
	// 对浮点数做处理，于是可以显示在lcd上
	if (Pitch < 0)
	{
		OLED_ShowStr(0, 0, "Pitch: -", LARGE_FONT); // 显示负号
		Roll = -Roll;
	}
	else
		OLED_ShowStr(0, 0, "Pitch:  ", LARGE_FONT); // 显示正号
	OLED_Shownum3(64, 2, Pitch, LARGE_FONT);	   // 显示 Pitch 俯仰角
	if (Roll < 0)
	{
		OLED_ShowStr(0, 2, "Roll:  -", LARGE_FONT); // 显示负号
		Roll = -Roll;
	}
	else
		OLED_ShowStr(0, 2, "Roll:  ", LARGE_FONT);					 // 显示正号
	OLED_Shownum3( 64, 2, Roll, LARGE_FONT); // 显示Roll 翻滚角

	if (Yaw < 0)
	{
		OLED_ShowStr(0, 4, "Yaw:   -", LARGE_FONT);
		Yaw = -Yaw;
	}
	else
		OLED_ShowStr(0, 4, "Yaw:    ", LARGE_FONT);
	OLED_Shownum3(64, 4, Yaw, LARGE_FONT); // 显示Yaw航向角
}

/**
 * @brief  显示三位整数和一位小数
 *
 * @param x 显示点的x坐标
 * @param y 显示点的y坐标
 * @param num 被显示的数字
 * @param TextSize 字号, SMALL_FONT:小号, LARGE_FONT:大号
 */
void OLED_Shownum3(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{

	unsigned int ge, shi, bai, qian;
	ge = num % 10;
	shi = (num % 100) / 10;
	bai = (num % 1000) / 100;
	qian = (num % 10000) / 1000;
	unsigned int font_size, font_width;
	font_size = (TextSize == SMALL_FONT) ? SMALL_FONT : LARGE_FONT;
	font_width = (TextSize == SMALL_FONT) ? SMALL_FONT_WIDTH : LARGE_FONT_WIDTH;

	OLED_ShowDigit(x, y, qian, font_size);
	OLED_ShowDigit(x + font_width * 1, y, bai, font_size);
	OLED_ShowDigit(x + font_width * 2, y, shi, font_size);
	OLED_ShowStr(x + font_width * 3, y, ".", font_size);
	OLED_ShowDigit(x + font_width * 4, y, ge, font_size);
}

/**
 * @brief 使用小字号,在指定位置(x,y) 显示指定的一串小于10位数的数字(正数或负数).如果超过屏幕宽度,则换行.
 *
 * @param x 指定的列
 * @param y 指定的行
 * @param num 被显示的数字
 * @param TextSize 字号, SMALL_FONT:小号, LARGE_FONT:大号
 */
void OLED_ShowNumber(unsigned char x, unsigned char y, int num, unsigned char TextSize)
{
	int font_width = 0, screen_size = 0;
	if (TextSize == SMALL_FONT)
	{
		font_width = SMALL_FONT_WIDTH;
		screen_size = SCREEN_WIDTH_FOR_SMALL_FONT;
	}
	else if (TextSize == LARGE_FONT)
	{
		font_width = LARGE_FONT_WIDTH;
		screen_size = SCREEN_WIDTH_FOR_LARGE_FONT;
	}
	else
	{
		return;
	}
	if (num == 0)
	{
		OLED_ShowDigit(x, y, num, TextSize);
		return;
	}
	if (num < 0)
	{
		OLED_ShowStr(x, y, "-", TextSize);
		x = x + font_width;
		num = -num;
	}
	unsigned int singleDigital[5], i = 0; // 存储十位的数字
	while (num > 0)
	{
		if (i >= 5) // 截断数字,溢出保护
			break;
		singleDigital[i++] = num % 10;
		num = num / 10;
	}
	for (int j = i - 1; j >= 0; j--)
	{
		if (x > screen_size)
		{
			x = 0;
			y = y + 1;
		}
		OLED_ShowDigit(x, y, singleDigital[j], TextSize);
		x = x + font_width;
	}
}
/**
 * @brief 使用指定字号来在指定位置(x,y) 显示指定的数字
 *
 * @param x 所在点阵的列位置
 * @param y 所在点阵的行位置
 * @param digit 所显示的单一数字,指从0到9的任何一个阿拉伯数字
 * @param TextSize 指定字号
 * @return int 0 if success, -1 if fail.
 */
int OLED_ShowDigit(unsigned int x, unsigned int y, unsigned int digit, unsigned char TextSize)
{
	if (digit > 9 || digit < 0)
		return -1;
	unsigned char c = 0, i = 0;
	c = 48 + digit;
	switch (TextSize)
	{
	case SMALL_FONT:
		if (x > SCREEN_WIDTH_FOR_SMALL_FONT)
			return -1;
		c = c - 32;
		OLED_SetPos(x, y);
		for (i = 0; i < SMALL_FONT_WIDTH; i++)
			OLED_Data(F6x8[c][i]);
		break;
	case LARGE_FONT:
		if (x > SCREEN_WIDTH_FOR_LARGE_FONT)
			return -1;
		c = c - 32;
		// 显示字符的上半部分
		OLED_SetPos(x, y);
		for (i = 0; i < LARGE_FONT_WIDTH; i++)
			OLED_Data(F8X16[c * 16 + i]);
		// 显示字符的下半部分
		OLED_SetPos(x, y + 1);
		for (i = 0; i < LARGE_FONT_WIDTH; i++)
			OLED_Data(F8X16[c * 16 + i + LARGE_FONT_WIDTH]);
	}
	return 0;
}

/**
 * @brief 显示codetab.h中的ASCII字符,有SMALL_FONT(6*8) 和 LARGE_FONT (8*16) 可供选择
 *
 * @param x 显示首字符的 x 列位置 (x: 0~126, 或 0~120)
 * @param y 显示首字符的 y 行位置 (y: 0~7)
 * @param ch 显示的字符串
 * @param TextSize 字号, SMALL_FONT:小号, LARGE_FONT:大号
 */
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
	unsigned char c = 0, i = 0, j = 0;
	switch (TextSize)
	{
	case 1:
	{
		while (ch[j] != '\0')
		{
			c = ch[j] - 32;
			if (x > 126)
			{
				x = 0;
				y++;
			}
			OLED_SetPos(x, y);
			for (i = 0; i < 6; i++)
				OLED_Data(F6x8[c][i]);
			x += 6;
			j++;
		}
	}
	break;
	case 2:
	{
		while (ch[j] != '\0')
		{
			c = ch[j] - 32;
			if (x > 120)
			{
				x = 0;
				y++;
			}
			OLED_SetPos(x, y);
			for (i = 0; i < 8; i++)
				OLED_Data(F8X16[c * 16 + i]);
			OLED_SetPos(x, y + 1);
			for (i = 0; i < 8; i++)
				OLED_Data(F8X16[c * 16 + i + 8]);
			x += 8;
			j++;
		}
	}
	break;
	}
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          :
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
//--------------------------------------------------------------
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm = 0;
	unsigned int adder = 32 * N;
	OLED_SetPos(x, y);
	for (wm = 0; wm < 16; wm++)
	{
		OLED_Data(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x, y + 1);
	for (wm = 0; wm < 16; wm++)
	{
		OLED_Data(F16x16[adder]);
		adder += 1;
	}
}
/**
 * @brief 显示BMP位图
 *
 * @param x0 起始点x坐标 ( x0:0~127)
 * @param y0 起始点y坐标 ( y0:0~7)
 * @param x1 起点对角线(结束点)的x坐标 ( x1:1~128)
 * @param y1 起点对角线(结束点)的y坐标 ( y1:1~8)
 * @param BMP BMP位图数据
 */
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[])
{
	unsigned int j = 0;
	unsigned char x, y;

	if (y1 % 8 == 0)
		y = y1 / 8;
	else
		y = y1 / 8 + 1;
	for (y = y0; y < y1; y++)
	{
		OLED_SetPos(x0, y);
		for (x = x0; x < x1; x++)
		{
			OLED_Data(BMP[j++]);
		}
	}
}

void OLED_Clear(void)
{
	OLED_Fill(0);
}

void OLED_SetPos(unsigned char x, unsigned char y) // 设置起始点坐标
{
	OLED_Command(0xb0 + y);
	OLED_Command(((x & 0xf0) >> 4) | 0x10);
	OLED_Command((x & 0x0f) | 0x01);
}

void OLED_Fill(unsigned char fill_Data) // 全屏填充
{
	unsigned char m, n;
	for (m = 0; m < 8; m++)
	{
		OLED_Command(0xb0 + m); // page0-page1
		OLED_Command(0x00);		// low column start address
		OLED_Command(0x10);		// high column start address
		for (n = 0; n < 128; n++)
		{
			OLED_Data(fill_Data);
		}
	}
}
/**
 * @brief 将OLED从休眠中唤醒
 *
 */
void OLED_ON(void)
{
	OLED_Command(0X8D); // 设置电荷泵
	OLED_Command(0X14); // 开启电荷泵
	OLED_Command(0XAF); // OLED唤醒
}
/**
 * @brief 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
 *
 */
void OLED_OFF(void)
{
	OLED_Command(0X8D); // 设置电荷泵
	OLED_Command(0X10); // 关闭电荷泵
	OLED_Command(0XAE); // OLED休眠
}

void OLED_Init(void)
{
	IIC_Init(); // GPIO初始化

	// OLED相关配置
	delay_ms(100);
	OLED_Command(0xAE); // display off
	OLED_Command(0x20); // Set Memory Addressing Mode
	OLED_Command(0x10); // 00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	OLED_Command(0xb0); // Set Page Start Address for Page Addressing Mode,0-7
	OLED_Command(0xc8); // Set COM Output Scan Direction              (c8正、c0反)
	OLED_Command(0xa1); //--set segment re-map 0 to 127              (a1正、a0反)
	OLED_Command(0x00); //---set low column address
	OLED_Command(0x10); //---set high column address
	OLED_Command(0x40); //--set start line address
	OLED_Command(0x81); //--set contrast control register
	OLED_Command(0xff); // 亮度调节 0x00~0xff
	OLED_Command(0xa6); //--set normal display
	OLED_Command(0xa8); //--set multiplex ratio(1 to 64)
	OLED_Command(0x3F); //
	OLED_Command(0xa4); // 0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	OLED_Command(0xd3); //-set display offset
	OLED_Command(0x00); //-not offset
	OLED_Command(0xd5); //--set display clock divide ratio/oscillator frequency
	OLED_Command(0xf0); //--set divide ratio
	OLED_Command(0xd9); //--set pre-charge period
	OLED_Command(0x22); //
	OLED_Command(0xda); //--set com pins hardware configuration
	OLED_Command(0x12);
	OLED_Command(0xdb); //--set vcomh
	OLED_Command(0x20); // 0x20,0.77xVcc
	OLED_Command(0x8d); //--set DC-DC enable
	OLED_Command(0x14); //
	OLED_Command(0xaf); //--turn on oled panel
	OLED_Fill(0x00);	// 清屏（也就是全用0填充）

	OLED_ShowStr(6, 1, "By: MasterQiao", 2);
	delay_ms(1000);
	OLED_ShowStr(6, 3, "QQ: 1686321091", 2);
	delay_ms(1000);
	OLED_ShowStr(10, 5, "  2024.03.25", 2);
	delay_ms(1000);
	OLED_Fill(0x00);
	OLED_ShowStr(0, 0, "OLED OK!", 1);
}

int OLED_Command(unsigned char Command)
{
	IIC_Start();
	IIC_Send_Byte(0x78); // Slave address,SA0=0
	if (IIC_Wait_Ack())
	{
		IIC_Stop();
		return 1;
	}
	IIC_Send_Byte(0x00); // write command
	if (IIC_Wait_Ack())
	{
		IIC_Stop();
		return 1;
	}
	IIC_Send_Byte(Command);
	if (IIC_Wait_Ack())
	{
		IIC_Stop();
		return 1;
	}
	IIC_Stop();
	return 0;
}

int OLED_Data(unsigned char Data)
{
	IIC_Start();
	IIC_Send_Byte(0x78); // D/C#=0; R/W#=0
	if (IIC_Wait_Ack())
	{
		IIC_Stop();
		return 1;
	}
	IIC_Send_Byte(0x40); // write data
	if (IIC_Wait_Ack())
	{
		IIC_Stop();
		return 1;
	}
	IIC_Send_Byte(Data);
	if (IIC_Wait_Ack())
	{
		IIC_Stop();
		return 1;
	}
	IIC_Stop();
	return 0;
}
