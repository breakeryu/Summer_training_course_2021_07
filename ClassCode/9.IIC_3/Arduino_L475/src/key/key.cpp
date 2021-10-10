#include "key.h"



/**
 * @brief	按键初始化函数
 *
 * @param   void
 *
 * @return  void
 */
void KEY_Init(void)
{
	/*
		KEY0 	- PD10
		KEY1 	- PD9
		KEY2 	- PD8
		WK_UP 	- PC13
	*/
	pinMode(PD8,INPUT_PULLUP);
    pinMode(PD9,INPUT_PULLUP);
    pinMode(PD10,INPUT_PULLUP);
    pinMode(PC13,INPUT_PULLDOWN);

 
}

/**
 * @brief	按键处理函数
 *
 * @remark	注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
 *
 * @param   mode	0:不支持连续按,1:支持连续按
 *
 * @return  u8		返回按键值	
*					0:没有任何按键按下,1:KEY0按下,2:KEY1按下,3:KEY2按下,4:WK_UP按下
 */
uint8_t KEY_Scan(uint8_t mode)
{
    static uint8_t key_up = 1;   //按键松开标志

    if(mode == 1)key_up = 1; //支持连按

    if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1))
    {
        delay(10);
        key_up = 0;

        if(KEY0 == 0)       return KEY0_PRES;

        else if(KEY1 == 0)  return KEY1_PRES;

        else if(KEY2 == 0)  return KEY2_PRES;

        else if(WK_UP == 1) return WKUP_PRES;
    }

    else if(KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WK_UP == 0)key_up = 1;

    return 0;   //无按键按下
}
