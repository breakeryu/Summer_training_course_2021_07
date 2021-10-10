#include <Arduino.h>
#include "adc/adc.h"
#include "beep/beep.h"
#include "exti/exti.h"
#include "key/key.h"
#include "led/led.h"
#include "pwm/pwm.h"
#include "usart/usart.h"



void setup() {
  // put your setup code here, to run once:
  attatchMotor();
  exti_init();
  LED_Init();

}

void loop() {

  LED_B_Toggle;
  delay(500);
  
}


