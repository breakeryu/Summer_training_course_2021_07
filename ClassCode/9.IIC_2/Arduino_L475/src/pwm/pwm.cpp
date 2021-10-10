#include "pwm.h"

/**
 * @brief	pwm IO初始化函数
 *
 * @param   a1,a2:函数入口引脚
 *
 * @return  void
 */
void attatchMotor(void)
{

  analogWrite(MA0, 0);
  analogWrite(MA1, 0);

}
/**
 * @brief	Motor停止 功能函数
 *
 * @param   void
 *
 * @return  void
 */
void MotorStop(void)
{

  analogWrite(MA0, 255);
  analogWrite(MA1, 255);

}
/**
 * @brief Motor前进 功能函数
 *
 * @param   void
 *
 * @return  void
 */
void MotorFullSpeedFoward(void)
{
  analogWrite(MA0, 255);
  analogWrite(MA1, 0);

}
/**
 * @brief	 Motor前进 功能函数
 *
 * @param   uint8_t speed
 *
 * @return  void
 */
void MotorFoward(uint8_t speed)
{

  analogWrite(MA0, speed);
  analogWrite(MA1, 0);
  
}

/**
 * @brief Motor反向转动 功能函数
 *
 * @param   void
 *
 * @return  void
 */
void MotorFullSpeedReverse(void)
{
  analogWrite(MA0, 0);
  analogWrite(MA1, 255);

}
/**
 * @brief	 Motor反向转动 功能函数
 *
 * @param   uint8_t speed
 *
 * @return  void
 */
void MotorReverse(uint8_t speed)
{
  analogWrite(MA0, 0);
  analogWrite(MA1, speed);
  
}


