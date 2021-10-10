#include <Arduino.h>
#include "iic/icm20608.h"
#include "Wire.h"


//todo 使用软件模拟进行读写iic

void setup() {
  Serial.begin(9600);
  ICM20608_Init();
  delay(1000);
  
}

void loop() {
  ICM20608_TestDemo();
  delay(500);
}

/*

  我们在使用IIC一类的接口传感器，往往可以在arduino框架下找到前人做好的传感器驱动，可以直接调用。
  今天演示的光强度和接近传感器一体的这款AP3216传感器就是如此。需要调整的部分是IIC的初始化部分，调整了
  输入的接口部分，然后其他的就如同example中的例子就可以。

*/


