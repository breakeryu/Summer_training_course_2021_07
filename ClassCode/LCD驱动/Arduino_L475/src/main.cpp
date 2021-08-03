#include <Arduino.h>
#include "led.h"
#include "beep.h"
#include "key.h"
#include "usart.h"
#include "pwm.h"
#include "exti.h"
#include"lcd.h"


uint8_t key = 0;

void setup() {
  // put your setup code here, to run once:

  LCD_Init();//LCD初始化
  tft.fillScreen(ST77XX_GREEN);//设置清屏为绿色
  LED_Init();//LED初始化
  
  
}

void loop() {
  key++;
  if (key > 4)
  {
    key = 0;
  }
  
  LED_B_TogglePin;
  delay(20);

  switch (key)
  {
  case 0:
        tft.fillScreen(ST77XX_RED);
    break;
  case 1:
        tft.fillScreen(ST77XX_BLACK);
    break;
  case 2:
        tft.fillScreen(ST77XX_WHITE);
  break;
  case 3:
        tft.fillScreen(ST77XX_CYAN);
  break;
  default:
        tft.fillScreen(ST77XX_ORANGE);
    break;
  }
  delay(100);
  
  tft.setCursor(20,20);//设置光标位置
  tft.setTextColor(ST77XX_BLUE);//设置文本颜色
  tft.setTextSize(2);//设置字体大小
  tft.setTextWrap(true);//设置字符串超出宽度之后是否允许自动换行
  tft.setRotation(2);//设置（0，0）位置的方向，0-3
  tft.print("HALLO,TFT! I'am 007.So great!");//打印字符串
  delay(1000);

}


