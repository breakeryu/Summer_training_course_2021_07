#include <Arduino.h>
#include <led.h>
#include"beep.h"
#include"key.h"
#include"usart.h"

#define TEST_ADCPIN PC4
#define sampleTime 5
uint32_t sourceValue[sampleTime];
uint32_t avargeResult;
double voltageValue;

void setup() {
  avargeResult = 0;
  voltageValue = 0;
}


void loop() {

  avargeResult = 0;
  for (int i = 0; i < sampleTime; i++)
  {
    sourceValue[i] = analogRead(TEST_ADCPIN);
    avargeResult += sourceValue[i];
  }
  voltageValue = (double)avargeResult / 1023 / sampleTime;
  voltageValue = 3.3 * voltageValue;
  // put your main code here, to run repeatedly:
  delay(2000);

}

/*

adc学习过程类似于普通输入的部分，该部分的输入配置都在arduino的框架下配置好了。
    使用adc时使用analogRead(TEST_ADCPIN)即可。
*/
