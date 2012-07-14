#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "Sensor.h"

class Accelerometer {
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
	
	Accelerometer();
	void getRawReading(short& x,short& y,short& z);
public:
	~Accelerometer();
	static Vector<double> getReading();
};

#endif
