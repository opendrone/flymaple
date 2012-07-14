#ifndef COMPASS_H
#define COMPASS_H

#include "Sensor.h"

class Compass {
	static Compass compass;
	
	static const unsigned char CompassAddress;
	static const short sign[3];
	
	Compass();
	void getRawReading(short& x,short& y,short& z);
public:
	~Compass();
	static Vector<double> getReading();
};

#endif
