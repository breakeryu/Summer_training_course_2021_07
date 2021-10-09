#include <Arduino.h>
#include <led.h>
#include"beep.h"
#include"key.h"
#include"usart.h"
#include"pwm.h"
#include"exti.h"





void setup() {
  // put your setup code here, to run once:

  attatchMotor();
  exti_init();
  LED_Init();
  

}

void loop() {

LED_B_TogglePin;
delay(500);
}


