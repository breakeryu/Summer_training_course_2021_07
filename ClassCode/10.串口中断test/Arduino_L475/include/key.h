#ifndef _KEY_H
#define _KEY_H
#include <Arduino.h>


/*
	KEY0 	- PD10
	KEY1 	- PD9
	KEY2 	- PD8
	WK_UP 	- PC13
*/
#define KEY0        digitalRead(PD10)
#define KEY1        digitalRead(PD9)
#define KEY2        digitalRead(PD8)
#define WK_UP       digitalRead(PC13)

#define KEY0_PRES 		1
#define KEY1_PRES		2
#define KEY2_PRES		3
#define WKUP_PRES   	4

void KEY_Init(void);
uint8_t KEY_Scan(uint8_t mode);
#endif
