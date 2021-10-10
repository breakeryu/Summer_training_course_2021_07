#ifndef _IIC_H
#define _IIC_H
#include <Arduino.h>
#include <Wire.h>
#include <AP3216_WE.h>


#define PIN_WIRE3_SDA PC1
#define PIN_WIRE3_SCL PC0


void AP3216_Init(void);
void AP3216_GetDate(void);
void AP3216_Print(void);



extern float als;
extern unsigned int prox;

#endif
