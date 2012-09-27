/**
 * @file   main.cpp
 * @author breadbread1984 <breadbread1984@163.com>
 * @date   Sat Jul 21 15:12:00 2012
 * 
 * @section DESCRIPTION 
 * 
 * openDrone Quadcopter Main function File
 * 
 * @section LICENSE
 * 
 * GPLv3 
 */


#include "wirish.h"
#include "GlobalXYZ.h"
#include "Pressure.h"

#define PWM_PIN 2

void setup()
{
    /* Set up the LED to blink  */
    pinMode(BOARD_LED_PIN, OUTPUT);

    /* Turn on PWM on pin PWM_PIN */
    pinMode(PWM_PIN, PWM);
    pwmWrite(PWM_PIN, 0x8000);

    /* Send a message out USART2  */
    Serial2.begin(9600);
	
	/* pin mode setup related to motor should has to be put here*/
	pinMode(D28,PWM);
	pinMode(D27,PWM);
	pinMode(D11,PWM);
	pinMode(D12,PWM);
	Timer3.setPeriod(2080);
}

void loop()
{
	while(1) {
#if 0
		Vector<double> x,y,z;
		GlobalXYZ::getXYZ(x,y,z);
		SerialUSB.print("X = ("); SerialUSB.print(x(0)); SerialUSB.print(","); SerialUSB.print(x(1)); SerialUSB.print(","); SerialUSB.print(x(2)); SerialUSB.print(") ");
		SerialUSB.print("Y = ("); SerialUSB.print(y(0)); SerialUSB.print(","); SerialUSB.print(y(1)); SerialUSB.print(","); SerialUSB.print(y(2)); SerialUSB.print(") ");
		SerialUSB.print("Z = ("); SerialUSB.print(z(0)); SerialUSB.print(","); SerialUSB.print(z(1)); SerialUSB.print(","); SerialUSB.print(z(2)); SerialUSB.print(")");
#endif
#if 1
		double roll = 0,pitch = 0,yaw = 0;
		GlobalXYZ::getRPY(roll,pitch,yaw);
		roll *= 180 / 3.1415926; pitch *= 180 / 3.1415926; yaw *= 180 / 3.1415926;
		SerialUSB.print("roll = "); SerialUSB.print(roll); SerialUSB.print("\t");
		SerialUSB.print("pitch = "); SerialUSB.print(pitch); SerialUSB.print("\t");
		SerialUSB.print("yaw = "); SerialUSB.print(yaw); SerialUSB.print("\t");
		Vector<double> pressure = Pressure::getReading();
		SerialUSB.print("pressure = "); SerialUSB.print(pressure(0)); SerialUSB.print("pa\t");
		SerialUSB.print("temperature = "); SerialUSB.print(pressure(1) * 0.1); SerialUSB.print("C\t");
		SerialUSB.print("altitude = "); SerialUSB.print(pressure(2)); SerialUSB.print("m\t");
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
#if 0
		Vector<double> retVal = Compass::getReading();
		SerialUSB.print("x = "); SerialUSB.print(retVal(0));
		SerialUSB.print("\ty = "); SerialUSB.print(retVal(1));
		SerialUSB.print("\tz = "); SerialUSB.print(retVal(2));
#endif
#if 0
		Compass::calibrate();
#endif

		SerialUSB.println();
		delay(100);
    }
    
	SerialUSB.println();
}

/* Please Do Not Remove & Edit Following Code */
int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
