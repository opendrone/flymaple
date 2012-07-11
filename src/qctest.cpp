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
#include "i2c.h"
#include "qctest.h"
#include "sensors.h"
#include "motor.h"
#include "Processing.h"

char str[512];

extern volatile unsigned int chan1PPM;  //PPM捕获值寄存器
extern volatile unsigned int chan2PPM;
extern volatile unsigned int chan3PPM;
extern volatile unsigned int chan4PPM;

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
    int16 i = 0;
    int16 temperature = 0;
    int32 pressure = 0;
    int32 centimeters = 0;
    float Heading;

    SerialUSB.println("\n\rSensors Testing...");
    SerialUSB.println();

    puts("Sensors Test begin: \r\n\n");
    while(!SerialUSB.available())
    {
        getAccelerometerData(acc);
        getGyroscopeData(gyro);
        
        temperature = bmp085GetTemperature(bmp085ReadUT());
        pressure = bmp085GetPressure(bmp085ReadUP());
        centimeters = bmp085GetAltitude(); //获得海拔高度，单位厘米

        /********* Acceleometer ********/
        for(i = 0; i < 3; i++)
        {
            SerialUSB.print(acc[i], DEC);
            Serial2.print(acc[i], DEC);
            SerialUSB.print("\t");
            Serial2.print(",");
        }

        SerialUSB.print("|\t");
        /******** Compass Heading *******/
        Heading = compassHeading();
        SerialUSB.print(Heading, DEC);
        SerialUSB.print("|\t");
        Serial2.print(",");
        
        /******** Gyroscope **************/
        for(i = 0; i < 3; i++)
        {  
            SerialUSB.print(gyro[i]);
            Serial2.print(gyro[i]);
            Serial2.print(",");
            SerialUSB.print("\t");
        }

        SerialUSB.print("|\t");

#ifdef PROCESSING
        /********* Processing *************/
        processing(acc, gyro);
#endif
        
        /******** Other Sensors ***********/
        SerialUSB.print(temperature, DEC);
        SerialUSB.print("\t|\t");
        SerialUSB.print(pressure, DEC);
        SerialUSB.print("\t|\t");
        SerialUSB.print(centimeters, DEC);
        SerialUSB.print("\t|\t");

        SerialUSB.println();
        Serial2.println();
        
        delay(50);
        
    }
    
    delay(50);
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
    unsigned long curMills = 0;
    int i = 0;
    char tch;
    int val = 2;

    SerialUSB.println("\n\rMotors Testing...");

    motorStop(); //stop the motor for init
    SerialUSB.println("Motor Stoped.");
    delay(100);
    
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
    delay(100);
    
    SerialUSB.println("Press j for increace Motor, Press K for motor Decrease.");
    
    while(1)
    {
        while(!SerialUSB.available()); //eat waste byte
        
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
        SerialUSB.print("\033[K"); 
        SerialUSB.print("  ");
        SerialUSB.print(val);
        SerialUSB.print("\t>>|");
        
        for(i = 0; i < 40; i++)
        {
            if(i <= val / 25) SerialUSB.print("|");
            else SerialUSB.print("-");
        }
        SerialUSB.print("|<<");
        SerialUSB.print("\r");
    }

    motorStop();
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

    while(!SerialUSB.available())
    {
        SerialUSB.print("PPM Channel 1: ");
        SerialUSB.print(chan1PPM, DEC);
        SerialUSB.print("  ");  
        SerialUSB.print("PPM Channel 2: ");
        SerialUSB.print(chan2PPM, DEC);
        SerialUSB.print("  ");  
        SerialUSB.print("PPM Channel 3: ");
        SerialUSB.print(chan3PPM, DEC);
        SerialUSB.print("  ");  
        SerialUSB.print("PPM Channel 4: ");
        SerialUSB.print(chan4PPM, DEC);
        SerialUSB.println("  ");  
        delay(100);
    }
    
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

