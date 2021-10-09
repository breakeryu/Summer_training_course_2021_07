#include <Arduino.h>
#include  "led/led.h"
#include  "beep/beep.h"
#include  "key/key.h"
#include  "pwm/pwm.h"
#include  "usart/usart.h"

#define EXAMPLE1 1  //串口普通输出
#define EXAMPLE2 0  //串口简单输入

void setup() {
  // put your setup code here, to run once:
  usart_init();
  LED_Init();
}

void loop() {
  #if EXAMPLE1
    Serial.println("hello, world!");
    Serial.println(12345);
    Serial.println(12345.0123);
    Serial.print(53,HEX);
    Serial.print("\n");
    uint8_t codec[5] = {0xee,0x1,0x3,0xd,0x3};
    for (int i = 0; i < 5; i++)
    {
      Serial.write(codec[i]);
    }
    int myVariable = 233;
    Serial.println(myVariable);
    delay(2000);
  #elif EXAMPLE2
    uint8_t c = 0;
    if (Serial.available())
    {
      c = Serial.read();
    }
    if (c == 0xaa)
    {
      LED_R_Toggle;
    }
  #endif
  // put your main code here, to run repeatedly:
  

}

/*

串口设置教程,可以参考太极创客中的资料查看。这里提供的两个例子可以参考使用。
    1.在setup中进行参数的配置Serial.begin(115200);
    2.在其他需要的地方采用串口输入或输出命令。

*/
