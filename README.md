# quadrupedal-spider
Arduino controlled joint 8-servo 4-legged Walking Robot
对原有的朋友项目的基础上进行改进；添加语音模块、wifi模块，后期换成其他主板提供基础
主要使用arduino和sg90舵机来控制，
- 开发语言C语言
- 开发工具arduino IDE，并配置Arduino Nano

# 选购清单
![alt text](image/buy-bill.png)
![alt text](image/buy-bill2.png)

# 步骤
- 购买完零件清单(buy-bill)
- 打印3D外观建模
- 下载arduino IDE，进行烧录代码文件

这些组件和模块共同构成了一个功能丰富的智能机器人系统，可以实现语音控制、自动避障、远程监控和物联网等多种高级功能l

布线细节：按照分配的舵机编号的顺序将它们连接到数字端子。舵机编号 2 → D2 销，舵机编号 3 → D3 销：颈部舵机为 D10。HC-SR04 超声波传感器通过将 Echo 引脚连接到 D12，将 Triger 引脚连接到 D11 引脚，并将 Vcc 和 GND 连接到额外的数字引脚来供电

## finish
![alt text](image/finish.jpg)
![alt text](image/finish2.jpg)