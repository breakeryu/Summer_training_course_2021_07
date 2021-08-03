#include <Arduino.h>
#include <led.h>
#include"beep.h"
#include"key.h"
#include"usart.h"
#include "icm20608.h"
#include "Wire.h"

double temp = 0;
short gayWay;
short Gy[3];
short Ac[3];


void setup() {
  Serial.begin(9600);
  ICM20608_Init();
  delay(1000);
  
}

void loop() {
  gayWay = MPU_Get_Temperature();	
  temp = (double)gayWay / 100.0;
  MPU_Get_Accelerometer(&Ac[0],&Ac[1],&Ac[2]);	
  MPU_Get_Gyroscope(&Gy[0],&Gy[1],&Gy[2]);	

  Serial.print("temp = ");
  Serial.println(temp);

  Serial.print("Gyroscope : ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print(Gy[i]);
    Serial.print("  ");
  }
  Serial.println();

  Serial.print("Accelerometer : ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print(Ac[i]);
    Serial.print("  ");
  }
  Serial.println();

  delay(3000);
}

/*

  我们在使用IIC一类的接口传感器，往往可以在arduino框架下找到前人做好的传感器驱动，可以直接调用。
  今天演示的光强度和接近传感器一体的这款AP3216传感器就是如此。需要调整的部分是IIC的初始化部分，调整了
  输入的接口部分，然后其他的就如同example中的例子就可以。

*/


