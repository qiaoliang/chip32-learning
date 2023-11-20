#include "stm32f10x.h"
#include <stdint.h>

/**************************************************************************
 *  函数功能：把TIM2初始化为编码器接口模式
 *
 *  入口参数：无
 *
 *  返 回 值：无
 **************************************************************************/
void Encoder_Init_TIM2(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                         // 使能定时器2的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); // 使能PA PB端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;            // 端口配置 PA15
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);                // 根据设定参数初始化GPIOA

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;             // 端口配置 PB3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);                // 根据设定参数初始化GPIOB

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                  // 预分频器
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;      // 设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 选择时钟分频：不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 边沿计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             // 初始化定时器2

    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // 使用编码器模式3

    TIM_ICStructInit(&TIM_ICInitStructure); // 把TIM_ICInitStruct 中的每一个参数按缺省值填入
    TIM_ICInitStructure.TIM_ICFilter = 10;  // 设置滤波器长度
    TIM_ICInit(TIM2, &TIM_ICInitStructure); // 根据 TIM_ICInitStruct 的参数初始化外设	TIMx

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);      // 清除TIM的更新标志位
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 使能定时器中断

    TIM_SetCounter(TIM2, 0);
    TIM_Cmd(TIM2, ENABLE); // 使能定时器2
}

/**************************************************************************
函数功能：把TIM3初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
void Encoder_Init_TIM3(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // 使能定时器3的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能PA端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // 端口配置 PA6 PA7
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  // 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 // 根据设定参数初始化GPIOA

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                  // 预分频器
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;      // 设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 选择时钟分频：不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 边沿计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             // 初始化定时器3

    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); // 使用编码器模式3(TIM_ICPolarity_Rising或者TIM_ICPolarity_Falling效果相同，都是4倍频)

    TIM_ICStructInit(&TIM_ICInitStructure); // 把TIM_ICInitStruct 中的每一个参数按缺省值填入
    TIM_ICInitStructure.TIM_ICFilter = 10;  // 设置滤波器长度
    TIM_ICInit(TIM3, &TIM_ICInitStructure); // 根据 TIM_ICInitStruct 的参数初始化外设	TIMx

    TIM_ClearFlag(TIM3, TIM_FLAG_Update);      // 清除TIM的更新标志位
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // 使能定时器中断
    TIM_SetCounter(TIM3, 0);
    TIM_Cmd(TIM3, ENABLE); // 使能定时器
}

/**************************************************************************
函数功能：单位时间读取编码器A计数
入口参数：无
返回  值：计数值
**************************************************************************/
float Read_EncoderA(void)
{
    int Encoder_TIM = 0;
    float Speed = 0.0;
    Encoder_TIM = (short)TIM2->CNT;
    TIM2->CNT = 0;
    return -Encoder_TIM;
}
/**************************************************************************
函数功能：单位时间读取编码器B计数
入口参数：无
返回  值：计数值
**************************************************************************/
float Read_EncoderB(void)
{
    int Encoder_TIM = 0;
    float Speed = 0.0;
    Encoder_TIM = (short)TIM3->CNT;
    TIM3->CNT = 0;
    return Encoder_TIM;
}

/**************************************************************************
 *  函数功能：TIM2中断服务函数
 *
 *  入口参数：无
 *
 *  返 回 值：无
 **************************************************************************/
void TIM2_IRQHandler(void)
{
    if (TIM2->SR & 0X0001) // 溢出中断
    {
    }
    TIM2->SR &= ~(1 << 0); // 清除中断标志位
}

/**************************************************************************
 *  函数功能：TIM3中断服务函数
 *
 *  入口参数：无
 *
 *  返 回 值：无
 **************************************************************************/
void TIM3_IRQHandler(void)
{
    if (TIM3->SR & 0X0001) // 溢出中断
    {
    }
    TIM3->SR &= ~(1 << 0); // 清除中断标志位
}
