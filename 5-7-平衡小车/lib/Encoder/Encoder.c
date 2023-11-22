#include "stm32f10x.h"                  // Device header
#include "Encoder.h"
/**
  * 函    数：编码器初始化
  * 参    数：无
  * 返 回 值：无
  */

void Encoder_Init(void)
{
	Encoder_Left_Init();
	Encoder_Right_Init();
}
void Encoder_Left_Init(void)
{
	/*开启外设时钟*/
	RCC_APB1PeriphClockCmd(Encoder_Left_TIMER_CLK, ENABLE);				// 开启TIM3的时钟
	RCC_APB2PeriphClockCmd(Encoder_Left_GPIO_CLK, ENABLE);				// 开启GPIOA的时钟

	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = Encoder_Left_A_Pin | Encoder_Left_B_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Encoder_Left_GPIO_Port, &GPIO_InitStructure); // 将PA6和PA7引脚初始化为上拉输入

	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;               //计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;                //预分频器. PSC 值. 这里是 0 ,表示不分频，因为频率由编码器的输入信号决定
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(Encoder_Left_TIMER, &TIM_TimeBaseInitStructure);	// 将结构体变量交给TIM_TimeBaseInit，配置TIM3的时基单元

	/*输入捕获初始化*/
	TIM_ICInitTypeDef TIM_ICInitStructure;							//定义结构体变量
	TIM_ICStructInit(&TIM_ICInitStructure);							//结构体初始化，若结构体没有完整赋值
																	//则最好执行此函数，给结构体所有成员都赋一个默认值
																	//避免结构体初值不确定的问题
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;				//选择配置定时器通道1
	TIM_ICInitStructure.TIM_ICFilter = 0xF;							//输入滤波器参数，可以过滤信号抖动
	TIM_ICInit(Encoder_Left_TIMER, &TIM_ICInitStructure);				// 将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;				//选择配置定时器通道2
	TIM_ICInitStructure.TIM_ICFilter = 0xF;							//输入滤波器参数，可以过滤信号抖动
	TIM_ICInit(Encoder_Left_TIMER, &TIM_ICInitStructure);				// 将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道

	/*编码器接口配置*/
	TIM_EncoderInterfaceConfig(Encoder_Left_TIMER, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	// 配置编码器模式以及两个输入通道是否反相
	// 注意此时参数的Rising和Falling已经不代表上升沿和下降沿了，而是代表是否反相
	// 此函数必须在输入捕获初始化之后进行，否则输入捕获的配置会覆盖此函数的部分配置

	/*TIM使能*/
	TIM_Cmd(Encoder_Left_TIMER, ENABLE); // 使能TIM3，定时器开始运行
}
void Encoder_Right_Init(void)
{
	/*开启外设时钟*/
	RCC_APB1PeriphClockCmd(Encoder_Right_TIMER_CLK, ENABLE); // 开启TIM3的时钟
	RCC_APB2PeriphClockCmd(Encoder_Right_GPIO_CLK, ENABLE);	// 开启GPIOA的时钟

	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = Encoder_Right_A_Pin | Encoder_Right_B_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Encoder_Right_GPIO_Port, &GPIO_InitStructure); // 将PA6和PA7引脚初始化为上拉输入

	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				  // 定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		  // 时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	  // 计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;				  // 计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;				  // 预分频器. PSC 值. 这里是 0 ,表示不分频，因为频率由编码器的输入信号决定
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			  // 重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(Encoder_Right_TIMER, &TIM_TimeBaseInitStructure); // 将结构体变量交给TIM_TimeBaseInit，配置TIM3的时基单元

	/*输入捕获初始化*/
	TIM_ICInitTypeDef TIM_ICInitStructure;	// 定义结构体变量
	TIM_ICStructInit(&TIM_ICInitStructure); // 结构体初始化，若结构体没有完整赋值
											// 则最好执行此函数，给结构体所有成员都赋一个默认值
											// 避免结构体初值不确定的问题
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;	  // 选择配置定时器通道1
	TIM_ICInitStructure.TIM_ICFilter = 0xF;				  // 输入滤波器参数，可以过滤信号抖动
	TIM_ICInit(Encoder_Left_TIMER, &TIM_ICInitStructure); // 将结构体变量交给TIM_ICInit，配置TIM4的输入捕获通道
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;	  // 选择配置定时器通道2
	TIM_ICInitStructure.TIM_ICFilter = 0xF;				  // 输入滤波器参数，可以过滤信号抖动
	TIM_ICInit(Encoder_Right_TIMER, &TIM_ICInitStructure); // 将结构体变量交给TIM_ICInit，配置TIM4的输入捕获通道

	/*编码器接口配置*/
	TIM_EncoderInterfaceConfig(Encoder_Right_TIMER, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	// 配置编码器模式以及两个输入通道是否反相
	// 注意此时参数的Rising和Falling已经不代表上升沿和下降沿了，而是代表是否反相
	// 此函数必须在输入捕获初始化之后进行，否则输入捕获的配置会覆盖此函数的部分配置

	/*TIM使能*/
	TIM_Cmd(Encoder_Right_TIMER, ENABLE); // 使能TIM3，定时器开始运行
}

/**
  * 函    数：获取编码器的增量值
  * 参    数：无
  * 返 回 值：自上此调用此函数后，编码器的增量值
  */
int16_t Encoder_Left_Get(void)
{
	/*使用Temp变量作为中继，目的是返回CNT后将其清零*/
	int16_t Temp;
	Temp = TIM_GetCounter(Encoder_Left_TIMER);
	TIM_SetCounter(Encoder_Left_TIMER, 0);
	return Temp;
}
int16_t Encoder_Right_Get(void)
{
	/*使用Temp变量作为中继，目的是返回CNT后将其清零*/
	int16_t Temp;
	Temp = TIM_GetCounter(Encoder_Right_TIMER);
	TIM_SetCounter(Encoder_Right_TIMER, 0);
	return Temp;
}