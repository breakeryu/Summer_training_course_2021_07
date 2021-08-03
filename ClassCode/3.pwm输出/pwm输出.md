# PWM输出

## 1.pwm配置和digital输出Pin配置要点
    在测试之后，我确定了一件事情：
    PWM和Digital输出是不能够重复定义的。在配置的时候，不能把已经配置为数字输出（digitalPin）的引脚在模拟输出中再次使用。
 
 例如：
 
 ```cpp
//配置PIN MODE
pinMode(MA0, OUTPUT);
pinMode(MA1, OUTPUT);

//数字输出和模拟输出混合使用
digitalWrite(MA0, LOW);
analogWrite(MA1, LOW);

//数字输出和模拟输出混合使用
analogWrite(MA0, 255);
digitalWrite(MA1, LOW);

```
    或者，用另外一种方式说这种情况：
    如果一个PIN，要作为模拟输出（pwm输出）的话，我们不能再将该PIN设置为数字输出模式。
     
    在arduino这个框架下的stm32开发中，一些东西的定义和原生的arduino板卡的开发模式稍稍是不同的。但是这个开发环境继承了
    arduino的很多优点。
     
## 2.代码驱动

    这次编写的电机驱动代码，使用了PA0,PA1两个Pin，驱动潘多拉开发板的板载电机。代码参考了arduino的库：DRV8833。
    该库是使用c++来编写的，这里，我就将他们改写为几个简单的C函数。
    
    这次修改部分包括pwm.cpp , pwm.h , main.c .
    
    最终实现的功能：
    
    loop:
    正转满速2s，停
    反转满速2s，停
    正转2s慢速，停
    反转2s快速，停
    
    
pwm.cpp
```cpp

#include "pwm.h"
/**
 * @brief pwm IO初始化函数
 *
 * @param   a1,a2:函数入口引脚
 *
 * @return  void
 */
void attatchMotor(void)
{
  analogWrite(MA0, LOW);
  analogWrite(MA1, LOW);
}

/**
 * @brief Motor停止 功能函数
 *
 * @param   void
 *
 * @return  void
 */
void MotorStop(void)
{
  analogWrite(MA0, 255);
  analogWrite(MA1, 255);
}

/**
 * @brief Motor前进 功能函数
 *
 * @param   void
 *
 * @return  void
 */
void MotorFoward(void)
{
  analogWrite(MA0, 255);
  analogWrite(MA1, LOW);
}

/**
 * @brief  Motor前进 功能函数
 *
 * @param   uint8_t speed
 *
 * @return  void
 */
void MotorFoward(uint8_t speed)
{
  analogWrite(MA0, speed);
  analogWrite(MA1, LOW);
}

/**
 * @brief Motor反向转动 功能函数
 *
 * @param   void
 *
 * @return  void
 */
void MotorBReverse(void)
{
  analogWrite(MA0, LOW);
  analogWrite(MA1, 255);
}

/**
 * @brief  Motor反向转动 功能函数
 *
 * @param   uint8_t speed
 *
 * @return  void
 */
void MotorBReverse(uint8_t speed)
{
  analogWrite(MA0, LOW);
  analogWrite(MA1, speed);
  
}


```
pwm.h

```cpp

#ifndef _PWM_H_
#define _PWM_H_
#include"Arduino.h"
#define MA0 PA0
#define MA1 PA1
void attatchMotor(void);
void MotorStop(void);
void MotorFoward(void);
void MotorFoward(uint8_t speed);
void MotorBReverse(void);
void MotorBReverse(uint8_t speed);
#endif

```
main,cpp
```cpp

#include <Arduino.h>
#include <led.h>
#include"beep.h"
#include"key.h"
#include"usart.h"
#include"pwm.h"
//开始一个新的项目
//参考rtt裸机历程，改写一个按键中断，驱动电机和蜂鸣器
uint8_t count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  attatchMotor();

}

void loop() {
  Serial.println("hallo!");

  count += 1;
   if (count > 4){
      count = 0;
   }

    switch (count)
    {
      case 1:
        MotorFoward();
        break;
      case 3:
        MotorFoward(128);
        break;
      case 2:
        MotorBReverse();
      break;
      case 4:
        MotorBReverse(200);
      break;
    default:
        MotorStop();
      break;
    }
    delay(2000);
    MotorStop();   
    delay(200);
}


```

## 3.断点调试功能
        
    这几次的调试过程都使用了platformio的断点调试功能，对于程序的测试是非常有帮助的。
    这次也发现PIO对于断点上面的一个支持限制：
    对于断点这个是利于系统资源的，他限制最多你可以设置6个断点。超过个数之后，调试功能就会异常。
       
    F10，F11之后也是我们在写代码后面要常常使用的功能。
## 4.遗留问题
    接下来使用中断，来控制电机。使用定时器也可以控制电机。