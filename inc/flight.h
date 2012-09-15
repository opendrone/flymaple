/**
 * @file   flight.h
 * @author tonghuix <tonghuix@tonghuix-Studio-1450>
 * @date   Thu Jul 12 02:38:52 2012
 * 
 * @brief  Flight mode header file
 * 
 * 
 */

#ifndef __FLIGHT__
#define __FLIGHT__

#include "libmaple_types.h"

/** 
 * Control Struct
 * 
 */
typedef struct
{
    int16 thr;
    int16 roll;
    int16 yaw;
    int16 pitch;
} QuadAttitude;

void flightMode();
void textControl();
void ppmControl();



#endif
