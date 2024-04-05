#include "oled.h"
#include "codetab.h"//oled字符库


void OLED_ShowPWM(int PWM)
{
	if(PWM<0)
	{
		OLED_ShowStr(50,6,"-",2);		//显示负号
		PWM=-PWM;
	}
	else OLED_ShowStr(50,6," ",2); //掩盖负号
	OLED_Shownum1(58,6,PWM,2);	    //显示俯仰角

}


void OLED_ShowAngle(float roll,float yaw)
{
	int Roll,Yaw;
	Roll=(int)(roll*10);
	Yaw=(int)(yaw*10);
	//对浮点数做处理，于是可以显示在lcd上

	if(Roll<0)
	{
		OLED_ShowStr(0,2,"-",2);		//显示负号
		Roll=-Roll;
	}
	else OLED_ShowStr(0,2," ",2); //掩盖负号
	OLED_Shownum3(8,2,Roll,2);	  //显示翻滚角

	if(Yaw<0)
	{
		OLED_ShowStr(0,4,"-",2);
		Yaw=-Yaw;
	}
	else OLED_ShowStr(0,4," ",2);
	OLED_Shownum3(8,4,Yaw,2);	    //显示航向角
}


void OLED_Shownum1(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned int ge,shi,bai,qian;
	ge=num%10;
	shi=(num%100)/10;
	bai=(num%1000)/100;
	qian=(num%10000)/1000;

	if(TextSize==1)
	{
		OLED_ShowSNum(x,y,qian,TextSize);
		OLED_ShowSNum(x+6,y,bai,TextSize);
		OLED_ShowSNum(x+12,y,shi,TextSize);
		OLED_ShowSNum(x+18,y,ge,TextSize);
	}

	if(TextSize==2)
	{
		OLED_ShowSNum(x,y,qian,TextSize);
		OLED_ShowSNum(x+8,y,bai,TextSize);
		OLED_ShowSNum(x+16,y,shi,TextSize);
		OLED_ShowSNum(x+24,y,ge,TextSize);
	}
}



void OLED_Shownum2(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned int ge,shi,bai;
	ge=num%10;
	shi=(num%100)/10;
	bai=(num%1000)/100;

	if(TextSize==1)
	{
		OLED_ShowSNum(x,y,bai,TextSize);
		OLED_ShowSNum(x+6,y,shi,TextSize);
		OLED_ShowStr(x+12,y,".",TextSize);
		OLED_ShowSNum(x+18,y,ge,TextSize);
	}

	if(TextSize==2)
	{
		OLED_ShowSNum(x,y,bai,TextSize);
		OLED_ShowSNum(x+8,y,shi,TextSize);
		OLED_ShowStr(x+16,y,".",TextSize);
		OLED_ShowSNum(x+24,y,ge,TextSize);
	}
}


void OLED_Shownum3(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned int ge,shi,bai,qian;
	ge=num%10;
	shi=(num%100)/10;
	bai=(num%1000)/100;
	qian=(num%10000)/1000;

	if(TextSize==1)
	{
		OLED_ShowSNum(x,y,qian,TextSize);
		OLED_ShowSNum(x+6,y,bai,TextSize);
		OLED_ShowSNum(x+12,y,shi,TextSize);
		OLED_ShowStr(x+18,y,".",TextSize);
		OLED_ShowSNum(x+24,y,ge,TextSize);
	}

	if(TextSize==2)
	{
		OLED_ShowSNum(x,y,qian,TextSize);
		OLED_ShowSNum(x+8,y,bai,TextSize);
		OLED_ShowSNum(x+16,y,shi,TextSize);
		OLED_ShowStr(x+24,y,".",TextSize);
		OLED_ShowSNum(x+32,y,ge,TextSize);
	}
}



//功能：在一行中显示五位数字
//wgn 2021.4.29
void OLED_ShowNum(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned int ge,shi,bai,qian,wan;
	ge=num%10;
	shi=(num%100)/10;
	bai=(num%1000)/100;
	qian=(num%10000)/1000;
	wan=num/10000;

	if(TextSize==1)
	{
		switch( Num_Digit(num) )
		{
			case 1:
			{
				OLED_ShowSNum(x,y,ge,TextSize);
			}
			break;

			case 2:
			{
				OLED_ShowSNum(x,y,shi,TextSize);
				OLED_ShowSNum(x+6,y,ge,TextSize);
			}
			break;

			case 3:
			{
				OLED_ShowSNum(x,y,bai,TextSize);
				OLED_ShowSNum(x+6,y,shi,TextSize);
				OLED_ShowSNum(x+12,y,ge,TextSize);
			}
			break;

			case 4:
			{
				OLED_ShowSNum(x+6,y,qian,TextSize);
				OLED_ShowSNum(x+12,y,bai,TextSize);
				OLED_ShowSNum(x+18,y,shi,TextSize);
				OLED_ShowSNum(x+24,y,ge,TextSize);
			}
			break;

			case 5:
			{
				OLED_ShowSNum(x,y,wan,TextSize);
				OLED_ShowSNum(x+6,y,qian,TextSize);
				OLED_ShowSNum(x+12,y,bai,TextSize);
				OLED_ShowSNum(x+18,y,shi,TextSize);
				OLED_ShowSNum(x+24,y,ge,TextSize);

			}
			break;
		}
	}

	if(TextSize==2)
	{
		switch( Num_Digit(num) )
		{
			case 1:
			{
				OLED_ShowSNum(x,y,ge,TextSize);
			}
			break;

			case 2:
			{
				OLED_ShowSNum(x,y,shi,TextSize);
				OLED_ShowSNum(x+8,y,ge,TextSize);
			}
			break;

			case 3:
			{
				OLED_ShowSNum(x,y,bai,TextSize);
				OLED_ShowSNum(x+8,y,shi,TextSize);
				OLED_ShowSNum(x+16,y,ge,TextSize);
			}
			break;

			case 4:
			{
				OLED_ShowSNum(x,y,qian,TextSize);
				OLED_ShowSNum(x+8,y,bai,TextSize);
				OLED_ShowSNum(x+16,y,shi,TextSize);
				OLED_ShowSNum(x+24,y,ge,TextSize);
			}
			break;

			case 5:
			{
				OLED_ShowSNum(x,y,wan,TextSize);
				OLED_ShowSNum(x+8,y,qian,TextSize);
				OLED_ShowSNum(x+16,y,bai,TextSize);
				OLED_ShowSNum(x+24,y,shi,TextSize);
				OLED_ShowSNum(x+32,y,ge,TextSize);
			}
			break;
		}
	}
}


void OLED_ShowSNum(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	unsigned char ch[2];
	ch[0]=48+num;
	ch[1]= '\0';
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					OLED_Data(F6x8[c][i]);

				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					OLED_Data(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					OLED_Data(F8X16[c*16+i+8]);

				x += 8;
				j++;
			}
		}break;
	}
}

//功能：计算五位数以内数字位数
//wgn 2021.4.29
int Num_Digit(int num)
{
    if(num>=0 && num<100000)
    {
        if(num<10) return 1;
        if(num<100) return 2;
        if(num<1000) return 3;
        if(num<10000) return 4;
        if(num<1000000) return 5;
    }
    return 0;
}


//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// Calls          :
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
// Description    : 显示codetab.h中的ASCII字符,有6*8和8*16可选择
//--------------------------------------------------------------
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					OLED_Data(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					OLED_Data(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					OLED_Data(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}
void OLED_ShowSmallStr(unsigned char x, unsigned char y, unsigned char ch[]){
	uint8_t c = 0, i = 0, j = 0;
	while (ch[j] != '\0')
	{
		c = ch[j] - 32;
		if (x > 126)
		{
			x = 0;
			y++;
		}
		OLED_ShowSmallChar(x, y, ch[j]);
		x += 6;
		j++;
	}
}
void OLED_ShowLargeStr(unsigned char x, unsigned char y, unsigned char ch[]){
	uint8_t c = 0, i = 0, j = 0;
	while (ch[j] != '\0')
	{
		c = ch[j] - 32;
		if (x > 120)
		{
			x = 0;
			y++;
		}
		OLED_ShowLargeChar(x, y, ch[j]);
		x += 8;
		j++;
	}
}


	/**
	 * @brief  OLED显示一个字符(显示codetab.h中的ASCII字符,小尺寸 6*8)
	 * @param  Line 行位置
	 * @param  Column 列位置
	 * @param  Char 要显示的一个字符，范围：ASCII可见字符
	 * @retval 无
	 */
	void OLED_ShowSmallChar(uint8_t x, uint8_t y, char Char)
{
	OLED_SetPos(x, y);
	for (int i = 0; i < 6; i++)
		OLED_Data(F6x8[Char][i]);
}
/**
 * @brief  OLED显示一个字符(显示codetab.h中的ASCII字符,大尺寸 8*16)
 * @param  Line 行位置，范围：
 * @param  Column 列位置，范围：
 * @param  Char 要显示的一个字符，范围：ASCII可见字符
 * @retval 无
 */
void OLED_ShowLargeChar(uint8_t x, uint8_t y, char Char)
{
	OLED_SetPos(x, y);
	int i;
	for (int i = 0; i < 8; i++)
		OLED_Data(F8X16[Char * 16 + i]);
	OLED_SetPos(x, y + 1);
	for (i = 0; i < 8; i++)
		OLED_Data(F8X16[Char * 16 + i + 8]);
}
/**
 * @brief  OLED次方函数
 * @retval 返回值等于X的Y次方
 */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}
/**
 * @brief  OLED显示数字（十六进制，正数）
 * @param  Line 起始行位置，范围：1~4
 * @param  Column 起始列位置，范围：1~16
 * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
 * @param  Length 要显示数字的长度，范围：1~8
 * @retval 无
 */
void OLED_ShowHexNum(uint8_t Column, uint8_t Line, uint32_t Number, uint8_t Length)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)
	{
		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10)
		{
			OLED_ShowSmallChar(Column + i, Line, SingleNumber + '0');
		}
		else
		{
			OLED_ShowSmallChar(Column + i, Line, SingleNumber - 10 + 'A');
		}
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
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_Data(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_Data(F16x16[adder]);
		adder += 1;
	}
}


//--------------------------------------------------------------
// Prototype      : void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
// Calls          :
// Parameters     : x0,y0 -- 起始点坐标(x0:0~127, y0:0~7); x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
// Description    : 显示BMP位图
//--------------------------------------------------------------
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			OLED_Data(BMP[j++]);
		}
	}
}


void OLED_Clear(void)
{
	OLED_Fill(0);
}


void OLED_SetPos(unsigned char x, unsigned char y) //设置起始点坐标
{
	OLED_Command(0xb0+y);
	OLED_Command(((x&0xf0)>>4)|0x10);
	OLED_Command((x&0x0f)|0x01);
}


void OLED_Fill(unsigned char fill_Data)//全屏填充
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_Command(0xb0+m);		//page0-page1
		OLED_Command(0x00);		//low column start address
		OLED_Command(0x10);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_Data(fill_Data);
			}
	}
}


//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          :
// Parameters     : none
// Description    : 将OLED从休眠中唤醒
//--------------------------------------------------------------
void OLED_ON(void)
{
	OLED_Command(0X8D);  //设置电荷泵
	OLED_Command(0X14);  //开启电荷泵
	OLED_Command(0XAF);  //OLED唤醒
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          :
// Parameters     : none
// Description    : 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
	OLED_Command(0X8D);  //设置电荷泵
	OLED_Command(0X10);  //关闭电荷泵
	OLED_Command(0XAE);  //OLED休眠
}


void OLED_Init(void)
{
	IIC_Init(); //GPIO初始化

	//OLED相关配置
	Delay_ms(100);
	OLED_Command(0xAE); //display off
	OLED_Command(0x20);	//Set Memory Addressing Mode
	OLED_Command(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	OLED_Command(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	OLED_Command(0xc8);	//Set COM Output Scan Direction              (c8正、c0反)
	OLED_Command(0xa1); //--set segment re-map 0 to 127              (a1正、a0反)
	OLED_Command(0x00); //---set low column address
	OLED_Command(0x10); //---set high column address
	OLED_Command(0x40); //--set start line address
	OLED_Command(0x81); //--set contrast control register
	OLED_Command(0xff); //亮度调节 0x00~0xff
	OLED_Command(0xa6); //--set normal display
	OLED_Command(0xa8); //--set multiplex ratio(1 to 64)
	OLED_Command(0x3F); //
	OLED_Command(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	OLED_Command(0xd3); //-set display offset
	OLED_Command(0x00); //-not offset
	OLED_Command(0xd5); //--set display clock divide ratio/oscillator frequency
	OLED_Command(0xf0); //--set divide ratio
	OLED_Command(0xd9); //--set pre-charge period
	OLED_Command(0x22); //
	OLED_Command(0xda); //--set com pins hardware configuration
	OLED_Command(0x12);
	OLED_Command(0xdb); //--set vcomh
	OLED_Command(0x20); //0x20,0.77xVcc
	OLED_Command(0x8d); //--set DC-DC enable
	OLED_Command(0x14); //
	OLED_Command(0xaf); //--turn on oled panel
	OLED_Fill(0x00);    //清屏（也就是全用0填充）

	OLED_ShowStr(6,1,"By: MasterQiao",2);
	Delay_ms(1000);
	OLED_ShowStr(6,3,"QQ: 1686321091",2);
	Delay_ms(1000);
	OLED_ShowStr(10,5,"  2024/4/1",2);
	Delay_ms(1000);
	OLED_Fill(0x00);
	OLED_ShowStr(0,0,"OLED OK!",1);
}


int OLED_Command(unsigned char Command)
{
   IIC_Start();
   IIC_Send_Byte(0x78);         //Slave address,SA0=0
	 if(IIC_Wait_Ack())
	 {
		 IIC_Stop();
		 return 1;
	 }
   IIC_Send_Byte(0x00);	       //write command
	 if(IIC_Wait_Ack())
	 {
		 IIC_Stop();
		 return 1;
	 }
   IIC_Send_Byte(Command);
	 if(IIC_Wait_Ack())
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
   IIC_Send_Byte(0x78);			//D/C#=0; R/W#=0
	 if(IIC_Wait_Ack())
	 {
		 IIC_Stop();
		 return 1;
	 }
   IIC_Send_Byte(0x40);			//write data
	 if(IIC_Wait_Ack())
	 {
		 IIC_Stop();
		 return 1;
	 }
   IIC_Send_Byte(Data);
	 if(IIC_Wait_Ack())
	 {
		 IIC_Stop();
		 return 1;
	 }
   IIC_Stop();
	 return 0;
}
void OLED_check(){

											   /*
												   while (1)
												   {
													   MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ); // 获取MPU6050的数据
													   OLED_ShowSignedNum(2, 1, AX, 5);			   // OLED显示数据
													   OLED_ShowSignedNum(3, 1, AY, 5);
													   OLED_ShowSignedNum(4, 1, AZ, 5);
													   OLED_ShowSignedNum(2, 8, GX, 5);
													   OLED_ShowSignedNum(3, 8, GY, 5);
													   OLED_ShowSignedNum(4, 8, GZ, 5);
												   }
												   */
}
