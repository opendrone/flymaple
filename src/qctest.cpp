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
#include "Accelerometer.h"
#include "Compass.h"
#include "Gyroscope.h"
#include "GlobalXYZ.h"

char str[512];

/** 
 * Sensors Test
 *
 * @input   None
 * @output  None
 */
void sensorsTest()
{    
	SerialUSB.println("\n\rSensors Testing...");
    //Put Sensors Test Codes Here

	while(1) {
#if 0
		double roll = 0,pitch = 0,yaw = 0;
		GlobalXYZ::getRPY(roll,pitch,yaw);
		roll *= 180 / 3.1415926; pitch *= 180 / 3.1415926; yaw *= 180 / 3.1415926;
		SerialUSB.print("roll = "); SerialUSB.print(roll); SerialUSB.print("\t");
		SerialUSB.print("pitch = "); SerialUSB.print(pitch); SerialUSB.print("\t");
		SerialUSB.print("yaw = "); SerialUSB.print(yaw); SerialUSB.print("\t");
#endif
#if 0
		Vector<double> retVal = Accelerometer::getReading();
		SerialUSB.print("x = "); SerialUSB.print(retVal(0)); 
		SerialUSB.print("\ty = "); SerialUSB.print(retVal(1)); 
		SerialUSB.print("\tz = "); SerialUSB.print(retVal(2));
#endif
#if 0
		Vector<double> retVal = Gyroscope::getReading();
		SerialUSB.print("x = "); SerialUSB.print(retVal(0)); 
		SerialUSB.print("\ty = "); SerialUSB.print(retVal(1)); 
		SerialUSB.print("\tz = "); SerialUSB.print(retVal(2));		
#endif
#if 1
		Vector<double> retVal = Compass::getReading();
		SerialUSB.print("x = "); SerialUSB.print(retVal(0));
		SerialUSB.print("\ty = "); SerialUSB.print(retVal(1));
		SerialUSB.print("\tz = "); SerialUSB.print(retVal(2));
#endif

		SerialUSB.println();
		delay(100);
    }
    
	SerialUSB.println();

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

