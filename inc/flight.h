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
 * Motor Struct
 * 
 */

void flightMode();
void pitch(int16 val);
void roll(int16 val);
void yaw(int16 val);
void qcThrottle(int16 val);
void textFlightMode();
void ppmFlightMode();

#endif
