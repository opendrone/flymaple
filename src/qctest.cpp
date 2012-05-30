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
            SerialUSB.print("\t");
        }

        for(j = 0; j < 4; j++)
        {
            SerialUSB.print(gyro[i]);
            SerialUSB.print("\t");
        }

        delay(100);
        
        SerialUSB.println();
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
        
        if(val > 1 && val < 999){
            if(tch = 'j')  val = val + 100;
            if(tch = 'k')  val = val - 100;
            motorCustom(val, val, val, val);
            SerialUSB.println(val);
        }
        else
            motorStop();
    }
    

    
    
        
        /*p
        SerialUSB.println("Motor Stoped.");
        curMills = millis();
        interal = 1000;
        if(curMills - pMills > interal)
        {
            motorStop();
        }

        SerialUSB.println("Motor Rolling Half...");
        pMills = curMills;
        curMills = millis();
        if(curMills - pMills > 5000)
        {
            motorHalf();
        }

        SerialUSB.println("Motor Customes 200,300,500,800....");
        pMills = curMills;
        curMills = millis();
        if(curMills - pMills > 8000)
        {
           
        }
        */

    
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

