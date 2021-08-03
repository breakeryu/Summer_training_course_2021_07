#ifndef _PWM_H_
#define _PWM_H_
#include"Arduino.h"

#define MA0 PA0
#define MA1 PA1


void attatchMotor(void);

void MotorStop(void);
void MotorFoward(void);
void MotorFoward(uint8_t speed);
void MotorBReverse(void);
void MotorBReverse(uint8_t speed);


#endif
