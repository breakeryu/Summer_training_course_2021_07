#include "iic.h"


TwoWire myWire3(PIN_WIRE3_SDA,PIN_WIRE3_SCL);
AP3216_WE myAP3216 = AP3216_WE(&myWire3);
float als;
unsigned int prox;

void AP3216_Init(void){
    myWire3.begin();
	myAP3216.init();
    myAP3216.setLuxRange(RANGE_20661);
    myAP3216.setMode(AP3216_ALS_PS_ONCE);
}


void AP3216_GetDate(void){
    als = myAP3216.getAmbientLight();       //读取寄存器中环境光强度数值
    prox = myAP3216.getProximity();         //读取寄存器中接近传感器数值
    AP3216_Print();                         // print date
    myAP3216.setMode(AP3216_ALS_PS_ONCE);   // initiates next measurement
}


void AP3216_Print(void){
    Serial.print("Lux: "); Serial.print(als);
    Serial.print("  Proximity: "); Serial.println(prox);
}

