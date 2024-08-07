//复制到arduino IDE中，创建文件
//按此图来连接线路；
//  --------                 --------
// |  D9    |               |  D7    |
// | joint9 |               | joint7 |
//  ----- --------     --------- -----
//       |  D8    |   |  D6    |
//       | joint8 |   | joint6 |
//        --------     --------
//       |  D2    |  |   D4    |
//       | joint2 |  |  joint4 |
//  ----- --------    --------- -----
// |  D3    |               |  D5    |
// | joint3 |               | joint5 |
            
//***************************************
// 包含Servo库用于控制舵机
#include <Servo.h>

// 定义舵机实例
Servo joint2;  // 右前髋关节 右前臀部
Servo joint3;  // 右前腿 右前腿
Servo joint4;  // 左前髋关节 左前臀部
Servo joint5;  // 左前腿
Servo joint6;  // 左后髋关节 左后臀部
Servo joint7;  // 左后腿
Servo joint8;  // 右后髋关节 右后臀部
Servo joint9;  // 右后腿
Servo neck_servo;  // 颈部伺服电机

