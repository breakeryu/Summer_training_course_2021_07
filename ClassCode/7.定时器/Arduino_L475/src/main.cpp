#include <Arduino.h>
#include "led/led.h"
#include "beep/beep.h"
#include "key/key.h"
#include "usart/usart.h"
#include "adc/adc.h"
#include "pwm/pwm.h"
#include "exti/exti.h"
#include "timer/timer.h"




void setup() {
  usart_init();
  LED_Init();
  timer_Init();
 
}

void loop() {

  timer_demo_loop();
  
}


/*

定时器学习的部分,要参考STM32的配置方式，从根本上看，还是对寄存器进行配置。可以参考#include "HardwareTimer.h"
中的定义，来对定时器进行设置。
    配置的过程中，需要计算定时器的周期等参数，还需要对定时器的时钟生成有一定的了解，可以参考芯片的数据手册来进行
  设置。

*/

