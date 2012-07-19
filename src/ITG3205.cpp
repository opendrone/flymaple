/**
 * @file   ITG3205.cpp
 * @author tonghuix <tonghuix@tonghuix-Studio-1450>
 * @date   Fri Apr 13 18:41:00 2012
 * 
 * @brief  Gyroscope Functions
 * 
 * 
 */

#include "wirish.h"
#include "ITG3205.h"
#include "config.h"
#include "misc.h"

static short g_offset[] = {0,0,0};

//初始化陀螺仪
void initGyro()
{
  /*****************************************
   * ITG 3200
   * 电源管理设定：
   * 时钟选择 =内部振荡器
   * 无复位, 无睡眠模式
   * 无待机模式
   * 采样率 = 125Hz
   * 参数为+ / - 2000度/秒
   * 低通滤波器=5HZ
   * 没有中断
   ******************************************/
    writeTo(GYRO, G_PWR_MGM, 0x00); //00
    writeTo(GYRO, G_SMPLRT_DIV, 0x07); //07 EB, 50, 80, 7F, DE, 23, 20, FF
    writeTo(GYRO, G_DLPF_FS, 0x1E); //1E +/- 2000 dgrs/sec, 1KHz, 1E, 19
    writeTo(GYRO, G_INT_CFG, 0x00);
	
	float accumulator[] = {0,0,0};
	for(int i = 0 ; i < 100 ; i++) {
		short gyro[4];
		getGyroscopeData(gyro);
		accumulator[0] += gyro[0];
		accumulator[1] += gyro[1];
		accumulator[2] += gyro[2];
	}
	for(int i = 0 ; i < 3 ; i++) g_offset[i] = accumulator[i] / 100;
}


void getGyroscopeData(int16 * result)
{
    /**************************************
     * 陀螺仪ITG- 3200的I2C
     * 寄存器：
     * temp MSB = 1B, temp LSB = 1C
     * x axis MSB = 1D, x axis LSB = 1E
     * y axis MSB = 1F, y axis LSB = 20
     * z axis MSB = 21, z axis LSB = 22
     *************************************/

    uint8 regAddress = 0x1B;
    int16 temp, x, y, z;
    uint8 buff[G_TO_READ];

    readFrom(GYRO, regAddress, G_TO_READ, buff); //读取陀螺仪ITG3200的数据

    result[0] = (((int16)buff[2] << 8) | buff[3]) + g_offset[0];
    result[1] = (((int16)buff[4] << 8) | buff[5]) + g_offset[1];
    result[2] = (((int16)buff[6] << 8) | buff[7]) + g_offset[2];
    result[3] = ((int16)buff[0] << 8) | buff[1]; // 温度
}
