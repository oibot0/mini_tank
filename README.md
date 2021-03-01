# mini_tank


This project is developed using Tuya SDK, which enables you to quickly develop branded apps connecting and controlling smart scenarios of many devices.For more information, please check Tuya Developer Website.

程序设计
       基于STM32cubeIDE的开发环境，首先很方便的配置MCU资源，其次STM32有很多的样例程序供参考，强大的HAL库，比如实现I2C，LPUART的控制都非常方便，包括现成HAL_Delay()等常用函数。涂鸦模块提供了MCU_sdk,但调试起来并不是很顺畅，也许提供更多的MCU接口样例供参考就更好了。配置串口比较容易出现问题，缺乏经验，按照涂鸦的移植教程，不能一步成功。参考了多位高手的样例，才将MCU和涂鸦模块连接到一块了。        配网后，程序控制也比较简单，MCU获取温度等信息，并上报手机APP，同时比较手机APP下发的温度值，如果未达到温度值，则打开开关，进行加热。当加热过程中发生过流情况，限流开关关闭，MCU接受到错误检测信号后，停止加热，并等待十秒后，再次启动加热，如果连续三次出错，需要手动复位。

硬件
主控：STM32L031F6P6
温湿度传感器：SHT30
联网模块：WB3D WiFi&BLE 双协议模组

开发环境：STM32CubeIDE
语言：C
目录结构
├─Core

│  ├─Inc

│  └─Src

├─Drivers

│  ├─CMSIS

│  ├─STM32L0xx_HAL_Driver

用STM32CubeIDE打开.project文件即可打开工程

作品相关图片
整体 界面展示 客户端界面



硬件演示
https://oshwhub.com/oibot/zhi-neng-xiao-yu-gang

License
MIT
