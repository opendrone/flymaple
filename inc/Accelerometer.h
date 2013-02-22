#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

/**
 * @file   Accelerometer.h
 * @author breadbread1984 <breadbread1984@163.com>
 * @date   Sat Jul 21 15:12:00 2012
 * 
 * @brief	The static class for manipulating the accelerometer. 
 * 
 * @copyright GPLv3 
 */

#include "Sensor.h"

class Accelerometer : public Sensor {
	static Accelerometer accelerometer;
	
	static const unsigned char AccelAddress;
	static const unsigned char XL345_DEVID;
	static const unsigned char ADXLREG_BW_RATE;
	static const unsigned char ADXLREG_POWER_CTL;
	static const unsigned char ADXLREG_DATA_FORMAT;
	static const unsigned char ADXLREG_DEVID;
	static const unsigned char ADXLREG_DATAX0;
	static const unsigned short GRAVITY;
	static const short sign[3];
	static short offset[3];
	//ADXL345 specification
	static const float sensitivity;
	
	/**
	 * Constructor initializing the accelerometer.
	 * To do the initialization for only once, the constructor is hide from developer.
	 * The only one Accelerometer object is a static one created automatically.
	 */
	Accelerometer();
	void getRawReading(short& x,short& y,short& z);
public:
	/**
	 * Destructor.
	 */
	~Accelerometer();
	/**
	 * Get the accelerations on three axes of the body frame.
	 * 
	 * @return the acdelerations on three axes (g)
	 */
	static Vector<double> getReading();
};

#endif
