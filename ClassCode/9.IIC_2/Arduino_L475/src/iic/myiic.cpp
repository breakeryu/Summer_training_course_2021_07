#include "myiic.h"

/*********************************************************************************
			  ___   _     _____  _____  _   _  _____  _____  _   __
			 / _ \ | |   |_   _||  ___|| \ | ||_   _||  ___|| | / /
			/ /_\ \| |     | |  | |__  |  \| |  | |  | |__  | |/ /
			|  _  || |     | |  |  __| | . ` |  | |  |  __| |    \
			| | | || |_____| |_ | |___ | |\  |  | |  | |___ | |\  \
			\_| |_/\_____/\___/ \____/ \_| \_/  \_/  \____/ \_| \_/

 *	******************************************************************************
 *	本程序只供学习使用，未经作者许可，不得用于其它任何用途
 *	ALIENTEK Pandora STM32L475 IOT开发板
 *	IIC驱动代码
 *	正点原子@ALIENTEK
 *	技术论坛:www.openedv.com
 *	创建日期:2018/10/27
 *	版本：V1.0
 *	版权所有，盗版必究。
 *	Copyright(C) 广州市星翼电子科技有限公司 2014-2024
 *	All rights reserved
 *	******************************************************************************
 *	初始版本
 *	******************************************************************************/

/**
 * @brief	IIC初始化函数
 *
 * @param   void
 *
 * @return  void
 */
void IIC_Init(void)
{
    pinMode(IIC_SCLPIN,OUTPUT);
    pinMode(IIC_SDAPIN,OUTPUT);

    IIC_SDA(1);
    IIC_SCL(1);
}

/**
 * @brief	产生IIC起始信号
 *
 * @param   void
 *
 * @return  void
 */
void IIC_Start(void)
{
    SDA_OUT();     //sda线输出
    IIC_SDA(1);
    IIC_SCL(1);
    delayMicroseconds(4);
    IIC_SDA(0);//START:when CLK is high,DATA change form high to low
	delayMicroseconds(4);
    IIC_SCL(0);//钳住I2C总线，准备发送或接收数据
}
/**
 * @brief	产生IIC停止信号
 *
 * @param   void
 *
 * @return  void
 */
void IIC_Stop(void)
{
    SDA_OUT();//sda线输出
	IIC_SDA(0);
    IIC_SCL(1);
    delayMicroseconds(4);
	IIC_SDA(1);//STOP:when CLK is high DATA change form low to high
	delayMicroseconds(4);
	IIC_SCL(0);//发送I2C总线结束信号
}

/**
 * @brief	等待应答信号到来
 *
 * @param   void
 *
 * @return  uint8_t		1，接收应答失败
 *					0，接收应答成功
 */
uint8_t IIC_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    SDA_IN();      //SDA设置为输入
    IIC_SDA(1);
    delayMicroseconds(2);
    IIC_SCL(1);
    delayMicroseconds(2);

    while(READ_SDA)
    {
        ucErrTime++;

        if(ucErrTime > 250)
        {
            IIC_Stop();
            return 1;
        }
    }

    IIC_SCL(0);//时钟输出0
    return 0;
}
/**
 * @brief	产生ACK应答
 *
 * @param   void
 *
 * @return  void
 */
void IIC_Ack(void)
{
    IIC_SCL(0);
    SDA_OUT();
    IIC_SDA(0);
    delayMicroseconds(2);
    IIC_SCL(1);
    delayMicroseconds(2);
    IIC_SCL(0);
}
/**
 * @brief	不产生ACK应答
 *
 * @param   void
 *
 * @return  void
 */
void IIC_NAck(void)
{
    IIC_SCL(0);
    SDA_OUT();
    IIC_SDA(1);
    delayMicroseconds(2);
    IIC_SCL(1);
    delayMicroseconds(2);
    IIC_SCL(0);
}
/**
 * @brief	IIC发送一个字节
 *
 * @param   txd		需要发送的数据
 *
 * @return  void
 */
void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    IIC_SCL(0);//拉低时钟开始数据传输

    for(t = 0; t < 8; t++)
    {
        IIC_SDA((txd & 0x80) >> 7);
        txd <<= 1;
        IIC_SCL(1);
        delayMicroseconds(2);
        IIC_SCL(0);
        delayMicroseconds(2);
    }
}
/**
 * @brief	读1个字节数据
 *
 * @param   ack		1，发送ACK		0，发送nACK
 *
 * @return  uint8_t		返回读取数据
 */
uint8_t IIC_Read_Byte(unsigned char ack)
{
    unsigned char i, receive = 0;
    SDA_IN();//SDA设置为输入

    for(i = 0; i < 8; i++)
    {
        IIC_SCL(0);
        delayMicroseconds(2);
        IIC_SCL(1);
        receive <<= 1;
        if(READ_SDA)receive++;
        delayMicroseconds(2);
    }

    if(!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK

    return receive;
}


