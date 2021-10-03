#ifndef __BEEP_H
#define __BEEP_H
#include <Arduino.h>


#define BEEP(n)	(n?digitalWrite(PB2,HIGH):digitalWrite(PB2,LOW))
#define BEEP_TogglePin	digitalToggle(PB2)


void BEEP_Init(void);




#endif


