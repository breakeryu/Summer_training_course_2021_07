#include "exti.h"
#include "pwm.h"
/**
 * @brief	exit IO初始化函数
 *
 * @param   配置KEY0,KEY1,KEY2,WAKE_UP为中断源
 *
 * @return  void
 */
void exti_init(void)
{
    attachInterrupt(PD8,motor_forward,FALLING);//KEY2 --前进
    attachInterrupt(PD9,motor_forward_low,FALLING);//KEY1 --
    attachInterrupt(PD10, motor_breverse,FALLING);//KEY0
    attachInterrupt(PC13,motor_breverse_fast,RISING);//WAKE_UP

}

/**
 * @brief	KEY2中断回调 函数
 *
 * @param   void
 *
 * @return  void
 */
void motor_forward(void)
{

    MotorFoward();
    
}


/**
 * @brief	KEY1中断回调 函数
 *
 * @param   void
 *
 * @return  void
 */
void motor_forward_low(void)
{
     MotorFoward(128);

}

/**
 * @brief	KEY0中断回调 函数
 *
 * @param   void
 *
 * @return  void
 */
void motor_breverse(void)
{
     MotorBReverse();

}

/**
 * @brief	WAKE_UP中断回调 函数
 *
 * @param   void
 *
 * @return  void
 */
void motor_breverse_fast(void)
{
    MotorBReverse(200);

}




