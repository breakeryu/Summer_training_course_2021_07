#include <Arduino.h>
#include "led/led.h"
#include "beep/beep.h"
#include "key/key.h"
#include "pwm/pwm.h"



uint8_t count = 0;
void setup() {
  // put your setup code here, to run once:
  attatchMotor();
}

void loop() {

  count += 1;

  if (count > 4){
    count = 0;
  }

  switch (count)
  {
    case 1:
      MotorFullSpeedFoward();
      break;
    case 2:
      MotorFoward(100);
      break;
    case 3:
      MotorFullSpeedReverse();
      break;
    case 4:
      MotorReverse(100);
    break;

  default:
      MotorStop();
    break;
  }

  delay(2000);

  MotorStop();   
  delay(2000);

}


/*

PWM的输出，在arduino环境下，引脚的配置已经完成，我们可以直接调用函数进行PWM输出
    具体的函数为  analogWrite(MA0, 255);
    模拟输出过程，对于初学者可以不考虑其他的配置，直接驱动常见的模块。
    如果要学习PWM其他的配置功能，如输出频率，占空比参数，可以自己进行深入的研究。

*/
