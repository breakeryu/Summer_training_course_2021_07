#include "adc.h"


uint32_t sourceValue[sampleTime];
double voltageValue;


void adc_init(void){
    adc_Test_Channel(&voltageValue,TEST_ADCPIN);
    adc_debug_print();
}

double adc_Test_Channel(double *voltage, int adcpin){
    *voltage = 3.3 * (double)adc_Get_Channel_Value(sourceValue,sampleTime,adcpin) / 1023 ;
    return *voltage;
}

void adc_debug_print(void){
    Serial.print("voltage = ");
    Serial.println(voltageValue);
}

uint32_t adc_Get_Channel_Value(uint32_t * value, uint8_t sampleNum,int adcPin){
    uint32_t avargeResult = 0;
    for (int i = 0; i < sampleNum; i++)
    {
        value[i] = analogRead(adcPin);
        avargeResult += value[i];
    }
    return (avargeResult / sampleNum);
}
