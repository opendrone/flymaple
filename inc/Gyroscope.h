#ifndef GYROSCOPE_H
#define GYROSCOPE_H

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
	
	Gyroscope();
	void getRawReading(short& x,short& y,short& z);
public:
	~Gyroscope();
	static Vector<double> getReading();
};

#endif
