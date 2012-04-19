/**
 * @file   ITG3205.h
 * @author tonghuix <tonghuix@tonghuix-1011PX>
 * @date   Thu Apr 12 16:21:55 2012
 * 
 * @brief  Gyro Header Symbols
 * 
 * 
 */

#ifndef __ITG345__
#define __ITG345__

#include "libmaple_types.h"

// 陀螺仪 ITG3205 
#define GYRO 0x68 // 定义传感器地址,将AD0连接到GND口，传感器地址为二进制数11101000 (请参考你接口板的原理图)
#define G_SMPLRT_DIV 0x15  //采样率寄存器地址
#define G_DLPF_FS 0x16     //检测灵敏度及其低通滤波器设置
#define G_INT_CFG 0x17     //配置寄存器
#define G_PWR_MGM 0x3E     //传感器数据寄存器起始地址，包括温度及其3轴角速度

#define G_TO_READ 8 // x,y,z 每个轴2 bytes

void initGyro();

void getGyroscopeData(int16 * result);


#endif
