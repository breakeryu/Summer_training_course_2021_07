#include <Arduino.h>
#include "led/led.h"
#include "key/key.h"
#include "beep/beep.h"

uint8_t key;


void setup() {
  // put your setup code here, to run once:
  LED_Init();
  BEEP_Init();
  KEY_Init();

}

void loop() {
  // put your main code here, to run repeatedly:
 
  key = KEY_Scan(0);          //按键扫描，不支持连续按

        switch(key)
        {
            case  WKUP_PRES:		//控制蜂鸣器状态翻转
                BEEP_Toggle;
                break;

            case  KEY2_PRES:		//控制LED_B红灯状态翻转
                LED_B_Toggle;
                break;

            case  KEY1_PRES:		//控制LED_G绿灯状态翻转
                LED_G_Toggle;
                break;

            case  KEY0_PRES:		//控制LED_R蓝灯状态翻转
                LED_R_Toggle;
                break;
			      default:
				        break;
        }

        delay(10);


}


/*

IO普通输入：
    这次的实验使用了IO的输入模式，使用步骤如下：
        1.在setup中配置使用方式pinMode(PD8,INPUT_PULLDOWN);
            输入模式有       INPUT 
                            INPUT_PULLUP 
                            INPUT_PULLDOWN
        2.然后可以在需要的地方使用digitalRead来读取IO的电平状态

*/

