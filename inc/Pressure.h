#ifndef PRESSURE_H
#define PRESSURE_H

/**
 * @file	Pressure.h
 * @author	breadbread1984 <breadbread1984@163.com>
 * @date	Fri Sep 7 10:01:00 2012
 * 
 * @brief	The static class for manipulating the pressure sensor.
 * 
 * @copyright GPLv3
 */

#include "Sensor.h"

class Pressure : public Sensor {
	using Sensor::read;
	static Pressure pressure;
	
	static const unsigned char PressureAddress;
	static const unsigned char OSS;
	static const unsigned char BMP085_CAL_AC[6];
	static const unsigned char BMP085_CAL_B[2];
	static const unsigned char BMP085_CAL_MB;
	static const unsigned char BMP085_CAL_MC;
	static const unsigned char BMP085_CAL_MD;
	static const unsigned char BMP085_CONTROL;
	static const unsigned char BMP085_CONTROL_OUTPUT;
	static const unsigned char READ_TEMPERATURE;
	static const unsigned char READ_PRESSURE;
	static const int MSLP;
	static const int Altitude_cm_Offset;
	
	static short ac[6],b[2],mb,mc,md;
	static int b5;
  
	/**
	 * Constructor initializing the pressure sensor.
	 * To do the initialization for only once. The constructor is hiden from developer.
	 * The only one Pressure object is a static one created automatically.
	 */
	Pressure();
	short read(unsigned char addr);
	void getRawReading(unsigned int& up,unsigned short& ut);
	int rawToPressure(unsigned int up);
	short rawToTemperature(unsigned short ut);
	double pressureToAltitude(int p);
public:
	/**
	 * Destructor
	 */
	~Pressure();
	/**
	 * Get the pressure, temperature, altitude (in centimeter) of the quadcopter.
	 * 
	 * @return the elements in the returned vector are pressure (of int type in Pa), temperature (of short type in 0.1 degree C) and altitude (of double type in meters) in sequence.
	 */
	static Vector<double> getReading();
};

#endif
