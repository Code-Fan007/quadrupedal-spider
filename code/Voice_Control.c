//请联合arduino和语言扩展板（卖家会给资料）模块使用
//复制到arduino中，创建文件
#include <Servo.h>

// 舵机定义
Servo joint2;  // 右前臀部
Servo joint3;  // 右前腿部
Servo joint4;  // 左前臀部
Servo joint5;  // 左前腿部
Servo joint6;  // 左后臀部
Servo joint7;  // 左后腿部
Servo joint8;  // 右后臀部
Servo joint9;  // 右后腿部
Servo neck_servo;  // 颈部伺服电机

// 舵机的初始位置（主位置）
int home_joint2 = 120;
int home_joint3 = 15;
int home_joint4 = 60;
int home_joint5 = 165;
int home_joint6 = 100;
int home_joint7 = 15;
int home_joint8 = 70;
int home_joint9 = 165;

// 语音模块的引脚定义
const int cmdForwardPin = A3; // 前进命令的引脚
const int cmdBackwardPin = A4; // 后退命令的引脚

void setup() {
  // 初始化舵机
  joint2.attach(2);
  joint3.attach(3);
  joint4.attach(4);
  joint5.attach(5);
  joint6.attach(6);
  joint7.attach(7);
  joint8.attach(8);
  joint9.attach(9);
  neck_servo.attach(10);  // 假定颈部伺服电机连接到了数字引脚10

  // 将舵机移到初始位置
  standHome();

  // 设置语音模块引脚为输入
  pinMode(cmdForwardPin, INPUT);
  pinMode(cmdBackwardPin, INPUT);

  // 开始串行通信
  Serial.begin(9600);
}

void loop() {
  // 读取语音模块的引脚状态
  if (digitalRead(cmdForwardPin) == HIGH) {
    forward(1);  // 只执行1步前进动作
  }
  else if (digitalRead(cmdBackwardPin) == HIGH) {
    backward(1);  // 只执行1步后退动作
  }
}

void forward(unsigned int step){
  while (step-- > 0){
    // 前进动作逻辑
    joint3.write(home_joint3 + 30);
    joint7.write(home_joint7 + 30);
    delay(100);
    joint2.write(home_joint2 + 30);
    joint8.write(home_joint8 - 30);
    joint4.write(home_joint4);
    joint6.write(home_joint6);
    delay(100);
    joint3.write(home_joint3);
    joint7.write(home_joint7);
    delay(100);
    joint5.write(home_joint5 - 30);
    joint9.write(home_joint9 - 30);
    delay(100);
    joint2.write(home_joint2);
    joint8.write(home_joint8);
    joint4.write(home_joint4 - 30);
    joint6.write(home_joint6 + 30);
    delay(100);
    joint5.write(home_joint5);
    joint9.write(home_joint9);
    delay(100);
  }
}

void backward(unsigned int step){
  while (step-- > 0){
    // 后退动作逻辑
    joint3.write(home_joint3 + 30);
    joint7.write(home_joint7 + 30);
    delay(100);
    joint2.write(home_joint2);
    joint8.write(home_joint8);
    joint4.write(home_joint4 - 30);
    joint6.write(home_joint6 + 30);
    delay(100);
    joint3.write(home_joint3);
    joint7.write(home_joint7);
    delay(100);
    joint5.write(home_joint5 - 30);
    joint9.write(home_joint9 - 30);
    delay(100);
    joint2.write(home_joint2 + 30);
    joint8.write(home_joint8 - 30);
    joint4.write(home_joint4);
    joint6.write(home_joint6);
    delay(100);
    joint5.write(home_joint5);
    joint9.write(home_joint9);
    delay(100);
  }
}

void standHome(){
  // 舵机回到初始位置
  joint2.write(home_joint2);
  joint3.write(home_joint3);
  joint4.write(home_joint4);
  joint5.write(home_joint5);
  joint6.write(home_joint6);
  joint7.write(home_joint7);
  joint8.write(home_joint8);
  joint9.write(home_joint9);
  neck_servo.write(90); // 颈部伺服电机回到90度的中心位置
  delay(500);
}

