#ifndef __ADC_H
#define __ADC_H
#include <Arduino.h>



#define TEST_ADCPIN PC4
#define sampleTime 10

void adc_init(void);
double adc_Test_Channel(double *voltage, int adcpin);
void adc_debug_print(void);
uint32_t adc_Get_Channel_Value(uint32_t * value, uint8_t sampleNum,int adcPin);

extern uint32_t sourceValue[sampleTime];
extern double voltageValue;

#endif