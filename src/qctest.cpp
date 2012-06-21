/**
 * @file   test.cpp
 * @author tonghuix <tonghuix@gmail.com>
 * @date   Wed Apr 11 22:28:16 2012
 * @license GPLv3
 *
 * @brief  For Founcitons and Feathers Test
 * 
 * @note   Don't User these founctions for Flight Mode
 * 
 */

#include "misc.h"
#include "qctest.h"
#include "ADXL345.h"
#include "ITG3205.h"
#include "BMP085.h"
#include "motor.h"

char str[512];

/** 
 * Sensors Test
 *
 * @input   None
 * @output  None
 */
void sensorsTest()
{
    int16 acc[3];
    int16 gyro[4];
    int16 i = 0, j = 0;
    
    SerialUSB.println("\n\rSensors Testing...");
    //Put Sensors Test Codes Here
    SerialUSB.println();
    SerialUSB.println("(a) Accelerometer & Gyroscope Test");
    SerialUSB.println("(p) Pressure & Temperature Test");
    SerialUSB.println("(c) Compass Test");

   puts("Sensors Test begin: \r\n\n");

   while(!SerialUSB.available())
    {
         getAccelerometerData(acc);
         getGyroscopeData(gyro);
        
        for(i = 0; i < 3; i++)
        {
            SerialUSB.print(acc[i]);
            Serial2.print(acc[i]);
            SerialUSB.print("\t");
            Serial2.print("|");
        }

        for(j = 0; j < 4; j++)
        {
            SerialUSB.print(gyro[i]);
            Serial2.print(gyro[i]);
            Serial2.print("|");
            SerialUSB.print("\t");
        }

        delay(100);
        
        SerialUSB.println();
        Serial2.print(";");
    }
    
    delay(100);
  //延时50毫秒
    return;
}

/** 
 * Motors Test
 *
 * @input  None
 * @output None
 */
void motorsTest()
{
    unsigned long pMills = millis();
    int interal = 1000;
    unsigned long curMills = 0;

    char tch;
    int val = 2;

    SerialUSB.println("\n\rMotors Testing...");

    motorStop(); //stop the motor for init
    SerialUSB.println("Motor Stoped.");
    
    while(!SerialUSB.available())
    {
        curMills = millis();
        switch(curMills - pMills)
        {
        case 1000: {SerialUSB.println("Motor Rolling Half..."); motorHalf();break;}
        case 6000: {SerialUSB.println("Motor Customs...");  motorCustom(200, 300, 500, 800); break;}
        case 14000: pMills = curMills; break;
            default: break;
        }
    }

    motorStop();
    delay(1000);
    
    SerialUSB.println("Press j for increace Motor, press K for motor Decrease.");
    
    while(1)
    {
        tch = SerialUSB.read();

        switch(tch)
        {
            case 'j': val = val + 50;break;
            case 'k': val = val - 50;break;
            case 'r': return;
            default: motorStop(); val = 0; break;

        }

        if(val > 1 && val <= 999){
            motorCustom(val, val, val, val);
            delay(100);
        }
        else if(val > 999)
        {
            motorCustom(999, 999, 999, 999);
            val = 999;
        }
        
        else if(val < 0)
        {
            motorCustom(2, 2, 2, 2);
            val = 2;
        }
        SerialUSB.println(val);
    }
        
    return;
}

/** 
 * Remote Control Test
 *
 * @input  None
 * @output None
 */
void remoteTest()
{
    SerialUSB.println("\n\rRemote Control Testing...");
    //Put Remote Control code Here
    return;
}

/** 
 * Quadcopter Take Off
 *
 * @input   None
 * @output  None
 * @note   Default Take off on 1 metre high
 */
void qcTakeOff()
{
    SerialUSB.println("Default Take off on 1m..");
    SerialUSB.println("Please be seated and fasten your seat belt.");
    //Put Take off code Here
    return;
}


/** 
 * Quadcopter Landing
 *
 * @input  None
 * @output None
 */
void qcLanding()
{
    SerialUSB.println("Landing now!");
    SerialUSB.println("Please be seated and fasten your seat belt.");
    //Put landing code Here
    return;
}

