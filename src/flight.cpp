/**
 * @file   flight.cpp
 * @author tonghuix <tonghuix@tonghuix-Studio-1450>
 * @date   Sat Jul 14 02:35:37 2012
 * 
 * @brief  Flight Mode Main Source Code
 * @motors -
 
 motor[1] %   ^   % motor[4]
           \  |  /
            \   /
             \ /
              #
             / \
            /   \
           /     \
 motor[2] %       % motor[3]
 * 
 */


#include "sensors.h"
#include "flight.h"
#include "wirish.h"
#include "motor.h"
#include "qctest.h"
#include "config.h"
#include "misc.h"

int16 motor[5];
unsigned long preMillis = 0;
extern volatile unsigned int chan1PPM;  //PPMs' value store
extern volatile unsigned int chan2PPM;
extern volatile unsigned int chan3PPM;
extern volatile unsigned int chan4PPM;


void flightMode()
{
    int8 i = 1;
    unsigned long interval = 1000;
    unsigned long currentMillis ;

    preMillis = millis();
    SerialUSB.println(">> Flight Mode <<");
    SerialUSB.print("\n\r Plugin PPM controller -  ");
    
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
            i--;
        }
    }
    if(i <= 0 )
    {
        SerialUSB.println("\n\r PPM Check Failed!");
        SerialUSB.println("\n\r Entering [Text-based Flight Mode]...");
        textFlightMode();
    }
    else
    {
        SerialUSB.println("\n\r Entering [PPM Flight Mode] ...");
        ppmFlightMode();
    }
    
    
    //TODO
    
    return;
}


/** 
 * Quadcopter Flight Control Functions
 * @Note: http://hi.baidu.com/zizio/item/7fc3b37316fe0a43ee1e53af
 * @param val

 */

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
void textFlightMode()
{
    char control;
//TODO
}

/** 
 * PPM Flight Mode
 * 
 */
void ppmFlightMode()
{
    //TODO
}

/** 
 * 
 * 
 * 
 * @return 
 */
int readSerialUSB()
{
//TODO    
}

int readSerial()
{
    //TODO
}
