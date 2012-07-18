#ifndef COMPASS_H
#define COMPASS_H

#include "Sensor.h"

class Compass {
	static Compass compass;
	
	static const unsigned char CompassAddress;
	static const short sign[3];
	static const double scale[3];
	
	Compass(unsigned char gain = 5);
	void getRawReading(short& x,short& y,short& z);
public:
	~Compass();
	static Vector<double> getReading();
	static void calibrate(unsigned char gain = 5);
};

#endif
