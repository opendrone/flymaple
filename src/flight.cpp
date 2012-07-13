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
extern volatile unsigned int chan1PPM;  //PPM捕获值寄存器
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
void pitch(int16 val)
{
    /* Motor(2,3) Motor(1,4)
     */
    uint8 i;
    for(i = 1; i <= 4; i++)
    {
        if(val < MAX_RPM && val > IDLE_RPM)
        {
            if (i == 1 | i == 4) motor[i] += val;
            if (i == 2 | i == 3) motor[i] -= val;
        }
        else if(val >= MAX_RPM) motor[i] = MAX_RPM;
        else motor[i] = IDLE_RPM;
        motor[i] = motor[i];
    }
        
    motorCustom(motor[1], motor[2], motor[3], motor[4]);
    
}

void roll(int16 val)
{
    /* Motor(1,2) Motor(3,4)
     */

    motor[1] += val;
    motor[2] += val;
    motor[3] -= val;
    motor[4] -= val;
    motorCustom(motor[1], motor[2], motor[3], motor[4]);
}

void yaw(int16 val)
{
     /* Motor(1,3) Motor(2,4)
     */
    motor[1] += val;
    motor[3] += val;
    motor[2] -= val;
    motor[4] -= val;
    motorCustom(motor[1], motor[2], motor[3], motor[4]);
}

void qcThrottle(int16 val)
{
    uint8 i;

    for(i = 1; i <= 4; i++)
    {
        if(val < MAX_RPM && val > 0) motor[i] = val;
        else if(val >= MAX_RPM) motor[i] = MAX_RPM;
        else motor[i] = 0;
    }

    motorCustom(motor[1],
                motor[2],
                motor[3],
                motor[4]);
}


void textFlightMode()
{
    int16  val = 0, i, j;
    
    while(1)
    {
        SerialUSB.print(motor[1]);
        SerialUSB.print("\t");
        SerialUSB.print(motor[2]);
        SerialUSB.print("\t");
        SerialUSB.print(motor[3]);
        SerialUSB.print("\t");
        SerialUSB.println(motor[4]);
        
        while(SerialUSB.available()); //eat waste byte
        
        switch(SerialUSB.read())
        {
            case '+':
               if(val < MAX_RPM) { qcThrottle(val); val += 50; }
               else {val = MAX_RPM; qcThrottle(MAX_RPM); }
               break; 
            case '-':
                if(val > 0) { qcThrottle(val); val -= 50; }
                else { val = 0; qcThrottle(0); }
                break; 
            case '7':
                if(val < MAX_RPM) { qcThrottle(val); val += 10; }
                else { val = MAX_RPM; qcThrottle(MAX_RPM); }
                break; 
            case '1':
                if(val > 0) { qcThrottle(val); val -= 10;}
                else { val = 0; qcThrottle(0); }
                break; 
            case '8':
                 pitch( 50 );
                break;
            case '2':
                 pitch(-50);
            case '4':
                 roll(50);
            case '6':
                roll(-50);
            case '0':
                yaw(50);
            case '.':
                yaw(50);

        }
    }
}

/** 
 * PPM Flight Mode
 * 
 */
void ppmFlightMode()
{
    //TODO
}



