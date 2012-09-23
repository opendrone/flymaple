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

#define COE 0.12

int16 motor[5];
unsigned long preMillis = 0;
extern volatile unsigned int chan1PPM;  //PPMs' value store
extern volatile unsigned int chan2PPM;
extern volatile unsigned int chan3PPM;
extern volatile unsigned int chan4PPM;

QuadAttitude ctrlVal;
QuadAttitude  adjVal;

void flightMode()
{
    int8 i = 1;
    /* Delay timer */
    unsigned long interval = 5000; //1000 = 1 second, 4000 = 4 second
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
#ifdef TOPLEVEL

            Serial2.println('REQ');
    
#endif
            toggleLED();
            motorStop();
            i--;
        }
    }
    if(i <= 0 )
        SerialUSB.println("\n\r PPM Check Failed!");

    /* Set all channal to null value to safty care */
        chan1PPM = chan2PPM = chan3PPM = chan4PPM = 0;    
    
    while(1)
    {
        
        ppmControl();
//        SerialUSB.println("Ready to get control charactor: ");
        textControl();
        
#ifndef PID
        adjVal.thr = ctrlVal.thr;
        adjVal.roll= ctrlVal.roll * COE;
        adjVal.yaw = ctrlVal.yaw * COE;
        adjVal.pitch = ctrlVal.pitch * COE;
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
        
#if 1
        SerialUSB.print("THR: "); SerialUSB.print(ctrlVal.thr); SerialUSB.println("    ");
        SerialUSB.print("ROLL: "); SerialUSB.print(ctrlVal.roll); SerialUSB.println("    ");
        SerialUSB.print("PITCH: "); SerialUSB.print(ctrlVal.pitch); SerialUSB.println("    ");
        SerialUSB.print("YAW:"); SerialUSB.print(ctrlVal.yaw); SerialUSB.println("    ");
        SerialUSB.println();
        SerialUSB.print("M1: "); SerialUSB.println(motor[1]);
        SerialUSB.print("M2: "); SerialUSB.println(motor[2]);
        SerialUSB.print("M3: "); SerialUSB.println(motor[3]);
        SerialUSB.print("M4: "); SerialUSB.println(motor[4]);
        for(int i = 9; i > 0; i--) puts("\033[A");
#endif
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
 * X or x - Pitch Backward
 * H or h - Hold Positon
 * S - All motors stop
 */
void textControl()
{
    char ctlCh = 0 ;
    while(SerialUSB.available()){
        ctlCh = SerialUSB.read();
        // SerialUSB.print(ctlCh);  //echo input

        switch(ctlCh)
        {
        case 'J': // Throttle Up
        case 'j': ctrlVal.thr + 50 > MAX_RPM ? ctrlVal.thr = MAX_RPM : ctrlVal.thr += 50;
            toggleLED();
            break; break;
        case 'K': 
        case 'k': ctrlVal.thr - 50 < 0 ? ctrlVal.thr = 0 :ctrlVal.thr -= 50;
            toggleLED();
            break; break;
        case 'a': 
        case 'A': ctrlVal.roll - 20 < -2000 ? ctrlVal.roll = -2000 : ctrlVal.roll -= 20;
            toggleLED();
            break; break;
        case 'd':
        case 'D': ctrlVal.roll + 20 > 2000  ? ctrlVal.roll = 2000 : ctrlVal.roll += 20;
            toggleLED();
            break; break;
        case 'w':
        case 'W': ctrlVal.pitch + 20 > 2000 ? ctrlVal.pitch = 2000 : ctrlVal.pitch += 20;
            toggleLED();
            break; break;
        case 'x':
        case 'X': ctrlVal.pitch - 20 < -2000 ? ctrlVal.pitch = -2000 : ctrlVal.pitch -= 20;
            toggleLED();
            break; break;
        case 'z':
        case 'Z': ctrlVal.yaw + 50 > 2000 ? ctrlVal.yaw = 2000 : ctrlVal.yaw += 50;
            toggleLED() ;
            break; break;
        case 'c':
        case 'C': ctrlVal.yaw - 50 < -2000 ? ctrlVal.yaw = -2000 : ctrlVal.yaw -= 50;
            toggleLED();
            break; break;
        case 's':
        case 'S':
            ctrlVal.roll = 0;
            ctrlVal.pitch = 0;
            ctrlVal.yaw = 0;
            break; break;
#ifdef TOPLEVEL
        case 'b':
        case 'B':
            parements();
            break;break;
#endif
        default: break; break;
        }
    }
}


/**
 * Centeral about 500
 * (D31) CH1 - Yaw: 930 <-> 100
 * (D32) CH2 - Pitch: pitch forward 100, backward 900
 * (D33) CH3 - Thruttle 0 <-> 930
 * (D34) CH4 - Roll 100 <-> 930
 */
/** 
 * PPM Flight Mode
 * 
 */
void ppmControl()
{
    if(chan1PPM && chan2PPM && chan3PPM && chan4PPM ){
        ctrlVal.thr = chan3PPM - 1000;
        ctrlVal.roll = chan4PPM - 1500;
        ctrlVal.pitch = -(chan2PPM - 1500);
        ctrlVal.yaw = chan1PPM - 1500;
    }
    //TODO
    return;
}

