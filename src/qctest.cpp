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

    while(1)
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
    


            //sprintf(str, "%d, %d, %d, %d, %d, %d, %d", acc[0], acc[1], acc[2], gyro[0], gyro[1], gyro[2], gyro[3]);  

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
    SerialUSB.println("\n\rMotors Testing...");
    //Put Motors Test Code Here
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

