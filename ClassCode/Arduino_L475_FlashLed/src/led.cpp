#include "led.h"

/**
 * @brief	LED IO初始化函数
 *
 * @param   void
 *
 * @return  void
 */
void LED_Init(void)
{
	/*
		LED-B	PE9
		LED-G	PE8
		LED-R	PE7	
	*/
    pinMode(PE7,OUTPUT);
    pinMode(PE8,OUTPUT);
    pinMode(PE9,OUTPUT);

	LED_R(1);
	LED_G(1);
	LED_B(1);

}





