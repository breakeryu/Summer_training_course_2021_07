#ifndef _LED_H
#define _LED_H
#include <Arduino.h>

#define LEDR    PE7
#define LEDG    PE8
#define LEDB    PE9

#define LED_R(n)			(n?digitalWrite(LEDR,HIGH):digitalWrite(LEDR,LOW))
#define LED_R_TogglePin		digitalToggle(LEDR)

#define LED_G(n)			(n?digitalWrite(LEDG,HIGH):digitalWrite(LEDG,LOW))
#define LED_G_TogglePin     digitalToggle(LEDG)

#define LED_B(n)			(n?digitalWrite(LEDB,HIGH):digitalWrite(LEDB,LOW))
#define LED_B_TogglePin     digitalToggle(LEDB)

void LED_Init(void);

#endif
