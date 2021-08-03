#include <Arduino.h>
#include <led.h>

//初始化函数
void setup() {
  // put your setup code here, to run once:
  LED_Init();
}

//主循环函数
void loop() {
  // put your main code here, to run repeatedly:
 LED_R(0);
 delay(1000);
 LED_R(1);
 delay(1000);

 LED_G(0);
 delay(1000);
 LED_G(1);
 delay(1000);

 LED_B(0);
 delay(1000);
 LED_B(1);
 delay(1000);
 
}

/*

IO的普通输出配置：
  1.在setup函数中使用pinMode函数，设置引脚的模式
  2.配置之后可以使用以下几个函数设置引脚的输出电平
      digitalWrite  //该函数可对选用的IO设置值
      digitalToggle //该函数可对选用的IO的电平进行翻转

*/

