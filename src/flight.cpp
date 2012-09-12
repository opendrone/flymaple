/**
 * @file   flight.cpp
 * @author tonghuix <tonghuix@tonghuix-Studio-1450>
 * @date   Sat Jul 14 02:35:37 2012
 * 
 * @brief  Flight Mode Main Source Code
 * @motors -
 
 motor[1] %   ^   % motor[2]
           \  |  /
            \   /
             \ /
              #
             / \
            /   \
           /     \
 motor[3] %       % motor[4]
 * 
 */

/** 
 * Quadcopter Flight Control Functions
 * @Note: http://hi.baidu.com/zizio/item/7fc3b37316fe0a43ee1e53af
 */

#include "sensors.h"
#include "flight.h"
#include "wirish.h"
#include "motor.h"
#include "qctest.h"
#include "config.h"
#include "misc.h"
#include "GlobalXYZ.h"

int16 motor[5];
unsigned long preMillis = 0;
extern volatile unsigned int chan1PPM;  //PPMs' value store
extern volatile unsigned int chan2PPM;
extern volatile unsigned int chan3PPM;
extern volatile unsigned int chan4PPM;
val ctrlVal;
val adjVal;


void flightMode()
{
    int8 i = 1;
    unsigned long interval = 1000;
    unsigned long currentMillis ;

    preMillis = millis();
    SerialUSB.println(">> Flight Mode <<");
    SerialUSB.print("\n\r Plugin PPM controller -  ");

    motorStop(); //shutdown all motors
    
    while(!(chan1PPM & chan2PPM & chan3PPM & chan4PPM) && i >= 0)
    {
        currentMillis = millis();
        if(currentMillis - preMillis > interval)
        {    
            // save the last time you blinked the LED 
            preMillis = currentMillis;
            SerialUSB.print("\b");  
            SerialUSB.print(i, DEC);
            toggleLED();
            motorStop();
            i--;
        }
    }
    if(i <= 0 ) SerialUSB.println("\n\r PPM Check Failed!");

    while(1)
    {
        ppmControl();
        textControl();
        
#ifndef PID
        adjVal.thr = ctrlVal.thr;
        adjVal.roll= ctrlVal.roll;
        adjVal.yaw = ctrlVal.yaw;
        adjVal.pitch = ctrlVal.pitch;
#endif
        
#ifdef PID
        adjVal.thr = pidAdj(ctrlVal.thr);
        adjVal.roll= pidAdj(ctrlVal.roll);
        adjVal.yaw = pidAdj(ctrlVal.yaw);
        adjVal.pitch = pidAdj(ctrlVal.pitch);
#endif
    
        motor[1] = motorLimit(adjVal.thr + adjVal.roll - adjVal.pitch + adjVal.yaw);
        motor[2] = motorLimit(adjVal.thr - adjVal.roll - adjVal.pitch - adjVal.yaw);
        motor[3] = motorLimit(adjVal.thr + adjVal.roll + adjVal.pitch - adjVal.yaw);
        motor[4] = motorLimit(adjVal.thr - adjVal.roll + adjVal.pitch + adjVal.yaw);
        
        motorCustom(motor[1], motor[2], motor[3], motor[4]);
    //TODO
    }
    
    return;
}



/** 
 * Text-based Control 
 * Any Test-based control is here, like Xbee, BlueTooth etc.
 * It will send some certain charactor to control our qc
 * J or j - Throttle Up
 * K or k - Throttle Down
 * A or a - Roll Left
 * D or d - Roll Right
 * W or w - Pitch Forward
 * S or s - Pitch Backward
 * H or h - Hold Positon
 */
void textControl()
{
    uint8 ctlCh  ;
    while(!Serial2.available())
        ctlCh = Serial2.read();
    while(!SerialUSB.available())
        ctlCh = SerialUSB.read();
    
    switch(ctlCh)
    {
    case 'J':
    case 'j': ctrlVal.thr += 20; break;
    case 'K':
    case 'k': ctrlVal.thr -= 20; break;
    case 'a':
    case 'A': ctrlVal.roll += 20; break;
    case 'd':
    case 'D': ctrlVal.roll -= 20; break;
    case 'w':
    case 'W': ctrlVal.pitch -= 20; break;
    case 's':
    case 'S': ctrlVal.pitch += 20; break;
    }
    
}

/** 
 * PPM Flight Mode
 * 
 */
void ppmControl()
{
    //TODO
}

