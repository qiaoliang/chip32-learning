## 功能说明

使用STM32F103C8T6开发板,实现外部中断的基本结构.

上升沿与下降沿都可以捕获中断.

## 硬件模块

* STM32F103C8T6最小系统板

![STM32F103C8T6最小系统板](STM32F103C8T6.png)

* STLink2 USB调试器

![STLink2 USB调试器](STLink2.png)]

* 0.96 OLED液晶屏

![OLED液晶屏](OLED.png)

* SG90 舵机

![SG90 舵机](sg90.png)


## 接线图

![](pcb-board.jpg)


## 外部中断的基本结构

初始化中断,通常从左到右依序进行.

![初始化中断](外部中断基本结构.png)