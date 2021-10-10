#include "aht10.h"
#include "delay.h"
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
 *	AHT10驱动代码
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
 * @brief	向ATH10写入数据
 *
 * @param   cmd		命令
 * @param   data	要写入的数据
 * @param   len		写入数据大小
 *
 * @return  u8		0,正常,其他,错误代码
 */
u8 AHT10_Write_Data(u8 cmd, u8 *data, u8 len)
{
    IIC_Start();
    IIC_Send_Byte((AHT10_IIC_ADDR << 1) | 0); //发送器件地址+写命令

    if(IIC_Wait_Ack())          //等待应答
    {
        IIC_Stop();
        return 1;
    }

    IIC_Send_Byte(cmd);         //写寄存器地址
    IIC_Wait_Ack();             //等待应答

    for(u8 i = 0; i < len; i++)
    {
        IIC_Send_Byte(data[i]);     //发送数据
        IIC_Wait_Ack();				//等待应答
    }

    IIC_Stop();
    return 0;
}


/**
 * @brief	读一个字节
 *
 * @param   void
 *
 * @return  u8		读到的数据
 */
u8 AHT10_ReadOneByte(void)
{
    u8 res = 0;
    IIC_Start();
    IIC_Send_Byte((AHT10_IIC_ADDR << 1) | 0X01); //发送器件地址+读命令

    if(IIC_Wait_Ack())          //等待应答
    {
        IIC_Stop();
        return 1;
    }

    res = IIC_Read_Byte(0);		//读数据,发送nACK
    IIC_Stop();                 //产生一个停止条件
    return res;
}

/**
 * @brief	读数据
 *
 * @param   data	数据缓存
 * @param   len		读数据大小
 *
 * @return  u8		0,正常,其他,错误代码
 */
u8 AHT10_Read_Data(u8 *data, u8 len)
{
    IIC_Start();
    IIC_Send_Byte((AHT10_IIC_ADDR << 1) | 0x01); //发送器件地址+读命令

    if(IIC_Wait_Ack())          //等待应答
    {
        IIC_Stop();
        return 1;
    }

    for(u8 i = 0; i < len; i++)
    {
        if(i == (len - 1))
            data[i] = IIC_Read_Byte(0);		//读数据,发送nACK

        else
            data[i] = IIC_Read_Byte(1);		//读数据,发送ACK
    }

    IIC_Stop();
    return 0;
}

/**
 * @brief	读取温度数据
 *
 * @param   void
 *
 * @return  float	温度数据（单位：摄氏度）
 */
float AHT10_Read_Temperature(void)
{
    u8 res = 0;
    u8 cmd[2] = {0, 0};
    u8 temp[6];
    float cur_temp;

    res = AHT10_Write_Data(AHT10_GET_DATA, cmd, 2); //发送读取数据命令

    if(res)	return 1;

    res = AHT10_Read_Data(temp, 6);				//读取数据

    if(res)	return 1;

    cur_temp = ((temp[3] & 0xf) << 16 | temp[4] << 8 | temp[5]) * 200.0 / (1 << 20) - 50;

    return cur_temp;
}

/**
 * @brief	读取湿度数据
 *
 * @param   void
 *
 * @return  float	湿度数据（单位：%RH）
 */
float AHT10_Read_Humidity(void)
{
    u8 res = 0;
    u8 cmd[2] = {0, 0};
    u8 humi[6];
    float cur_humi;

    res = AHT10_Write_Data(AHT10_GET_DATA, cmd, 2); //发送读取数据命令

    if(res)	return 1;

    res = AHT10_Read_Data(humi, 6);				//读取数据

    if(res)	return 1;

    cur_humi = ((humi[1]) << 12 | humi[2] << 4 | (humi[3] & 0xF0)) * 100.0 / (1 << 20);

    return cur_humi;
}

/**
 * @brief	ATH10传感器初始化
 *
 * @param   void
 *
 * @return  u8		0,初始化成功，其他,失败
 */
u8 AHT10_Init(void)
{
    u8 res;
    u8 temp[2] = {0, 0};

    IIC_Init();		//初始化IIC接口：注意这里的IIC总线为：SCL-PD6 SDA-PC1

    res = AHT10_Write_Data(AHT10_NORMAL_CMD, temp, 2);

    if(res != 0)	return 1;

    delay_ms(300);

    temp[0] = 0x08;
    temp[1] = 0x00;
    res = AHT10_Write_Data(AHT10_CALIBRATION_CMD, temp, 2);

    if(res != 0)	return 1;

    delay_ms(300);

    return 0;
}


