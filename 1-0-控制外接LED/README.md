# 关于 Stm32 Standard Library 的使用说明

当你使用 STM32F103C8T6 这个单片机学习时，你会发现在 PlatformIO 的文档与平台中找不到 SPL。

Stm32 Standard Library， 简称 SPL，是STM32 标准库。

因为 SPL 已经不推荐使用，而是使用 STM32Cube, 参见[这里的讨论。](https://community.platformio.org/t/stm32-standard-library/7086/11)


1. 将目录 framework-spl 复制到 ~/.platformio/packages 之下。
2. 修改 ~/.platformio/platforms/ststm32/boards/bluepill_f103c8.json 文件
  1. adds "spl" into the "frameworks" array   。这可以让 Platformio.ini 文件使用 framework=spl
  2. 在json 中的 "build:extra_flags"一节中，加入  '-DSTM32F10X_MD' ， 变为 "-DSTM32F1 -DSTM32F10X_MD -DSTM32F103xB"。因为这个是教程需要的选项。

