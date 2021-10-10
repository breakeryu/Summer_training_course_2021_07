#include <Arduino.h>
#include "led/led.h"
#include "beep/beep.h"
#include "key/key.h"
#include "pwm/pwm.h"
#include "usart/usart.h"
#include "adc/adc.h"


void setup() {
  usart_init();
  adc_init();
}


void loop() {
  
}

/*

adc学习过程类似于普通输入的部分，该部分的输入配置都在arduino的框架下配置好了。
    使用adc时使用analogRead(TEST_ADCPIN)即可。
*/
