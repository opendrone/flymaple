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
#include "GlobalXYZ.h"

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

	GlobalXYZ xyz;
	double roll,pitch,yaw;
    
    while(!SerialUSB.available())
    {
		xyz.getRPY(roll,pitch,yaw);
		SerialUSB.print("roll = "); SerialUSB.print(roll * 180 / 3.1415926);
		SerialUSB.print("\tpitch = "); SerialUSB.print(pitch * 180 / 3.1415926);
		SerialUSB.print("\tyaw = "); SerialUSB.print(yaw * 180 / 3.1415926); SerialUSB.println();
		delay(50);
	}
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
    int i = 0, j = 0;
    char tch;
    int val = 2;
    
    uint16 motor[5] = {0};

    SerialUSB.println("\n\rMotors Testing...");

    motorStop(); //stop the motor for init
    SerialUSB.println("Motor Stoped.\r\n");
    delay(100);
    
    SerialUSB.println("## NOTE: Press 1 ~ 4 to select motor, or Press 'a' for select All motors.");
    SerialUSB.println("##       Press 'j' for increace Motor, Press 'k' for motor Decrease.");
    
    puts("\r\n");
    
    while(1)
    {
        puts("M1: ");
        displayThrottle(motor[1]);
        puts("\r\n");
        puts("M2: ");
        displayThrottle(motor[2]);
        puts("\r\n");
        puts("M3: ");
        displayThrottle(motor[3]);
        puts("\r\n");
        puts("M4: ");
        displayThrottle(motor[4]);
        puts("\r");
        puts("\033[A");puts("\033[A");puts("\033[A");//puts("\033[A");
        
        while(!SerialUSB.available()); //eat waste byte
        
        tch = SerialUSB.read();

        switch(tch)
        {
            case '1': j = 1;  break; continue;
            case '2': j = 2;  break; continue;
            case '3': j = 3;  break; continue;
            case '4': j = 4;  break; continue;
            case 'a': j = 0; break; continue;
            case 'j': val += 50;break;
            case 'k': val -= 50;break;
            case 'r': return;
            default: motorStop(); val = 0; break;

        }

        if(val > 999) val = 999;
        else if(val < 0) val = 2;

        if(j != 0) motor[j] = val;
        else for(i = 0;i <= 4; i++) motor[i] = val;

        /*
        for(i = 0; i < 5 ; i++)
        {  
            SerialUSB.print(motor[i]);
            SerialUSB.print("\t");
        }
        SerialUSB.println(val);
        puts("\r\n");
        */

        motorCustom(motor[1], motor[2], motor[3], motor[4]);
        
    }

    motorStop();
    return;
}

/** 
 * Display Thruttle
 * 
 */
void displayThrottle(int val)
{
    int i = 0;
    SerialUSB.print("\t");
    SerialUSB.print("\033[K"); 
    SerialUSB.print(val);
    SerialUSB.print("\t>>|");
    
    for(i = 0; i < 40; i++)
    {
        if(i <= val / 25) SerialUSB.print("|");
        else SerialUSB.print("-");
    }
    SerialUSB.print("|<<");
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

    do
    {
        puts("CH1: ");
        displayThrottle(chan1PPM - 1000);
        puts("\r\n");
        puts("CH2: ");
        displayThrottle(chan2PPM - 1000);
        puts("\r\n");
        puts("CH3: ");
        displayThrottle(chan3PPM - 1000);
        puts("\r\n");
        puts("CH4: ");
        displayThrottle(chan4PPM - 1000);
        puts("\r");
        
                
         puts("\033[A");puts("\033[A");puts("\033[A");//puts("\033[A");
         
    }while((chan1PPM & chan2PPM & chan3PPM & chan4PPM) != 0);
    
    while(!SerialUSB.available()) SerialUSB.print("PPM Error, Press any key to quit.\r");
    
    
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

