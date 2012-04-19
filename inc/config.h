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

/* 陀螺仪误差修正的偏移量 */
const int16 g_offx = 0;
const int16 g_offy = 0;
const int16 g_offz = 0;

/* 加速度传感器误差修正的移量 */
const int16 a_offx = 0;
const int16 a_offy = 0;
const int16 a_offz = 0;


#endif
