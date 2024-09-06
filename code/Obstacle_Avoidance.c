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

// 定义初始位置的角度值
int home_joint2 = 120;
int home_joint3 = 15;
int home_joint4 = 60;
int home_joint5 = 165;
int home_joint6 = 100;
int home_joint7 = 15;
int home_joint8 = 70;
int home_joint9 = 165;

// 定义超声波传感器的引脚
#define neck_survoPin 10
#define trigPin 11
#define echoPin 12

// 定义变量用于存储超声波测距结果
float Dulation = 0;
float Distance = 0;
int angle = 90;
int sum = 0;

void setup(){
  // 绑定舵机实例到对应的引脚
  joint2.attach(2);
  joint3.attach(3);
  joint4.attach(4);
  joint5.attach(5);
  joint6.attach(6);
  joint7.attach(7);
  joint8.attach(8);
  joint9.attach(9);

  // 绑定颈部伺服电机到指定引脚，并设置脉冲宽度范围
  neck_servo.attach(neck_survoPin, 500, 2400);
  neck_servo.write(angle);  // 设置颈部伺服电机到初始角度

  // 设置超声波传感器引脚模式
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);

  // 将所有舵机设置到初始位置
  joint2.write(home_joint2);
  joint3.write(home_joint3);
  joint4.write(home_joint4);
  joint5.write(home_joint5);
  joint6.write(home_joint6);
  joint7.write(home_joint7);
  joint8.write(home_joint8);
  joint9.write(home_joint9);

  // 延时3秒，用于舵机稳定
  delay(3000);
}

void loop(){
  // 调用standhome函数，将机器人归位到初始状态
  standhome();
  // 向前移动一步
  forward(1);

  // 超声波传感器测距
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  Dulation = pulseIn(echoPin,HIGH);
  Distance = Dulation*340*100/2/1000000;  // 计算距离，单位为厘米

  // 如果距离小于10厘米，则认为前方有障碍物
  if(Distance < 10){
    // 检测左侧是否有障碍物
    int right = 0;
    int left = 0;
    int sumright = 0;
    int sumleft = 0;
    int i = 170;
    delay(10);
    while(i >= 120){
      neck_servo.write(i);
      i=i-2;
      digitalWrite(trigPin,LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin,HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin,LOW);
      Dulation = pulseIn(echoPin,HIGH);
      Distance = Dulation*340*100/2/1000000;
      if(Distance < 15){
        left = 1;
        sumleft++;
      }
      delay(10);
    }
    i = 10;
    delay(10);
    while(i <= 60){
      neck_servo.write(i);
      i=i+2;
      digitalWrite(trigPin,LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin,HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin,LOW);
      Dulation = pulseIn(echoPin,HIGH);
      Distance = Dulation*340*100/2/1000000;
      if(Distance < 15){
        right = 1;
        sumright++;
      }
      delay(10);
    }

    neck_servo.write(90);
    delay(10);
    // 根据左右两侧的障碍物情况，决定机器人的转向
    if(sumright > sumleft){
      leftturn(3);
    } else {
      rightturn(3);
    }
    // 如果某一侧的障碍物数量达到20个，则后退并转向
    if(sumright >= 20){
      backward(3);
      leftturn(3);
    } else if(sumleft >= 20){
      backward(3);
      rightturn(3);
    }
  }
  delay(10);
}

// 机器人待机状态函数
void idle(){
  delay(100);
}

// 机器人归位到初始状态函数
void standhome(){
  // 将所有舵机设置到初始位置
  joint2.write(home_joint2);
  joint3.write(home_joint3);
  joint4.write(home_joint4);
  joint5.write(home_joint5);
  joint6.write(home_joint6);
  joint7.write(home_joint7);
  joint8.write(home_joint8);
  joint9.write(home_joint9);
}

// 机器人坐下函数
void sithome(){
  // 设置特定角度，使机器人坐下
  joint2.write(135);
  joint3.write(65);
  joint4.write(45);
  joint5.write(110);
  joint6.write(135);
  joint7.write(80);
  joint8.write(45);
  joint9.write(110);
}

// 机器人起立动作1
void stand1(){
  // 执行一系列动作，使机器人从坐下状态起立
  sithome();
  joint2.write(170);
  delay(300);
  joint2.write(home_joint2);
  delay(300);
  joint4.write(10);
  delay(300);
  joint4.write(home_joint4);
  delay(300);
  joint6.write(170);
  delay(300);
  joint6.write(home_joint6);
  delay(300);
  joint8.write(10);
  delay(300);
  joint8.write(home_joint8);
  
  joint3.write(home_joint3);
  joint5.write(home_joint5);
  joint7.write(home_joint7);
  joint9.write(home_joint9);
}

// 机器人起立动作2
void stand2(){
  // 执行一系列动作，使机器人从坐下状态起立
  sithome();
  joint2.write(175);
  joint4.write(5);
  joint6.write(175);
  joint8.write(5);
  delay(600);
  
  joint2.write(home_joint2);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  joint8.write(home_joint8);
  delay(600);
  
  joint3.write(home_joint3);
  joint5.write(home_joint5);
  joint7.write(home_joint7);
  joint9.write(home_joint9);
}

// 机器人起立动作3
void stand3(){
  // 执行一系列动作，使机器人从坐下状态起立
  sithome();
  int i;
  int j = 90;
  int k = 90;
  joint2.write(home_joint2);
  joint4.write(home_joint4);
  joint6.write(home_joint6);
  joint8.write(home_joint8);
  for(i = 90; i < 165; i++){
    joint5.write(i);
    j = j - 1;
    joint3.write(j);
    delay(20);
  }
  
  for(i = 115; i < 165; i++){
    joint9.write(i);
    k = k - 1;
    joint7.write(k);
    delay(20);
  }
}

// 机器人快速进行上下动作
void downaction(unsigned int step){
  while (step-- > 0){
    sithome();
    delay(100);
    standhome();
    delay(100);
  }
}

// 机器人挥动手臂
void wink(unsigned int step){
  standhome();
  joint9.write(home_joint9-30);
  
  while (step-- > 0){
    joint5.write(30);
    joint4.write(home_joint4 + 60);
    delay(300);
    joint4.write(home_joint4 - 60);
    delay(300);
  }
}

// 机器人摆动身体
void twist(){
  joint3.write(home_joint3);
  joint5.write(home_joint5);
  joint7.write(home_joint7);
  joint9.write(home_joint9);
  
  for(int right=90; right<170; right++){
      joint2.write(right);
      joint6.write(right);
      joint4.write(right-90);
      joint8.write(right-90);
      delay(10);
  }
  
  for(int right=170; right>90; right--){
joint2.write(right);
joint6.write(right);
joint4.write(right-90);
joint8.write(right-90);
delay(10);
}
}

// 机器人前进指定步数
void forward(unsigned int step){
while (step-- > 0){
joint3.write(home_joint3+30);  // 右前腿向前
joint7.write(home_joint7+30);  // 左后腿向前
delay(100);
joint2.write(home_joint2+30);  // 右后腿向前
joint8.write(home_joint8-30);  // 左前腿向后
joint4.write(home_joint4);  // 左前腿保持不变
joint6.write(home_joint6);  // 右前腿保持不变
delay(100);
joint3.write(home_joint3);  // 右前腿回到初始位置
joint7.write(home_joint7);  // 左后腿回到初始位置
idle();  // 待机
joint5.write(home_joint5-30);  // 右前腿向后
joint9.write(home_joint9-30);  // 左后腿向后
delay(100);
joint2.write(home_joint2);  // 右后腿回到初始位置
joint8.write(home_joint8);  // 左前腿回到初始位置
joint4.write(home_joint4-30);  // 左前腿向后
joint6.write(home_joint6+30);  // 右前腿向前
delay(100);
joint5.write(home_joint5);  // 右前腿回到初始位置
joint9.write(home_joint9);  // 左后腿回到初始位置
idle();  // 待机
}
}

// 机器人后退指定步数
void backward(unsigned int step){
while (step-- > 0){
joint3.write(home_joint3+30);  // 右前腿向后
joint7.write(home_joint7+30);  // 左后腿向后
delay(100);
joint2.write(home_joint2);  // 右后腿保持不变
joint8.write(home_joint8);  // 左前腿保持不变
joint4.write(home_joint4-30);  // 左前腿向后
joint6.write(home_joint6+30);  // 右前腿向后
delay(100);
joint3.write(home_joint3);  // 右前腿回到初始位置
joint7.write(home_joint7);  // 左后腿回到初始位置
idle();  // 待机
joint5.write(home_joint5-30);  // 右前腿向前
joint9.write(home_joint9-30);  // 左后腿向前
delay(100);
joint2.write(home_joint2+30);  // 右后腿向前
joint8.write(home_joint8-30);  // 左前腿向后
joint4.write(home_joint4);  // 左前腿保持不变
joint6.write(home_joint6);  // 右前腿保持不变
delay(100);
joint5.write(home_joint5);  // 右前腿回到初始位置
joint9.write(home_joint9);  // 左后腿回到初始位置
idle();  // 待机
}
}

// 机器人向右转指定步数
void rightturn(unsigned int step){
neck_rightrotate();  // 头部向右转
while (step-- > 0){
joint5.write(home_joint5-30);  // 右前腿向后
joint9.write(home_joint9-30);  // 左后腿向后
delay(100);
joint2.write(home_joint2+30);  // 右后腿向前
joint8.write(home_joint8-30);  // 左前腿向后
joint4.write(home_joint4-30);  // 左前腿向后
joint6.write(home_joint6+30);  // 右前腿向前
delay(100);
joint5.write(home_joint5);  // 右前腿回到初始位置
joint9.write(home_joint9);  // 左后腿回到初始位置
idle();  // 待机
joint3.write(home_joint3+30);  // 右前腿向前
joint7.write(home_joint7+30);  // 左后腿向前
delay(100);
joint2.write(home_joint2);  // 右后腿保持不变
joint8.write(home_joint8);  // 左前腿保持不变
joint4.write(home_joint4);  // 左前腿保持不变
joint6.write(home_joint6);  // 右前腿保持不变
delay(100);
joint3.write(home_joint3);  // 右前腿回到初始位置
joint7.write(home_joint7);  // 左后腿回到初始位置
idle();  // 待机
}
neck_home();  // 头部回到正直位置
}

// 机器人向左转指定步数
void leftturn(unsigned int step){
neck_leftrotate();  // 头部向左转
while (step-- > 0){
joint3.write(home_joint3+30);  // 右前腿向前
joint7.write(home_joint7+30);  // 左后腿向前
delay(100);
joint2.write(home_joint2+30);  // 右后腿向前
joint8.write(home_joint8-30);  // 左前腿向后
joint4.write(home_joint4-30);  // 左前腿向后
joint6.write(home_joint6+30);  // 右前腿向前
delay(100);
joint3.write(home_joint3);  // 右前腿回到初始位置
joint7.write(home_joint7);  // 左后腿回到初始位置
idle();  // 待机
joint5.write(home_joint5-30);  // 右前腿向后
joint9.write(home_joint9-30);  // 左后腿向后
delay(100);
joint2.write(home_joint2);  // 右后腿回到初始位置
joint8.write(home_joint8);  // 左前腿回到初始位置
joint4.write(home_joint4);  // 左前腿保持不变
joint6.write(home_joint6);  // 右前腿保持不变
delay(100);
joint5.write(home_joint5);  // 右前腿回到初始位置
joint9.write(home_joint9);  // 左后腿回到初始位置
idle();  // 待机
}
neck_home();  // 头部回到正直位置
}

// 头部左右移动
void neckrotate(){
int i=90;
while(i < 150){
neck_servo.write(i);
i++;
delay(5);
}
while(i > 30){
neck_servo.write(i);
i--;
delay(5);
}
while(i <= 90){
neck_servo.write(i);
i++;
delay(5);
}
}

// 头部向左转
void neck_leftrotate(){
int i=90;
while(i < 150){
neck_servo.write(i);
i++;
delay(5);
}
}

// 头部向右转
void neck_rightrotate(){
int i=90;
while(i > 30){
neck_servo.write(i);
i--;
delay(5);
}
}

// 头部回到正直位置
void neck_home(){
neck_servo.write(90);
}
/**
 *                    _ooOoo_
 *                   o8888888o
 *                   88" . "88
 *                   (| -_- |)
 *                    O\ = /O
 *                ____/`---'\____
 *              .   ' \\| |// `.
 *               / \\||| : |||// \
 *             / _||||| -:- |||||- \
 *               | | \\\ - /// | |
 *             | \_| ''\---/'' | |
 *              \ .-\__ `-` ___/-. /
 *           ___`. .' /--.--\ `. . __
 *        ."" '< `.___\_<|>_/___.' >'"".
 *       | | : `- \`.;`\ _ /`;.`/ - ` : | |
 *         \ \ `-. \_ __\ /__ _/ .-` / /
 * ======`-.____`-.___\_____/___.-`____.-'======
 *                    `=---='
 *
 * .............................................
 *          佛祖保佑             永无BUG
 */

