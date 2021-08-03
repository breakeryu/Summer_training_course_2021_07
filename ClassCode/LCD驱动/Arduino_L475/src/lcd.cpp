#include "lcd.h"


Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS , TFT_DC , TFT_MOSI , TFT_SCLK , TFT_RST);

/**
 * @brief	LCD初始化
 *
 * @param   void
 *
 * @return  void
 */
void LCD_Init(void)
{
  pinMode(PB7,OUTPUT);
  LCD_PWR(1);
  tft.init(LCD_Width,LCD_Height);

}

/**
 * 打开LCD显示
 *
 * @param   void
 *
 * @return  void
 */
void LCD_DisplayOn(void)
{
    LCD_PWR(1);
}
/**
 * 关闭LCD显示
 *
 * @param   void
 *
 * @return  void
 */
void LCD_DisplayOff(void)
{
    LCD_PWR(0);
}


