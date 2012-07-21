#ifndef GYROSCOPE_H
#define GYROSCOPE_H

/**
 * @file   Gyroscope.h
 * @author breadbread1984 <breadbread1984@163.com>
 * @date   Sat Jul 21 15:12:00 2012
 * 
 * @section DESCRIPTION 
 * 
 * The static class for manipulating the gyroscope. 
 * 
 * @section LICENSE
 * 
 * GPLv3 
 */

#include "Sensor.h"

class Gyroscope {
	static Gyroscope gyroscope;
	
	static const unsigned char GyroAddress;
	static const unsigned char PWR_MGM;
	static const unsigned char DLPF_FS;
	static const unsigned char INT_CFG;
	static const unsigned char SMPLRT_DIV;
	static const unsigned char GYROX_H;
	static const short sign[3];
	static short offset[3];
	//ITG3205 specification 上面定义的精度
	//(http://www.dzsc.com/uploadfile/company/772705/2011821231617930.pdf)
	static const float sensitivity;
	
	/**
	 * Constructor initializing the gyroscope.
	 * To do the initialization for only once, the constructor is hide from developer.
	 * The only one Gyroscope object is a static one created automatically.
	 */
	Gyroscope();
	/**
	 * Get raw data from the gyroscope.
	 */
	void getRawReading(short& x,short& y,short& z);
public:
	/**
	 * Desctructor.
	 */ 
	~Gyroscope();
	/**
	 * Get the angular speed from the gyroscope.
	 * 
	 * @return the angular speeds (rad/s) around the three axis of the body frame.
	 */
	static Vector<double> getReading();
};

#endif
