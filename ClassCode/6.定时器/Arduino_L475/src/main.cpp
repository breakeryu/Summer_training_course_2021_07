#include <Arduino.h>
#include <led.h>
#include"beep.h"
#include"key.h"
#include"usart.h"

#define USER_TIMER_CHANNEL  1
#define USER_PERIOD 500
#define USER_PSC  80
//定时器句柄
HardwareTimer myTimer(TIM3);

void ledToggle(void){
  LED_R_TogglePin;
} 


void timerInit(void){
  myTimer.setMode(USER_TIMER_CHANNEL,TIMER_OUTPUT_COMPARE);   //配置定时器通道，设置定时器输出方式

  //定时器输出周期 P = 时钟频率（80M）/ 分频系数（USER_PSC）/ 计数值（USER_PERIOD）/ 1000000
  myTimer.setPrescaleFactor(USER_PSC);                        //设置分频系数
  myTimer.setCount(USER_PERIOD,MICROSEC_FORMAT);              //设置定时器周期

  myTimer.attachInterrupt(ledToggle);                         //配置中断函数
  myTimer.resumeChannel(USER_TIMER_CHANNEL);                  //开启定时器
}


void setup() {
  LED_Init();
  timerInit();
  // Serial.begin(9600);
  // Serial.println(myTimer.getTimerClkFreq());
}

void loop() {


}


/*

定时器学习的部分,要参考STM32的配置方式，从根本上看，还是对寄存器进行配置。可以参考#include "HardwareTimer.h"
中的定义，来对定时器进行设置。
    配置的过程中，需要计算定时器的周期等参数，还需要对定时器的时钟生成有一定的了解，可以参考芯片的数据手册来进行
  设置。

*/

