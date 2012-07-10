/**
 * @file   config.h
 * @author tonghuix <tonghuix@tonghuix-1011PX>
 * @date   Thu Apr 12 16:23:14 2012
 * 
 * @brief  Configuration file
 * 
 * 
 */

#ifndef __CONFIG__
#define __CONFIG__

#include "libmaple_types.h"

/* Bootdelay Seconds */
#define BOOTDELAY 5

#define Channel1Pin  D31  //PPM捕获管脚定义 数字口31
#define Channel2Pin  D32
#define Channel3Pin  D33
#define Channel4Pin  D34

/* 陀螺仪误差修正的偏移量 */
const int16 g_offx = 0;
const int16 g_offy = 0;
const int16 g_offz = 0;

/* 加速度传感器误差修正的移量 */
const int16 a_offx = 0;
const int16 a_offy = 0;
const int16 a_offz = 0;

#define HMC_POS_BIAS 1  //正基准值配置量
#define HMC_NEG_BIAS 2  //负基准值配置量


/* Compass Config */
// Local magnetic declination
// I use this web : http://www.ngdc.noaa.gov/geomag-web/#declination
#define MAGNETIC_DECLINATION -6.0    // not used now -> magnetic bearing



#endif
