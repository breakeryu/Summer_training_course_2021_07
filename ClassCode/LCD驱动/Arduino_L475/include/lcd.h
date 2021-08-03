#ifndef _LCD_H_
#define _LCD_H

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789


//LCD的宽和高定义
#define LCD_Width 	240
#define LCD_Height 	240

/*
	LCD_PWR:	PB7
	LCD_RST:	PB6
	LCD_DC:		PB4
	LCD_CS:		PD7
*/
#define TFT_CS    PD7
#define TFT_RST   PB6
#define TFT_DC    PB4
#define TFT_MOSI  PB5
#define TFT_SCLK  PB3

#define	LCD_PWR(n)		(n?digitalWrite(PB7,HIGH):digitalWrite(PB7,LOW))


void LCD_Init(void);									//初始化
void LCD_DisplayOn(void);								//开显示
void LCD_DisplayOff(void);								//关显示

extern Adafruit_ST7789 tft;
#endif

