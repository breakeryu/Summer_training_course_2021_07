#include <Arduino.h>
#include <led.h>
#include"beep.h"
#include"key.h"
#include"usart.h"
#include <Wire.h>
#include <AP3216_WE.h>

TwoWire myWire3(PIN_WIRE3_SDA,PIN_WIRE3_SCL);
AP3216_WE myAP3216 = AP3216_WE(&myWire3);

void setup() {
  Serial.begin(9600);
  myWire3.begin();
	myAP3216.init();
  myAP3216.setLuxRange(RANGE_20661);
  myAP3216.setMode(AP3216_ALS_PS_ONCE);
  delay(1000);
}

void loop() {
  float als = myAP3216.getAmbientLight();       //读取寄存器中环境光强度数值
  unsigned int prox = myAP3216.getProximity();  //读取寄存器中接近传感器数值
  Serial.print("Lux: "); Serial.print(als);
  Serial.print("  Proximity: "); Serial.println(prox);
  myAP3216.setMode(AP3216_ALS_PS_ONCE); // initiates next measurement
  delay(1000); 
}

/*

  我们在使用IIC一类的接口传感器，往往可以在arduino框架下找到前人做好的传感器驱动，可以直接调用。
  今天演示的光强度和接近传感器一体的这款AP3216传感器就是如此。需要调整的部分是IIC的初始化部分，调整了
  输入的接口部分，然后其他的就如同example中的例子就可以。

*/


