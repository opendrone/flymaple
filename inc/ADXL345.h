/**
 * @file   ADXL345.h
 * @author tonghuix <tonghuix@tonghuix-1011PX>
 * @date   Thu Apr 12 16:27:32 2012
 * 
 * @brief  Accelerameter Header File
 * 
 * 
 */

#ifndef __ADXL345__
#define __ADXL345__


#include "libmaple_types.h"
#include "i2c.h"

// 加速度传感器 ADXL345
#define ACC (0x53)    //定义ADXL345地址
#define A_TO_READ (6) //读取每次占用的字节数 (每个坐标轴占两个字节)
#define XL345_DEVID   0xE5
// ADXL345控制寄存器
#define ADXLREG_BW_RATE      0x2C
#define ADXLREG_POWER_CTL    0x2D
#define ADXLREG_DATA_FORMAT  0x31
#define ADXLREG_FIFO_CTL     0x38
#define ADXLREG_BW_RATE      0x2C
#define ADXLREG_TAP_AXES     0x2A
#define ADXLREG_DUR          0x21

//ADXL345数据寄存器
#define ADXLREG_DEVID        0x00
#define ADXLREG_DATAX0       0x32
#define ADXLREG_DATAX1       0x33
#define ADXLREG_DATAY0       0x34
#define ADXLREG_DATAY1       0x35
#define ADXLREG_DATAZ0       0x36
#define ADXLREG_DATAZ1       0x37


void initAcc();

void getAccelerometerData(int16 * result);


#endif
